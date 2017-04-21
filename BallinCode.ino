/*
 * created by Rui Santos, http://randomnerdtutorials.com
 * 
 * Complete Guide for Ultrasonic Sensor HC-SR04
 *
    Ultrasonic sensor Pins:
        VCC: +5VDC
        Trig : Trigger (INPUT) - Pin 6
        Echo: Echo (OUTPUT) - Pin 5
        GND: GND
 */

#include <Stepper.h>
//int WHITE = 4;
//int BROWN = 5;
//int GREEN = 6;
//int RED = 7;
const int stepsPerRevolution = 200;
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

//int dcMotor1 
//int dcMotor2
int trigPin1 = 6;    //Trig - green Jumper
int echoPin1 = 5;    //Echo - yellow Jumper
int trigPin2 = 4;    //Trig - green Jumper
int echoPin2 = 3;    //Echo - yellow Jumper
int duration1, inches1;
int duration2, inches2;
//float basket1distance, basket2distance, basket3distance;
//int toCorner;
float pi = 3.14159265359;
 
void setup() {
  //Serial Port begin
  Serial.begin (9600);
  myStepper.setSpeed(100);
  //Define inputs and outputs
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT); 
  pinMode(echoPin2, INPUT);

 //pinMode(WHITE, OUTPUT);
 //pinMode(BROWN, OUTPUT);
 //pinMode(GREEN, OUTPUT);
 //pinMode(RED, OUTPUT);
}
 
void loop()
{

 Serial.println("in Loop");
 int someSteps = findLocation();
 int degreesAcrossBoard = (someSteps * 3.6);
 Serial.println(degreesAcrossBoard);
 //find basketdistances
 int perpendicular = someSteps/2;
 for(int i = 0; i < perpendicular; i++){
  stepForward();
 }

 delay(10000);

//find basket1
//find basket2
//find basket3

//scan/point

//load ball

//shoot



 

 
 
 
 /*while(int i = 0; i < 10; i++){
  //point
  //shoot
 }*/
 

}

int findLocation(){

  Serial.println("in findLocation");
  int situation = readY();
  int steps = 0;
  
  if(situation < 72){
    steps = backboard();
  }
  else if(situation > 72){
    steps = noBackboard();
  }

  return steps;
}


void stepForward(){
  
    myStepper.step(5);

  

     //Serial.println("Done stepping forward.");
}
void stepBackward(){
  

   myStepper.step(-5);
   //Serial.println("Done stepping backward.");
  
}


int readX(){

  Serial.println("in readX");
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
 
  pinMode(echoPin2, INPUT);
  duration1 = pulseIn(echoPin2, HIGH);

  delay(50);

  inches2 = ((duration2)/2) / 74; //x - coordinate

  return inches2;
  
}
int readY(){
  Serial.println("in readY");
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
 
  pinMode(echoPin1, INPUT);
  duration1 = pulseIn(echoPin1, HIGH);

  delay(50);

  inches1 = ((duration1/2)) / 74; //x - coordinate

  return inches1;
}

int backboard(){

  Serial.println("in backboard");
  while(readY() < 72){
    stepForward();
    Serial.println(readY());
    
  }

  while(readY() > 72){
    stepBackward();
    Serial.println(readY());
  }

  int stepsAcrossBoard = 0;
  while(readY() < 72){
    stepBackward();
    Serial.println(readY());
    stepsAcrossBoard++;
  }


return stepsAcrossBoard;
  
}

int noBackboard(){

  Serial.println("in no backboard");
  
  while(readY() > 72){
    stepForward();
  }

  int stepsAcrossBoard = 0;
  while(readY() < 72){
    stepForward();
    stepsAcrossBoard++;
  }

  for(int i = 0; i < stepsAcrossBoard; i++){
    stepBackward();
  }

  return stepsAcrossBoard;
}

int leftBasketDistance(){

 int y = readY();
 int x = readX();

double basket1distance = (((x^2)+((y-15)^2)))^(1/2);
  
}

int leftBasketAngle(){

 int y = readY();
 int x = readX();

 int basket1theta = atan((y-15)/x);
  
}

int middleBasketDistance(){

 int y = readY();
 int x = readX();

double basket2distance = (((x^2)+((y-36)^2)))^(1/2);
  
}

int middleBasketAngle(){

 int y = readY();
 int x = readX();

 int basket2theta = atan((y-36)/x);
  
}

int rightBasketDistance(){

 int y = readY();
 int x = readX();

double basket3distance = (((x^2)+((y-57)^2)))^(1/2);
  
}

int rightBasketAngle(){

 int y = readY();
 int x = readX();

 int basket3theta = atan((y-57)/x);
  
}


