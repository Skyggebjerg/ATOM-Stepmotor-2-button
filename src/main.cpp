#include <Arduino.h>
#include <M5Atom.h>
#include "StepperDriver.h"
#include "FastLED.h"

#define Neopixel_PIN 26
#define NUM_LEDS     37

CRGB leds[NUM_LEDS];
uint8_t gHue = 0;  // Initial tone value.
uint8_t brightn = 0;  // Initial brightness value. 

int cur_value1 = 0, cur_value2 = 0;

int motor_steps = 200;
int step_divisition = 32; //32
int en_pin = 22;
int dir_pin = 23;
int step_pin = 19;

int step = 0;
int speed = 0;

int toggler =0;

StepperDriver ss(motor_steps, step_divisition, en_pin, dir_pin, step_pin);

void setup()
{
  M5.begin(true, false, true);
  //pinMode(32, INPUT); // set pin mode to input
  //pinMode(26, INPUT);
  ss.powerEnable(false);
  ss.setSpeed(0);
  delay(1600);

      // Neopixel initialization.
    FastLED.addLeds<WS2811, Neopixel_PIN, GRB>(leds, NUM_LEDS)
        .setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(10);  // set the LED brightness to 5.
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    FastLED.show();
    brightn =5;
}

void loop()

{
   if(M5.Btn.wasPressed()) {
      toggler=toggler+1;
      if(toggler==7) toggler=0;
   }

   if(toggler==0)
   {
      ss.powerEnable(false);
      ss.setSpeed(0);
      fill_solid(leds, NUM_LEDS, CRGB::Black);
      FastLED.show();
   }   

   if(toggler==1)
   {
      ss.powerEnable(true);
      ss.setSpeed(300); // 60 = 60 revolutions per minute (rpm) = 1 rev per sec
      ss.step(3000);
      ss.setSpeed(600);
      ss.step(6000);

      //ss.setSpeed(800);
      //ss.step(8000);

      //ss.setSpeed(900);
      //ss.step(9000);

      //ss.setSpeed(1000);
      //ss.step(10000);
      //delay(500);
      //ss.step(-5000);
      //delay(3000);
      ss.powerEnable(false);
      toggler=2;
}   

   if(toggler==3)
   {
            fill_solid(leds, NUM_LEDS, CRGB::White);
            FastLED.setBrightness(255);
            FastLED.show();
   }

   if(toggler==4)
   {
            fill_solid(leds, NUM_LEDS, CRGB::White);
            FastLED.setBrightness(255);
            FastLED.show();

      ss.powerEnable(true);
      ss.setSpeed(300); // 60 = 60 revolutions per minute (rpm) = 1 rev per sec
      ss.step(6000);
      ss.powerEnable(false);
      toggler=5;
   }

   if(toggler==6)
   {
       fill_rainbow(
        leds, NUM_LEDS, gHue,
        7);  // Set the leds from 0 to 37 beads to gradient rainbow color, the
             // starting tone value to gHue, and the color difference between
             // adjacent beads to 7.
        FastLED.show();  // Updated LED color
        delay(10);
        gHue++;
   }

      M5.update();
   }


/* {
  cur_value1 = digitalRead(32); // read the value of BUTTONS
  cur_value2 = digitalRead(26);

  if (cur_value1 == 0)
  {
    ss.powerEnable(true);
    ss.setSpeed(200);
    ss.step(100);
    ss.powerEnable(false);
  }

  if (cur_value2 == 0)
  {
    ss.powerEnable(true);
    ss.setSpeed(100);
    ss.step(-100);
    ss.powerEnable(false);
  } */
//}
