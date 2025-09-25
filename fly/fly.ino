// // DROITE => mauvais sens
// const int INAD = 33; //INA corresponds to IN+
// const int INBD = 32; //INB corresponds to IN-

// // GAUCHE => bon sens
// const int INAG = 26; //INA corresponds to IN+
// const int INBG = 25; //INB corresponds to IN-

// const int freq = 1000;
// const int resolution = 12; // passé de 8 à 12 ^cq trop rapide

// void setup() {
//     Serial.begin(115200);
//     Serial.println("coucou je démarre");

//     ledcAttach(INBD, freq, resolution); // associe PWM directement à la pin
//     pinMode(INAD, OUTPUT);

//     ledcAttach(INAG, freq, resolution); // associe PWM directement à la pin
//     pinMode(INBG, OUTPUT);

//     Serial.println("coucou je suis prêt");
// }

// void loop() {
//     // Turn counterclockwise
//     Serial.println("vroom avion");

//     digitalWrite(INAD, LOW);        // fixe le sens
//     ledcWrite(INBD, 900);           // vitesse (0–255)
//     digitalWrite(INBG, LOW);        // fixe le sens
//     ledcWrite(INAG, 900);           // vitesse (0–255)
//     delay(2000);

//     // Serial.println("stop");
//     // ledcWrite(INBD, 0);    
//     // ledcWrite(INAG, 0);           // arrêt
//     // delay(2000);
// }


// DROITE => mauvais sens
const int INAD = 33; // INA corresponds to IN+  (PWM possible)
const int INBD = 32; // INB corresponds to IN-  (direction)

// GAUCHE => bon sens
const int INAG = 26; // INA corresponds to IN+  (PWM possible)
const int INBG = 25; // INB corresponds to IN-  (direction)

const int freq = 300;        // <-- teste 100, 200, 300, 500, 1000
const int resolution = 12;   // 12 bits -> 0..4095
const int pwmMax = (1 << resolution) - 1; // 4095

// Paramètres pour aider le démarrage à faibles vitesses
const int minRunThreshold = 900; // en pratique tu disais ~900 => garde ce seuil comme repère
const int kickValue = pwmMax;    // valeur "coup de pouce" (plein)
const int kickTimeMs = 60;       // durée du coup (ms) : 30..200 selon moteur
const int rampStep = 100;        // pas d'incrément pendant le ramp (en unités PWM)
const int rampDelayMs = 30;      // délai entre incréments pendant le ramp

void setup() {
  Serial.begin(115200);
  Serial.println("coucou je démarre");

  // Moteur droit : PWM sur INAD, direction via INBD
  ledcAttach(INAD, freq, resolution);
  pinMode(INBD, OUTPUT);

  // Moteur gauche : PWM sur INAG, direction via INBG
  ledcAttach(INAG, freq, resolution);
  pinMode(INBG, OUTPUT);

  Serial.println("coucou je suis prêt");
}

// met la direction et applique la vitesse en % (0..100)
// percent -> 0..100
void setSpeed(int pin_pwm, int pin_dir, int percent) {
  if (percent <= 0) {
    // arrêt
    ledcWrite(pin_pwm, 0);
    return;
  }
  if (percent > 100) percent = 100;

  // calcule target PWM sur 0..pwmMax
  int target = (long)percent * pwmMax / 100;

  // si target est faible et inférieur au seuil minimal de démarrage,
  // on lance un kick puis on rampe doucement vers la valeur cible
  if (target > 0 && target < minRunThreshold) {
    // bouton d'aide : court coup à pleine puissance
    ledcWrite(pin_pwm, kickValue);
    delay(kickTimeMs);

    // descendre vers la valeur cible en rampant (évite de "sauter")
    int current = kickValue;
    while (current > target) {
      current -= rampStep;
      if (current < target) current = target;
      ledcWrite(pin_pwm, current);
      delay(rampDelayMs);
    }
  } else {
    // valeur suffisante : on écrit directement
    ledcWrite(pin_pwm, target);
  }
}

void loop() {
  Serial.println("Test vitesse très basse (10%)");
  // Sens avant : ici LOW comme tu avais (ajuste si nécessaire)
  digitalWrite(INBD, LOW);
  digitalWrite(INBG, LOW);
  setSpeed(INAD, INBD, 50); // 10% pour moteur droit
  setSpeed(INAG, INBG, 50); // 10% pour moteur gauche
  delay(3000);

  Serial.println("Test vitesse encore plus petite (5%)");
  setSpeed(INAD, INBD, 20);
  setSpeed(INAG, INBG, 20);
  delay(3000);

  // Serial.println("Test stop");
  // setSpeed(INAD, INBD, 0);
  // setSpeed(INAG, INBG, 0);
  // delay(3000);
}
