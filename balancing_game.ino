/* 
 This is a balancing game, made with an Arduino an accelerometer and some LEDs

 Put all the circuitry on a plank and put the plank on a tube, have your victim
 stand on the plank and make them balance, if they stay balanced for long enough
 the LEDs play the "win" animation, if they lose balance they lose all their progress.


 The score logic:
 * "counter" is set to the pin of the first LED, and is used to turn on the LEDs
 * state is set to 1, 1 = tilted, 0 = balanced

 * If you are balanced "state" is set to 0
 * While "state" is 0, set "counter" to HIGH and increment counter
   there is a 1 second delay in the while loop.
 * If you stay balanced till all the LEDs light up, do the "win" animation
   set state to 1 and reset counter to the pin of the first LED
 
 * If you lose your balance, the LEDs are turned off, state is set to 1
   and counter reset to the pin of the firs LED.


 This code only supports the MPU 6050 accelerometer/gyroscope sensor.
 Though porting it to other sensors should be pretty easy.

 This codes github repo: https://github.com/sit-on-cushions-we-must/balancing_game
 Wiring diagrams and stuff is here: 

 This code is licensed under the MIT license: https://mit-license.org/ 
*/

#include<Wire.h>

// the LEDs
const int led1 = 2;
const int led2 = 3;
const int led3 = 4;
const int led4 = 5;
const int led5 = 6;
const int led6 = 7;

const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcY; // used to store the accelerometer Y axis readings.

int state = 1; // used to store the state of the sensor, 1 = tilted, 0 = balanced.
int counter = 2; // used to light up the LEDs


void setup() {
  // power on and wake up the sensor
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

  Serial.begin(9600);
}


void loop() {
	// request readings from the sensor
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3D);  // starting with register 0x3D (ACCEL_YOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  // read the Y axis value
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)

  // for debugging
  Serial.print("AcY = "); Serial.println(AcY);


  /* 
   check if the sensor is balanced
   if it is set state to 0 if it isn't
   set state to 1 and turn off all the LEDs
  */
  if (AcY <= 8000 && AcY >= -8000) {
    state = 0;// set "state" to 0
    Serial.println("balanced");
  } else {
    // set state to 1
    Serial.println("tilted");
    state = 1;
    // reset counter
    counter = 2;
    // turn off all the LEDs
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
  }


  /*
   while the sensor is balanced,
   turn on the LEDs one after the other
  */
  while(state == 0) {
    digitalWrite(counter, HIGH);
    delay(1000);
    counter ++;
    break;
  }

  // if the sensor stays balanced for 6 seconds
  if (counter > 8) {
    // reset counter
    counter = 2;
    // set state to 1
    state = 1;
    // play the "you win" animation
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
    delay(300);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
    digitalWrite(led6, HIGH);
    delay(300);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
    delay(300);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
    digitalWrite(led6, HIGH);
    delay(300);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
  }
}