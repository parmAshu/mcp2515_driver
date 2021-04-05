/**
 * @author Ashutosh Singh Parmar
 * @file mcp2515_driver_pal_defs.h
 * @brief This file contains all the required type definitions.
*/
#ifndef MCP2515_DRIVER_PAL_DEFS
#define MCP2515_DRIVER_PAL_DEFS

#include <Arduino.h>
#include <SPI.h>

#define MSB_FIRST 1
#define LSB_FIRST 0

#define IDLE_HIGH 1
#define IDLE_LOW 0

#define LEADING_EDGE 1
#define TRAILING_EDGE 0

typedef struct mcp2515_driver_config{ 
    uint8_t ss_pin;
}mcp2515_driver_config;

#endif