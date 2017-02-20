/**
 * Simple code for 
 * Single-axis Gyroscope Analog Gyro ENC-03RC
 * w/ FIR filtering
 * FIR-filtering isn't really needed, gyro already
 * has internal filtering, so better off using
 * Gyro_Basic instead. If you have Gyro+Accelerometer,
 * Then use a Complemenetary filter instead
 *
 * VCC: 5V or 3.3V
 * OUT: A0
 * REF:
 * GND: GND
 * 
 * Dont forget to connect the Analog Reference 
 * pin on the Arduino to 3.3V or 5V
 */

#include <FIR.h>

FIR fir;

const int gyroPin = A0;
int output = 0;

void setup() {
  Serial.begin(9600); 
  analogReference(EXTERNAL);

  // declare variables for coefficients
  // these should be calculated by hand, or using a tool
  // in case a phase linear filter is required, the coefficients are symmetric
  // for time optimization it seems best to enter symmetric values like below
  float coef[FILTERTAPS] = { 
    0.021, 0.096, 0.146, 0.096, 0.021   };

  fir.setCoefficients(coef);

  //declare gain coefficient to scale the output back to normal
  float gain = 0.56; // set to 1 and input unity to see what this needs to be
  fir.setGain(gain);
}

void loop() {
  int sensorValue = analogRead(gyroPin); 
  Serial.print(sensorValue);      
  Serial.print(" - ");      

  output = fir.process(sensorValue);
  Serial.println(output);      

  delay(1);        // delay in between reads for stability            
}






