//T0005 - Test

// Pololu Github - https://github.com/pololu/dual-vnh5019-motor-shield/
#include <DualVNH5019MotorShield.h>
// Pololu Github - https://github.com/pololu/vl53l0x-arduino
#include <VL53L0X.h>
// Pololu Github - https://github.com/pololu/qtr-sensors-arduino
#include <QTRSensors.h>
// Pololu Github - https://github.com/pololu/pushbutton-arduino
#include <Pushbutton.h>

// --- define PINS
#define LED_PIN 13
#define BUTTON_PIN 11
#define START_PIN 3
#define STOP_PIN 5

// --- define Variables
int MAX_SPEED = 400;
int m1Speed = MAX_SPEED / 2;
int m2Speed = MAX_SPEED / 2;


// --- define Objects
Pushbutton button(BUTTON_PIN); // button create and init
DualVNH5019MotorShield MD;     // MotorDriver create

void setup()
{
  pinMode(LED_PIN, OUTPUT);  // LED PIN init
  pinMode(START_PIN, INPUT);  // LED PIN init
  pinMode(STOP_PIN, INPUT);  // LED PIN init  
  digitalWrite(LED_PIN, LOW);// LED set to OFF
  MD.init();                 // MotorDriver init
  Serial.begin(115200);
}

void loop()
{
delay(500);
Serial.print(digitalRead(START_PIN));
Serial.print(" - ");
Serial.println(digitalRead(STOP_PIN));
//Serial.println("");
}