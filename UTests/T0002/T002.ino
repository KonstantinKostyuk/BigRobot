//BigRobot SW for competition

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
  pinMode(LED_PIN, OUTPUT);  // LED PIN init
  digitalWrite(LED_PIN, LOW);// LED set to OFF
  MD.init();                 // MotorDriver init
}

void loop()
{
    digitalWrite(LED_PIN, LOW);      // LED OFF
    MD.setSpeeds( 0,  0);           // Both motors stop(speed = 0)
    while (button.isPressed())      // wait for button to be released
    {
        delay(10);                   // debounce the button release
        digitalWrite(LED_PIN, HIGH); // LED ON
        MD.setSpeeds( m1Speed,  m2Speed); // Both motors drive
    };
}