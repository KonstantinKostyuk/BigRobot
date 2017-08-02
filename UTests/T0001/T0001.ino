//T001

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