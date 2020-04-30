/*
   Copyright (C) 2013-2014 Ladislas de Toldi <ladislas at leka dot io> and Leka <http://leka.io>

   This file is part of Leka, a spherical robotic smart toy for autistic children.

   Leka is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   Leka is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with Leka. If not, see <http://www.gnu.org/licenses/>.
   */

#include <Arduino.h>
#include "Motor.h"


/**
 * @file Motor.cpp
 * @author Ladislas de Toldi
 * @version 1.0
 */

/**
 * @brief Instantiates a new motor, given its direction and speed pins
 * @param directionPin the direction pin of the motor
 * @param speedPin the speed pin of the motor
 */
Motor::Motor(uint8_t directionPin, uint8_t speedPin) {
	_directionPin = directionPin;
	_speedPin = speedPin;
}

/**
 * @brief Tells a motor to spin in a given direction, at a given speed
 * @param direction the direction to spin (FORWARD | BACKWARD)
 * @param speed the speed to spin (0-MOTOR_MAX_SPEED)
 */
void Motor::spin(Rotation rotation, uint8_t speed) {
	digitalWrite(_directionPin, (uint8_t) rotation);
	analogWrite(_speedPin, speed);
}

/**
 * @brief Tells a motor to immediately stop
 */
void Motor::stop(void) {
	spin(Rotation::clockwise, 0);
}
