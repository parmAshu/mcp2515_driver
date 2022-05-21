/**
 * @author Ashutosh Singh Parmar
 * @file mcp2515_driver.h
 * @brief This file contains function declarations for core driver APIs.
*/
#ifndef MCP2515_DRIVER
#define MCP2515_DRIVER

#include "mcp2515_driver_pal.h"

/**
 * @brief ADDRESS OF MCP2515 CONTROL REGISTERS.
 */
#define BFPCTRL 0X0C	/* bit modify */

#define TXRTSCTRL 0X0D	/* bit modify */

#define CANSTAT 0XFE

#define CANCTRL 0XFF	/* bit modify */

#define TEC 0X1C

#define REC 0X1D

#define CNF3 0X28	/* bit modify */

#define CNF2 0X29	/* bit modify */

#define CNF1 0X2A	/* bit modify */

#define CANINTE 0X2B	/* bit modify */

#define CANINTF 0X2C	/* bit modify */

#define EFLG 0X2D	/* bit modify */

#define TXB0CTRL 0X30	/* bit modify */

#define TXB1CTRL 0X40	/* bit modify */

#define TXB2CTRL 0X50	/* bit modify */

#define RXB0CTRL 0X60	/* bit modify */

#define RXB1CTRL 0X70	/* bit modify */


/**
 * @brief MCP2515 INSTRUCTIONS
 */

#define MCP_RESET 0XC0

#define MCP_READ  0X03

#define MCP_WRITE 0X02

#define MCP_RTS_TX0 0X81

#define MCP_RTS_TX1 0X82

#define MCP_RTS_TX2 0X84

#define MCP_RTS_TX0_TX1 0X83

#define MCP_RTS_TX0_TX2 0X85

#define MCP_RTS_TX1_TX2 0X86

#define MCP_RTS_ALL 0X87

#define MCP_READ_STATUS 0XA0

#define MCP_RX_STATUS 0XB0

#define MCP_BIT_MODIFY 0X05

#define MCP_LOAD_TX0_ID 0x40

#define MCP_LOAD_TX0_DATA 0x41

#define MCP_LOAD_TX1_ID 0x42

#define MCP_LOAD_TX1_DATA 0x43

#define MCP_LOAD_TX2_ID 0x44

#define MCP_LOAD_TX2_DATA 0x45

#define MCP_READ_RX0_ID 0x90

#define MCP_READ_RX0_DATA 0x92

#define MCP_READ_RX1_ID 0x94

#define MCP_READ_RX1_DATA 0x96



/**
 * @brief ADDRESSES OF MCP2515 RECEIVE BUFFER REGISTERS
 */

#define RXB0SIDH 0X61

#define RXB0SIDL 0X62

#define RXB0EID8 0X63

#define RXB0EID0 0X64

#define RXB0DLC 0X65

#define RXB0D0 0X66

#define RXB0D1 0X67

#define RXB0D2 0X68

#define RXB0D3 0X69

#define RXB0D4 0X6A

#define RXB0D5 0X6B

#define RXB0D6 0X6C

#define RXB0D7 0X6D



#define RXB1SIDH 0X71

#define RXB1SIDL 0X72

#define RXB1EID8 0X73

#define RXB1EID0 0X74

#define RXB1DLC 0X75

#define RXB1D0 0X76

#define RXB1D1 0X77

#define RXB1D2 0X78

#define RXB1D3 0X79

#define RXB1D4 0X7A

#define RXB1D5 0X7B

#define RXB1D6 0X7C

#define RXB1D7 0X7D


/**
 * @brief ADDRESSES OF MCP2515 TRANSMIT BUFFERS
 */

#define TXB0SIDH 0X31

#define TXB0SIDL 0X32

#define TXB0EID8 0X33

#define TXB0EID0 0X34

#define TXB0DLC 0X35

#define TXB0D0 0X36

#define TXB0D1 0X37

#define TXB0D2 0X38

#define TXB0D3 0X39

#define TXB0D4 0X3A

#define TXB0D5 0X3B

#define TXB0D6 0X3C

#define TXB0D7 0X3D


#define TXB1SIDH 0X41

#define TXB1SIDL 0X42

#define TXB1EID8 0X43

#define TXB1EID0 0X44

#define TXB1DLC 0X45

#define TXB1D0 0X46

#define TXB1D1 0X47

#define TXB1D2 0X48

#define TXB1D3 0X49

#define TXB1D4 0X4A

#define TXB1D5 0X4B

#define TXB1D6 0X4C

#define TXB1D7 0X4D


#define TXB2SIDH 0X51

#define TXB2SIDL 0X52

#define TXB2EID8 0X53

#define TXB2EID0 0X54

#define TXB2DLC 0X55

#define TXB2D0 0X56

#define TXB2D1 0X57

#define TXB2D2 0X58

#define TXB2D3 0X59

#define TXB2D4 0X5A

#define TXB2D5 0X5B

#define TXB2D6 0X5C

#define TXB2D7 0X5D

/**
 * @brief MCP2515 MASKS AND FILTERS.
 */

#define RXF0SIDH 0x00

#define RXF0SIDL 0x01

#define RXF0EID8 0x02

#define RXF0EID0 0x03


#define RXF1SIDH 0x04

#define RXF1SIDL 0x05

#define RXF1EID8 0x06

#define RXF1EID0 0x07


#define RXF2SIDH 0x08

#define RXF2SIDL 0x09

#define RXF2EID8 0x0A

#define RXF2EID0 0x0B


#define RXF3SIDH 0X10

#define RXF3SIDL 0X11

#define RXF3EID8 0X12

#define RXF3EID0 0X13


#define RXF4SIDH 0X14

#define RXF4SIDL 0X15

#define RXF4EID8 0X16

#define RXF4EID0 0X17


#define RXF5SIDH 0X18

#define RXF5SIDL 0X19

#define RXF5EID8 0X1A

#define RXF5EID0 0X1B


#define RXM0SIDH 0X20

#define RXM0SIDL 0X21

#define RXM0EID8 0X23

#define RXM0EID0 0X24


#define RXM1SIDH 0X25

#define RXM1SIDL 0X26

#define RXM1EID8 0X27

#define RXM1EID0 0X28

/**
 * BITS
 */

/** 
 * @brief TXBnCTRL
 */
#define ABTF 6
#define MLOA 5
#define TXERR 4
#define TXREQ 3
#define TXP1 1
#define TXP0 0

/**
 * @brief TXBnSIDL, RXFnSIDL
*/
#define EXIDE 3

/**
 * @brief TXBnDLC
 */
#define RTR 6

/**
 * @brief CANCTRL
 */
#define REQOP2 7
#define REQOP1 6
#define REQOP0 5
#define ABAT 4
#define OSM 3
#define CLKEN 2
#define CLKPRE1 1
#define CLKPRE0 0

/**
 * @brief CANSTAT
*/
#define OPMOD2 7
#define OPMOD1 6
#define OPMOD0 5
#define ICOD2 3
#define ICOD1 2
#define ICOD0 1

/**
 * @brief CANINTF
*/
#define MERRF 7
#define WAKIF 6
#define ERRIF 5
#define TX2IF 4
#define TX1IF 3
#define TX0IF 2
#define RX1IF 1
#define RX0IF 0

/**
 * @brief CANINTE
*/
#define MERRE 7
#define WAKIE 6
#define ERRIE 5
#define TX2IE 4
#define TX1IE 3
#define TX0IE 2
#define RX1IE 1
#define RX0IE 0

/**
 * @brief RXBnCTRL
*/
#define RXM1 6
#define RXM0 5
#define RXRTR 3
#define BUKT 2
#define BUKT1 1
#define FILHIT00 0
#define FILHIT21 2
#define FILHIT11 1
#define FILHIT10 0

/**
 * @brief RXBnSIDL
*/
#define IDE 3

/**
 * @brief speed 16M
*/

#define MCP_16MHz_1000kBPS_CNF1 (0x00)
#define MCP_16MHz_1000kBPS_CNF2 (0xD0)
#define MCP_16MHz_1000kBPS_CNF3 (0x82)

#define MCP_16MHz_500kBPS_CNF1 (0x00)
#define MCP_16MHz_500kBPS_CNF2 (0xF0)
#define MCP_16MHz_500kBPS_CNF3 (0x86)

#define MCP_16MHz_250kBPS_CNF1 (0x41)
#define MCP_16MHz_250kBPS_CNF2 (0xF1)
#define MCP_16MHz_250kBPS_CNF3 (0x85)

#define MCP_16MHz_200kBPS_CNF1 (0x01)
#define MCP_16MHz_200kBPS_CNF2 (0xFA)
#define MCP_16MHz_200kBPS_CNF3 (0x87)

#define MCP_16MHz_125kBPS_CNF1 (0x03)
#define MCP_16MHz_125kBPS_CNF2 (0xF0)
#define MCP_16MHz_125kBPS_CNF3 (0x86)

#define MCP_16MHz_100kBPS_CNF1 (0x03)
#define MCP_16MHz_100kBPS_CNF2 (0xFA)
#define MCP_16MHz_100kBPS_CNF3 (0x87)

#define MCP_16MHz_95kBPS_CNF1 (0x03)
#define MCP_16MHz_95kBPS_CNF2 (0xAD)
#define MCP_16MHz_95kBPS_CNF3 (0x07)

#define MCP_16MHz_83k3BPS_CNF1 (0x03)
#define MCP_16MHz_83k3BPS_CNF2 (0xBE)
#define MCP_16MHz_83k3BPS_CNF3 (0x07)

#define MCP_16MHz_80kBPS_CNF1 (0x03)
#define MCP_16MHz_80kBPS_CNF2 (0xFF)
#define MCP_16MHz_80kBPS_CNF3 (0x87)

#define MCP_16MHz_50kBPS_CNF1 (0x07)
#define MCP_16MHz_50kBPS_CNF2 (0xFA)
#define MCP_16MHz_50kBPS_CNF3 (0x87)

#define MCP_16MHz_40kBPS_CNF1 (0x07)
#define MCP_16MHz_40kBPS_CNF2 (0xFF)
#define MCP_16MHz_40kBPS_CNF3 (0x87)

#define MCP_16MHz_33kBPS_CNF1 (0x09)
#define MCP_16MHz_33kBPS_CNF2 (0xBE)
#define MCP_16MHz_33kBPS_CNF3 (0x07)

#define MCP_16MHz_31k25BPS_CNF1 (0x0F)
#define MCP_16MHz_31k25BPS_CNF2 (0xF1)
#define MCP_16MHz_31k25BPS_CNF3 (0x85)

#define MCP_16MHz_25kBPS_CNF1 (0X0F)
#define MCP_16MHz_25kBPS_CNF2 (0XBA)
#define MCP_16MHz_25kBPS_CNF3 (0X07)

#define MCP_16MHz_20kBPS_CNF1 (0x0F)
#define MCP_16MHz_20kBPS_CNF2 (0xFF)
#define MCP_16MHz_20kBPS_CNF3 (0x87)

#define MCP_16MHz_10kBPS_CNF1 (0x1F)
#define MCP_16MHz_10kBPS_CNF2 (0xFF)
#define MCP_16MHz_10kBPS_CNF3 (0x87)

#define MCP_16MHz_5kBPS_CNF1 (0x3F)
#define MCP_16MHz_5kBPS_CNF2 (0xFF)
#define MCP_16MHz_5kBPS_CNF3 (0x87)

#define MCP_16MHz_666kBPS_CNF1 (0x00)
#define MCP_16MHz_666kBPS_CNF2 (0xA0)
#define MCP_16MHz_666kBPS_CNF3 (0x04)


/**
 * @brief speed 8M
*/

#define MCP_8MHz_1000kBPS_CNF1 (0x00)
#define MCP_8MHz_1000kBPS_CNF2 (0x80)
#define MCP_8MHz_1000kBPS_CNF3 (0x00)

#define MCP_8MHz_500kBPS_CNF1 (0x00)
#define MCP_8MHz_500kBPS_CNF2 (0x90)
#define MCP_8MHz_500kBPS_CNF3 (0x02)

#define MCP_8MHz_250kBPS_CNF1 (0x00)
#define MCP_8MHz_250kBPS_CNF2 (0xb1)
#define MCP_8MHz_250kBPS_CNF3 (0x05)

#define MCP_8MHz_200kBPS_CNF1 (0x00)
#define MCP_8MHz_200kBPS_CNF2 (0xb4)
#define MCP_8MHz_200kBPS_CNF3 (0x06)

#define MCP_8MHz_125kBPS_CNF1 (0x01)
#define MCP_8MHz_125kBPS_CNF2 (0xb1)
#define MCP_8MHz_125kBPS_CNF3 (0x05)

#define MCP_8MHz_100kBPS_CNF1 (0x01)
#define MCP_8MHz_100kBPS_CNF2 (0xb4)
#define MCP_8MHz_100kBPS_CNF3 (0x06)

#define MCP_8MHz_80kBPS_CNF1 (0x01)
#define MCP_8MHz_80kBPS_CNF2 (0xbf)
#define MCP_8MHz_80kBPS_CNF3 (0x07)

#define MCP_8MHz_50kBPS_CNF1 (0x03)
#define MCP_8MHz_50kBPS_CNF2 (0xb4)
#define MCP_8MHz_50kBPS_CNF3 (0x06)

#define MCP_8MHz_40kBPS_CNF1 (0x03)
#define MCP_8MHz_40kBPS_CNF2 (0xbf)
#define MCP_8MHz_40kBPS_CNF3 (0x07)

#define MCP_8MHz_31k25BPS_CNF1 (0x07)
#define MCP_8MHz_31k25BPS_CNF2 (0xa4)
#define MCP_8MHz_31k25BPS_CNF3 (0x04)

#define MCP_8MHz_20kBPS_CNF1 (0x07)
#define MCP_8MHz_20kBPS_CNF2 (0xbf)
#define MCP_8MHz_20kBPS_CNF3 (0x07)

#define MCP_8MHz_10kBPS_CNF1 (0x0f)
#define MCP_8MHz_10kBPS_CNF2 (0xbf)
#define MCP_8MHz_10kBPS_CNF3 (0x07)

#define MCP_8MHz_5kBPS_CNF1 (0x1f)
#define MCP_8MHz_5kBPS_CNF2 (0xbf)
#define MCP_8MHz_5kBPS_CNF3 (0x07)      /* Sample point at 80% */

/**
 * @brief Operating modes of mcp2515 chip.
*/
typedef enum MCP_CAN_MODE{ mcp_normal_mode=0, mcp_sleep_mode=1, mcp_loopback_mode=2, mcp_listen_only_mode=3, mcp_configuration_mode=4 } MCP_CAN_MODE;

/**
 * @brief Error codes for mcp2515 chip.
*/
typedef enum MCP_CAN_TX_ERROR{ mcp_no_error_tx=0, mcp_tx_lost_arbitration=1, mcp_tx_message_error=2 } MCP_CAN_TX_ERROR;

/**
 * @brief Can frame types.
*/
typedef enum CAN_FRAME_TYPE{ can_standard=0, can_extended=1, can_data_frame=2, can_remote_frame=3 }CAN_FRAME_TYPE;

typedef struct CAN_FRAME
{
	CAN_FRAME_TYPE type;
	uint8_t isRemote;
	uint32_t ID;
	uint8_t DLC;
	unsigned char DATA[8];
}CAN_FRAME;



/**
 * @brief The following macro enables the intialization of SPI port by the init API itself. If you do not want this then, disable 
 * comment the following line.
*/
#define AUTO_SPI_INITIALIZATION

/**
 * @brief The following macro defines the chip frequency in Hz.
*/
#define MCP_CHIP_FREQ 8000000



/**
 * 	FUNCTIONS
 */

MCP_CAN_MODE canGetMode(void);

void canRequestMode(MCP_CAN_MODE);

void canSetBitTiming(unsigned char, unsigned char, unsigned char);

void canBegin(void*, uint16_t);

uint8_t canGetTEC(void);

uint8_t canGetREC(void);

void canChipReset(void);

uint8_t canIsFreeTX(uint8_t);

uint8_t canSetPriorityTX(uint8_t, uint8_t);

uint8_t canSetSID_TX(uint8_t, uint16_t);

uint8_t canSetEID_TX(uint8_t, uint32_t);

void canSetTXREQ(uint8_t);

void canRequestTransmission_wiRTS(uint8_t);

uint8_t canTransmit(uint8_t, uint8_t, unsigned char [8]);

uint8_t canTransmit_wSID(uint8_t, uint16_t, uint8_t, unsigned char[8]);

uint8_t canTransmit_wEID(uint8_t, uint32_t, uint8_t, unsigned char[8]);

uint8_t canRemoteTransmit_wSID(uint8_t, uint16_t);

uint8_t canRemoteTransmit_wEID(uint8_t, uint32_t);

MCP_CAN_TX_ERROR canGetErrorTX(uint8_t);

void canClearMessageError(void);

void canAbortTX(uint8_t);

void canEnableFilterRX(uint8_t);

void canDisableFilterRX(uint8_t);

void canEnableRX(uint8_t);

uint8_t canIsFilledRX(uint8_t);

void canSetMaskRX(uint8_t, uint32_t);

void canSetFilterRX(uint8_t, CAN_FRAME_TYPE, uint32_t);

CAN_FRAME canGetFrame_wID(uint8_t);

#endif
