int en1 = 2;
int en2 = 3;
int a = 12;
int b = 11;
int c = 10;
int d = 9;

void setup() {
  pinMode(en1, OUTPUT);
  pinMode(en2, OUTPUT);
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  digitalWrite(en1, HIGH);
  digitalWrite(en2, HIGH);
}

void loop() {
  forward();
  delay(1500);
  turnRight();
  delay(1500);
  backwards();
  delay(1500);
  turnLeft();
  delay(1500);
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
