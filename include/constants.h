#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <Arduino.h>

// Analog pins configuration
static constexpr uint8_t PIN_SENSOR_UV = A0;
static constexpr uint8_t PIN_SENSOR_GROUND_HUMIDITY = A1;


// I2C addresses
static constexpr unsigned int ADDR_SENSOR_BME = 0x77;
static constexpr unsigned int ADDR_SENSOR_LIGHT = 0x23;


#endif // CONSTANTS_H