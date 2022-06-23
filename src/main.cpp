#include <Arduino.h>
#include <FastLED.h>

FASTLED_USING_NAMESPACE

// FastLED "100-lines-of-code" demo reel, showing just a few
// of the kinds of animation patterns you can quickly and easily
// compose using FastLED.
//
// This example also shows one easy way to define multiple
// animations patterns and have them automatically rotate.
//
// -Mark Kriegsman, December 2014

#define DATA_PIN 33
//#define CLK_PIN   4
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS 16
CRGB leds[NUM_LEDS];

#define BRIGHTNESS 96
#define FRAMES_PER_SECOND 60

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0;                  // rotating "base color" used by many of the patterns

void addGlitter(fract8 chanceOfGlitter)
{
  if (random8() < chanceOfGlitter)
  {
    leds[random16(NUM_LEDS)] += CRGB::White;
  }
}

void confetti()
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy(leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV(gHue + random8(64), 200, 255);
}

void rainbow()
{
  // FastLED's built-in rainbow generator
  fill_rainbow(leds, NUM_LEDS, gHue, 7);
}

void rainbowWithGlitter()
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(80);
}

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy(leds, NUM_LEDS, 20);
  int pos = beatsin16(13, 0, NUM_LEDS - 1);
  leds[pos] += CHSV(gHue, 255, 192);
}

void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8(BeatsPerMinute, 64, 255);
  for (int i = 0; i < NUM_LEDS; i++)
  { // 9948
    leds[i] = ColorFromPalette(palette, gHue + (i * 2), beat - gHue + (i * 10));
  }
}

void ringRotateFade()
{
    static int lNumber = 0;
    for (lNumber = 0; lNumber < NUM_LEDS * 6; lNumber++) 
    {
    const byte fadeAmt = 128;
    const int cometSize = 1;
    static int iDirection = -1;
    static int iPos = NUM_LEDS-1;

    if (iPos == (-1))
      iPos = NUM_LEDS - cometSize;
//        iDirection *= -1;
    
    for (int i = 0; i < cometSize; i++)
//        g_LEDs[iPos + i].setColorCode(0xFFFFFF); // set to pure white via hex
          leds[iPos] = CRGB( 255, 0, 0) ; // set to pure red via RGB
//       Randomly fade the LEDs
//        if (random(10) > 5)
    for (int j = 0; j < NUM_LEDS; j++)
            leds[j] = leds[j].fadeToBlackBy(fadeAmt);  
    iPos += iDirection;
    FastLED.show();
    Serial.printf("The loop number is %i.\n", lNumber);
    delay(50);
    }
}


void ringRedFade()
{
  // hue - red
  // saturation - max
  // value - 0-255

  fill_solid(leds, NUM_LEDS, CRGB::Red);
  //  fill_gradient_RGB(leds, NUM_LEDS/2, CRGB::Red, CRGB::Black );
  for (byte i = 0; i < 200; i++)
  {
    fadeToBlackBy(leds, NUM_LEDS, 10);
    //  fill_gradient_RGB(leds[7], NUM_LEDS/2, CRGB::Red, CRGB::Black );
    //  int position = 0;
    //  for (int i = 0; i < NUM_LEDS; i++)
    //    FastLED.setPixelColor((i + position) % NUM_LEDS, getPixelColorHsv(i, 0, 255, FastLED.gamma8(i * (255 / NUM_LEDS))));
    FastLED.show();
    //  position++;
    //  position %= NUM_LEDS;
    delay(50);
  }
}

void pulseRed()
{
  //  fill_solid( leds, NUM_LEDS, CRGB( 255, 0, 0));
  for (int redLed = 0; redLed < (NUM_LEDS / 4); redLed = redLed + 1)
  {
    // Turn our current led on to red, then show the leds
        for (int i = 0; i < NUM_LEDS; i += 4){
        leds[redLed+i] = CRGB::Red;
//        Serial.printf("%i\n", i);
    }
    // Show the leds (only one of which is set to red, from above)
    FastLED.show();

    // Wait a little bit
    delay(100);

    // Turn our current led back to black for the next loop around
        for (int i = 0; i < NUM_LEDS; i += 4){
        leds[redLed+i] = CRGB::Black;
    }
  }
}

void juggle()
{
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy(leds, NUM_LEDS, 20);
  uint8_t dothue = 0;
  for (int i = 0; i < 8; i++)
  {
    leds[beatsin16(i + 7, 0, NUM_LEDS - 1)] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}
// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
// SimplePatternList gPatterns = {ringRed, pulseRed, rainbow, rainbowWithGlitter, confetti, sinelon, juggle, bpm};
SimplePatternList gPatterns = {ringRotateFade, ringRedFade, pulseRed, sinelon};

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE(gPatterns);
}

void setup()
{
  Serial.begin(115200);
  Serial.printf("Sketch name is Blink-Nano");
  delay(3000); // 3 second delay for recovery

  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  // FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}

void loop()
{
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();
  // insert a delay to keep the framerate modest
//  FastLED.delay(1000 / FRAMES_PER_SECOND);

  // do some periodic updates
  EVERY_N_MILLISECONDS(20) { gHue++; }   // slowly cycle the "base color" through the rainbow
  EVERY_N_SECONDS(10) { nextPattern(); } // change patterns periodically
}
