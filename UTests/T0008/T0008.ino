//T0002 - Test

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

// --- define Variables
int MAX_SPEED = 400;
int m1Speed = MAX_SPEED / 2;
int m2Speed = MAX_SPEED / 2;


// --- define Objects
Pushbutton button(BUTTON_PIN); // button create and init
DualVNH5019MotorShield MD;     // MotorDriver create

void setup()
{
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);  // LED PIN init
  MD.init();                 // MotorDriver init
  Serial.println("Start");
}

void loop()
{
  delay(500);                   // debounce the button release
  Serial.println("FWD");
  digitalWrite(LED_PIN, HIGH); // LED ON
  //MD.setSpeeds( m1Speed,  m2Speed); // Both motors drive
  MD.setSpeeds( 0,  m2Speed); // Both motors drive
  //MD.setSpeeds( m1Speed,  0); // Both motors drive
  //MD.setSpeeds( -m1Speed,  -m2Speed); // Both motors drive
  delay(500);                   //
}
