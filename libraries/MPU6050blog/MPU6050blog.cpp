#include "MPU6050blog.h"
 
MPU6050::MPU6050() {
  id = MPU6050_DEVICE_ADDRESS;
}
 
/* Wake up device and use default values for
 accelerometer (±2g) and gyroscope (±250°/sec). */
void MPU6050::wakeup() {
  writeBit(MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_SLEEP_BIT, 0);
}
 
/* Read device memory to extract current
 accelerometer and gyroscope values. */
void MPU6050::read6dof(int* ax, int* ay, int* az, int* gx, int* gy, int* gz) {
  readBytes(MPU6050_RA_ACCEL_XOUT_H, 14, buffer);
  *ax = (((int)buffer[0]) << 8) | buffer[1];
  *ay = (((int)buffer[2]) << 8) | buffer[3];
  *az = (((int)buffer[4]) << 8) | buffer[5];
  *gx = (((int)buffer[8]) << 8) | buffer[9];
  *gy = (((int)buffer[10]) << 8) | buffer[11];
  *gz = (((int)buffer[12]) << 8) | buffer[13];
}
 
/* Read a single byte from specified register. */
void MPU6050::readByte(byte reg, byte *data) {
  readBytes(reg, 1, data);
}
 
/* Read multiple bytes starting at specified register. */
void MPU6050::readBytes(byte reg, byte len, byte *data) {
  byte count = 0;
  Wire.beginTransmission(id);
  Wire.write(reg);
  Wire.requestFrom(id, len);
  while (Wire.available()) data[count++] = Wire.read();
  Wire.endTransmission();
}
 
/* Write bit to specified register and location. */
void MPU6050::writeBit(byte reg, byte num, byte data) {
  byte b;
  readByte(reg, &b);
  b = (data != 0) ? (b | (1 << num)) : (b & ~(1 << num));
  writeByte(reg, b);
}
 
/* Write byte to specified register. */
void MPU6050::writeByte(byte reg, byte data) {
  Wire.beginTransmission(id);
  Wire.write(reg); 
  Wire.write(data);
  Wire.endTransmission(); 
}
