/**
 * @author Ashutosh Singh Parmar
 * @file mcp2515_driver_pal.h
 * @brief This file contains function declarations for platform abstraction layer APIs.
*/
#ifndef MCP2515_DRIVER_PAL
#define MCP2515_DRIVER_PAL

#include "mcp2515_driver_pal_defs.h"

/**
 * @brief This PAL API will be called by core APIs to suspend execution by '_int' milliseconds.
 * 
 * @param 
 * 1. uint32_t _int : number of milliseconds.
 * 
 * @return
 * NOTHING
*/
inline void pal_delay_ms(uint32_t _int)
{
    /* !...Platform Specific Code here...! */
}

/**
 * @brief This PAL API will be called by core APIs to suspend execution by '_int' microseconds.
 * 
 * @param 
 * 1. uint32_t _int : number of microseconds.
 * 
 * @return
 * NOTHING
*/
inline void pal_delay_us(uint32_t _int)
{
    /* !...Platform Specific Code here...! */
}


/**
 * @brief This PAL API will be called by core APIs to initialize the SPI port.
 * 
 * @param 
 * 1. void * data : pointer to a custom structure containing initialization information.
 * 2. uint8_t data_direction : Direction of shifting out data - MSB_FIRST or LSB_FIRST.
 * 3. uint8_t idle_level : The idle level of spi port - IDLE_HIGH OR IDLE_LOW.
 * 4. uint8_t shift_iedge : The edge at which data will be shifted out - RISING or FALLING.
 * 
 * @return NOTHING
*/
void pal_spi_init(void*, uint8_t, uint8_t, uint8_t);

/**
 * @brief This PAL API will be called by core APIs to select the mcp2515 chip.
 * 
 * @param 
 * NONE
 * 
 * @return NOTHING
*/
void pal_select_slave(void);

/**
 * @brief This PAL API will be called by core APIs to deselect the mcp2515 chip.
 * 
 * @param 
 * NONE
 * 
 * @return NOTHING
*/
void pal_deselect_slave(void);

/**
 * @brief This PAL API will be called by core APIs to send a byte over the SPI port.
 * 
 * @param 
 * 1. uint8_t byt : The data byte to send
 * 
 * @return 
 * NOTHING
*/
void pal_spi_send(uint8_t byt);

/**
 * @brief This PAL API will be called by core APIs to send a byte over the SPI port.
 * 
 * @param 
 * NONE
 * 
 * @return 
 * uint8_t : the data byte read over the SPI port.
*/
uint8_t pal_spi_read(void);


#endif