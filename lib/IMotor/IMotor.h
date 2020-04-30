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

#ifndef LEKA_ARDUINO_CLASS_INTERFACE_MOTOR_H_
#define LEKA_ARDUINO_CLASS_INTERFACE_MOTOR_H_

/**
 * @file IMotors.h
 * @author Ladislas de Toldi
 * @version 1.0
 */

/**
 * @class IMotor
 * @brief Inteface for the Motor class
 */

#include <Arduino.h>

enum class Rotation : uint8_t {
   clockwise        = 0,
   counterClockwise = 1
};

class IMotor {
	public:
		virtual void spin(Rotation rotation, uint8_t speed) = 0;
		virtual void stop(void) = 0;
};

#endif
