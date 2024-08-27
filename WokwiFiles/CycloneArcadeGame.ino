#include <Adafruit_NeoPixel.h>

#define LED_PIN     5  
#define NUMPIXELS   60 
#define BUTTON_PIN  2  
#define POT_PIN     4  

Adafruit_NeoPixel pixels(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

volatile bool buttonPressed = false; 
int ledIndex = 0;  
int delayTime = 50; 

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);  
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonPress, FALLING); 
  pixels.begin(); 
  pixels.show();  

void loop() {
  delayTime = map(analogRead(POT_PIN), 0, 1023, 10, 200); 
  pixels.clear(); 

  pixels.setPixelColor(ledIndex, pixels.Color(255, 0, 0)); 
  pixels.show(); 

  if (buttonPressed) {
    checkWinCondition();
    buttonPressed = false; 
  }

  ledIndex = (ledIndex + 1) % NUMPIXELS; 
  delay(delayTime); 

void buttonPress() {
  buttonPressed = true; 
}

void checkWinCondition() {
  if (ledIndex == 30) {
    blinkColor(0, 255, 0); 
  } else {
    blinkColor(255, 0, 0); 
  }
}

void blinkColor(uint8_t r, uint8_t g, uint8_t b) {
  for (int i = 0; i < 3; i++) { 
    pixels.fill(pixels.Color(r, g, b), 0, NUMPIXELS);
    pixels.show();
    delay(1000);
    pixels.clear();
    pixels.show();
    delay(1000);
  }
  
  resetGame(); 
}

void resetGame() {
  ledIndex = 0; 
  while (!digitalRead(BUTTON_PIN)) {} 
}
