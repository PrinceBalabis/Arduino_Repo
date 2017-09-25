
/*
  Microsecond counter
*/
 
unsigned long start, finished, elapsed;
 
void setup()
{
  Serial.begin(9600);
}
 
void loop()
{
  Serial.println("Start...");
  start=micros();
  delay(1000);
  finished=micros();
  Serial.println("Finished");
  elapsed=finished-start;
  Serial.print(elapsed);
  Serial.println(" microseconds elapsed");
  Serial.println();
  delay(500);
}
