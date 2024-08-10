#include <gbdk/platform.h>
#include <stdio.h>

#include "led_driver.h"

// Function to combine a command and subcommand, and write it to control
void set_command(unsigned int command, unsigned int subcommand) { 
	// Mask off only the first four bits of each, then shift the command up and 
	// bitwise or them together to create the combined command
	unsigned int combined = ((command & 0xF) << 4) | (subcommand & 0xF);
	// once the combined command is created, issue it to the control register
	CTL_REG = combined;
}

// Function to set the LED color of a given LED
int set_led_color(
	unsigned char led_index,
	unsigned char red,
	unsigned char green,
	unsigned char blue
) { 
	// Thanks to @H3xCat on Discord for this code
	// This section sets DAT0 to contain the value we want
	DAT0_REG = red;
	//CTL_REG = ((led_index << 4) | 0x01);

	// Order the WRLED command to be run for channel R/0
	set_command(led_index, 0x00);

	DAT0_REG = green;
	//CTL_REG = ((led_index << 4) | 0x00);
	set_command(led_index, 0x01);

	DAT0_REG = blue;
	//CTL_REG = ((led_index << 4) | 0x02);
	set_command(led_index, 0x02);

	// Order an LEDSYNC to make the LED change take effect
	set_command(0x09, 0x00); 
	//CTL_REG = 0x90;

	// Success
	return 1;
}
