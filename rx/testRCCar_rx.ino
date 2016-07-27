// receiver.pde
//
// Simple example of how to use VirtualWire to receive messages
// Implements a simplex (one-way) receiver with an Rx-B1 module
//
// See VirtualWire.h for detailed API docs
// Author: Mike McCauley (mikem@airspayce.com)
// Copyright (C) 2008 Mike McCauley
// $Id: receiver.pde,v 1.3 2009/03/30 00:07:24 mikem Exp $

#include <VirtualWire.h>

#include "Car.h"
Car car;
unsigned long lastCmd;

void setup()
{
    Serial.begin(9600);	// Debugging only
    Serial.println("setup");

    // Initialise the IO and ISR
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(2400);	 // Bits per sec
    vw_set_rx_pin(2);
    vw_rx_start();       // Start the receiver PLL running

    // Initialize Car Pins
    car.setup(11,9,8,10,7,6,255);
}

void loop()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
    
    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
        Serial.println((char*)buf);

        digitalWrite(13, true); // Flash a light to show received good message
        if(strncmp((char*)buf, "FWD", 3) == 0){
            car.goForward();
        } 
        else if (strncmp((char*)buf, "BWD", 3) == 0){
            car.goBackward();
        } 
        else if (strncmp((char*)buf, "RGT", 3) == 0){
            car.turnRight();
        } 
        else if (strncmp((char*)buf, "LFT", 3) == 0){
            car.turnLeft();   
        } 
        else if (strncmp((char*) buf, "BRK", 3) == 0){
            car.brake();   
        }
        lastCmd = millis();
    }
    else if(millis() > lastCmd + 1000){
        //a second has passed since last command
        car.brake();

    }
}










