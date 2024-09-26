//Demo for Pegasus BR with Hex LEDs in the  bottom and a stepmotor


#include <Arduino.h>
#include <M5Atom.h>
#include "StepperDriver.h"
#include "FastLED.h"

#define Neopixel_PIN 26
#define NUM_LEDS     37

CRGB leds[NUM_LEDS];
CRGB background[NUM_LEDS];
//uint8_t gHue = 0;  // Initial tone value.
uint8_t brightn = 0;  // Initial brightness value. 

void drawBackground() {
  // A simple plasma effect
  fill_noise16 (background, NUM_LEDS, 1, millis(), 30, 1, 0, 50, millis() / 3, 10);
}

void drawMovingPixel() {
  // A pixel that moves back and forth using noise
  uint16_t pos = inoise16(millis() * 100);
  pos = constrain(pos, 13000, 51000);
  pos = map(pos, 13000, 51000, 0, NUM_LEDS - 1);
  leds[pos] = CRGB::Red;
}

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
  ss.powerEnable(false);
  ss.setSpeed(0);
  delay(1600);

      // Neopixel initialization.
    FastLED.addLeds<WS2811, Neopixel_PIN, GRB>(leds, NUM_LEDS)
        .setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(100);  // set the LED brightness to 5.
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

   if(toggler==1) // Turn on Stepmotor - fast
   {
      ss.powerEnable(true);
      ss.setSpeed(500); // 60 = 60 revolutions per minute (rpm) = 1 rev per sec
      ss.step(6000,200,200);
      //ss.setSpeed(600);
      //ss.step(6000);

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

   if(toggler==3) // Turn on white LEDs
   {
            fill_solid(leds, NUM_LEDS, CRGB::White);
            FastLED.setBrightness(255);
            FastLED.show();
   }

   if(toggler==4) // Turn on white LEDS and fast motor
   {
            fill_solid(leds, NUM_LEDS, CRGB::White);
            FastLED.setBrightness(255);
            FastLED.show();

      ss.powerEnable(true);
      ss.setSpeed(600); // 60 = 60 revolutions per minute (rpm) = 1 rev per sec
      ss.step(60000,200,0);
      //ss.step(6000);
      //ss.powerEnable(false);
      delay(100);
      //toggler=5;
   }

   if(toggler==5) // Stop stepmotor
   {
      ss.powerEnable(false);

   }

   if(toggler==6) // Turn on Disco show with LEDs
   {
  drawBackground();
  drawMovingPixel();

  EVERY_N_MILLISECONDS(20) {
    fadeToBlackBy(leds, NUM_LEDS, 10); 
    nblend(leds, background, NUM_LEDS, 30);
  } 
  
  FastLED.show();


/*        fill_rainbow(
        leds, NUM_LEDS, gHue,
        7);  // Set the leds from 0 to 37 beads to gradient rainbow color, the
             // starting tone value to gHue, and the color difference between
             // adjacent beads to 7.
        FastLED.show();  // Updated LED color
        delay(10);
        gHue++; */
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
