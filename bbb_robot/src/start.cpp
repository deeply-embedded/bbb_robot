//============================================================================
// Name        : bbb_robot.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <GPIO.h>
#include "periphery/actor/servo.h"

using namespace std;
using namespace RSL;
//using namespace RSL_core;


int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	double position = 0;

	GPIOPin gpioPin = P8_3;


	RSL_core::GPIO::exportPin(gpioPin);

	Servo myServo = new Servo(gpioPin);
	myServo.enableServo();

	myServo.setPosition(position);


	while(1){


	}



	return 0;
}
