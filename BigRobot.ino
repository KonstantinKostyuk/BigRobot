//T0005 - Test

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

// --- define PINS
#define LED_PIN 13
#define BUTTON_PIN 11
#define RC_START 3 //Remote Controll(StertModule)
#define RC_KILL 5  //Remote Controll(StertModule)
#define XSHUT_pin2 16 //VL53L0X power controll pin
#define XSHUT_pin1 17 //VL53L0X power controll pin

//VL53L0X ADDRESS_DEFAULT 0b0101001 or 41
//#define Sensor1_newAddress 41 not required address change
#define Sensor2_newAddress 42
#define Sensor3_newAddress 43

//rotation direction
#define RIGHT 0
#define LEFT 1

// --- define Variables
// Speed: 0 is stopped, 400 is full speed, -400 reverce 
int FULL_SPEED = 400;         //MAX motor speed
int m1Speed = FULL_SPEED / 2; //Initially motor speed
int m2Speed = FULL_SPEED / 2; //Initially motor speed
int REVERSE_SPEED = 200;      //Reverse motor speed
int TURN_SPEED = 250;         //Turn motor 
int FORWARD_SPEED = 250;      //Forward motor speed
int STOP = 0;                 //Stop motor
int Border_Distance = 1200;    //MAX distance, if bigger = error = 0


//Variables 
int PS0, PS1, PS2;      //Robot detection(Proximity sensor) vars
byte RDM;                //Robot detection Matrix
byte First_RDM=B10101010;//Robot detection Matrix, loop before
byte buttonState = 0;    //Start buttun
byte RC_Start_State = 0; //Start Module satart state
byte RC_Stop_State = 0;  //Kill Module satart state 
byte goPressed = 0;      //button pressed once
byte goStart = 0;        //started once
byte rotation = LEFT;    //defult rotation to left

// --- define Objects
Pushbutton button(BUTTON_PIN); // button create and init
DualVNH5019MotorShield motors; // MotorDriver create
VL53L0X Sensor1;               //VL53L0X Sensor
VL53L0X Sensor2;               //VL53L0X Sensor
VL53L0X Sensor3;               //VL53L0X Sensor


void RDMprint()
{
Serial.print("PS0:");
Serial.print(PS0);
Serial.print(", PS1:");
Serial.print(PS1);
Serial.print(", PS2:");
Serial.print(PS2);
Serial.print(", Start:");
Serial.print(RC_Start_State);
//Serial.print(", Stop:");
//Serial.print(RC_Stop_State);
Serial.print(" = ");
Serial.println(RDM, BIN);
};

void SensorsRead()
{
  // --- Read Proximity sensors 
  PS0=Sensor1.readRangeContinuousMillimeters();
  PS1=Sensor2.readRangeContinuousMillimeters();
  PS2=Sensor3.readRangeContinuousMillimeters();

  if ((PS0 == -1) && (PS1 == -1) && (PS2 == -1))
    {
      init_Sensors();
    };
    
  
  // --- check if sensor val into condition
  boolean BPS0 = 10 < PS0 && PS0 < Border_Distance;
  boolean BPS1 = 10 < PS1 && PS1 < Border_Distance;
  boolean BPS2 = 10 < PS2 && PS2 < Border_Distance;

  // --- Read Start-Stop astates
  RC_Start_State = digitalRead(RC_START);
  RC_Stop_State = digitalRead(RC_KILL);

  RDM=0xFF;
  RDM=RDM<<1|1;  
  RDM=RDM<<1|1;
  RDM=RDM<<1|1;
  RDM=RDM<<1|1;
  RDM=RDM<<1|!BPS2;
  RDM=RDM<<1|!BPS1;
  RDM=RDM<<1|!BPS0;
  RDM=RDM<<1|!RC_Start_State;
//  RDM=RDM<<1|!RC_Stop_State;
  RDM=~RDM;
};
 
void init_Sensors()
{
// --- Init I2C bus
Wire.begin();
Serial.println("Wire.begin");

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

void setup()
{   
  Serial.begin(115200);
  Serial.println("rotation = LEFT");
 
  //Shutdown pins of VL53L0X ACTIVE-LOW-ONLY NO TOLERANT TO 5V will fry them
  pinMode(XSHUT_pin2, OUTPUT);
  pinMode(XSHUT_pin1, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(RC_START, INPUT);
  pinMode(RC_KILL, INPUT);
    
  digitalWrite(LED_PIN, LOW);
  motors.init();                 // MotorDriver init
  Serial.println("motors.init");

  init_Sensors();
  Serial.println("setup done!");
}

void loop()
{
SensorsRead();

  
buttonState = button.isPressed();
if ((goPressed != HIGH) and (buttonState == HIGH))
  {
    goPressed = 1; //set to High after first press    
    rotation = RIGHT;
    Serial.println("rotation = RIGHT");
  };
digitalWrite(LED_PIN, rotation);

    
if (First_RDM != RDM)//If no changes into RDM, do nothing
  {
    RDMprint(); //debug output of Sharp reading
    First_RDM = RDM;//Save current RDM
    switch(RDM){//Main case, as FSM serch current state of RDM
    case B00001111://Go forward
      motors.setSpeeds(FULL_SPEED, FULL_SPEED); 
      Serial.println("Forward");
    break;
    case B00000011://Go rotate left
      motors.setSpeeds(0, FULL_SPEED); 
      Serial.println("Fast Left");
      rotation=LEFT;
      break;
    case B00000111://Go rotate left
      motors.setSpeeds(FORWARD_SPEED, FULL_SPEED); 
      Serial.println("Left");
      rotation=LEFT;   
    break;
    case B00001001://Go rotate right
      motors.setSpeeds(FULL_SPEED, 0);
      Serial.println("Fast Right");
      rotation=RIGHT;
    break;
    case B00001101://Go rotate right
      motors.setSpeeds(FULL_SPEED, FORWARD_SPEED); 
      Serial.println("Right");
      rotation=RIGHT;
    break;
    case B00001000:
    case B00000010:
    case B00001110:
    case B00000000:    
      motors.setSpeeds(STOP, STOP); 
      Serial.println("Stop");
      rotation=RIGHT;
    break;    
    default:
      switch(rotation){
        if (RC_Start_State == HIGH)//Start then RC_Start pin HIGH, Kill pin LOW
        {     
        switch(rotation){
            case LEFT: motors.setSpeeds(-TURN_SPEED, TURN_SPEED); break;
            case RIGHT: motors.setSpeeds(TURN_SPEED, -TURN_SPEED);break;  
          };
      };
    };
    Serial.println("Find");
  };
};
}