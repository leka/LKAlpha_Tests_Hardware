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

#ifndef LEKA_ARDUINO_CLASS_MOTOR_H_
#define LEKA_ARDUINO_CLASS_MOTOR_H_

/**
 * @file Motors.h
 * @author Ladislas de Toldi
 * @version 1.0
 */

#include <Arduino.h>
#include "IMotor.h"

/**
 * @class Motor
 * @brief Motor class gathers all the motor functions for Leka.
 */

class Motor : public IMotor {
	public:
		Motor(uint8_t directionPin, uint8_t speedPin);

		void spin(Rotation rotation = Rotation::clockwise, uint8_t speed = MAX_SPEED);
		void stop(void);

      static const uint8_t MAX_SPEED = 255;

	private:
		uint8_t _directionPin;
		uint8_t _speedPin;
};

#endif
