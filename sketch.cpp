#include "Arduino.h"
#include "HardwareSerial.h"
#include "Wire.h"

#define LEDPIN  14

char buf[100];
char ch;

double foo_double;

//  MPU-6050 Registers
#define MPU6050_ADDRESS          (uint8_t)0xD0
#define MPU6050_WHO_AM_I         (uint8_t)0x75

#define MPU6050_PWR_MGMT_1         0x6B   // R/W
#define MPU6050_PWR_MGMT_2         0x6C   // R/W

#define MPU6050_ACCEL_XOUT_H     (uint8_t)0x3B
#define MPU6050_ACCEL_XOUT_L     (uint8_t)0x3C

void mainmenu();

void setup()
{
  foo_double = 1.23456;
  foo_double = foo_double * 1.2;
  Serial.begin(9600);
  Wire.begin();
  pinMode(LEDPIN, OUTPUT);
  mainmenu();
}

void loop()
{

  if(Serial.available())
    {
      ch = Serial.read();

      Serial.println(ch);

      switch (ch)
	{
	case '1':
	  Serial.println("LED ON");
	  digitalWrite(LEDPIN, HIGH);
	  break;
	case '2':
	  Serial.println("LED OFF");
	  digitalWrite(LEDPIN, LOW);
	  break;
	case '3':
	  Serial.println("MPU6050 WHO_AM_I");
	  Wire.beginTransmission(MPU6050_ADDRESS);
	  Wire.requestFrom(MPU6050_WHO_AM_I,1);
	  Wire.endTransmission();
	  Serial.print(Wire.read());
	  break;
	case '4':
	  Serial.println("Clear sleep");
	  Wire.beginTransmission(MPU6050_ADDRESS);
	  Wire.write(MPU6050_PWR_MGMT_1);
	  Wire.write(0);
	  Wire.endTransmission();
	  break;
	case '5':
	  Serial.println("MPU6050 X-axis");
	  Wire.beginTransmission(MPU6050_ADDRESS);
	  Wire.requestFrom(MPU6050_ACCEL_XOUT_H,2);
	  Wire.endTransmission();
	  Serial.print("MPU6050 X axis: ");
	  Serial.println((int16_t)((Wire.read()) + (Wire.read()<<8)));
	  break;
	default:
	  break;
	}
      mainmenu();
    }
  
}

void mainmenu()
{
  Serial.println("Main Menu - Restrictor Plate v0.1");
  Serial.println("1.  LED ON");
  Serial.println("2.  LED OFF");
  Serial.println("3.  MPU6050 WHO_AM_I");
  Serial.println("4.  Clear sleep");
  Serial.println("5.  Read X");
  Serial.print("==> ");
}


