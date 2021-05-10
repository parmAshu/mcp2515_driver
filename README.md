## CROSS PLATFORM C LIBRARY FOR MCP2515 STANDALONE CAN CONTROLLER
---


This library provides functions which allows a mircocontroller with interact with MCP2515 standalone CAN controller chip.

> To better understand the API reference kindly go through CAN specifications first. Also go through the MCP2515 datasheet.

## API reference for mcp2515_driver library
---

```
void canBegin(void* data, uint16_t data_rate)
```
This function is used to initialize the MCP2515 chip.

**Parameters**

1. `void * data` : This is a pointer to any data required for SPI port initialization. The pointer is passed as it is to the `pal_spi_init()` API from the the platform abstraction layer. If some complicated data is to be passed for SPI port initialization (depending upon platform) then user may create a custom structure and put its definition in the file `mcp2515_driver_pal_defs.h` .

2. `uint16_t data_rate` : The CAN bus data rate in Kbps.
        Allowed values -
            5 Kbps
            10 Kbps
            20 Kbps
            40 Kbps
            50 Kbps
            80 Kbps
            100 Kbps
            125 Kbps
            200 Kbps
            250 Kbps
            500 Kbps
            1000 Kbps
    
**Returns**

NOTHING

<br/>
<br/>

```
MCP_CAN_MODE canGetMode(void)
```
This function is used to get current mode of the MCP2515 chip.

**Parameters**

NONE

**Returns**

Type : `MCP_CAN_MODE`

`mcp_normal_mode` when in normal mode of operation

`mcp_configuration_mode` when in configuration mode

`mcp_sleep_mode` when in sleep mode

`mcp_listen_only_mode` when in listen only mode

<br/>
<br/>

```
void canRequestMode(MCP_CAN_MODE _mode)
```
This function is used to put the chip into a specific mode of operation. The API blocks operation until the chip has entered the requested mode of operation.

**Parameters**

1. `MCP2515_CAN_MODE` : The mode to put the chip in.

    `mcp_normal_mode` for normal mode of operation

    `mcp_configuration_mode` for configuration mode

    `mcp_sleep_mode` for in sleep mode

    `mcp_listen_only_mode` for in listen only mode

**Returns**

NOTHING

<br/>
<br/>

```
uint8_t canGetTEC()
```

This function returns the TEC value for the chip. TEC stands for Trasmit Error Code and is a part of CAN specification.

**Parameters**

NONE

**Returns**

Type : `uint8_t`

The current TEC value

<br/>
<br/>

```
uint8_t canGetREC()
```

This function returns the REC value for the chip. REC stands for Recieve Error Code and is a part of CAN specification.

**Parameters**

NONE

**Returns**

Type : `uint8_t`

The REC value

<br/>
<br/>

```
void canChipReset()
```

This API resets the chip through command.

**Parameters**

NONE

**Returns**

NOTHING

<br/>
<br/>

```
uint8_t canIsFreeTX(uint8_t _buff)
```

MCP2515 chip contains three transmit buffers. These buffers are loaded with CAN frames to send over the bus. After looading the buffers, transmission must be initiated using external signal or command. This function is used to check is a transmit buffer is free or not.

**Parameters**

1. `uint8_t _buff` : The buffer number for which availability is to be tested.

**Returns**

type

<br/>
<br/>

```
uint8_t canSetPriorityTX(uint8_t _txBuffer, uint8_t _priority)
```

This API  is used to set relative priority of the transmit buffers. MCP2515 chip allows setting relative priority for the transmit buffers.

**Parameters**

1. `uint8_t _txBuffer` : The buffer number for which priority has to be set.
2. `uint8_t _priority` : The relative priority

**Returns**

Type : `uint8_t`

`1` if priority was set successfully

`0` if the buffer already contains a frame to send because of which priority cannot be updated.

<br/>
<br/>

```
uint8_t canSetSID_TX(uint8_t _buff, uint16_t _sid)
```

This API is used to set STANDARD CAN ID for a transmit buffer.

**Parameters**

1. `uint8_t _buff` : The buffer for which ID has to be set
2. `unt16_t _sid` : The 11 bit STANDARD ID. 

**Returns**

Type : `uint8_t`

`1` if ID was set successfully

`0` if the buffer already contains a frame to send because of which ID cannot be updated.

<br/>
<br/>

```
uint8_t canSetEID_TX(uint8_t  _buff, uint32_t _eid)
```

This function writes the 29 bit EXTENDED ID to one of the three transmit buffers. The API automatically enables the extended ID frame format for that transmit buffer.

**Parameters**

1. `uint8_t _buff` : The buffer for which ID has to be set
2. `uint32_t _sid` : The 29 bit STANDARD ID. 

**Returns**

Type : `uint8_t`

`1` if ID was set successfully

`0` if the buffer already contains a frame to send because of which ID cannot be updated.

<br/>
<br/>

```
void canSetTXREQ(uint8_t _buff)
```

This function requests transmission of CAN frame in a transmit buffer sby setting the corresponding TXREQ.

**Parameters**

1. `uint8_t _buff` : The buffer for transmission is to be requested

**Returns**

NOTHING

<br/>
<br/>

```
void canRequestTransmission_wRTS(uint8_t _buff)
```

This function requests transmission of CAN frame using RTS command.

**Parameters**

1. `uint8_t _buff` : The buffer for transmission is to be requested

**Returns**

NOTHING

<br/>
<br/>

```
uint8_t canTransmit(uint8_t _buff, uint8_t _num_bytes, unsigned char _data[8])

```

 This API initiates transmission through one of the three transmit buffers. This API does not sets the ID. Once data is loaded into the buffer, the API calls the `canRequestTransmission_wRTS()` to initiate the trasmission.

**Parameters**

 1. `uint8_t  _buff` : the transmit buffer number to use for transmission.
 2. `uint8_t _num_bytes` : number of data bytes.
 3. `_data[8]` : the actual data bytes; only `_num_bytes` number of data bytes will be considered from this array

**Returns**

Type : `uint8_t`

`1` if data was loaded into the buffer successfully

`0` if the buffer already contains a frame to send because of which new data cannot be loaded into it


<br/>
<br/>

```
uint8_t canTransmit_wSID(uint8_t _buff, uint16_t _sid, uint8_t _num_bytes, unsigned char _data[8])
```

This function initiates transmission through one of the three transmit buffers. This function loads STANDARD ID along with data. Once data is loaded into the buffer, the API calls the `canRequestTransmission_wRTS()` to initiate the trasmission.

**Parameters**

1. `uint8_t _buff` : the transmit buffer to use.
2. `uint16_t _sid` : standard ID for the data frame.
3. `uint8_t _num_bytes` : number of data bytes.
4. `uint8_t _data[8]` : the actual data bytes.

**Returns**

Type : `uint8_t`

`1` if data was loaded into the buffer successfully

`0` if the buffer already contains a frame to send because of which new data cannot be loaded into it

<br/>
<br/>

```
uint8_t canTransmit_wEID(uint8_t _buff, uint32_t _eid, uint8_t _num_bytes, unsigned char _data[8])
```

This API initiates transmission through one of the three transmit buffers. This function loads EXTENDED ID along with data. Once data is loaded into the buffer, the API calls the `canRequestTransmission_wRTS()` to initiate the trasmission. 

DO NOT PERFORM ANY SHIFTING WHILE PASSING THE EXTENDED ID TO MAKE ADJUSTMENTS FOR THE CHIP REGISTERS. THIS IS AUTOMATICALLY HANDLED BY THE FUNCTION.

**Parameters**

1. `uint8_t _buff` : the transmit buffer to use.
2. `uint32_t _eid` : EXTENDED ID for the data frame.
3. `uint8_t _num_bytes` : number of data bytes.
4. `uint8_t _data[8]` : the actual data bytes.

**Returns**

Type : `uint8_t`

`1` if data was loaded into the buffer successfully

`0` if the buffer already contains a frame to send because of which new data cannot be loaded into it

<br/>
<br/>

```
uint8_t canTransmitRemote_wSID(uint8_t _buff, uint16_t _sid)
```

This API is used to tramit a remote frame with STANDARD ID. This API initiates transmission through one of the three transmit buffers. This function sets STANDARD ID along with data. Once data is loaded into the buffer, the API calls the `canRequestTransmission_wRTS()` to initiate the trasmission.

PASS SID WITHOUT LEFT SHIFTING TO ADJUST FOR THE REGISTER POSTION, THIS IS AUTOMATICAALY DONE BY THE FUNCTION.

**Parameters**

1. `uint8_t _buff` : the transmit buffer to use.
2. `uint16_t _sid` : STANDARD ID for the data frame.

**Returns**

Type : `uint8_t`

`1` if remote frame was loaded into the buffer successfully

`0` if the buffer already contains a frame to send because of which new data cannot be loaded into it

<br/>
<br/>

```
uint8_t canTransmitRemote_wEID(uint8_t _buff, uint32_t _eid)
```

This API is used to tramit a remote frame with EXTENDED ID. This API initiates transmission through one of the three transmit buffers. This function sets EXTENDED ID along with data. Once data is loaded into the buffer, the API calls the `canRequestTransmission_wRTS()` to initiate the trasmission.

PASS EID WITHOUT LEFT SHIFTING TO ADJUST FOR THE REGISTER POSTION, THIS IS AUTOMATICAALY DONE BY THE API.

**Parameters**

1. `uint8_t _buff` : the transmit buffer to use.
2. `uint32_t _eid` : EXTENDED ID for the data frame.

**Returns**

Type : `uint8_t`

`1` if remote frame was loaded into the buffer successfully

`0` if the buffer already contains a frame to send because of which new data cannot be loaded into it

<br/>
<br/>

```
MCP_CAN_TX_ERROR canGetErrorTX(uint8_t _buff)
```

This function gets the error status of a transmit buffer after having initiated a frame transmission through that buffer.

**Parameters**

1. `uint8_t _buff` : the transmit buffer number.

**Returns**

Type : `MCP_CAN_TX_ERROR`
`mcp_no_error_tx` : if there is no error in transmission.

`mcp_tx_lost_arbitration` : if the message lost arbitration during transmission.

`mcp_tx_message_error` : if there was some other error during message transmission.


<br/>
<br/>

```
void canClearMessageError(void)
```

This API clears the `MEMRF` flag in the chip.

**Parameters**

NONE

**Returns**

NOTHING

<br/>
<br/>

```
void canAbortTX(uint8_t _buff)
```

This API is used to abort thr farme transmission pending in  any of the three transmit buffers. The abort is achieved by clearing the TXREQ bit. Calling this API does not set the abort flag.

**Parameters**

1. `uint8_t _buff` : The transmit buffer number.

**Returns**

NOTHING

<br/>
<br/>

```
void canEnableFilterRX(uint8_t _buff)
```

This API enables Filters on one of the two receive buffers in the chip.

**Parameters**

1. `uint8_t _buff` : the receive buffer number.

**Returns**

NOTHING

<br/>
<br/>

```
void canDisableFilterRX(uint8_t _buff)
```

This API disables Filters on one of the two receive buffers in the chip.

**Parameters**

1. `uint8_t _buff` : the receive buffer number.

**Returns**

NOTHING

<br/>
<br/>

```
void enableRX(uint8_t _buff)
```

This API makes available one the two receive buffer for receiving CAN data. This API clears the `RXnIF` flags for this purpose.

**Parameters**

1. _buff : the receive buffer number

**Returns**

NOTHING

<br/>
<br/>

```
uint8_t canIsFilledRX(uint8_t _buff)
```

This API checks if one of the two buffers has new CAN frame.

**Parameters**

1. _buff : the receive buffer number

**Returns**

Type : `uint8_t`

`1` if there is new CAN frame available

`0` otherwise

<br/>
<br/>


```
void canSetMaskRX(uint8_t _num, uint32_t _mask)
```

This API loads the filter mask registers for one of the two receive buffers. The API writes the lower order 29 bits from the `_mask` variable into the filter registers and thus one must be careful while using only the *Standard CAN frames as then the mask bits that are relevent, must be shifted left by 18 bits and then passed into `_mask`. This is due to interval architecure of the protocol controller.*

**Parameters**

1. `uint8_t  _num` : the receive buffer number.
2. `uint32_t _mask` : the actual mask data.

**Returns**

NOTHING

<br/>
<br/>


```
void canSetFilterRX(uint8_t _num, CAN_FRAME_TYPE _frame, uint32_t _filter)
```

This API loads the filter registers for one of the two receive buffers. The API writes the lower order 29 bits from the `_mask` variable into the filter registers and thus one must be careful while using only the *Standard CAN frames as then the mask bits that are relevent, must be shifted left by 18 bits and then passed into `_mask`. This is due to interval architecure of the protocol controller.*

**Parameters**

1. `uint8_t _num` : the filter number.
2. `CAN_FRAME_TYPE _frame` : the type of frame to apply the specific filter to, can_standard or can_extended. Allowed values are -

    `can_standard`

    `can_extended`

3. `uint32_t _filter` : the actual filter data.

**Returns**

NOTHING 

<br/>
<br/>

```
CAN_FRAME canGetFrame_wID(uint8_t _buff)
```

This API gets the complete CAN data frame from one of the two receive buffers.

**Parameters**

1.`uint8_t  _buff` : the receive buffer number

**Returns**

Type : `CAN_FRAME`
The can data frame

<br/>
<br/>

## Structures and Enumerations
---

```
typedef enum MCP_CAN_MODE{ mcp_normal_mode=0, mcp_sleep_mode=1, mcp_loopback_mode=2, mcp_listen_only_mode=3, mcp_configuration_mode=4 } MCP_CAN_MODE;
```
Operating modes of MCP2515 chip.

<br/>
<br/>

```
typedef enum MCP_CAN_TX_ERROR{ mcp_no_error_tx=0, mcp_tx_lost_arbitration=1, mcp_tx_message_error=2 } MCP_CAN_TX_ERROR;
```
Error codes related to MCP2515 chip's operation.

<br/>
<br/>

```
typedef enum CAN_FRAME_TYPE{ can_standard=0, can_extended=1, can_data_frame=2, can_remote_frame=3 }CAN_FRAME_TYPE;
```
CAN frame types.

<br/>
<br/>

```
typedef struct CAN_FRAME
{
	CAN_FRAME_TYPE type;
	uint8_t isRemote;
	uint32_t ID;
	uint8_t DLC;
	unsigned char DATA[8];
}CAN_FRAME;
```
This structure represents a CAN bus frame. It is returned when we read a CAN frame from the bus using `canGetFrame_wID()` API. It has the following members :

1. `CAN_FRAME_TYPE type` : The type of CAN frame.
2. `uint8_t isRemote`:

    `1` if the frame is a remote frame

    `2` if the frame is a data frame
3. `uin32_t ID` : ID of the frame. In case of standard ID, only 11 lsb are occupied. In case of extended ID only 29 lsb are occupied.
4. `uint8_t DLC` : The number of data bytes.
5. `unsigned char DATA[8]` : This array holds the actual data bytes.

<br/>
<br/>

## Macros
---

<br/>
<br/>

`AUTO_SPI_INITIALIZATION`
 
 Defined in `mcp2515_driver.h` header file.

 This macro makes the `canBegin()` API perform SPI port initialization for MCP2515 chip by call the `pal_spi_init()` API. Comment its defnition if there are multiple SPI slaves and application needs to initialize the SPI port separately. By default it is defined and thus ports are initialized by the `canBegin()` API.

 <br/>
 <br/>

 `MCP_CHIP_FREQ`

Defined in `mcp2515_driver.h` header file.

This is the frequency of oscillator that is clocking the MCP2515 chip. By default it is set to `8000000` Hz. User may change to if required.
 
<br/>
<br/>


## Platform Abstraction Layer
---

This is the layer that makes the driver cross platform compatible. This layer contains wrapper APIs that are used to access SPI port on a microcontroller. To make the API compatible with a platform, one needs to simply alter the code within the function definitions of this layer.

The actual driver APIs internally call these API for accessing the SPI port and do not know anything abou the SPI port of the actual device.

<br/>
<br/>

### Steps to port the driver for a platform

<br/>

1. Some platforms may not contain the definitions of types like `uint8_t`, `uint16_t`, `uint32_t` etc, used in the driver code. In this case open the header file `mcp2515_driver_pal_defs.h`; find and uncomment the following lines.

```
// typedef unsigned char uint8_t;
// typedef unigend short int uint16_t;
// typedef unsigned int uint32_t;
// typedef unsigned long uin64_t;
```

2. Now open the file `mcp2515_driver_pal.c` and put the platform specific code in various funtion bodies.

<br/>

In the following function, put the code needed for initializing SPI port on the device. If the user has removed `AUTO_SPI_INITIALIZATION` macro definition in which case the driver will not perform the initilzation, leave this function empty as it will never be called. 
<br/>
The `void * data` is used to pass initilization information from application code to this low level API. This information is mostly related to the slave select gpio for the MCP2515 chip. However it actually depends upon the platform.
```
void pal_spi_init(void* data, uint8_t data_direction, uint8_t idle_level, uint8_t shift_edge)
{
    /* !...Platform Specific Code here...! */
}
```

<br/>
<br/>

In the following function, put the code nedded for selecting the MCP2515 chip for SPI communication. The slave select gpio may be stored in a global variable or the user may harcode the gpio number in this function. In the latter case driver will work only when MCP2515's enable pin is wired to the hardcoded gpio pin. A better approach is to pass the gpio number from the appplication code during the initialzation and storing this number in the global variable which can be accessed by this API.

```
void pal_select_slave(void)
{
    /* !...Platform Specific Code here...! */
}
```
<br/>
<br/>

In the following function, put the code needed for de-selecting the MCP2515 chip. The slave select gpio may be stored in a global variable or the user may harcode the gpio number in this function. In the latter case driver will work only when MCP2515's enable pin is wired to the hardcoded gpio pin. A better approach is to pass the gpio number from the appplication code during the initialzation and storing this number in the global variable which can be accessed by this API.

```
void pal_deselect_slave(void)
{
    /* !...Platform Specific Code here...! */
}
```
<br/>
<br/>

In the following function, put the code needed for sending one byte of data over SPI port.
```
void pal_spi_send(uint8_t byt)
{
    /* !...Platform Specific Code here...! */
}
```

<br/>
<br/>

In the following function, put the code needed for reading one byte of data from SPI port.
```
uint8_t pal_spi_read(void)
{
    /* !...Platform Specific Code here...! */
}
```

### Example - porting the driver for Arduino platform

<br/>

This is a global variable that will hold the GPIO number which the MCP2515's chip select is connected to.
```
static uint8_t SS_PIN;
```

<br/>
<br/>

SPISettings object with correct settings for MCP2515 chip
```
SPISettings mcp2515_setings(10000000, MSBFIRST, SPI_MODE0);
```

<br/>
<br/>

FOLLOWING CODE SHOWS HOW `void * data` CAN BE USEFUL FOR INITIALIZATION OF SPI PORT.

Initialization code for SPI port. This API expects `void * data` to be a pointer to an `mcp2515_driver_config` type structure which contains the GPIO pin number that MCP2515's chip select is wired to. Since, the `canBegin()` API passed the takes a pointer and passes it 'as it is' to this API, the application code will have to pass a pointer to `mcp2515_driver_config` type structure containing gpio number, while calling the `canBegin()` API.
<br/>
The type definition for `mcp2515_driver_config` is put in `mcp2515_driver_pal_defs.h` header file :

```
typedef struct mcp2515_driver_config
{ 
    uint8_t ss_pin;
}mcp2515_driver_config;
```

```
void pal_spi_init(void* data, uint8_t data_direction, uint8_t idle_level, uint8_t shift_edge)
{
    /* !...Platform Specific Code here...! */

    SPI.begin();

    SPI.setBitOrder(MSBFIRST);

    SPI.setDataMode(SPI_MODE0);

    SPI.setClockDivider(SPI_CLOCK_DIV2);

    SS_PIN = ((mcp2515_driver_config *)data)->ss_pin;

    pinMode(SS_PIN, OUTPUT);

    digitalWrite(SS_PIN, HIGH);

    SPI.beginTransaction(mcp2515_setings);
    SPI.endTransaction();

}
```
Example of calling the `canBegin()` :

```
mcp2515_driver_config chipConfig = {
  .ss_pin = 10
};

void setup() 
{
  Serial.begin(9600);

  canBegin(&chipConfig, 500);
  ...
}
```


<br/>
<br/>

```
void pal_select_slave(void)
{
    /* !...Platform Specific Code here...! */
    digitalWrite(SS_PIN, LOW);
}
```

```
void pal_deselect_slave(void)
{
    /* !...Platform Specific Code here...! */
    digitalWrite(SS_PIN, HIGH);
}
```

```
void pal_spi_send(uint8_t byt)
{
    /* !...Platform Specific Code here...! */
    SPI.transfer(byt);
}
```

```
uint8_t pal_spi_read(void)
{
    /* !...Platform Specific Code here...! */
    return SPI.transfer(0XFF);
}
```