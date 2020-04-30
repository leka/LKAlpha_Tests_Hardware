
/*
   Copyright (C) 2013-2018 Ladislas de Toldi <ladislas at leka dot io> and Leka <http://leka.io>

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

#ifndef _LEKA_LOGGER_H_
#define _LEKA_LOGGER_H_

/**
 * @file LekaLogger.h
 * @author Ladislas de Toldi
 * @version 1.0
 */

#include <Arduino.h>
#include <string.h>

// Pass the parameter to gcc with -DDEBUG_IS_ON
// or uncomment #define DEBUG_IS_ON
// #define DEBUG_IS_ON

#if defined(DEBUG_IS_ON)
#warning "Debug is ON"

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#ifndef LOG_BUFFER_SIZE
#define LOG_BUFFER_SIZE       128 // start with 64 and if you notice strange characters use a larger buffer
#endif

#ifndef outputLevel
#define outputLevel           DebugLevel::verbose
#endif

#ifndef showTime
#define showTime              true
#endif

#ifndef showHumanReadableTime
#define showHumanReadableTime true
#endif

#ifndef showLevel
#define showLevel             true
#endif

#ifndef showFreeMemory
#define showFreeMemory        true
#endif

#ifndef showFileName
#define showFileName          true
#endif

#ifndef showFunctionName
#define showFunctionName      true
#endif

enum class DebugLevel {
	verbose = 0,
	debug,
	info,
	warning,
	error,
};

namespace LekaLogger {

	inline char buffer[LOG_BUFFER_SIZE];

	inline unsigned long currentTime = 0;
	inline unsigned long ms = 0;
	inline unsigned long sec = 0;
	inline unsigned long min = 0;
	inline unsigned long hour = 0;

	inline unsigned int __heap_start;
	inline void *__brkval;

	/*
	 * The free list structure as maintained by the
	 * avr-libc memory allocation routines.
	 */
	struct __freelist {
		size_t sz;
		struct __freelist *nx;
	};

	/* The head of the free list structure */
	extern struct __freelist *__flp;


	/* Calculates the size of the free list */
	inline int freeListSize() {

		struct __freelist* current;
		int total = 0;

		for (current = __flp; current; current = current->nx) {

			total += 2; /* Add two bytes for the memory block's header  */
			total += (int) current->sz;

		}

		return total;

	}

	inline int getFreeMemory() {

		int free_memory;

		if ((int)__brkval == 0) {

			free_memory = ((int)&free_memory) - ((int)&__heap_start);

		}
		else {

			free_memory = ((int)&free_memory) - ((int)__brkval);
			free_memory += freeListSize();

		}

		return free_memory;

	}

	inline void printWhiteSpace(void) {
		Serial.print(F(" "));
	}

	inline void printOpeningBracket(void) {
		Serial.print(F("["));
	}

	inline void printClosingBracket(void) {
		Serial.print(F("]"));
	}

	inline void printColon(void) {
		Serial.print(F(":"));
	}

	inline void printArrow(void) {
		Serial.print(F(">"));
	}

	inline void printDebugLevel(DebugLevel lvl) {

		if (lvl == DebugLevel::verbose) Serial.print(F("[VERBOSE]"));
		if (lvl == DebugLevel::debug) Serial.print(F("[DEBUG]"));
		if (lvl == DebugLevel::info) Serial.print(F("[INFO]"));
		if (lvl == DebugLevel::warning) Serial.print(F("[WARNING]"));
		if (lvl == DebugLevel::error) Serial.print(F("[ERROR]"));
		LekaLogger::printWhiteSpace();

	}

	inline void printTime(void) {

		LekaLogger::currentTime = millis();
		Serial.print(LekaLogger::currentTime);
		LekaLogger::printWhiteSpace();

	}

	inline void printHumanReadableTime(void) {

		LekaLogger::currentTime = millis();
		LekaLogger::ms   = LekaLogger::currentTime % 1000;
		LekaLogger::sec  = (LekaLogger::currentTime / 1000);
		LekaLogger::min  = (LekaLogger::sec / 60) % 60;
		LekaLogger::hour = (LekaLogger::min / 60);
		sprintf(LekaLogger::buffer,
				"%04lu:%02lu:%02lu:%03lu",
				LekaLogger::hour,
				LekaLogger::min,
				LekaLogger::sec % 60,
				LekaLogger::ms);
		Serial.print(LekaLogger::buffer);
		LekaLogger::printWhiteSpace();

	}

	inline void printFreeMemory(void) {

		Serial.print(LekaLogger::getFreeMemory());
		LekaLogger::printWhiteSpace();

	}

} // namespace LekaLogger


//
// Mark:- Define _log_showTime
//

#if showTime && showHumanReadableTime
#define _log_showTime do {                \
	LekaLogger::printHumanReadableTime(); \
} while(0)

#elif showTime
#define _log_showTime do {   \
	LekaLogger::printTime(); \
} while(0)

#else
#define _log_showTime

#endif // showTime


//
// Mark:- Define _log_showLevel
//

#if showLevel
#define _log_showLevel(lvl) do {      \
	LekaLogger::printDebugLevel(lvl); \
} while(0)

#else
#define _log_showLevel(lvl)

#endif // showLevel


//
// Mark:- Define _log_showFreeMemory
//

#if showFreeMemory
#define _log_showFreeMemory do {   \
	LekaLogger::printFreeMemory(); \
} while(0)

#else
#define _log_showFreeMemory

#endif // showFreeMemory


//
// Mark:- Define _log_showFileName
//

#if showFileName
#define _log_showFileName do {   \
	LekaLogger::printFileName(); \
} while(0)

#else
#define _log_showFileName

#endif // showFileName


//
// Mark:- Define _log_showFunctionName
//

#if showFunctionName
#define _log_showFunctionName do {   \
	LekaLogger::printFunctionName(); \
} while(0)

#else
#define _log_showFunctionName

#endif // showFunctionName


//
// Mark:- Define _log_showArrowSeparator
//

#if showTime || showLevel || showFreeMemory || showFileName || showFunctionName
#define _log_showArrowSeparator do { \
	LekaLogger::printArrow();        \
	LekaLogger::printWhiteSpace();   \
} while(0)

#else
#define _log_showArrowSeparator

#endif // showArrowSeparator


//
// Mark:- Define printMessage
//

#define printMessage(str, lvl, ...) do {                        \
	_log_showTime;                                              \
	_log_showLevel(lvl);                                        \
	_log_showFreeMemory;                                        \
	if (showFileName) {                                         \
		LekaLogger::printOpeningBracket();;                     \
		Serial.print(__FILENAME__);                             \
		LekaLogger::printColon();                               \
		Serial.print(__LINE__);                                 \
		LekaLogger::printClosingBracket();;                     \
		LekaLogger::printWhiteSpace();                          \
		if (showFunctionName) {                                 \
			Serial.print(__PRETTY_FUNCTION__);                  \
			LekaLogger::printWhiteSpace();                      \
		}                                                       \
	}                                                           \
	_log_showArrowSeparator;                                    \
	sprintf(LekaLogger::buffer, str __VA_OPT__(,) __VA_ARGS__); \
	Serial.print(LekaLogger::buffer);                         \
} while(0) // define printMessage()

#define printlnMessage(str, lvl, ...) do {                        \
	_log_showTime;                                              \
	_log_showLevel(lvl);                                        \
	_log_showFreeMemory;                                        \
	if (showFileName) {                                         \
		LekaLogger::printOpeningBracket();;                     \
		Serial.print(__FILENAME__);                             \
		LekaLogger::printColon();                               \
		Serial.print(__LINE__);                                 \
		LekaLogger::printClosingBracket();;                     \
		LekaLogger::printWhiteSpace();                          \
		if (showFunctionName) {                                 \
			Serial.print(__PRETTY_FUNCTION__);                  \
			LekaLogger::printWhiteSpace();                      \
		}                                                       \
	}                                                           \
	_log_showArrowSeparator;                                    \
	sprintf(LekaLogger::buffer, str __VA_OPT__(,) __VA_ARGS__); \
	Serial.println(LekaLogger::buffer);                         \
} while(0) // define printMessage()

#define printAppendMessage(str, ...) do {                        \
	sprintf(LekaLogger::buffer, str __VA_OPT__(,) __VA_ARGS__); \
	Serial.print(LekaLogger::buffer);                         \
} while(0) // define printMessage()

#define printlnAppendMessage(str, ...) do {                        \
	sprintf(LekaLogger::buffer, str __VA_OPT__(,) __VA_ARGS__); \
	Serial.println(LekaLogger::buffer);                         \
} while(0) // define printMessage()

#define log_verbose(str, ...) do {                                        \
	if (outputLevel <= DebugLevel::verbose) {                             \
		printMessage(str, DebugLevel::verbose __VA_OPT__(,) __VA_ARGS__); \
	}                                                                     \
} while(0)

#define logln_verbose(str, ...) do {                                        \
	if (outputLevel <= DebugLevel::verbose) {                             \
		printlnMessage(str, DebugLevel::verbose __VA_OPT__(,) __VA_ARGS__); \
	}                                                                     \
} while(0)

#define log_debug(str, ...) do {                                        \
	if (outputLevel <= DebugLevel::debug) {                             \
		printMessage(str, DebugLevel::debug __VA_OPT__(,) __VA_ARGS__); \
	}                                                                   \
} while(0)

#define logln_debug(str, ...) do {                                        \
	if (outputLevel <= DebugLevel::debug) {                             \
		printlnMessage(str, DebugLevel::debug __VA_OPT__(,) __VA_ARGS__); \
	}                                                                   \
} while(0)

#define log_info(str, ...) do {                                        \
	if (outputLevel <= DebugLevel::info) {                             \
		printMessage(str, DebugLevel::info __VA_OPT__(,) __VA_ARGS__); \
	}                                                                  \
} while(0)

#define logln_info(str, ...) do {                                        \
	if (outputLevel <= DebugLevel::info) {                             \
		printlnMessage(str, DebugLevel::info __VA_OPT__(,) __VA_ARGS__); \
	}                                                                  \
} while(0)

#define log_warning(str, ...) do {                                        \
	if (outputLevel <= DebugLevel::warning) {                             \
		printMessage(str, DebugLevel::warning __VA_OPT__(,) __VA_ARGS__); \
	}                                                                     \
} while(0)

#define logln_warning(str, ...) do {                                        \
	if (outputLevel <= DebugLevel::warning) {                             \
		printlnMessage(str, DebugLevel::warning __VA_OPT__(,) __VA_ARGS__); \
	}                                                                     \
} while(0)

#define log_error(str, ...) do {                                        \
	if (outputLevel <= DebugLevel::error) {                             \
		printMessage(str, DebugLevel::error __VA_OPT__(,) __VA_ARGS__); \
	}                                                                   \
} while(0)

#define logln_error(str, ...) do {                                        \
	if (outputLevel <= DebugLevel::error) {                             \
		printlnMessage(str, DebugLevel::error __VA_OPT__(,) __VA_ARGS__); \
	}                                                                   \
} while(0)

#define log_append(str, ...) do {                                        \
	printAppendMessage(str, __VA_OPT__(,) __VA_ARGS__); \
} while(0)

#define logln_append(str, ...) do {                                        \
	printlnAppendMessage(str, __VA_OPT__(,) __VA_ARGS__); \
} while(0)

#else // DEBUG_IS_OFF
#warning "Debug is OFF"

#define log_verbose(str, ...)
#define log_debug(str, ...)
#define log_info(str, ...)
#define log_warning(str, ...)
#define log_error(str, ...)

#define logln_verbose(str, ...)
#define logln_debug(str, ...)
#define logln_info(str, ...)
#define logln_warning(str, ...)
#define logln_error(str, ...)

#endif // DEBUG_IS_ON or DEBUG_IS_OFF

#endif // _LEKA_LOGGER_H_
