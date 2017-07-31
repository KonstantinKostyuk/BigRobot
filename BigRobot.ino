//BigRobot SW for competition

// Pololu Github - https://github.com/pololu/dual-vnh5019-motor-shield/
#include <DualVNH5019MotorShield.h>
// Pololu Github - https://github.com/pololu/vl53l0x-arduino
#include <VL53L0X.h>
// Pololu Github - https://github.com/pololu/qtr-sensors-arduino
#include <QTRSensors.h>
// Pololu Github - https://github.com/pololu/pushbutton-arduino
#include <Pushbutton.h>

#define LED_PIN 13
#define BUTTON_PIN 11

Pushbutton button(BUTTON_PIN);

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop()
{
    digitalWrite(LED_PIN, LOW);      // LED OFF
    while (button.isPressed())      // wait for button to be released
    {
        delay(10);                   // debounce the button release
        digitalWrite(LED_PIN, HIGH); // LED ON
    };
}