#include <Arduino.h>
#include <M5Atom.h>
#include "StepperDriver.h"

int cur_value1 = 0, cur_value2 = 0;

int motor_steps = 200;
int step_divisition = 32;
int en_pin = 22;
int dir_pin = 23;
int step_pin = 19;

int step = 0;
int speed = 0;

StepperDriver ss(motor_steps, step_divisition, en_pin, dir_pin, step_pin);

void setup()
{
  M5.begin(true, false, true);
  pinMode(32, INPUT); // set pin mode to input
  pinMode(26, INPUT);
  ss.setSpeed(0);
  delay(1600);
}

void loop()
{
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
  }
}
