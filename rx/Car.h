#ifndef __CAR_H__
#define __CAR_H__

class Car{
private:
    // pins
    int EN_1, IN_1A, IN_1B;
    int EN_2, IN_2A, IN_2B;
    // speed
    int PW; //power
public:
    Car();
    void setup(int EN_1, int IN_1A, int IN_1B,
    int EN_2, int IN_2A, int IN_2B, int PW);

private:
    void CW(int en, int a, int b);
    void CCW(int en, int a, int b);
public:
    void goForward();
    void goBackward();
    void turnLeft();
    void turnRight();
    void brake();
};

#endif
