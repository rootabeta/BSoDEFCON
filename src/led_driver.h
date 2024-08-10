#define DAT0_REG (*(volatile unsigned int *)0xFF7D)
#define DAT1_REG (*(volatile unsigned int *)0xFF7E)
#define IDR_REG  (*(volatile unsigned int *)0xFF7F)
#define CTL_REG  (*(volatile unsigned int *)0xFF7F)

// command to send a command to the CTRL register
void set_command(unsigned int command, unsigned int subcommand);

// function to do all the nitty-gritty associated with setting LED values
int set_led_color(
	unsigned char led_index,
	unsigned char red,
	unsigned char green,
	unsigned char blue
);
