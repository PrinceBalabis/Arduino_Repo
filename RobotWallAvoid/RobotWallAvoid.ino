int en1 = 2;
int en2 = 3;
int a = 8;
int b = 9;
int c = 12;
int d = 13;

#define echoPin 5 // Echo Pin
#define trigPin 6 // Trigger Pin

int minimumRange = 10;
long duration, distance; // Duration used to calculate distance


void setup() {
  // Motors setup
  pinMode(en1, OUTPUT);
  pinMode(en2, OUTPUT);
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  digitalWrite(en1, HIGH);
  digitalWrite(en2, HIGH);


  // Distance Sensor setup
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  /* The following trigPin/echoPin cycle is used to determine the
   distance of the nearest object by bouncing soundwaves off of it. */
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  //Calculate the distance (in cm) based on the speed of sound.
  distance = duration / 58.2;

  if (distance <= minimumRange) {
    turnRight();
    delay(1000);
  }
  else {
    forward();
  }
}

void forward() {
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
}

void backwards() {
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
}

void turnRight() {
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
}

void turnLeft() {
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
}
