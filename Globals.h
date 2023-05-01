/**
 * @file Globals.h
 * @author Lyam (LyamBRS@gmail.com.com)
 * @brief This file contains the various class
 * definitions used throughout this project.
 * This allows classes and object to be accessed
 * globally by all entities at any point.
 * 
 * @attention
 * You must initialize each class in this file
 * in void setup prior to actually using them.
 * @version 0.1
 * @date 2023-04-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
/*  ############    ############     ##########
    ############    ############     ##########
              ##              ##   ## 
    ####    ##      ####    ##     ############
    ####    ##      ####    ##     ############
              ##              ##             ##
    ############    ####      ##   ##########
    ############    ####      ##   ##########   */

#ifndef BRS_GLOBALS_H
    #define BRS_GLOBALS_H

#include <iostream>
#include <cstring>
#include <Adafruit_NeoPixel.h>
#include "Defines.h"
#include "Enums.h"
#include "RGB.h"
#include "Device.h"
#include "Chunk.h"
#include "Data.h"
#include "Joystick.h"
#include "_UNIT_TEST_Rgb.h"
#include "_UNIT_TEST_Data.h"
#include "_UNIT_TEST_Chunk.h"
#include "_UNIT_TEST_Joystick.h"
#include "_UNIT_TEST.h"

///@brief RGB LED uses GPIO 48
#define RGB_PIN 48
///@brief The button of the left joystick is GPIO45
#define LEFT_JOYSTICK_SWITCH_PIN 26
///@brief The button of the right joystick is GPIO16
#define RIGHT_JOYSTICK_SWITCH_PIN 9
///@brief The X axis ADC of the left joystick is GPIO 
#define LEFT_JOYSTICK_X_PIN 38
///@brief The X axis ADC of the right joystick is GPIO 
#define RIGHT_JOYSTICK_X_PIN 15
///@brief The Y axis ADC of the left joystick is GPIO 
#define LEFT_JOYSTICK_Y_PIN 39
///@brief The Y axis ADC of the right joystick is GPIO 
#define RIGHT_JOYSTICK_Y_PIN 4

#define RGB_COUNT 1
#define DEBUG_BAUD_RATE 9600
#define CLOCK_PERIOD_MS 1

/** 
 * @brief Hardware handling class that
 * directly handles the WS2812 RGB
 * LEDs. This is used by the RGB class. 
 */
Adafruit_NeoPixel WS2812(RGB_COUNT, RGB_PIN, NEO_GRB + NEO_KHZ800);
/**
 * @brief Interface allowing easy
 * handling of colors and modes of the
 * WS2812 addressable RGB LEDs without
 * having to manually deal with the
 * Adafruit hardware handling class.
 */
RGB Rgb;

/**
 * @brief Class allowing easy readings
 * and interfacing of Gamepad's
 * left joystick.
 * This is a timebase class and must have
 * its update called periodically.
 */
cJoystick LeftJoystick;

/**
 * @brief Class allowing easy readings
 * and interfacing of Gamepad's
 * right joystick.
 * This is a timebase class and must have
 * its update called periodically.
 */
cJoystick RightJoystick;

/**
 * @brief The class that represents the device
 * that executes this program. This class
 * is global and accessed by multiple other
 * classes and functions. It is used to set
 * modes and take global actions.
 */
cDevice Device;

/**
 * @brief Global object which can be accessed
 * by all programs which include the Globals.h
 * file. This object is used to handle low level
 * BFIO chunk conversions. See Chunk.h for the
 * class's details such as its members and
 * methods.
 */
cChunk Chunk;

/**
 * @brief Global object which can be accessed
 * by all program swhich includes Globals.h.
 * This object is used to handle type convertions
 * to arrays of bytes and vise versa to be used
 * through the BFIO protocol.
 */
cData Data;

#pragma region Functions
/**
 * @brief Function that initializes and
 * builds the classes defined in the
 * section above. Call this as the
 * very first thing in your program.
 * @return Execution:
 * See definition for potential values.
 */
Execution InitializeProject()
{
    Serial.begin(DEBUG_BAUD_RATE);
    Rgb = RGB(RGB_PIN);
    Device = cDevice();
    Chunk = cChunk();
    Data = cData();
    LeftJoystick = cJoystick(LEFT_JOYSTICK_X_PIN, LEFT_JOYSTICK_Y_PIN, LEFT_JOYSTICK_SWITCH_PIN);
    RightJoystick = cJoystick(RIGHT_JOYSTICK_X_PIN, RIGHT_JOYSTICK_Y_PIN, RIGHT_JOYSTICK_SWITCH_PIN);

    return Execution::Passed;
}

/**
 * @brief Function that tests if the
 * initialization done when calling
 * @ref InitializeProject 
 * was successful.
 * 
 * @return Execution
 */
Execution TestInitialization()
{
    Serial.println("Project test: -> START");

    if(!Rgb.built)
    {
        Serial.println("Project test: -> RGB OBJECT FAIL");
        return Execution::Failed;
    }

    if(!Device.built)
    {
        Serial.println("Project test: -> DEVICE OBJECT FAIL");
        return Execution::Failed;
    }

    if(!Chunk.built)
    {
        Serial.println("Project test: -> CHUNK OBJECT FAIL");
        return Execution::Failed;
    }

    if(!Data.built)
    {
        Serial.println("Project test: -> DATA OBJECT FAIL");
        return Execution::Failed;
    }

    if(!LeftJoystick.built)
    {
      Serial.println("Project test: -> LEFTJOYSTICK OBJECT FAIL");
      return Execution::Failed;
    }

    if(!RightJoystick.built)
    {
      Serial.println("Project test: -> RIGHTJOYSTICK OBJECT FAIL");
      return Execution::Failed;
    }

    Serial.println("Project test: -> SUCCESS");
    return Execution::Passed;
}
#pragma endregion

#endif
