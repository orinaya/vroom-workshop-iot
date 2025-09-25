const int INA2 = 26; //INA corresponds to IN+
const int INB2 = 25;  //INB corresponds to IN-

// const int INA2 = 33; //INA corresponds to IN+
// const int INB2 = 32;  //INB corresponds to IN-

void setup() {
    Serial.begin(115200);
    Serial.println("coucou je démarre");

    pinMode(INA2, OUTPUT);
    pinMode(INB2, OUTPUT);
    Serial.println("coucou je suis prêt");
}

void loop() {
  //Turn counterclockwise
    Serial.println("vroom avion");
    digitalWrite(INA2, HIGH);
    digitalWrite(INB2, LOW);
    delay(2000);

    Serial.println("vroom autre sens");
    digitalWrite(INB2, HIGH);
    digitalWrite(INA2, LOW);
    delay(2000);

    Serial.println("vroom avion");
    digitalWrite(INA2, HIGH);
    digitalWrite(INB2, LOW);
    delay(2000);

    Serial.println("vroom autre sens");
    digitalWrite(INB2, HIGH);
    digitalWrite(INA2, LOW);
    delay(2000);
}