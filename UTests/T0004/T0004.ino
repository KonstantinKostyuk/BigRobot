//T0003 - Test

#include <Wire.h>
// Pololu Github - https://github.com/pololu/vl53l0x-arduino
#include <VL53L0X.h>

// --- define Objects
VL53L0X sensor;

// --- Configuration Setup

// LONG_RANGE - increases the sensitivity of the sensor and extends its potential range to 2000 mm
#define LONG_RANGE


// Uncomment ONE of these two lines to get
// - higher speed at the cost of lower accuracy OR
// - higher accuracy at the cost of lower speed

#define HIGH_SPEED
//#define HIGH_ACCURACY


void setup()
{
  Serial.begin(9600);
  Wire.begin();

  sensor.init();
  sensor.setTimeout(500);

#if defined LONG_RANGE
  // lower the return signal rate limit (default is 0.25 MCPS)
  sensor.setSignalRateLimit(0.1);
  // increase laser pulse periods (defaults are 14 and 10 PCLKs)
  sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
  sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
#endif

#if defined HIGH_SPEED
  // reduce timing budget to 20 ms (default is about 33 ms)
  sensor.setMeasurementTimingBudget(20000);
#elif defined HIGH_ACCURACY
  // increase timing budget to 200 ms
  sensor.setMeasurementTimingBudget(200000);
#endif
}

void loop()
{
  Serial.print(millis());
  Serial.print(' - ');
  Serial.print(sensor.readRangeSingleMillimeters());
  if (sensor.timeoutOccurred()) { Serial.print("Sensor TIMEOUT"); }

  Serial.println();
}