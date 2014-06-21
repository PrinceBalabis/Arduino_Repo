#include "Arduino.h"
#include "Wire.h"
 
#define MPU6050_DEVICE_ADDRESS   0x68
#define MPU6050_RA_ACCEL_XOUT_H  0x3B
#define MPU6050_RA_PWR_MGMT_1    0x6B
#define MPU6050_PWR1_SLEEP_BIT   6
 
class MPU6050 {
public:
  MPU6050();
  void wakeup();
  void read6dof(int* ax, int* ay, int* az, int* gx, int* gy, int* gz);
 
private:
  byte id;
  byte buffer[14];
  void readByte(byte reg, byte *data);
  void readBytes(byte reg, byte len, byte *data);
  void writeBit(byte reg, byte num, byte data);
  void writeByte(byte reg, byte data);
};