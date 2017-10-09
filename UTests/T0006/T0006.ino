//T0006 - Test 6 VL53L0X

// Pololu Github - https://github.com/pololu/dual-vnh5019-motor-shield/
#include <DualVNH5019MotorShield.h>
// Pololu Github - https://github.com/pololu/vl53l0x-arduino
#include <VL53L0X.h>
// Pololu Github - https://github.com/pololu/qtr-sensors-arduino
#include <QTRSensors.h>
// Pololu Github - https://github.com/pololu/pushbutton-arduino
#include <Pushbutton.h>
// I2C library
#include <Wire.h>

//#define XSHUT_pin3 not required for address change
#define XSHUT_pin1 16
#define XSHUT_pin2 17


// HIGH_SPEED - at the cost of lower accuracy
#define HIGH_SPEED

//ADDRESS_DEFAULT 0b0101001 or 41
//#define Sensor1_newAddress 41 not required address change
#define Sensor2_newAddress 42
#define Sensor3_newAddress 43

int PS0, PS1, PS2;      //Robot detection(Proximity sensor) vars
int Border_Distance = 1200;    //MAX distance, if bigger = error = 0
byte RDM;               //Robot detection Matrix

VL53L0X Sensor1; //Right
VL53L0X Sensor2; //Center
VL53L0X Sensor3; //Left


void setup()
{ /*WARNING*/
  //Shutdown pins of VL53L0X ACTIVE-LOW-ONLY NO TOLERANT TO 5V will fry them
  pinMode(XSHUT_pin2, OUTPUT);
  pinMode(XSHUT_pin1, OUTPUT);
  
  Serial.begin(115200);

  // --- Init I2C bus
  Wire.begin();

  // --- Power up, change addres and init 3x VL53L0X sensors
  //Sensor3 is powered, change address of Sensor3 and power up next one
  Sensor3.setAddress(Sensor3_newAddress);
  //Activate(power up) next Sensor2 and change address
  pinMode(XSHUT_pin2, INPUT);//For power-up procedure t-boot max 1.2ms "Datasheet: 2.9 Power sequence"
  delay(10);
  Sensor2.setAddress(Sensor2_newAddress);
  //Activate(power up) next Sensor1, address not change 41
  pinMode(XSHUT_pin1, INPUT);
  delay(10);
  
  // Init 3x Sensors
  Sensor1.init();
  Sensor2.init();
  Sensor3.init();
 
  // Set setTimeout 3x Sensors
  Sensor1.setTimeout(500);
  Sensor2.setTimeout(500);
  Sensor3.setTimeout(500);

  // Set LONG_RANGE(about 2000mm) 3x Sensors
  // LONG_RANGE - increases the sensitivity of the sensor and extends its potential range to 2000 mm
  // --- Sensor1
  // lower the return signal rate limit (default is 0.25 MCPS)
  Sensor1.setSignalRateLimit(0.1);
  // increase laser pulse periods (defaults are 14 and 10 PCLKs)
  Sensor1.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
  Sensor1.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
  // --- Sensor2
  Sensor2.setSignalRateLimit(0.1);
  Sensor2.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
  Sensor2.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
  // --- Sensor3
  Sensor3.setSignalRateLimit(0.1);
  Sensor3.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
  Sensor3.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);

  // Set HIGH_SPEED 3x Sensors
  // HIGH_SPEED - at the cost of lower accuracy
  // reduce timing budget to 20 ms (default is about 33 ms)
  Sensor1.setMeasurementTimingBudget(20000);
  Sensor2.setMeasurementTimingBudget(20000);
  Sensor3.setMeasurementTimingBudget(20000);

  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. sensor.startContinuous(100)).
  Sensor1.startContinuous();
  Sensor2.startContinuous();
  Sensor3.startContinuous();
}

void loop()
{
  // --- Read Proximity sensors 
PS0=Sensor1.readRangeContinuousMillimeters();
PS1=Sensor2.readRangeContinuousMillimeters();
PS2=Sensor3.readRangeContinuousMillimeters();

// --- check if sensor val into condition
boolean BPS0 = 0 < PS0 && PS0 < Border_Distance;
boolean BPS1 = 0 < PS1 && PS1 < Border_Distance;
boolean BPS2 = 0 < PS2 && PS2 < Border_Distance;

  RDM=0xFF;
  RDM=RDM<<1|1;  
  RDM=RDM<<1|1;
  RDM=RDM<<1|1;
  RDM=RDM<<1|1;
  RDM=RDM<<1|!BPS2;
  RDM=RDM<<1|!BPS1;
  RDM=RDM<<1|!BPS0;
  RDM=RDM<<1|!0;
  RDM=~RDM;

  Serial.print("PS0:");
  Serial.print(PS0);
  Serial.print(", PS1:");
  Serial.print(PS1);
  Serial.print(", PS2:");
  Serial.print(PS2);
  Serial.print(" = ");
  Serial.println(RDM, BIN);
}
