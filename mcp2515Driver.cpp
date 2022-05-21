/**
 * @author Ashutosh Singh Parmar
 * @file mcp2515_driver.c
 * @brief This file contains the core driver APIs.
*/

#include "mcp2515Driver.h"

static CAN_FRAME _frame={ can_standard, 0, 0, 0, {0,0,0,0,0,0,0,0} };



/* UTILITY FUNCTIONS ********************************************************************************************************/

/**
 * @brief Utility function to get the address of TXBnCTRL register.
*/
static uint8_t TXBnCTRL(uint8_t _buff)
{
	switch(_buff)
	{
		case 0:
			return TXB0CTRL;

		case 1:
			return TXB1CTRL;

		case 2:
			return TXB2CTRL;
	}

	return 0;
}

/**
 * @brief Utility function to get the address of RXBnCTRL register.
*/
static uint8_t RXBnCTRL(uint8_t _buff)
{
	switch(_buff)
	{
		case 0:
			return RXB0CTRL;

		case 1:
			return RXB1CTRL;
	}

	return 0;
}

/**
 * @brief Utility function to get the address of TXBnSIDH register.
*/
static uint8_t TXBnSIDH(uint8_t _buff)
{
	switch(_buff)
	{
		case 0:
			return TXB0SIDH;

		case 1:
			return TXB1SIDH;

		case 2:
			return TXB2SIDH;
	}

	return 0;
}

/**
 * @brief Utility function to get the address of RXBnSIDH register.
*/
static uint8_t RXBnSIDH(uint8_t _buff)
{
	switch(_buff)
	{
		case 0:
			return RXB0SIDH;

		case 1:
			return RXB1SIDH;
	}

	return 0;
}

/**
 * @brief Utility function to get the address of TXBnDLC register.
*/
static uint8_t TXBnDLC(uint8_t _buff)
{
	switch(_buff)
	{
		case 0:
			return TXB0DLC;

		case 1:
			return TXB1DLC;

		case 2:
			return TXB2DLC;
	}

	return 0;
}

/**
 * @brief Utility function to get the address of RXBnDLC register.
*/
static uint8_t RXBnDLC(uint8_t _buff)
{
	switch(_buff)
	{
		case 0:
			return RXB0DLC;

		case 1:
			return RXB1DLC;
	}

	return 0;
}

/**
 * @brief Utility function to get the address of RXMnSIDH register.
*/
static uint8_t RXMnSIDH(uint8_t _buff)
{
	switch(_buff)
	{
	case 0:
		return RXM0SIDH;

	case 1:
		return RXM1SIDH;
	}

	return 0;
}

/**
 * @brief Utility function to get the address of RXFnSIDH register.
*/
static uint8_t RXFnSIDH(uint8_t _buff)
{
	switch(_buff)
	{
	case 0:
		return RXF0SIDH;

	case 1:
		return RXF1SIDH;

	case 2:
		return RXF2SIDH;

	case 3:
		return RXF3SIDH;

	case 4:
		return RXF4SIDH;

	case 5:
		return RXF5SIDH;
	}
	return 0;
}
/*************************************************************************************************************************/



/**
 * @brief= This function gets the current mode of MCP2515 chip.
 *
 * @param NONE
 *
 * @return MCP_CAN_MODE : Current mode of operation of the mcp2515 chip
 * 		mcp_normal_mode
 * 		mcp_configuration_mode
 * 		mcp_sleep_mode
 * 		mcp_listen_only_mode
 */
MCP_CAN_MODE canGetMode(void)
{
	pal_select_slave();
	pal_spi_send( MCP_READ );
	pal_spi_send( CANSTAT );
	uint8_t _mode = pal_spi_read();
	_mode = _mode >> 5;
	_mode = _mode & 0X07;
	pal_deselect_slave();
	return _mode;
}


/**
 * @brief This function requests for a mode of MCP2515 chip.
 *
 * @param
 * 1. _mode : this is the mode requested by the calling function.
 *
 * @return
 * NOTHING
 */
void canRequestMode(MCP_CAN_MODE _mode)
{
	pal_select_slave();
	pal_spi_send( MCP_BIT_MODIFY );
	pal_spi_send( CANCTRL );
	pal_spi_send( 0XE0 );
	pal_spi_send( _mode << 5 );
	pal_deselect_slave();
	// wait till the mode is actually set in the chip
	while( canGetMode() != _mode );
}

/**
 * @brief This function sets the bit timing of the can bus chip by writing to the CNFn control registers.
 *
 * @param
 * 1. cnf1 : CNF1 register content
 * 2. cnf2 : CNF2 register content
 * 3. cnf3 : CNF3 register content
 *
 * @return
 * 		NOTHING
 */
void canSetBitTiming(unsigned char _cnf1, unsigned char _cnf2, unsigned char _cnf3)
{
	// selecting the MCP2515 chip using slave select line.
	pal_select_slave();
	// sending the write command
	pal_spi_send(MCP_WRITE);
	// sending the starting address for write command
	pal_spi_send(CNF3);
	//sending the data
	pal_spi_send(_cnf3);
	pal_spi_send(_cnf2);
	pal_spi_send(_cnf1);
	// de selecting the MCP2515 chip using slave select line
	pal_deselect_slave();
}

/**
 * @brief This function makes appropriate on chip initializations for the passed CAN data rate.
 *
 * @param
 * 1. data_rate : contains the CAN bus data rate in kbps.
 *
 * @return
 * 		NOTHING.
 */
void canBegin(void* data, uint16_t data_rate)
{

#ifdef AUTO_SPI_INITIALIZATION
	// initialize the SPI port for interacting with can.
	pal_spi_init( data, MSB_FIRST, IDLE_LOW, LEADING_EDGE);
#endif

	pal_delay_us(5);

	canRequestMode(mcp_configuration_mode);
	//setting the bit time for CAN bus
	switch(data_rate)
	{
		case 5:
#if		MCP_CHIP_FREQ==8000000
			canSetBitTiming(MCP_8MHz_5kBPS_CNF1, MCP_8MHz_5kBPS_CNF2, MCP_8MHz_5kBPS_CNF3);
#elif	MCP_CHIP_FREQ==16000000
			canSetBitTiming(MCP_16MHz_5kBPS_CNF1, MCP_16MHz_5kBPS_CNF2, MCP_16MHz_5kBPS_CNF3);
#elif	MCP_CHIP_FREQ==20000000
			canSetBitTiming(MCP_20MHz_40kBPS_CNF1, MCP_20MHz_40kBPS_CNF2, MCP_20MHz_40kBPS_CNF3);
#endif
		break;


		case 10:
#if		MCP_CHIP_FREQ==8000000
			canSetBitTiming(MCP_8MHz_10kBPS_CNF1, MCP_8MHz_10kBPS_CNF2, MCP_8MHz_10kBPS_CNF3);
#elif	MCP_CHIP_FREQ==16000000
			canSetBitTiming(MCP_16MHz_10kBPS_CNF1, MCP_16MHz_10kBPS_CNF2, MCP_16MHz_10kBPS_CNF3);
#elif	MCP_CHIP_FREQ==20000000
			canSetBitTiming(MCP_20MHz_40kBPS_CNF1, MCP_20MHz_40kBPS_CNF2, MCP_20MHz_40kBPS_CNF3);
#endif
		break;

		case 20:
#if		MCP_CHIP_FREQ==8000000
			canSetBitTiming(MCP_8MHz_20kBPS_CNF1, MCP_8MHz_20kBPS_CNF2, MCP_8MHz_20kBPS_CNF3);
#elif	MCP_CHIP_FREQ==16000000
			canSetBitTiming(MCP_16MHz_20kBPS_CNF1, MCP_16MHz_20kBPS_CNF2, MCP_16MHz_20kBPS_CNF3);
#elif	MCP_CHIP_FREQ==20000000
			canSetBitTiming(MCP_20MHz_40kBPS_CNF1, MCP_20MHz_40kBPS_CNF2, MCP_20MHz_40kBPS_CNF3);
#endif
		break;

		case 40:
#if		MCP_CHIP_FREQ==8000000
			canSetBitTiming(MCP_8MHz_40kBPS_CNF1, MCP_8MHz_40kBPS_CNF2, MCP_8MHz_40kBPS_CNF3);
#elif	MCP_CHIP_FREQ==16000000
			canSetBitTiming(MCP_16MHz_40kBPS_CNF1, MCP_16MHz_40kBPS_CNF2, MCP_16MHz_40kBPS_CNF3);
#elif	MCP_CHIP_FREQ==20000000
			canSetBitTiming(MCP_20MHz_40kBPS_CNF1, MCP_20MHz_40kBPS_CNF2, MCP_20MHz_40kBPS_CNF3);
#endif
		break;

		case 50:
#if		MCP_CHIP_FREQ==8000000
			canSetBitTiming(MCP_8MHz_50kBPS_CNF1, MCP_8MHz_50kBPS_CNF2, MCP_8MHz_50kBPS_CNF3);
#elif	MCP_CHIP_FREQ==16000000
			canSetBitTiming(MCP_16MHz_50kBPS_CNF1, MCP_16MHz_50kBPS_CNF2, MCP_16MHz_50kBPS_CNF3);
#elif	MCP_CHIP_FREQ==20000000
			canSetBitTiming(MCP_20MHz_50kBPS_CNF1, MCP_20MHz_50kBPS_CNF2, MCP_20MHz_50kBPS_CNF3);
#endif
		break;

		case 80:
#if		MCP_CHIP_FREQ==8000000
			canSetBitTiming(MCP_8MHz_80kBPS_CNF1, MCP_8MHz_80kBPS_CNF2, MCP_8MHz_80kBPS_CNF3);
#elif	MCP_CHIP_FREQ==16000000
			canSetBitTiming(MCP_16MHz_80kBPS_CNF1, MCP_16MHz_80kBPS_CNF2, MCP_16MHz_80kBPS_CNF3);
#elif	MCP_CHIP_FREQ==20000000
			canSetBitTiming(MCP_20MHz_80kBPS_CNF1, MCP_20MHz_80kBPS_CNF2, MCP_20MHz_80kBPS_CNF3);
#endif
		break;

		case 100:
#if		MCP_CHIP_FREQ==8000000
			canSetBitTiming(MCP_8MHz_100kBPS_CNF1, MCP_8MHz_100kBPS_CNF2, MCP_8MHz_100kBPS_CNF3);
#elif	MCP_CHIP_FREQ==16000000
			canSetBitTiming(MCP_16MHz_100kBPS_CNF1, MCP_16MHz_100kBPS_CNF2, MCP_16MHz_100kBPS_CNF3);
#elif	MCP_CHIP_FREQ==20000000
			canSetBitTiming(MCP_20MHz_100kBPS_CNF1, MCP_20MHz_100kBPS_CNF2, MCP_20MHz_100kBPS_CNF3);
#endif
		break;

		case 125:
#if		MCP_CHIP_FREQ==8000000
			canSetBitTiming(MCP_8MHz_125kBPS_CNF1, MCP_8MHz_125kBPS_CNF2, MCP_8MHz_125kBPS_CNF3);
#elif	MCP_CHIP_FREQ==16000000
			canSetBitTiming(MCP_16MHz_125kBPS_CNF1, MCP_16MHz_125kBPS_CNF2, MCP_16MHz_125kBPS_CNF3);
#elif	MCP_CHIP_FREQ==20000000
			canSetBitTiming(MCP_20MHz_125kBPS_CNF1, MCP_20MHz_125kBPS_CNF2, MCP_20MHz_125kBPS_CNF3);
#endif
		break;

		case 200:
#if		MCP_CHIP_FREQ==8000000
			canSetBitTiming(MCP_8MHz_200kBPS_CNF1, MCP_8MHz_200kBPS_CNF2, MCP_8MHz_200kBPS_CNF3);
#elif	MCP_CHIP_FREQ==16000000
			canSetBitTiming(MCP_16MHz_200kBPS_CNF1, MCP_16MHz_200kBPS_CNF2, MCP_16MHz_200kBPS_CNF3);
#elif	MCP_CHIP_FREQ==20000000
			canSetBitTiming(MCP_20MHz_200kBPS_CNF1, MCP_20MHz_200kBPS_CNF2, MCP_20MHz_200kBPS_CNF3);
#endif
		break;

		case 250:
#if		MCP_CHIP_FREQ==8000000
			canSetBitTiming(MCP_8MHz_250kBPS_CNF1, MCP_8MHz_250kBPS_CNF2, MCP_8MHz_250kBPS_CNF3);
#elif	MCP_CHIP_FREQ==16000000
			canSetBitTiming(MCP_16MHz_250kBPS_CNF1, MCP_16MHz_250kBPS_CNF2, MCP_16MHz_250kBPS_CNF3);
#elif	MCP_CHIP_FREQ==20000000
			canSetBitTiming(MCP_20MHz_250kBPS_CNF1, MCP_20MHz_250kBPS_CNF2, MCP_20MHz_250kBPS_CNF3);
#endif
		break;

		case 500:
#if		MCP_CHIP_FREQ==8000000
			canSetBitTiming(MCP_8MHz_500kBPS_CNF1, MCP_8MHz_500kBPS_CNF2, MCP_8MHz_500kBPS_CNF3);
#elif	MCP_CHIP_FREQ==16000000
			canSetBitTiming(MCP_16MHz_500kBPS_CNF1, MCP_16MHz_500kBPS_CNF2, MCP_16MHz_500kBPS_CNF3);
#elif	MCP_CHIP_FREQ==20000000
			canSetBitTiming(MCP_20MHz_500kBPS_CNF1, MCP_20MHz_500kBPS_CNF2, MCP_20MHz_500kBPS_CNF3);
#endif
		break;

		case 1000:
#if		MCP_CHIP_FREQ==8000000
			canSetBitTiming(MCP_8MHz_1000kBPS_CNF1, MCP_8MHz_1000kBPS_CNF2, MCP_8MHz_1000kBPS_CNF3);
#elif	MCP_CHIP_FREQ==16000000
			canSetBitTiming(MCP_16MHz_1000kBPS_CNF1, MCP_16MHz_1000kBPS_CNF2, MCP_16MHz_1000kBPS_CNF3);
#elif	MCP_CHIP_FREQ==20000000
			canSetBitTiming(MCP_20MHz_1000kBPS_CNF1, MCP_20MHz_1000kBPS_CNF2, MCP_20MHz_1000kBPS_CNF3);
#endif
		break;

		default:
#if		MCP_CHIP_FREQ==8000000
			canSetBitTiming(MCP_8MHz_125kBPS_CNF1, MCP_8MHz_125kBPS_CNF2, MCP_8MHz_125kBPS_CNF3);
#elif	MCP_CHIP_FREQ==16000000
			canSetBitTiming(MCP_16MHz_125kBPS_CNF1, MCP_16MHz_125kBPS_CNF2, MCP_16MHz_125kBPS_CNF3);
#elif	MCP_CHIP_FREQ==20000000
			canSetBitTiming(MCP_20MHz_125kBPS_CNF1, MCP_20MHz_125kBPS_CNF2, MCP_20MHz_125kBPS_CNF3);
#endif
		break;
	}

	canRequestMode(mcp_normal_mode);
}

/**
 * @brief This function reads the transmit error counter of for the chip.
 *
 * @param
 * NOTHING
 *
 * @return
 * THE VALUE OF TEC.
 */
uint8_t canGetTEC(void)
{
	pal_select_slave();
	pal_spi_send( MCP_READ );
	pal_spi_send( TEC );
	uint8_t _tec=pal_spi_read();
	pal_deselect_slave();
	return _tec;
}

/**
 * @brief This function reads the receive error counter of the chip.
 *
 * @param
 * NOTHING
 *
 * @return
 * THE VALUE OF REC.
 */
uint8_t canGetREC(void)
{
	pal_select_slave();
	pal_spi_send( MCP_READ );
	pal_spi_send( REC );
	uint8_t _rec=pal_spi_read();
	pal_deselect_slave();
	return _rec;
}

/**
 * @brief This function resets the MCP2515 chip by sending the SPI RESET instruction.
 * 
 * @param NONE
 * 
 * @return NOTHING.
 */
void canChipReset(void)
{
	pal_select_slave();
	pal_spi_send( MCP_RESET );
	pal_deselect_slave();
}



/*
 * 		!	 C A N		T R A N S M I T			R O U T I N E S		!
 */


/**
 * @brief This function gets the state of one of the transmit buffers. It informs whether the buffer is occupied or not.
 *
 * @param
 * 1. _buff : the buffer number.
 *
 * @return
 * 1 : IF THE BUFFER IS AVAILABLE
 * 2 : IF THE BUFFER IS NOT AVAILABLE
 */
uint8_t canIsFreeTX(uint8_t _buff)
{
	pal_select_slave();
	pal_spi_send(MCP_READ);
	pal_spi_send( TXBnCTRL(_buff) );
	uint8_t tx=pal_spi_read();
	pal_deselect_slave();
	if( ( tx & (1<<TXREQ) ) )
		return 0;
	else
		return 1;
}

/**
 * @brief This function sets the priority for a transmit buffer.
 *
 * @param
 * 1. _buff : the buffer number
 * 2. _priority : the buffer priority
 *
 * @return
 * 1. SUCCESS
 * 2. FAILED
 */
uint8_t canSetPriorityTX(uint8_t _txBuffer, uint8_t _priority)
{
	if( canIsFreeTX(_txBuffer) )
	{
		pal_select_slave();
		pal_spi_send(MCP_BIT_MODIFY);
		pal_spi_send( TXBnCTRL(_txBuffer) );
		pal_spi_send(0X03);
		pal_spi_send(_priority);
		pal_deselect_slave();
		return 1;
	}
	else
		// message transmission pending and thus, the operation could not be performed
		return 0;
}

/**
 * @brief This function writes standard identifier to one of the three transmit buffers.
 *
 * @param
 * 1. _buff : the buffer number
 * 2. _sid : 11 bit standard identifier
 *
 * @return
 * 1. SUCCESS
 * 2. FAILED
 */
uint8_t canSetSID_TX(uint8_t _buff, uint16_t _sid)
{
	if( canIsFreeTX(_buff) )
	{
		pal_select_slave();
		pal_spi_send(MCP_WRITE);
		pal_spi_send(TXBnSIDH(_buff));
		pal_spi_send( (_sid>>3) );
		pal_spi_send( (_sid<<5) );
		pal_deselect_slave();

		return 1;
	}
	else
		return 0;
}

/**
 * @brief This function writes the 29 bit extended ID to one of the three transmit buffers. The function
 * automatically enables the extended ID frame format for that transmit buffer.
 *
 * @param
 * 1. _buff : the transmit buffer number.
 * 2. _eid : 29 bits extended ID.
 *
 * @return
 * 1. SUCCESS
 * 2. FAILED
 */
uint8_t canSetEID_TX(uint8_t  _buff, uint32_t _eid)
{
	if( canIsFreeTX(_buff) )
	{
		pal_select_slave();
		pal_spi_send(MCP_WRITE);
		pal_spi_send(TXBnSIDH(_buff));
		pal_spi_send( (_eid >> 21) );
		//enabling the extended ID format in transmit buffer 0
		pal_spi_send(  (_eid >> 13 & 0XE0) | (_eid>>16 & 3) | (1<<EXIDE) );
		pal_spi_send( (_eid >> 8) );
		pal_spi_send( _eid );
		pal_deselect_slave();

		return 1;
	}
	else
		return 0;
}

/**
 * @brief This function requests transmission of CAN frame by setting the corresponding TXREQ.
 *
 * @param
 * 1. _buff : the buffer number.
 *
 * @return
 * NOTHING
 */
void canSetTXREQ(uint8_t _buff)
{
	pal_select_slave();

	pal_spi_send( MCP_BIT_MODIFY );
	pal_spi_send( TXBnCTRL(_buff) );
	pal_spi_send( (1<< TXREQ) );
	pal_spi_send( 0XFF );

	pal_deselect_slave();

}


/**
 * @brief This function requests transmission of CAN frame by RTS command to the mcp2515 chip.
 *
 * @param
 * 1. _buff : the buffer number.
 *
 * @return
 * NOTHING
 */
void canRequestTransmission_wRTS(uint8_t _buff)
{
	pal_select_slave();
	switch(_buff)
	{
		case 0:
				pal_spi_send( MCP_RTS_TX0 );
		break;

		case 1:
				pal_spi_send( MCP_RTS_TX1 );
		break;

		case 2:
				pal_spi_send( MCP_RTS_TX2 );
		break;
	}
	pal_deselect_slave();
}


/**
 * @brief This function initiates transmission through one of the three transmit buffers.
 * This function does not sets the ID.
 *
 * @param
 * 1. _buff : the transmit buffer number to use for transmission.
 * 2. _num_bytes : number of data bytes.
 * 3. _data[8] : the actual data bytes.
 *
 * @return
 * 1. SUCCESS
 * 2. FAILED
 */
uint8_t canTransmit(uint8_t _buff, uint8_t _num_bytes, unsigned char _data[8])
{
	if( canIsFreeTX(_buff) )
	{
		pal_select_slave();
		pal_spi_send(MCP_WRITE);
		pal_spi_send(TXBnDLC(_buff));
		pal_spi_send(_num_bytes);
		// sending the data bytes;
		for(uint8_t i=0; i< _num_bytes; i++)
		{
			pal_spi_send( _data[i] );
		}
		pal_deselect_slave();

		canRequestTransmission_wRTS(_buff);

		return 1;
	}
	else
		return 0;
}

/**
 * @brief This function initiates transmission through one of the three transmit buffers.
 * This function sets ID along with data.
 *
 * @param
 * 1. _buff : the transmit buffer to use.
 * 2. _sid : standard ID for the data frame.
 * 3. _num_bytes : number of data bytes.
 * 4. _data : the actual data bytes.
 *
 * @return
 * 1. SUCCESS
 * 2. FAILED
 *
 * @note
 * PASS SID WITHOUT LEFT SHIFTING TO ADJUST FOR THE REGISTER POSTION, THIS IS AUTOMATICAALY DONE BY THE FUNCTION.
 */
uint8_t canTransmit_wSID(uint8_t _buff, uint16_t _sid, uint8_t _num_bytes, unsigned char _data[8])
{
	if( canIsFreeTX(_buff) )
	{
		pal_select_slave();

		pal_spi_send( MCP_WRITE );
		pal_spi_send( TXBnSIDH(_buff) );

		pal_spi_send( (_sid>>3) );
		pal_spi_send( (_sid<<5) );
		pal_spi_send( 0X00 );
		pal_spi_send( 0X00 );

		pal_spi_send(_num_bytes);
		// sending the data bytes;
		for(uint8_t i=0; i< _num_bytes; i++)
		{
			pal_spi_send( _data[i] );
		}
		pal_deselect_slave();

		canRequestTransmission_wRTS(_buff);

		return 1;
	}
	else
		return 0;
}

/**
 * @brief This function initiates transmission through one of the three transmit buffers.
 *  This function sets ID along with data.
 *
 * @param
 * 1. _buff : the transmit buffer number.
 * 1. _eid : extended ID for the data frame.
 * 2. _num_bytes : number of data bytes.
 * 3. _data : the actual data bytes.
 *
 * @return
 * 1. SUCCESS
 * 2. FAILED
 *
 * @note
 * PERFORM NO SHIFTING WHILE PASSING THE EXTENDED ID TO MAKE ADJUSTMENTS FOR THE CHIP REGISTERS. THIS IS
 * AUTOMATICALLY HANDLED BY THE FUNCTION.
 */
uint8_t canTransmit_wEID(uint8_t _buff, uint32_t _eid, uint8_t _num_bytes, unsigned char _data[8])
{
	if( canIsFreeTX(_buff) )
	{
		pal_select_slave();

		pal_spi_send( MCP_WRITE );
		pal_spi_send( TXBnSIDH(_buff) );

		pal_spi_send( (_eid >> 21) );
		//enabling the extended ID format in transmit buffer 0
		pal_spi_send(  (_eid >> 13 & 0XE0) | (_eid>>16 & 3) | (1<<EXIDE) );
		pal_spi_send( (_eid >> 8) );
		pal_spi_send( _eid );

		pal_spi_send(_num_bytes);
		// sending the data bytes;
		for(uint8_t i=0; i< _num_bytes; i++)
		{
			pal_spi_send( _data[i] );
		}
		pal_deselect_slave();

		canRequestTransmission_wRTS(_buff);

		return 1;
	}
	else
		return 0;

}

/**
 * @brief This function initiates transmission through one of the three transmit buffers.
 * This function sets ID along with data.
 *
 * @param
 * 1. _buff : the transmit buffer to use.
 * 2. _sid : standard ID for the data frame.
 *
 * @return
 * 1. SUCCESS
 * 2. FAILED
 *
 * @note
 * PASS SID WITHOUT LEFT SHIFTING TO ADJUST FOR THE REGISTER POSTION, THIS IS AUTOMATICAALY DONE BY THE FUNCTION.
 */
uint8_t canTransmitRemote_wSID(uint8_t _buff, uint16_t _sid)
{
	if( canIsFreeTX(_buff) )
	{
		pal_select_slave();

		pal_spi_send( MCP_WRITE );
		pal_spi_send( TXBnSIDH(_buff) );

		pal_spi_send( (_sid>>3) );
		pal_spi_send( (_sid<<5) );
		pal_spi_send( 0X00 );
		pal_spi_send( 0X00 );
		pal_spi_send( (1<<RTR));

		pal_deselect_slave();

		canRequestTransmission_wRTS(_buff);

		return 1;
	}
	else
		return 0;
}

/**
 * @brief This function initiates Remote transmission request through one of the three transmit buffers.
 *  This function sets ID along with data.
 *
 * @param
 * 1. _buff : the transmit buffer number.
 * 1. _eid : extended ID for the data frame.
 *
 * @return
 * 1. SUCCESS
 * 2. FAILED
 *
 * @note
 * PERFORM NO SHIFTING WHILE PASSING THE EXTENDED ID TO MAKE ADJUSTMENTS FOR THE CHIP REGISTERS. THIS IS
 * AUTOMATICALLY HANDLED BY THE FUNCTION.
 */
uint8_t canTransmitRemote_wEID(uint8_t _buff, uint32_t _eid)
{
	if( canIsFreeTX(_buff) )
	{
		pal_select_slave();

		pal_spi_send( MCP_WRITE );
		pal_spi_send( TXBnSIDH(_buff) );

		pal_spi_send( (_eid >> 21) );
		//enabling the extended ID format in transmit buffer 0
		pal_spi_send(  (_eid >> 13 & 0XE0) | (_eid>>16 & 3) | (1<<EXIDE) );
		pal_spi_send( (_eid >> 8) );
		pal_spi_send( _eid );
		pal_spi_send( (1<<RTR) );

		pal_deselect_slave();

		canRequestTransmission_wRTS(_buff);

		return 1;
	}
	else
		return 0;
}

/**
 * @brief This function gets the error status of a transmit buffer.
 *
 * @param
 * 1. _buff : the transmit buffer number.
 *
 * @return
 * SPECIAL ENUM :
 * 1. mcp_no_error_tx : if there is no error in transmission.
 * 2. mcp_tx_lost_arbitration : if the message lost arbitration during transmission.
 * 3. mcp_tx_message_error : if there was some other error during message transmission.
 */
MCP_CAN_TX_ERROR canGetErrorTX(uint8_t _buff)
{
	uint8_t _error;

	pal_select_slave();
	pal_spi_send( MCP_READ );
	pal_spi_send( TXBnCTRL(_buff) );
	_error=pal_spi_read();
	pal_deselect_slave();

	if( _error & (1<<MLOA))
		return mcp_tx_lost_arbitration;
	else if( _error & (1<<TXERR))
		return mcp_tx_message_error;
	else
		return mcp_no_error_tx;
}

/**
 * @brief This function clears the MERRF flag.
 *
 * @param
 * NOTHING
 *
 * @return
 * NOTHING
 */
void canClearMessageError(void)
{
	pal_select_slave();
	pal_spi_send( MCP_BIT_MODIFY );
	pal_spi_send( CANINTF );
	pal_spi_send( (1<<MERRF) );
	pal_spi_send( 0X00 );
	pal_deselect_slave();
}

/**
 * @brief This function aborts the message of any of the three transmit buffers.
 * The abort is achieved by clearing the TXREQ bit. This method does not set the abort flag.
 *
 * @param
 * 1. _buff : the transmit buffer number.
 *
 * @return
 * NOTHING
 */
void canAbortTX(uint8_t _buff)
{
	pal_select_slave();

	pal_spi_send( MCP_BIT_MODIFY );
	pal_spi_send( TXBnCTRL(_buff) );
	pal_spi_send( (1<<TXREQ) );
	pal_spi_send( 0X00 );

	pal_deselect_slave();
}



/*
 * 		!	 C A N		R E C E I V E   	R O U T I N E S		!
 */


/**
 * @brief This function enables Filters on one of the two receive buffers.
 *
 * @param
 * 1. _buff : the receive buffer number.
 *
 * @return
 * NOTHING
 */
void canEnableFilterRX(uint8_t _buff)
{
	pal_select_slave();
	pal_spi_send( MCP_BIT_MODIFY );
	pal_spi_send( RXBnCTRL(_buff));
	pal_spi_send( (1<<RXM1) | (1<<RXM0) );
	pal_spi_send( 0 );
	pal_deselect_slave();
}

/**
 * @brief This function disables Filters on one of the two receive buffers.
 *
 * @param
 * 1. _buff : the receive buffer number.
 *
 * @return
 * NOTHING
 */
void canDisableFilterRX(uint8_t _buff)
{
	pal_select_slave();
	pal_spi_send( MCP_BIT_MODIFY );
	pal_spi_send( RXBnCTRL(_buff) );
	pal_spi_send( (1<<RXM1) | (1<<RXM0) );
	pal_spi_send( (1<<RXM1) | (1<<RXM0) );
	pal_deselect_slave();
}

/**
 * @brief This function makes available one the two receive buffer for available CAN data.
 * The  function clears the RXnIF flags for this purpose.
 *
 * @param
 * 1. _buff : the receive buffer number.
 *
 * @return
 * NOTHING
 */
void enableRX(uint8_t _buff)
{
	pal_select_slave();

	pal_spi_send( MCP_BIT_MODIFY );
	pal_spi_send( CANINTF );
	switch(_buff)
	{
	case 0:
	pal_spi_send( (1<<RX0IF) );
	break;

	case 1:
	pal_spi_send( (1<<RX1IF) );
	break;
	}
	// clearing the interrupt flag and make the buffer available for incoming CAN data
	pal_spi_send( 0 );

	pal_deselect_slave();
}


/**
 * @brief This function checks if one of the two buffers has new CAN frame.
 *
 * @param
 * 1. _buff : the receive buffer number.
 *
 * @return
 * NOTHING
 */
uint8_t canIsFilledRX(uint8_t _buff)
{
	uint8_t flag=0;

	pal_select_slave();
	pal_spi_send( MCP_RX_STATUS );
	uint8_t _ctrl=pal_spi_read();
	_ctrl = _ctrl >> 6;
	pal_deselect_slave();

	switch(_buff)
	{
	case 0:
	if( _ctrl == 1 || _ctrl == 3)
		flag=1;
	else
		flag=0;
	break;

	case 1:
	if( _ctrl ==2 || _ctrl == 3)
		flag=1;
	else
		flag=0;
	break;
	}

	return flag;
}

/**
 * @brief - This function sets the mask registers for one of the two receive buffers.
 *
 * @param
 * 1. _num : the receive buffer number.
 * 2. _mask : the actual mask data.
 *
 * @return
 * NOTHING
 *
 * @note
 * The function writes the lower order 29 bits from the _mask variable into the mask registers and thus one
 * must be careful while using only the Standard CAN frames as then the mask bits that actually matter will
 * be shifted left by 18 bits.
 */
void canSetMaskRX(uint8_t _num, uint32_t _mask)
{
	canRequestMode(mcp_configuration_mode);

	pal_select_slave();

	pal_spi_send( MCP_WRITE );
	pal_spi_send( RXMnSIDH(_num) );
	pal_spi_send( (_mask >> 21) );
	pal_spi_send(  (_mask >> 13 & 0XE0) | (_mask>>16 & 3) );
	pal_spi_send( (_mask >> 8) );
	pal_spi_send( _mask );

	pal_deselect_slave();

	canRequestMode(mcp_normal_mode);
}

/**
 * @brief This function sets the mask registers for one of the two receive buffers.
 *
 * @param
 * 1. _num : the filter number.
 * 2. _frame : the type of frame to apply the specific filter to, can_standard or can_extended.
 * 3. _filter : the actual mask data.
 *
 * @return
 * NOTHING
 *
 * @note
 * The function writes the lower order 29 bits from the _mask variable into the filter registers and thus one
 * must be careful while using only the Standard CAN frames as then the mask bits that actually matter will
 * be shifted left by 18 bits.
 */
void canSetFilterRX(uint8_t _num, CAN_FRAME_TYPE _frame, uint32_t _filter)
{
	canRequestMode(mcp_configuration_mode);

	pal_select_slave();

	pal_spi_send( MCP_WRITE );
	pal_spi_send( RXFnSIDH(_num) );
	pal_spi_send( (_filter >> 21) );
	if(_frame == can_standard)
	{
		pal_spi_send( (_filter >> 13 & 0XE0) | (_filter>>16 & 3) );
		pal_deselect_slave();
		return;
	}
	else if(_frame == can_extended)
		pal_spi_send( (_filter >> 13 & 0XE)  | (_filter>>16 & 3) | (1<<EXIDE) );
	pal_spi_send( (_filter >> 8) );
	pal_spi_send( _filter );

	pal_deselect_slave();

	canRequestMode(mcp_normal_mode);

}

/**
 * @brief This function gets the complete CAN data frame from one of the two receive buffers.
 *
 * @param
 * 1. _buff : the receive buffer number.
 *
 * @return
 * special structure containing entire CAN data frame and its details.
 *
 */
CAN_FRAME canGetFrame_wID(uint8_t _buff)
{
	uint8_t _ctrl;
	pal_select_slave();
	pal_spi_send( MCP_READ );
	pal_spi_send( RXBnCTRL(_buff) );
	_ctrl=pal_spi_read();
	pal_deselect_slave();

	if( _ctrl & (1<<RXRTR) )
		_frame.isRemote=1;
	else
		_frame.isRemote=0;

	uint32_t _id=0;
	uint32_t ch;
	pal_select_slave();
	switch(_buff)
	{
	case 0:
	pal_spi_send( MCP_READ_RX0_ID );
	break;

	case 1:
	pal_spi_send( MCP_READ_RX1_ID );
	break;
	}

	// reading the SIDH register
	ch=(uint32_t)pal_spi_read();
	_id |= (ch<<3);
	// reading the SIDL register
	ch=(uint32_t)pal_spi_read();
	_id |= ( ( ch>>5 ) & (0X07) );

	// if the id is extended
	if( ch & (1<<IDE) )
	{
		_frame.type = can_extended;
		_id = _id << 18;
		_id |= ( (ch & 0X03) << 16 );
		//reading RXB0EID8
		ch=(uint32_t)pal_spi_read();
		_id |= (ch<<8);
		//reading the RXB0ID0
		ch=(uint32_t)pal_spi_read();
		_id |= (ch);
	}
	else
	{
		_frame.type = can_standard;
		// flushing the extended ID bytes in case the frame is standard
		pal_spi_read();
		pal_spi_read();
	}

	_frame.ID=_id;

	if(_frame.isRemote)
	{
		_frame.DLC=0;
		pal_deselect_slave();
		return _frame;
	}

	// reading the data length code from CAN frame
	_frame.DLC=pal_spi_read();
	// reading the data bytes
	for(uint8_t i=0; i<8; i++)
	{
		_frame.DATA[i]=pal_spi_read();
	}

	pal_deselect_slave();

	return _frame;
}
