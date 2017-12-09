// KrystaLED stubb source, very rough for my prototype
// Pins does not match the PCB!

// Needs fastled library
#include "FastLED.h"

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 0

// Define the array of leds
CRGB led[1];

const int buttonPin = 2;

int state = 0;
const int states = 1;
int knopfcount = 0;

void setup()
{
  ////Serial  //Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(led, 1);

  FastLED.setBrightness(255);
  led[0] = CRGB::Black;
  FastLED.show();
}





boolean knopf() {
  const int dtime = 40;
  if (digitalRead(buttonPin) && knopfcount < dtime)
  {
    knopfcount++;
    if (knopfcount >= dtime)
    {
      state++;
      if (state > states)
      {
        state = 0;
      }
      //    knopfcount=0;
      //Serial.println("Pressed!");
      led[0] = CRGB::Black;
      FastLED.show();
      return true;
    }
  }
  if (!digitalRead(buttonPin))
  {
    knopfcount = 0;
  }
  return false;
}


void rainbow()
{
  for ( int h = 0; h < 255; h++)
  {
    led[0] = CHSV(h, 255, 255);
    FastLED.show();
    if (mydelay(1500)) return;
  }
}


boolean mydelay(int time)
{
  for (int i = 0; i < time; i++)
  {
    if (knopf()) return true;
    delay(1);
  }
  return false;
}

void loop() {
  //Serial.println(state,DEC);
  switch (state) {
    case 1:
      rainbow();
      mydelay(100);
      break;

    default:
      //Serial.println("default:");
      led[0] = CRGB::Black;
      FastLED.show();
      mydelay(100);
      break;
  }


}



