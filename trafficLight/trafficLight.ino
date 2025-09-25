const int PIN_RED = 4;
const int PIN_YELLOW = 16;
const int PIN_GREEN = 17;

const int RED_TIME = 4000;
const int YELLOW_TIME = 4000;
const int GREEN_TIME = 4000;

void setup() {
  Serial.begin(115200);
  Serial.println("coucou je démarre");
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_YELLOW, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  // red light on
  Serial.println("rouge");
  digitalWrite(PIN_RED, HIGH);   // turn on
  digitalWrite(PIN_YELLOW, LOW); // turn off
  digitalWrite(PIN_GREEN, LOW);  // turn off
  delay(RED_TIME); // keep red light on during a period of time

  Serial.println("jaune");
  digitalWrite(PIN_RED, LOW);    // turn off
  digitalWrite(PIN_YELLOW, HIGH); // turn on
  digitalWrite(PIN_GREEN, LOW); // turn off
  delay(YELLOW_TIME); // keep yellow light on during a period of time

  Serial.println("vert");
  digitalWrite(PIN_RED, LOW);    // turn off
  digitalWrite(PIN_YELLOW, LOW); // turn off
  digitalWrite(PIN_GREEN, HIGH); // turn on
  delay(GREEN_TIME); // keep green light on during a period of time
}
