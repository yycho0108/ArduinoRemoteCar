// transmitter.pde
//
// Simple example of how to use VirtualWire to transmit messages
// Implements a simplex (one-way) transmitter with an TX-C1 module
//
// See VirtualWire.h for detailed API docs
// Author: Mike McCauley (mikem@airspayce.com)
// Copyright (C) 2008 Mike McCauley
// $Id: transmitter.pde,v 1.3 2009/03/30 00:07:24 mikem Exp $

#include <ros.h>
#include <std_msgs/String.h>

#include <VirtualWire.h>

enum{
    FWD,BWD,LFT,RGT};
/* ROS STUFF */

void moveCar(const std_msgs::String& msg){
    digitalWrite(13, true); // Flash a light to show transmitting
	vw_send((uint8_t*)msg.data, 4);
    vw_wait_tx(); // Wait until the whole message is gone
    digitalWrite(13, false);
}

ros::NodeHandle nh;
std_msgs::String dir;
ros::Subscriber<std_msgs::String> dir_sub("dir", &moveCar);

//std_msgs::Int16 sensor_msg;
//ros::Publisher sensor_pub("sensor", &sensor_msg);

void setup()
{
    pinMode(13,OUTPUT);

    //Serial.begin(9600);	  // Debugging only
    //Serial.println("setup");

    // Initialise the IO and ISR
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_set_tx_pin(12);
    vw_setup(2400);	 // Bits per sec

    // Initialize ROS
    nh.initNode();
    nh.subscribe(dir_sub);

    //nh.advertise(we_pub);
}

void loop()
{
    /* TESTING CODE */


    //    char msg[16] = {
    //    };
    //    int n;
    //    if(n = Serial.available()){
    //        /* REPLACE WITH ROS API */
    //
    //        Serial.readBytes(msg, n);
    //        Serial.println(n); //echo msg
    //        digitalWrite(13, true); // Flash a light to show transmitting
    //        //vw_send((uint8_t *)msg, n);
    //        //vw_wait_tx(); // Wait until the whole message is gone
    //        digitalWrite(13, false);
    //
    //    }
    //    delay(200);

    //we_msg.data = 156;
    //we_pub.publish(&we_msg);

    nh.spinOnce();
    delay(1);
}







