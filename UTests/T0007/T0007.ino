
int PS0, PS1, PS2;      //Robot detection(Proximity sensor) vars
byte RDM;               //Robot detection Matrix
int Border_Distance = 1200;    //MAX distance, if bigger = error = 0

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  PS0 = 300;
  PS1 = 600;
  PS2 = 8100;

  // --- check if sensor val into condition
boolean BPS0 = 0 < PS0 && PS0 < Border_Distance;
boolean BPS1 = 0 < PS1 && PS1 < Border_Distance;
boolean BPS2 = 0 < PS2 && PS2 < Border_Distance;


  RDM=0xFF;
  RDM=RDM<<1|1;
  RDM=RDM<<1|1;
  RDM=RDM<<1|1;
  RDM=RDM<<1|!BPS2;
  RDM=RDM<<1|!BPS1;
  RDM=RDM<<1|!BPS0;
  RDM=RDM<<1|!0;
  RDM=RDM<<1|!0;
  RDM=~RDM;

  Serial.print("BPS0:");
  Serial.print(BPS0);
  Serial.print(", BPS1:");
  Serial.print(BPS1);
  Serial.print(", BPS2:");
  Serial.print(BPS2);
  Serial.print(" = ");
  Serial.println(RDM, BIN);
  
  Serial.print("PS0:");
  Serial.print(PS0);
  Serial.print(", PS1:");
  Serial.print(PS1);
  Serial.print(", PS2:");
  Serial.print(PS2);
  Serial.print(" = ");
  Serial.println(RDM, BIN);
  delay(1000);

}
