/*
  Funktion: Steuerung des Kettenfahrzeuges nach vorne, links und rechts
  Programierer: Ole Riehemann
  letzte Änderung: 10.11.2020
  Version: 0.0.1
  Bibliothek: AlignedJoy.h
  Hardware: 2x Motor 12V, PWM driver, Arduino UNO

*/


/*********Bibliothek-Einstellung*****/

#include <AlignedJoy.h>


//********* Joystick *********/

#define PIN_JOY1_X   0  //(up  down)
#define PIN_JOY1_Y   1  //(left  right)

AlignedJoy joystick_1(PIN_JOY1_X, PIN_JOY1_Y);
byte valXpos;
byte valXneg;
byte valYpos;
byte valYneg;
int motor1x = 0;   // Motor Links
int motor1y = 0;
int motor2x = 0; // Motor Rechts
int motor2y = 0;


#define motor1Richtung 5  // dir1
#define motor1Speed 6      // pwm1
#define motor2Richtung 9  // dir2
#define motor2Speed 10     //pwm2


void setup()
{
  pinMode(motor1Richtung, OUTPUT);
  pinMode(motor1Speed, OUTPUT);
  pinMode(motor2Richtung, OUTPUT);
  pinMode(motor2Speed, OUTPUT);

  Serial.begin(9600);
}


void loop()
{
  werte_Umrechnen();         // springe zu Void..

  motor1x = valXpos - (valYneg / 2);

  if (motor1x < 0)
  {
    byte motor1xtemp = motor1x * (-1);
    digitalWrite(motor1Richtung, LOW);
    analogWrite(motor1Speed, motor1xtemp);
    //Serial.println(motor1xtemp);
  }
  else
  {
    digitalWrite(motor1Richtung, HIGH);
    analogWrite(motor1Speed, motor1x);
    //Serial.println(motor1x);
  }

  motor2x = valXpos - (valYpos / 2);
  
  if (motor2x < 0)
  {
    byte motor2xtemp = motor2x * (-1);
    digitalWrite(motor2Richtung, LOW);
    analogWrite(motor2Speed, motor2xtemp);
    Serial.println(motor2xtemp);
  }
  else
  {
    digitalWrite(motor2Richtung, HIGH);
    analogWrite(motor2Speed, motor2x);
    Serial.println(motor2x);
  }

  delay(100);
}


void werte_Umrechnen()   // jeder Bereich von X/Y wird ausgelesen und  bekommt einen Wert von 0-255 zugewiesen // durch constrain begrenzt
{
  valXpos = constrain( map (joystick_1.read(X) / 2, 253, 511, 0, 255), 0, 255);    // Stick nach oben
  valXneg = constrain( map (joystick_1.read(X) / 2, 250, 0, 0, 255), 0, 255);      // Stick nach unten
  valYpos = constrain( map (joystick_1.read(Y) / 2, 253, 511, 0, 255), 0, 255);    // Stick nach links
  valYneg = constrain( map (joystick_1.read(Y) / 2, 250, 0, 0, 255), 0, 255);      // Stick nach rechts
}
