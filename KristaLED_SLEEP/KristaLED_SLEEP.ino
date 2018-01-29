// KrystaLED stubb source, very rough for my prototype
//

// Needs fastled library
#include "FastLED.h"

#include <avr/sleep.h>    // Sleep Modes
#include <avr/power.h>    // Power management


// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 4

// Define the array of leds
CRGB led[1];

const int buttonPin = 3;

int state = 0;
const int states = 1;
int knopfcount = 0;

void setup()
{
  ////Serial  //Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);

  // pin change interrupt ( for D3)
  PCMSK  |= bit (PCINT3);  // want pin D3 / HW pin 2 / Arduino 3
  GIFR   |= bit (PCIF);    // clear any outstanding interrupts
  GIMSK  |= bit (PCIE);    // enable pin change interrupts

  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(led, 1);

  FastLED.setBrightness(50);
  led[0] = CRGB::Black;
  FastLED.show();
  delay(100);
}

ISR (PCINT0_vect)
{
  // do something interesting here
    FastLED.setBrightness(50);

}

void goToSleep ()
{
  led[0] = CRGB::Black;
  FastLED.show();
  delay(500);
  
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  ADCSRA = 0;            // turn off ADC
  power_all_disable ();  // power off ADC, Timer 0 and 1, serial interface
  sleep_enable();
  sleep_cpu();
  sleep_disable();
  power_all_enable();    // power everything back on
  
  delay(500);
}  // end of goToSleep



boolean mydelay(int time)
{
  for (int i = 0; i < time; i++)
  {
    if (!digitalRead(buttonPin))
    {
      goToSleep();
      return true;
    }
    delay(1);
  }
  return false;
}


void rainbow()
{
  for ( int h = 0; h < 255; h++)
  {
    led[0] = CHSV(h, 255, 255);
    FastLED.show();
    if (mydelay(15)) return;
  }
}


void loop() {
  //Serial.println(state,DEC);
  rainbow();
  //goToSleep();
  // mydelay(100);
}



