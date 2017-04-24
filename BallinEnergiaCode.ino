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

const int stepsPerRevolution = 200;
Stepper myStepper(stepsPerRevolution, 11, 12, 13, 14);
Stepper myLoadingStepper(stepsPerRevolution, 2, 3, 4, 5);

int enA = 40;//dcmotor1
int in1 = 39;
int in2 = 38;

int enB = 37;//dcmotor2
int in3 = 36;
int in4 = 35;

int trigPin1 = 15;    //Trig - green Jumper
int echoPin1 = 17;    //Echo - yellow Jumper
int trigPin2 = 18;    //Trig - green Jumper
int echoPin2 = 19;    //Echo - yellow Jumper
int irSensor = 33;
int duration1, inches1;
int duration2, inches2;
float pi = 3.14159265359;
 
void setup() {
  //Serial Port begin
  Serial.begin (9600);
  myStepper.setSpeed(100);
  myLoadingStepper.setSpeed(100);
  //Define inputs and outputs
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT); 
  pinMode(echoPin2, INPUT);

  pinMode(irSensor, INPUT);

  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

}
 
void loop()
{

 Serial.println("in Loop");
 int someSteps = findLocation();
 int degreesAcrossBoard = (someSteps * 3.6);
 Serial.println(degreesAcrossBoard);

 //int perpendicular = someSteps/2;
 //for(int i = 0; i < perpendicular; i++){
 // stepForward();
 //}

 delay(10000);

int basket1distance = basket1distance();
int basket1angle = basket1angle();//find basket1
int basket2distance = basket1distance();
int basket2angle = basket1angle();//find basket2
int basket3distance = basket3distance();
int basket3angle = basket3angle();//find basket3
    
int stepsToBasket1 = basket1angle/3.6;
int stepsToBasket2 = basket2angle/3.6;
int stepsToBasket3 = basket3angle/3.6;


for(int i=0; i < 100; i++)
{
  basket = i % 5;
  switch basket;
    case 0:
    myStepper.step(stepsToBasket1);
    if (readIr = LOW)
    {
        shoot();
    }
    break;
    
    case 1:
    myStepper.step(stepsToBasket2 - stepsToBasket1);
    if (readIr() = LOW)
    {
        shoot();
    }
    break;
    
    case 2:
    myStepper.step(stepsToBasket3 - stepsToBasket2);
    if (readIr() = LOW)
    {
        shoot();
    }
    break;
    
    case 3:
    myStepper.step(-(stepsToBasket3 - stepsToBasket2));
    if (readIr() = LOW)
    {
        shoot();
    }
    break;
    
    case 4:
    myStepper.step(-(stepsToBasket2 - stepsToBasket1));
    if (readIr() = LOW)
    {
        shoot();
    }
    myStepper.step(-stepsToBasket1);
    break;
}
   

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
  
    myStepper.step(-5);
     //Serial.println("Done stepping forward.");
}
void stepBackward(){
  
   myStepper.step(5);
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
  while(readY() < 56){
    stepForward();
    Serial.println(readY());
    
  }

  while(readY() > 56){
    stepBackward();
    Serial.println(readY());
  }

  int stepsAcrossBoard = 0;
  while(readY() < 56){
    stepBackward();
    Serial.println(readY());
    stepsAcrossBoard++;
  }


return stepsAcrossBoard;
  
}

int noBackboard(){

  Serial.println("in no backboard");
  
  while(readY() > 56){
    stepForward();
  }

  int stepsAcrossBoard = 0;
  while(readY() < 56){
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

return basket1distance;
  
}

int leftBasketAngle(){

 int y = readY();
 int x = readX();

 int basket1theta = atan((y-15)/x);

 return basket1theta;
  
}

int middleBasketDistance(){

 int y = readY();
 int x = readX();

double basket2distance = (((x^2)+((y-36)^2)))^(1/2);

return basket2distance;
  
}

int middleBasketAngle(){

 int y = readY();
 int x = readX();

 int basket2theta = atan((y-36)/x);

 return basket2theta;
  
}

int rightBasketDistance(){

 int y = readY();
 int x = readX();

double basket3distance = (((x^2)+((y-57)^2)))^(1/2);

return basket3distance;
  
}

int rightBasketAngle(){

 int y = readY();
 int x = readX();

 int basket3theta = atan((y-57)/x);

  
}


int readIr(){
  irValue = digitalRead(irSensor);
  return irValue;
}

void shoot(){
    // this function will run the motors in both directions at a fixed speed
  // turn on motor A
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enA, 200);
  // turn on motor B
   digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enB, 200);
  // set speed to 200 out of possible range 0~255

  myLoadingStepper.step(50);
  myLoadingStepper.step(-50);
  delay(1000);
}

