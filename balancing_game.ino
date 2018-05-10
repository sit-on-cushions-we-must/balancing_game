

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

	// request readings from the sensor
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3D);  // starting with register 0x3D (ACCEL_YOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers

  // read the Y axis value
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)

  Serial.print("AcY = "); Serial.println(AcY);

  if (AcY >= 10000 || AcY <= -10000)  {
    Serial.println("tilted");

    for (int i = 0; i < 7; ++i) {
      /* code */
    }
  }

  delay(333);
}
