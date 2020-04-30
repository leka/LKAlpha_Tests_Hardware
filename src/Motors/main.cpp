#define DEBUG_IS_ON 1
#define outputLevel           DebugLevel::debug
#define showLevel             false
// #define showFreeMemory        false
#define showFileName          false
#define showFunctionName      false


#include <Arduino.h>
#include "IMotor.h"
#include "Motor.h"
#include "LekaLogger.h"

const uint8_t MOTOR_LEFT_DIRECTION_PIN  = 4;
const uint8_t MOTOR_LEFT_SPEED_PIN      = 5;
const uint8_t MOTOR_RIGHT_DIRECTION_PIN = 7;
const uint8_t MOTOR_RIGHT_SPEED_PIN     = 6;

const uint8_t MOTOR_MAX_SPEED           = (uint8_t) 255 * 90 / 100;

const int     ACCLERATION_DURATION_MS   = 2000;
const int     ACCLERATION_STEP_MS       = 100;
const int     MOVEMENT_DURATION_MS      = 30'000;

Motor motorLeft   = Motor(MOTOR_LEFT_DIRECTION_PIN, MOTOR_LEFT_SPEED_PIN);
Motor motorRight  = Motor(MOTOR_RIGHT_DIRECTION_PIN, MOTOR_RIGHT_SPEED_PIN);

unsigned long cycle = 1;

void moveForward(uint8_t speed) {
	// log_append(".");
	motorRight.spin(Rotation::clockwise, speed);
	motorLeft.spin(Rotation::counterClockwise, speed);
}

void moveBackward(uint8_t speed) {
	motorRight.spin(Rotation::counterClockwise, speed);
	motorLeft.spin(Rotation::clockwise, speed);
}

void stop() {
	motorLeft.stop();
	motorRight.stop();
}

void accelerate(void (*moveBackwardOrForward)(uint8_t), int duration, int stepDuration, uint8_t speed = MOTOR_MAX_SPEED) {

	int steps = duration / stepDuration;
	int remainingTime = duration % stepDuration;

	for (auto i = 0; i < steps; ++i) {
		auto currentSpeed = speed / steps * i;
		moveBackwardOrForward(currentSpeed);
		delay(stepDuration);
		log_append(".");
	}

	moveBackwardOrForward(speed);

	if (remainingTime != 0) {
		delay(remainingTime);
		logln_append(".");
	}
	else {
		logln_append("");
	}

}

void waitFor(int duration) {

	int stepDuration = 500;
	int steps = duration / stepDuration;
	int remainingTime = duration % stepDuration;

	for (int i = 0; i < steps; ++i) {
		delay(stepDuration);
		log_append(".");
	}

	if (remainingTime != 0) {
		delay(remainingTime);
		logln_append(".");
	}
	else {
		logln_append("");
	}

}

void setup() {
	Serial.begin(115200);
	delay(1000);
	log_info("Starting Motor Resistance Test");
	waitFor(5000);
	Serial.println("");
}

void loop() {

	logln_info("[Motors] - Cycle %04ld - Start", cycle);

	log_info("[Motors] - Cycle %04ld - Forward  - Accelerate for %is", cycle, ACCLERATION_DURATION_MS/1000);
	accelerate(moveForward, ACCLERATION_DURATION_MS, ACCLERATION_STEP_MS);

	log_info("[Motors] - Cycle %04ld - Forward  - Move for %is", cycle, MOVEMENT_DURATION_MS/1000);
	waitFor(MOVEMENT_DURATION_MS);

	log_info("[Motors] - Cycle %04ld - Forward  - Stop for %is", cycle, MOVEMENT_DURATION_MS/1000);
	stop();
	waitFor(MOVEMENT_DURATION_MS);

	log_info("[Motors] - Cycle %04ld - Backward - Accelerate for %is", cycle, ACCLERATION_DURATION_MS/1000);
	accelerate(moveBackward, ACCLERATION_DURATION_MS, ACCLERATION_STEP_MS);

	log_info("[Motors] - Cycle %04ld - Backward - Move for %is", cycle, MOVEMENT_DURATION_MS/1000);
	waitFor(MOVEMENT_DURATION_MS);

	log_info("[Motors] - Cycle %04ld - Backward - Stop for %is", cycle, MOVEMENT_DURATION_MS/1000);
	stop();
	waitFor(MOVEMENT_DURATION_MS);

	logln_info("[Motors] - Cycle %04ld - End\n", cycle);

	cycle++;

}

