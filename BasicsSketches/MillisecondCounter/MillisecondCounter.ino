
/*
  Example 37.1 - millis() demonstration
  http://tronixstuff.com/tutorials > chapter 37
  John Boxall | CC by-sa-nc
*/
 
unsigned long start, finished, elapsed;
 
void setup()
{
  Serial.begin(9600);
}
 
void loop()
{
  Serial.println("Start...");
  start=millis();
  delay(1000);
  finished=millis();
  Serial.println("Finished");
  elapsed=finished-start;
  Serial.print(elapsed);
  Serial.println(" milliseconds elapsed");
  Serial.println();
  delay(500);
}
