---
title: Arduino Remote Car
description: Control an Arduino Car Remotely Through Ros
layout: default
---

# Arduino Remote Car

## NOTES 
This project is still under development.

Currently, the chassis does not provide any stability beyond simple mobility.

Furthermore, only 1-way communication from the computer to the car is possible.

The repository itself is the code base for the Arduino Car controlled remotely through ROS.

![Car](images/carasm.JPG)

## Parts Needed

- 2x [Arduino Uno](https://www.sparkfun.com/products/11021)
- Lots of Wires (preferably with different colors, at least red and black)
- [WRL-10532](https://www.sparkfun.com/products/10532)/[WRL-10534](https://www.sparkfun.com/products/10534) Radio Receiver/Transmitter Pair
- 1x Motor H-Bridge IC (I used L293D)
- 1x 5V Voltage Regulator (I used LM78M05C)
- 1x 9V Battery
- 2x DC Motors (I used [This](http://www.vigorprecision.com.hk/ProductList.Asp?SortID=1) just because they were available. The chassis is adapted to this model.)
- 1x small caster wheel (see CAD for dimensions)
- 2x bigger wheels (see CAD for dimensions)
- 1x half-size breadboard
- 2x antenna (I just used solid wires)
- Some zip ties if you want to provide cheap securing to your assembly

## Building the Chassis

Get the CAD from [here](https://drive.google.com/open?id=0B75j6bliWwyTUGZSWWZrYkl3Mnc).

The bulk of the chassis can be 3d printed.

In my case, I could not find a good caster wheel, so I 3d printed the wheel and mounted it with sheet metal.

As for the main wheel, I recommend buying them. The dimensions are specified in the CAD file.

## Wiring the components

### Receiver

![RX](images/wiring_rx.png)

The receiver is connected to the arduino.

### Transmittor

![TX](images/wiring_tx.png)

The transmitter should be connected to your computer.

## Software

1. Install rosserial.

   Via Package Manager:

   ```bash
   sudo apt-get install ros-${ROS_DISTRO}-rosserial ros-${ROS_DISTRO}-rosserial-python ros-${ROS_DISTRO}-rosserial-arduino
   ```

   Alternatively, clone the github repository and run catkin_make.

   ```bash
   cd ~/catkin_ws/src
   git clone git@github.com:ros-drivers/rosserial.git   
   cd ..
   catkin_make
   ``` 

2. Build the ros package to remotely control the arduino from your computer.

   ```bash
   export CATKIN_WORKSPACE=${HOME}/catkin_ws #REPLACE WITH YOUR OWN
   git clone git@github.com:yycho0108/ArduinoRemoteCar.git
   cp ArduinoRemoteCar/arduino_rc_car ${CATKIN_WORKSPACE}/src
   cd ${CATKIN_WORKSPACE}
   catkin_make --pkg arduino_rc_car
   ```

3. Build rosserial_arduino.

   ```bash
   export ARDUINO_LIB_DIR=${HOME}/sketchbook/libraries
   cd ${ARDUINO_LIB_DIR}
   rm -rf ros_lib
   rosrun rosserial_arduino make_libraries.py 
   ```

   If this fails, check your arduino library directory.
  
   It may simply be ${HOME}/Arduino/libraries.

4. Install the arduino library [VirtualWire](https://www.pjrc.com/teensy/td_libs_VirtualWire.html) to facilitate RF communication.

   Here are [Instructions](https://www.arduino.cc/en/Guide/Libraries) on how to install an Arduino Library.

   Alternatively, simply run the following script: 

   ```bash
   export ARDUINO_LIB_DIR=${HOME}/sketchbook/libraries
   wget http://www.airspayce.com/mikem/arduino/VirtualWire/VirtualWire-1.27.zip
   unzip VirtualWire-1.27.zip
   mv VirtualWire ${ARDUINO_LIB_DIR}/VirtualWire
   ```

## Running the code

1. Upload the code to receiver/transmitter arduinos.

   If you encounter an error that you cannot open the serial port, run:

   ```bash
   sudo usermod -a -G dialout <username>
   sudo chmod a+rw /dev/ttyACM0
   ```

2. Power up the car(connect the battery).
3. Connect the transmitter arduino to your computer via serial port.
4. Check the ports to which the transmitter is connected.

   ```bash
   ls /dev/ttyACM*
   ```

5. Launch the ros control node.

   ```bash
   sudo -s
   roslaunch arduino_rc_car control.launch port:=/dev/ttyACM0
   ```

6. Press the arrows to control the car remotely. 
