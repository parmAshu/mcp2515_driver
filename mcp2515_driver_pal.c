/**
 * @author Ashutosh Singh Parmar
 * @file mcp2515_driver_pal.c
 * @brief This file contains the platform abstraction layer APIs.
*/

#include "mcp2515_driver_pal.h"

/**
 * @brief This PAL API will be called by core APIs to initialize the SPI port.
 * 
 * @param 
 * 1. void * data : pointer to a custom structure containing initialization information.
 * 2. uint8_t data_direction : Direction of shifting out data - MSB_FIRST or LSB_FIRST.
 * 3. uint8_t idle_level : The idle level of spi port - IDLE_HIGH OR IDLE_LOW.
 * 4. uint8_t shift_iedge : The edge at which data will be shifted out - LEADING or TRAILING.
 * 
 * @return NOTHING
*/
void pal_spi_init(void* data, uint8_t data_direction, uint8_t idle_level, uint8_t shift_edge)
{
    /* !...Platform Specific Code here...! */
}

/**
 * @brief This PAL API will be called by core APIs to select the mcp2515 chip.
 * 
 * @param 
 * NONE
 * 
 * @return NOTHING
*/
void pal_select_slave(void)
{
    /* !...Platform Specific Code here...! */
}

/**
 * @brief This PAL API will be called by core APIs to deselect the mcp2515 chip.
 * 
 * @param 
 * NONE
 * 
 * @return NOTHING
*/
void pal_deselect_slave(void)
{
    /* !...Platform Specific Code here...! */
}

/**
 * @brief This PAL API will be called by core APIs to send a byte over the SPI port.
 * 
 * @param 
 * 1. uint8_t byt : The data byte to send
 * 
 * @return 
 * NOTHING
*/
void pal_spi_send(uint8_t byt)
{
    /* !...Platform Specific Code here...! */
}

/**
 * @brief This PAL API will be called by core APIs to send a byte over the SPI port.
 * 
 * @param 
 * NONE
 * 
 * @return 
 * uint8_t : the data byte read over the SPI port.
*/
uint8_t pal_spi_read(void)
{
    /* !...Platform Specific Code here...! */
}