int DO=2;  //Pin for Digital Output - DO
int DA=A0;  // Pin for Analog Output - AO
int led = 13;
int threshold = 497; //Change this
int sensorvalue=0;

void setup(){
  Serial.begin(9600);
  pinMode(led, OUTPUT);     
}

void loop(){
  sensorvalue = analogRead(DA);  //Read the analog value
  Serial.print("Analog: ");  
  Serial.print(sensorvalue);  //Print the analog value
  Serial.print("  ");
  Serial.print("Digital: ");
  Serial.println(digitalRead(DO));  //Print the digital value

  if(sensorvalue >= threshold){  //Compare analog value with threshold 
    digitalWrite(led, HIGH);  //Turn ON Led
  }  
  else{
    digitalWrite(led, LOW);  //Turn OFF Led
  }
}
