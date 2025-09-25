#include <Stepper.h>// librairie Stepper

const int stepsPerRevolution = 2048;

const int Pin1 = 5;
const int Pin2 = 18;
const int Pin3 = 19;
const int Pin4 = 21;

Stepper myStepper(stepsPerRevolution, Pin1, Pin2, Pin3, Pin4); // instance objet stepper

void setup()
{
   myStepper.setSpeed(10); // speed
   Serial.begin(115200);
}

void loop()
{
//step() => fonction pour rotate le moteur 
    // Serial.println("clockwise");
    Serial.println("vroom");
    myStepper.step(stepsPerRevolution);
    // delay(1000);

    // Serial.println("counterclockwise");
    // myStepper.step(-stepsPerRevolution);
    // delay(1000);
}


