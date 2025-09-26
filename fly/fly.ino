#include <ezButton.h>
// #include <TM1637Display.h>

// DROITE => mauvais sens
const int INBG= 13; //INA corresponds to IN+
const int INAG = 12; //INB corresponds to IN-

const int INBD = 26; //INA corresponds to IN+
const int INAD = 25; //INB corresponds to IN-

ezButton button(18);
const int Y = 35; // Y
const int X = 34; // X

const int greenD = 21;
const int yellowD = 22;
const int redD = 23;

const int greenG = 4;
const int yellowG = 16;
const int redG = 17;

// const int dio = 2;
// const int clk = 15;

// TM1637Display display = TM1637Display(clk, dio);

int valueX = 0;
int valueY = 0;

int vitesse = 0;

int loopButton = 0;

const int freq = 1000;
const int resolution = 12; // passé de 8 à 12 ^cq trop rapide

void setup() {
    Serial.begin(115200);
    Serial.println("coucou je démarre");

    ledcAttach(INBD, freq, resolution); // associe PWM directement à la pin
    ledcAttach(INAD, freq, resolution); // associe PWM directement à la pin
    ledcAttach(INAG, freq, resolution); // associe PWM directement à la pin
    ledcAttach(INBG, freq, resolution); // associe PWM directement à la pin

    // servo.attach(15);
    // servo.setPeriodHertz(50);
    // servo.attach(15, 500, 2400); // Largeur minimale et maximale de l'impulsion (en µs) pour aller de 0° à 180°

    // display.clear();
    // display.setBrightness(5);

    pinMode(Y, INPUT);
    pinMode(X, INPUT);

    pinMode(redG, OUTPUT);
    pinMode(yellowG, OUTPUT);
    pinMode(greenG, OUTPUT);

    pinMode(redD, OUTPUT);
    pinMode(yellowD, OUTPUT);
    pinMode(greenD, OUTPUT);

    Serial.println("coucou je suis prêt");

    delay(5000);
    digitalWrite(redG, HIGH);
    digitalWrite(redD, HIGH);
    delay(500);
    digitalWrite(redG, LOW);
    digitalWrite(redD, LOW);
    delay(500);
    digitalWrite(redG, HIGH);
    digitalWrite(redD, HIGH);
    delay(500);
    digitalWrite(redG, LOW);
    digitalWrite(redD, LOW);
    delay(500);
    digitalWrite(redG, HIGH);
    digitalWrite(redD, HIGH);
    delay(500);
    digitalWrite(redG, LOW);
    digitalWrite(redD, LOW);
    delay(500);
    digitalWrite(yellowG, HIGH);
    digitalWrite(yellowD, HIGH);
    delay(500);
    digitalWrite(yellowG, LOW);
    digitalWrite(yellowD, LOW);
    delay(500);
    
    digitalWrite(greenG, HIGH);
    digitalWrite(greenD, HIGH); 
    delay(500);
    digitalWrite(greenG, LOW);
    digitalWrite(greenD, LOW); 
}

void loop() {
  // display.showNumberDec(1234);
  Serial.println("vroom avion");

  button.loop(); // MUST call the loop() function first
  int btnState = button.getState();

  if(btnState == 1){
    loopButton += 1;
    delay(1000);
    Serial.println("button pressed");
  }

  switch(loopButton){
    case 1:
      Serial.println("loop 1");
      digitalWrite(redG, HIGH);
      digitalWrite(redD, HIGH); 
      break;
    case 2:
      Serial.println("loop 2");
      digitalWrite(redG, LOW);
      digitalWrite(redD, LOW); 
      digitalWrite(yellowG, HIGH);
      digitalWrite(yellowD, HIGH); 
      break;
    case 3:
    Serial.println("loop 3");
      digitalWrite(yellowG, LOW);
      digitalWrite(yellowD, LOW); 
      digitalWrite(greenG, HIGH);
      digitalWrite(greenD, HIGH); 
      break;
    case 4:
      digitalWrite(greenG, LOW);
      digitalWrite(greenD, LOW);
      digitalWrite(redG, HIGH);
      digitalWrite(redD, HIGH);
      delay(200);
      digitalWrite(redG, LOW);
      digitalWrite(redD, LOW); 
      digitalWrite(yellowG, HIGH);
      digitalWrite(yellowD, HIGH);
      delay(200);
      digitalWrite(yellowG, LOW);
      digitalWrite(yellowD, LOW); 
      digitalWrite(greenG, HIGH);
      digitalWrite(greenD, HIGH); 
      delay(200);
      break;
    case 5:
      digitalWrite(greenG, LOW);
      digitalWrite(greenD, LOW);
      loopButton = 0;
      break;
    default:
    Serial.println("rien");
    break;
  }
 
  valueX = analogRead(X);
  valueY = analogRead(Y);

  if(valueX>2500){
    vitesse = valueX - 2400;
    ledcWrite(INBD, vitesse);
    ledcWrite(INBG, vitesse);
    digitalWrite(greenG, HIGH);
    digitalWrite(greenD, HIGH); 
  }
  else if(valueX<1600){
    vitesse = 1600 - valueX;
    ledcWrite(INAD, vitesse);
    ledcWrite(INAG, vitesse);
    digitalWrite(redG, HIGH);
    digitalWrite(redD, HIGH);
  }
  else{
    digitalWrite(greenG, LOW);
    digitalWrite(greenD, LOW);
    digitalWrite(redG, LOW);
    digitalWrite(redD, LOW);
    ledcWrite(INBD, 0);
    ledcWrite(INAD, 0);
    ledcWrite(INBG, 0);
    ledcWrite(INAG, 0);
  }

  if(valueY>2500){
    vitesse = valueY - 2400;
    ledcWrite(INAG, vitesse);
    digitalWrite(yellowD, HIGH);
  }
  else if(valueY<1600){
    vitesse = 1600 - valueY;
    ledcWrite(INAD, vitesse);
    digitalWrite(yellowG, HIGH);
  }
  else{
    digitalWrite(yellowG, LOW);
    digitalWrite(yellowD, LOW);
  }
}

