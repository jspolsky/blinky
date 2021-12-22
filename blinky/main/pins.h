#define PIN_BUTTON GPIO_NUM_3
#define PIN_SDA GPIO_NUM_5
#define PIN_SCL GPIO_NUM_6
#define PIN_RGB GPIO_NUM_8
#define PIN_IR_TX GPIO_NUM_18
#define PIN_IR_RX GPIO_NUM_19

#define I2C_ADDR_CHARLIEPLEXER 0x74

// RMT: channels 0 and 1 are for transmit, 2 and 3 are for receive
#define RMT_CHANNEL_TX_RGB RMT_CHANNEL_0
#define RMT_CHANNEL_TX_IR RMT_CHANNEL_1
#define RMT_CHANNEL_RX_IR RMT_CHANNEL_2
