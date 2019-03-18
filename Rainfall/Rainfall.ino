#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6

#define NUM_LEDS 29
// Pixels 0-2 (10) are the bottom right, should be "grass"
// Pixels 3-10 (40) are the right side, should have "rainfall"
// Pixels 11-17 (21) pixels accross the top, should be dark cloudy color
// Pixels 18-25 (40) are the left side, should have "rainfall"
// Pixels 26-28 (10) are the bottom left, should be "grass"

#define BRIGHTNESS 50

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code
  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  // Set the bottom right to grass
  for(uint8_t i=0; i<3; i++) {
    strip.setPixelColor(i, 0, 255, 0, 0);
    strip.show();
    delay(1);
  }
  // Set the bottom left to grass
  for(uint8_t i=26; i<29; i++) {
    strip.setPixelColor(i, 0, 255, 0, 0);
    strip.show();
    delay(1);
  }
  // Set top to Dark Cloudy color
  for(uint8_t i=11; i<18; i++) {
    strip.setPixelColor(i, 0, 0, 255, 0);
    strip.show();
    delay(1);
  }
  //Set right side to teal
  for(uint8_t i=18; i<26; i++) {
    //strip.setPixelColor(i, 0, 96, 96, 25);
    strip.setPixelColor(i, 0, 0, 0, 25);
    strip.show();
    delay(1);
  }
  //Set left side to teal
  for(uint8_t i=3; i<11; i++) {
    strip.setPixelColor(i, 0, 0, 0, 25);
    strip.show();
    delay(1);
  }
}

void loop() {
  Rainfall(20,110,2);
}


void Rainfall(uint8_t wait, uint8_t dropSpeed, uint8_t dropLength ) {
  
  
  int head = 10 - dropLength + 1;
  int tail = 10;

  static unsigned long lastTime = 0;

  while(true){
      for (uint16_t i=10; i>2; i--) {
        if ((i <= tail && i >= head) || (tail < head && i <= tail) || (tail < head && i >= head) ){
          strip.setPixelColor(i, 0, 0, 255, 0);
        }
        else{
          strip.setPixelColor(i, 0, 0, 0, 25);
        }
      }

      if (millis() - lastTime > dropSpeed) {
        head--;
        tail--;
        lastTime = millis();
      }
   
      head%=strip.numPixels();
      tail%=strip.numPixels();
      strip.show();
      delay(wait);
  }
}


