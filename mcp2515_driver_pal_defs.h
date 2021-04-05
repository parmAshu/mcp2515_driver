/**
 * @author Ashutosh Singh Parmar
 * @file mcp2515_driver_pal_defs.h
 * @brief This file contains all the required type definitions.
*/
#ifndef MCP2515_DRIVER_PAL_DEFS
#define MCP2515_DRIVER_PAL_DEFS

/**
 * Include Platform specfic header files over here.
 * 
 * Define any custom types below (if required).
*/

#define MSB_FIRST 1
#define LSB_FIRST 0

#define IDLE_HIGH 1
#define IDLE_LOW 0

#define LEADING_EDGE 1
#define TRAILING_EDGE 0

/**
 * If the platform does not support types - 1. uint8_t, uint16_t, uin32_t then uncomment and stuitably modify the following lines.
 * 
*/
// typedef unsigned char uint8_t;
// typedef unigend short int uint16_t;
// typedef unsigned int uint32_t;
// typedef unsigned long uin64_t;

#endif