#include "Wire.h"
#include "MPU6050.h"
 
MPU6050 mpu;  
int ax, ay, az, gx, gy, gz;
float smooth_ax, smooth_ay, smooth_az;
 
void setup()
{
  Wire.begin();
  Serial.begin(38400);
  mpu.wakeup();  
}
 
void loop()
{
  /* Read device to extract current
   accelerometer and gyroscope values. */
  mpu.read6dof(&ax, &ay, &az, &gx, &gy, &gz);
 
  /* Apply low pass filter to smooth
   accelerometer values. */
  smooth_ax = 0.95 * smooth_ax + 0.05 * ax;
  smooth_ay = 0.95 * smooth_ay + 0.05 * ay;
  smooth_az = 0.95 * smooth_az + 0.05 * az;
 
  /* Output to serial monitor. */
  Serial.print(smooth_ax);
  Serial.print("\t");
  Serial.print(smooth_ay);
  Serial.print("\t");
  Serial.print(smooth_az);
  Serial.print("\t");
  Serial.print(gx);
  Serial.print("\t");
  Serial.print(gy);
  Serial.print("\t");
  Serial.println(gz);
}

