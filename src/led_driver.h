#define DAT0_REG (*(volatile unsigned int *)0xFF7D)
#define DAT1_REG (*(volatile unsigned int *)0xFF7E)
#define IDR_REG  (*(volatile unsigned int *)0xFF7F)
#define CTL_REG  (*(volatile unsigned int *)0xFF7F)

#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) < (b) ? (a) : (b))

// Total number of LED lighting modes
#define LED_MODE_COUNT 10

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

