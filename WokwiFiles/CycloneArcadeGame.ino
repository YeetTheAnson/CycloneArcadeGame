#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define NEOPIXEL_PIN 5
#define NUM_LEDS 60
#define BUTTON_PIN 2
#define POT_PIN 4
#define OLED_RESET -1
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_NeoPixel strip(NUM_LEDS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

volatile bool buttonPressed = false;
int currentLed = 0;
bool gameOver = false;
bool masterMode = false;
bool speedMenu = true;
int gameSpeed = 10;
int riggedPercentage = 0;
unsigned long lastUpdateTime = 0;
bool isCurrentSessionRigged = false;

void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.show();
  
  Wire.begin(17, 16);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("Cyclone Arcade");
  display.display();

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonInterrupt, FALLING);
  
  randomSeed(analogRead(0));
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    
    if (command == "mastermode") {
      Serial.println("Please enter password");
      while (!Serial.available()) {
      }
      String password = Serial.readStringUntil('\n');
      password.trim();
      
      if (password == "HackClubArcade") {
        masterMode = true;
        Serial.println("Entered Master Mode");
        displayMasterMode();
      } else {
        Serial.println("Incorrect password");
      }
    } else if (command == "exitmastermode") {
      masterMode = false;
      Serial.println("Exited Master Mode");
      resetGame();
    }
  }

  if (masterMode) {
    handleMasterMode();
  } else {
    playGame();
  }
}

void buttonInterrupt() {
  buttonPressed = true;
}

void playGame() {
  if (gameOver) {
    if (buttonPressed) {
      resetGame();
    }
    return;
  }

  unsigned long currentTime = millis();
  if (currentTime - lastUpdateTime >= gameSpeed) {
    strip.clear();
    strip.setPixelColor(currentLed, strip.Color(255, 0, 0));
    strip.show();

    currentLed = (currentLed + 1) % NUM_LEDS;
    lastUpdateTime = currentTime;
  }

  if (buttonPressed) {
    handleButtonPress();
  }
}

void handleButtonPress() {
  buttonPressed = false;
  if (currentLed == 33 && isCurrentSessionRigged) {
    currentLed = random(2) == 0 ? 32 : 34;
    strip.clear();
    strip.setPixelColor(currentLed, strip.Color(255, 0, 0));
    strip.show();
  }

  if (currentLed == 30) {
    displayResult("You Win!");
    blinkLeds(strip.Color(0, 255, 0));
  } else {
    displayResult("You Lost!");
    blinkLeds(strip.Color(255, 0, 0));
  }
  gameOver = true;
}
void blinkLeds(uint32_t color) {
  for (int i = 0; i < 3; i++) {
    strip.fill(color);
    strip.show();
    delay(1000);
    strip.clear();
    strip.show();
    delay(1000);
  }
}

void resetGame() {
  gameOver = false;
  currentLed = 0;
  buttonPressed = false;
  strip.clear();
  strip.show();
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Cyclone Arcade");
  display.display();
  isCurrentSessionRigged = (random(100) < riggedPercentage);
  Serial.println("New game started!");
  Serial.print("Percentage rigged: ");
  Serial.print(riggedPercentage);
  Serial.println("%");
  Serial.print("Time per pixel: ");
  Serial.print(gameSpeed);
  Serial.println(" ms");
  Serial.print("Current session rigged: ");
  Serial.println(isCurrentSessionRigged ? "Yes" : "No");
}

void handleMasterMode() {
  int potValue = analogRead(POT_PIN);
  
  if (buttonPressed) {
    speedMenu = !speedMenu;
    buttonPressed = false;
  }

  if (speedMenu) {
    gameSpeed = map(potValue, 0, 4095, 1, 750);
  } else {
    riggedPercentage = map(potValue, 0, 4095, 0, 100);
  }

  displayMasterMode();
}

void displayMasterMode() {
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Master Mode");
  display.println(speedMenu ? "Speed Menu" : "Rigged % Menu");
  display.print(speedMenu ? "MS Per Pixel: " : "Rigged %: ");
  display.println(speedMenu ? gameSpeed : riggedPercentage);
  display.display();
}

void displayResult(const char* result) {
  display.clearDisplay();
  display.setCursor(0,0);
  display.println(result);
  display.display();
}