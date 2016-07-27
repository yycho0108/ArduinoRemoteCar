
#include "Car.h"

Car::Car(){
    
}

void Car::setup(int EN_1, int IN_1A, int IN_1B,
int EN_2, int IN_2A, int IN_2B, int PW){

    // MOTOR 1
    pinMode(EN_1, OUTPUT);
    pinMode(IN_1A, OUTPUT);
    pinMode(IN_1B, OUTPUT);

    this->EN_1 = EN_1;
    this->IN_1A = IN_1A;
    this->IN_1B = IN_1B;

    // MOTOR 2
    pinMode(EN_2, OUTPUT);
    pinMode(IN_2A, OUTPUT);
    pinMode(IN_2B, OUTPUT);

    this->EN_2 = EN_2;
    this->IN_2A = IN_2A;
    this->IN_2B = IN_2B;

    // POWER
    this->PW = PW;
}

void Car::CW(int en, int a, int b){
    analogWrite(en,PW) ;
    digitalWrite(a,HIGH) ;
    digitalWrite(b,LOW) ;
}
void Car::CCW(int en, int a, int b){
    analogWrite(en,PW) ;
    digitalWrite(a,LOW) ;
    digitalWrite(b,HIGH) ;
}    
void Car::goForward(){
    //all depends on pin-motor configuration. adjust accordingly
    CCW(EN_1,IN_1A,IN_1B);
    CW(EN_2,IN_2A,IN_2B);
}

void Car::goBackward(){
    CW(EN_1,IN_1A,IN_1B);
    CCW(EN_2,IN_2A,IN_2B);
}

void Car::turnLeft(){
    CCW(EN_1,IN_1A,IN_1B);
    CCW(EN_2,IN_2A,IN_2B);
}
void Car::turnRight(){
    CW(EN_1,IN_1A,IN_1B);
    CW(EN_2,IN_2A,IN_2B);
}
void Car::brake(){
    analogWrite(EN_1,0) ;
    digitalWrite(IN_1A,HIGH) ;
    digitalWrite(IN_1B,HIGH) ;

    analogWrite(EN_2,0) ;
    digitalWrite(IN_2A,HIGH) ;
    digitalWrite(IN_2B,HIGH) ;
}
