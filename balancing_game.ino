

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

  int counter = led1; // used to count in the while loops and to turn on the LEDs

	// request readings from the sensor
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3D);  // starting with register 0x3D (ACCEL_YOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers

  // read the Y axis value
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)

  Serial.print("AcY = "); Serial.println(AcY);

  /* 
   as long as the accelerometer is realtively flat
   turn on the LEDs one after the other, and when all
   the LEDs are lit do a flashing "win" animation.
  */
  while(AcY <= 10000 || AcY >= -10000) {

    // turn on the LED at "counter"
    digitalWrite(counter, HIGH);

    if (counter >= led6) {

      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, HIGH);
      digitalWrite(led5, HIGH);
      digitalWrite(led6, HIGH);
      delay(500);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
      digitalWrite(led6, LOW);
      delay(500);
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, HIGH);
      digitalWrite(led5, HIGH);
      digitalWrite(led6, HIGH);
      delay(500);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
      digitalWrite(led6, LOW);
    } else {
      counter++; // increment the value of counter
    }
  }

  delay(333);
}
