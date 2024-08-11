#define DAT0_REG (*(volatile unsigned int *)0xFF7D)
#define DAT1_REG (*(volatile unsigned int *)0xFF7E)
#define IDR_REG  (*(volatile unsigned int *)0xFF7F)
#define CTL_REG  (*(volatile unsigned int *)0xFF7F)

#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) < (b) ? (a) : (b))


// LED human-readble names
// Thanks to @kilukarp on discord for these
#define LED_SIDE_R_BOT  0
#define LED_BACK_R_BOT  1
#define LED_SIDE_L_TOP  2
#define LED_BACK_R_TOP  3
#define LED_EYE_R  4
#define LED_EYE_L  5
#define LED_SIDE_L  6
#define LED_BACK_L_BOT  7
#define LED_BACK_L_TOP  8

// Total number of LED lighting modes
#define LED_MODE_COUNT 9

// command to send a command to the CTRL register
void set_command(unsigned int command, unsigned int subcommand);

// function to do all the nitty-gritty associated with setting LED values
void set_led_color(
	unsigned char led_index,
	unsigned char red,
	unsigned char green,
	unsigned char blue
);

// set LEDs for a given mode, speed, and time value t
void set_leds(
	unsigned int led_mode, 
	int led_speed,
	unsigned int led_counter
);

