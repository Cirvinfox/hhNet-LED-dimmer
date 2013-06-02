/*

This is for the HHnet protocol stuff

*/

const char start_c = 0x01;  // ASCII Start Of Header
const char esc_c = 0x10;    // ASCII Data Link Escape
const char end_c = 0x04;    // ASCII End of Transmission



enum serialstate_t
{
  IDLE, 
  RX, 
  ESCAPE
};

enum hhNetReturnCode_t
{
  RC_HHNET_OK,
  RC_HHNET_NOT_IMPLEMENTED,
  RC_HHNET_BAD_PARAMETERS,
  RC_HHNET_FAULT
};

enum hhNetCommands_t
{
  CMD_HHNET_VERSION         = 'v',
  CMD_HHNET_WRITE_REGISTER  = 'w',
  CMD_HHNET_READ_REGISTER   = 'r',
  CMD_HHNET_RESET           = 'c'
};
  
typedef struct
{
	// hhnet struct registers
	uint16_t mode;
	uint8_t fadeRate;
	int flashOnTime;
	int flashOffTime;
	uint8_t intensity;
} hhNetRegs_t;
