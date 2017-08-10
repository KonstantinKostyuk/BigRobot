//T0003 - Test

// Pololu Github - https://github.com/pololu/qtr-sensors-arduino
#include <QTRSensors.h>

// --- define PINS
#define L_QTR_PIN               2  // A2
#define R_QTR_PIN               3  // A3

#define NUM_SENSORS             2  // number of sensors used
#define NUM_SAMPLES_PER_SENSOR  4  // average 4 analog samples per sensor reading

// --- define Variables
unsigned int sensorValues[NUM_SENSORS];

// --- define Objects
QTRSensorsAnalog qtra((unsigned char[]) {L_QTR_PIN, R_QTR_PIN}, NUM_SENSORS, NUM_SAMPLES_PER_SENSOR);

void setup()
{
  Serial.begin(9600); // set the data rate in bits per second for serial data transmission
  delay(500);
  Serial.println('Start QTR test');
}

void loop()
{
    Serial.print(' L = ');
    Serial.print(sensorValues[0]);
    Serial.print(' R = ');
    Serial.print(sensorValues[1]);
    Serial.println();

    delay(500);
}