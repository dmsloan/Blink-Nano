/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Christmas for around window 
// https://www.instructables.com/Easy-LED-Holiday-Light-Show-Wizards-in-Winter-WS28/  
// Modified for platformIO                                        //
/////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <Arduino.h>
#include <FastLED.h>
#define NUM_LEDS 150  // be sure to set this to the correct number of leds or it does not look good
#define DATA_PIN 5
#define BRIGHTNESS 255  // Max LED Brightness, 1-255

#define FASTLED_ALLOW_INTERRUPTS 0
FASTLED_USING_NAMESPACE

#define MAX_POWER_MILLIAMPS 500
#define LED_TYPE            WS2812B
#define COLOR_ORDER         GRB

#define UPDATES_PER_SECOND 100

// This is an array of leds.  One item for each led in your strip.
CRGB leds[NUM_LEDS];

uint8_t max_bright = BRIGHTNESS;


void setup() {
  // sanity check delay - allows reprogramming if accidently blowing power w/leds
  delay(2000);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(max_bright);
  set_max_power_in_volts_and_milliamps(5, MAX_POWER_MILLIAMPS);
}

void conductorIntro() {
  int i = 0;
  while (i < 3) {
    fill_solid(leds, NUM_LEDS, CRGB::Red);
    FastLED.delay(10);
    FastLED.clear();
    FastLED.delay(802);
    i++;
  }
  fill_solid(leds, NUM_LEDS, CRGB::Green);
  FastLED.delay(10);
  FastLED.clear();
  FastLED.delay(802);
}

void whiteFlashes7() {
  fill_solid(leds, NUM_LEDS, CRGB( 200, 172, 68) );
  FastLED.delay(20);
  FastLED.clear();
  FastLED.delay(185);

  fill_solid(leds, NUM_LEDS, CRGB( 200, 172, 68) );
  FastLED.delay(20);
  FastLED.clear();
  FastLED.delay(405);
  int i = 0;
  while (i < 5) {
    fill_solid(leds, NUM_LEDS, CRGB( 200, 172, 68) );
    FastLED.delay(20);
    FastLED.clear();
    FastLED.delay(185);

    fill_solid(leds, NUM_LEDS, CRGB( 200, 172, 68) );
    FastLED.delay(20);
    FastLED.clear();
    FastLED.delay(185);

    fill_solid(leds, NUM_LEDS, CRGB( 200, 172, 68) );
    FastLED.delay(20);
    FastLED.clear();
    FastLED.delay(405);
    i++;
  }
  fill_solid(leds, NUM_LEDS, CRGB( 200, 172, 68) );
  FastLED.delay(20);
  FastLED.clear();
  FastLED.delay(185);

  fill_solid(leds, NUM_LEDS, CRGB( 200, 172, 68) );
  FastLED.delay(20);
  FastLED.clear();
  FastLED.delay(75);
}



void incrementalReplacement() {
  fill_solid(leds, NUM_LEDS, CRGB::Red);
  FastLED.delay(140);
  FastLED.clear();
  FastLED.delay(40);

  fill_solid(leds, NUM_LEDS, CRGB::Green);
  FastLED.delay(140);
  FastLED.clear();
  FastLED.delay(40);

  fill_solid(leds, NUM_LEDS, CRGB::Blue);
  FastLED.delay(140);
  FastLED.clear();
  FastLED.delay(40);

  fill_solid(leds, NUM_LEDS, CRGB(200, 172, 68) );
  FastLED.delay(140);
  FastLED.clear();
  FastLED.delay(40);

  fill_solid(leds, NUM_LEDS, CRGB::Red);
  FastLED.delay(140);
  FastLED.clear();
  FastLED.delay(40);

  fill_solid(leds, NUM_LEDS, CRGB::Green);
  FastLED.delay(140);
  FastLED.clear();
  FastLED.delay(40);

  fill_solid(leds, NUM_LEDS, CRGB::Blue);
  FastLED.delay(140);
  FastLED.clear();
  FastLED.delay(100);
}



void incrementalWhiteLed7() {
  for (int whiteLed = 0; whiteLed < NUM_LEDS * 0.85714285714; whiteLed = whiteLed + NUM_LEDS / 7) {
    // Turn our current led on to white, then show the leds
    leds[whiteLed] = CRGB( 200, 172, 68) ;

    // Show the leds (only one of which is set to white, from above)
    FastLED.show();

    // Wait a little bit
    delay(18);

    // Turn our current led back to black for the next loop around
    leds[whiteLed] = CRGB::Black;
    FastLED.delay(185);
  }
}



void convergeThenSeparateWhite() {
  int i = 0;
  for (int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed++) {
    leds[whiteLed] = CRGB( 200, 172, 68) ;
    leds[NUM_LEDS - whiteLed] = CRGB( 200, 172, 68) ;
    FastLED.show();
    delay(6);
    leds[whiteLed] = CRGB::Black;
    leds[NUM_LEDS - whiteLed] = CRGB::Black ;
    i++;
  }
}



void convergeThenSeparateRed() {
  int i = 0;
  for (int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed++) {
    leds[whiteLed] = CRGB::Red;
    leds[NUM_LEDS - whiteLed] = CRGB::Red;
    FastLED.show();
    delay(6);
    leds[whiteLed] = CRGB::Black;
    leds[NUM_LEDS - whiteLed] = CRGB::Black ;
    i++;
  }
}



void convergeThenSeparateGreen() {
  int i = 0;
  for (int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed++) {
    leds[whiteLed] = CRGB::Green;
    leds[NUM_LEDS - whiteLed] = CRGB::Green;
    FastLED.show();
    delay(6);
    leds[whiteLed] = CRGB::Black;
    leds[NUM_LEDS - whiteLed] = CRGB::Black ;
    i++;
  }
}



void slideLeftToRight() {
  int i = 0;
  for (int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed++) {
    leds[whiteLed] = CRGB( 200, 172, 68) ;
    FastLED.show();
    delay(3.9);
    leds[whiteLed] = CRGB::Black;
    i++;
  }
}



void flashWhite() {
  fill_solid(leds, NUM_LEDS, CRGB( 200, 172, 68) );
  FastLED.show();
  FastLED.delay(300);
  FastLED.clear();
  FastLED.delay(100);
}



void slideRightToLeft() {
  int i = NUM_LEDS;
  for (int whiteLed = i; whiteLed > 0; whiteLed--) {
    leds[whiteLed] = CRGB( 200, 172, 68) ;
    FastLED.show();
    delay(3.9);
    leds[whiteLed] = CRGB::Black;
    i++;
  }
}



void Flashes() {
  // put your main code here, to run repeatedly:
  fill_solid(leds, NUM_LEDS, CRGB( 200, 172, 68)  );
  FastLED.delay(40);
  FastLED.clear();
  FastLED.delay(630);

  fill_solid(leds, NUM_LEDS, CRGB( 200, 172, 68) );
  FastLED.delay(40);
  FastLED.clear();
  FastLED.delay(162);

  fill_solid(leds, NUM_LEDS, CRGB( 200, 172, 68) );
  FastLED.delay(40);
  FastLED.clear();
  FastLED.delay(630);

  fill_solid(leds, NUM_LEDS, CRGB( 200, 172, 68) );
  FastLED.delay(40);
  FastLED.clear();
  FastLED.delay(162);
}



void halfColorSweepsAlteratingInOut() {
  for (int i = 0; i <= NUM_LEDS / 2; i = i + 2) {
    leds[i] = CRGB::Red;
    leds[i + 1] = CRGB::Red;
    delayMicroseconds(5000);
    FastLED.show();
  }
  for (int i = NUM_LEDS; i >= NUM_LEDS / 2; i = i - 2) {
    leds[i] = CRGB::Green;
    leds[i - 1] = CRGB::Green;
    delayMicroseconds(5000);
    FastLED.show();
  }
  for (int i = 0; i <= NUM_LEDS / 2; i = i + 2) {
    leds[i] = CRGB::Green;
    leds[i - 1] = CRGB::Green;
    delayMicroseconds(5000);
    FastLED.show();
  }
  for (int i = NUM_LEDS; i >= NUM_LEDS / 2; i = i - 2) {
    leds[i] = CRGB::Red;
    leds[i - 1] = CRGB::Red;
    delayMicroseconds(5000);
    FastLED.show();
  }
  FastLED.clear();
}



void RandomFlashes() {
  long randNumber1;
  long randNumber2;
  long randNumber3;
  long randNumber4;

  for (int i = 0; i < 400; i++) {
    randNumber1 = random(0, NUM_LEDS + 1);
    leds[randNumber1] = CRGB( 200, 172, 68) ;

    randNumber2 = random(0, NUM_LEDS + 1);
    leds[randNumber2] = CRGB( 200, 172, 68) ;

    randNumber3 = random(0, NUM_LEDS + 1);
    leds[randNumber3] = CRGB( 200, 172, 68) ;

    randNumber4 = random(0, NUM_LEDS + 1);
    leds[randNumber4] = CRGB( 200, 172, 68) ;

    FastLED.show();
    FastLED.delay(2);
    FastLED.clear();
  }
}


void Color3RandomFlashes() {
  long randNumber1;
  long randNumber2;
  long randNumber3;
  long randNumber4;

  for (int i = 0; i < 133; i++) {
    randNumber1 = random(0, NUM_LEDS + 1);
    leds[randNumber1] = CRGB( 200, 172, 68) ;

    randNumber2 = random(0, NUM_LEDS + 1);
    leds[randNumber2] = CRGB( 200, 172, 68) ;

    randNumber3 = random(0, NUM_LEDS + 1);
    leds[randNumber3] = CRGB( 200, 172, 68) ;

    randNumber4 = random(0, NUM_LEDS + 1);
    leds[randNumber4] = CRGB( 200, 172, 68) ;

    FastLED.show();
    FastLED.delay(2);
    FastLED.clear();
  }
  for (int i = 0; i < 133; i++) {
    randNumber1 = random(0, NUM_LEDS + 1);
    leds[randNumber1] = CRGB::Red;

    randNumber2 = random(0, NUM_LEDS + 1);
    leds[randNumber2] = CRGB::Red;

    randNumber3 = random(0, NUM_LEDS + 1);
    leds[randNumber3] = CRGB::Red;

    randNumber4 = random(0, NUM_LEDS + 1);
    leds[randNumber4] = CRGB::Red;

    FastLED.show();
    FastLED.delay(2);
    FastLED.clear();
  }
  for (int i = 0; i < 134; i++) {
    randNumber1 = random(0, NUM_LEDS + 1);
    leds[randNumber1] = CRGB::Green;

    randNumber2 = random(0, NUM_LEDS + 1);
    leds[randNumber2] = CRGB::Green;

    randNumber3 = random(0, NUM_LEDS + 1);
    leds[randNumber3] = CRGB::Green;

    randNumber4 = random(0, NUM_LEDS + 1);
    leds[randNumber4] = CRGB::Green;

    FastLED.show();
    FastLED.delay(2);
    FastLED.clear();
  }
}


void slowHalfColorSweepsAlteratingInOut() {
  for (int i = 0; i <= NUM_LEDS / 2; i = i + 2) {
    leds[i] = CRGB::Red;
    leds[i + 1] = CRGB::Red;
    delayMicroseconds(5500);
    FastLED.show();
  }
  for (int i = NUM_LEDS; i >= NUM_LEDS / 2; i = i - 2) {
    leds[i] = CRGB::Green;
    leds[i - 1] = CRGB::Green;
    delayMicroseconds(5500);
    FastLED.show();
  }
  for (int i = 0; i <= NUM_LEDS / 2; i = i + 2) {
    leds[i] = CRGB::Green;
    leds[i - 1] = CRGB::Green;
    delayMicroseconds(5500);
    FastLED.show();
  }
  for (int i = NUM_LEDS; i >= NUM_LEDS / 2; i = i - 2) {
    leds[i] = CRGB::Red;
    leds[i - 1] = CRGB::Red;
    delayMicroseconds(5500);
    FastLED.show();
  }

  for (int i = 0; i <= NUM_LEDS / 2; i = i + 2) {
    leds[i] = CRGB::Red;
    leds[i + 1] = CRGB( 200, 172, 68) ;
    delayMicroseconds(5500);
    FastLED.show();
  }
  for (int i = NUM_LEDS; i >= NUM_LEDS / 2; i = i - 2) {
    leds[i] = CRGB::Red;
    leds[i - 1] = CRGB( 200, 172, 68) ;
    delayMicroseconds(5500);
    FastLED.show();
  }
  for (int i = 0; i <= NUM_LEDS / 2; i = i + 2) {
    leds[i] = CRGB::Green;
    leds[i - 1] = CRGB::Red;
    delayMicroseconds(5500);
    FastLED.show();
  }
  for (int i = NUM_LEDS; i >= NUM_LEDS / 2; i = i - 2) {
    leds[i] = CRGB::Green;
    leds[i - 1] = CRGB::Red;
    delayMicroseconds(5500);
    FastLED.show();
  }
  FastLED.clear();
}



void slowSlideLeftToRight() {
  int i = 0;
  for (int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed++) {
    leds[whiteLed] = CRGB( 200, 172, 68) ;
    FastLED.show();
    delay(6000 / NUM_LEDS);
    leds[whiteLed] = CRGB::Black;
    i++;
  }
}



void slowConvergeThenSeparateRed() {
  int i = 0;
  for (int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed++) {
    leds[whiteLed] = CRGB::Red;
    leds[NUM_LEDS - whiteLed] = CRGB::Red;
    FastLED.show();
    delayMicroseconds(6100);
    leds[whiteLed] = CRGB::Black;
    leds[NUM_LEDS - whiteLed] = CRGB::Black ;
    i++;
  }
}



void slowConvergeThenSeparateGreen() {
  int i = 0;
  for (int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed++) {
    leds[whiteLed] = CRGB::Green;
    leds[NUM_LEDS - whiteLed] = CRGB::Green;
    FastLED.show();
    delayMicroseconds(6100);
    leds[whiteLed] = CRGB::Black;
    leds[NUM_LEDS - whiteLed] = CRGB::Black ;
    i++;
  }
}



void slowConvergeThenSeparateBlue() {
  int i = 0;
  for (int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed++) {
    leds[whiteLed] = CRGB::Blue;
    leds[NUM_LEDS - whiteLed] = CRGB::Blue;
    FastLED.show();
    delayMicroseconds(6100);
    leds[whiteLed] = CRGB::Black;
    leds[NUM_LEDS - whiteLed] = CRGB::Black ;
    i++;
  }
}



void slowConvergeThenSeparateWhite() {
  int i = 0;
  for (int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed++) {
    leds[whiteLed] = CRGB( 200, 172, 68);
    leds[NUM_LEDS - whiteLed] = CRGB( 200, 172, 68);
    FastLED.show();
    delayMicroseconds(6100);
    leds[whiteLed] = CRGB::Black;
    leds[NUM_LEDS - whiteLed] = CRGB::Black ;
    i++;
  }
}



void twinkle() {
  delay(300);
  fill_solid(leds, NUM_LEDS, CRGB::Red);
  FastLED.delay(20);
  FastLED.clear();
  FastLED.delay(180);

  fill_solid(leds, NUM_LEDS, CRGB::Green);
  FastLED.delay(20);
  FastLED.clear();
  FastLED.delay(180);

  fill_solid(leds, NUM_LEDS, CRGB::Blue);
  FastLED.delay(20);
  FastLED.clear();
  FastLED.delay(400);

  fill_solid(leds, NUM_LEDS, CRGB( 200, 172, 68) );
  FastLED.delay(790);
  FastLED.clear();
  FastLED.delay(20);


  fill_solid(leds, NUM_LEDS, CRGB::Red);
  FastLED.delay(20);
  FastLED.clear();
  FastLED.delay(180);

  fill_solid(leds, NUM_LEDS, CRGB::Green);
  FastLED.delay(20);
  FastLED.clear();
  FastLED.delay(180);

  fill_solid(leds, NUM_LEDS, CRGB::Blue);
  FastLED.delay(20);
  FastLED.clear();
  FastLED.delay(400);

  fill_solid(leds, NUM_LEDS, CRGB::Red);
  FastLED.delay(790);
  FastLED.clear();
  FastLED.delay(20);


  fill_solid(leds, NUM_LEDS, CRGB::Red);
  FastLED.delay(20);
  FastLED.clear();
  FastLED.delay(190);

  fill_solid(leds, NUM_LEDS, CRGB::Green);
  FastLED.delay(20);
  FastLED.clear();
  FastLED.delay(190);

  fill_solid(leds, NUM_LEDS, CRGB::Red);
  FastLED.delay(20);
  FastLED.clear();
  FastLED.delay(410);

  fill_solid(leds, NUM_LEDS, CRGB::Green);
  FastLED.delay(20);
  FastLED.clear();
  FastLED.delay(410);

  fill_solid(leds, NUM_LEDS, CRGB::Blue);
  FastLED.delay(20);
  FastLED.clear();
  FastLED.delay(410);

  fill_solid(leds, NUM_LEDS, CRGB::Red);
  FastLED.delay(20);
  FastLED.clear();
  FastLED.delay(410);

  fill_solid(leds, NUM_LEDS, CRGB::Green);
  FastLED.delay(20);
  FastLED.clear();
  FastLED.delay(410);

  fill_solid(leds, NUM_LEDS, CRGB( 200, 172, 68) );
  FastLED.delay(700);
  FastLED.clear();
  FastLED.delay(220);


  fill_solid(leds, NUM_LEDS, CRGB::Red);
  FastLED.delay(20);
  FastLED.clear();
  FastLED.delay(180);

  fill_solid(leds, NUM_LEDS, CRGB::Green);
  FastLED.delay(20);
  FastLED.clear();
  FastLED.delay(180);

  fill_solid(leds, NUM_LEDS, CRGB::Blue);
  FastLED.delay(20);
  FastLED.clear();
  FastLED.delay(400);

  fill_solid(leds, NUM_LEDS, CRGB( 200, 172, 68) );
  FastLED.delay(790);
  FastLED.clear();
  FastLED.delay(20);


  fill_solid(leds, NUM_LEDS, CRGB::Red);
  FastLED.delay(20);
  FastLED.clear();
  FastLED.delay(180);

  fill_solid(leds, NUM_LEDS, CRGB::Green);
  FastLED.delay(20);
  FastLED.clear();
  FastLED.delay(180);

  fill_solid(leds, NUM_LEDS, CRGB::Blue);
  FastLED.delay(20);
  FastLED.clear();
  FastLED.delay(400);

  fill_solid(leds, NUM_LEDS, CRGB::Red);
  FastLED.delay(790);
  FastLED.clear();
  FastLED.delay(20);


  fill_solid(leds, NUM_LEDS, CRGB::Red);
  FastLED.delay(20);
  FastLED.clear();
  FastLED.delay(190);

  fill_solid(leds, NUM_LEDS, CRGB::Green);
  FastLED.delay(20);
  FastLED.clear();
  FastLED.delay(190);

  fill_solid(leds, NUM_LEDS, CRGB::Red);
  FastLED.delay(20);
  FastLED.clear();
  FastLED.delay(410);

  fill_solid(leds, NUM_LEDS, CRGB::Green);
  FastLED.delay(20);
  FastLED.clear();
  FastLED.delay(410);

  fill_solid(leds, NUM_LEDS, CRGB::Blue);
  FastLED.delay(20);
  FastLED.clear();
  FastLED.delay(410);

  fill_solid(leds, NUM_LEDS, CRGB::Red);
  FastLED.delay(20);
  FastLED.clear();
  FastLED.delay(410);

  fill_solid(leds, NUM_LEDS, CRGB::Green);
  FastLED.delay(20);
  FastLED.clear();
  FastLED.delay(410);

  fill_solid(leds, NUM_LEDS, CRGB::Blue);
  FastLED.delay(300);
  FastLED.clear();
  FastLED.delay(200);
}

void loop() {
  // put your main code here, to run repeatedly:

  conductorIntro();
  // 0:00
  whiteFlashes7();

  incrementalWhiteLed7();

  whiteFlashes7();

  // incrementalWhiteLed7();
  incrementalReplacement();

  convergeThenSeparateWhite();
  convergeThenSeparateRed();
  convergeThenSeparateGreen();

  flashWhite();

  // incrementalWhiteLed7();
  incrementalReplacement();

  convergeThenSeparateWhite();
  convergeThenSeparateRed();
  convergeThenSeparateGreen();

  flashWhite();

  slideLeftToRight();

  flashWhite();

  slideRightToLeft();
  // 0:28
  Flashes();

  halfColorSweepsAlteratingInOut();

  RandomFlashes();
  // 0:37
  flashWhite();

  slideRightToLeft();

  Color3RandomFlashes();

  flashWhite();

  slideLeftToRight();

  flashWhite();

  slideRightToLeft();

  Flashes();

  slowHalfColorSweepsAlteratingInOut();
  // 0:50

  slowConvergeThenSeparateRed();

  slowConvergeThenSeparateGreen();

  slowConvergeThenSeparateBlue();

  slowConvergeThenSeparateWhite();

  twinkle();
  // 1:09
  flashWhite();

  slideLeftToRight();

  flashWhite();

  slideRightToLeft();
  
  Flashes();
  // 1:14
  halfColorSweepsAlteratingInOut();

  convergeThenSeparateWhite();
  convergeThenSeparateRed();
  convergeThenSeparateGreen();

  flashWhite();

  incrementalReplacement();

  Color3RandomFlashes();

  flashWhite();

  incrementalReplacement();

  flashWhite();

  incrementalReplacement();
}
