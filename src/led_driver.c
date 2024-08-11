#include <gbdk/platform.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <rand.h>

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
void set_led_color(
	unsigned char led_index,
	unsigned char red,
	unsigned char green,
	unsigned char blue
) { 
	// Thanks to @H3xCat on Discord for this code
	// This section sets DAT0 to contain the value we want
	// Order the WRLED command to be run for channel R/0
	DAT0_REG = red;
	set_command(led_index, 0x01);

	DAT0_REG = green;
	set_command(led_index, 0x00);

	DAT0_REG = blue;
	set_command(led_index, 0x02);

	// Order an LEDSYNC to make the LED change take effect
	set_command(0x09, 0x00); 
}

void set_leds(
	unsigned int led_mode, 
	int led_speed,
	unsigned int led_counter
) { 

	unsigned char red = 0;
	unsigned char green = 0;
	unsigned char blue = 0;

	int rainbow[7] = {
		0xff0000, // Red
		0xFFA500, // Orange
		0xffff00, // Yellow
		0x00ff00, // Green
		0x0000ff, // Blue
		0x4b0082, // Indigo
		0x9400d3  // Violet
	};


	led_counter *= led_speed;

	switch (led_mode) { 
		// Turn off all LEDs
		case 0:
			for (int i=0; i<=8; i++) { 
				set_led_color(i, 0, 0, 0);

			};

			break;

		// Turn LEDs to BSoD-worthy Blue (default)
		case 1:
			for (int i=0; i<=8; i++) { 
				set_led_color(i, 0, 0, 255);

			};

			break;

		// Rainbow pulse (thanks @kit03201 on Discord)
		case 2:
			if (led_counter < 12) { 
				led_counter = 12;
			};

			// Makes for cleaner loops
			led_counter %= 196;

			red   = max(0,min(255,255-abs((led_counter*6)-255)))/2;
			green = max(0,min(255,255-abs((led_counter*6)-510)))/2;
			blue  = max(0,min(255,255-abs((led_counter*6)-765)))/2;

			for (int i=0; i<=8; i++) { 
				set_led_color(i, red, green, blue);
			};

			break;

		// Rainbow runner
		case 3:
			for (int i=0; i<=8; i++) { 
				// clamp LED values
				led_counter = min(max(led_counter + 1, 12), 255);

				red   = max(0,min(255,255-abs((led_counter*6)-255)))/2;
				green = max(0,min(255,255-abs((led_counter*6)-510)))/2;
				blue  = max(0,min(255,255-abs((led_counter*6)-765)))/2;

				set_led_color(i, red, green, blue);
			};

			break;

		// Blue runners
		case 4:
			for (int i=0; i<=8; i++) { 
				if ( (led_counter >> 2) % 2 == i % 2) { 
					set_led_color(i, 0, 0, 255);
				} else { 
					set_led_color(i, 0, 0, 0);
				}
			};

			break;

		// Po-po runners
		case 5:
			for (int i=0; i<=8; i++) { 
				if ( (led_counter >> 2) % 2 == i % 2) { 
					set_led_color(i, 0, 0, 255);
				} else { 
					set_led_color(i, 255, 0, 0);
				}
			};
			
			break;
		
		// Rainbow puke
		case 6:
			for (int i=0; i<=8; i++) { 
				red   = max(0,min(255,255-abs((i + led_counter*6)-255)))/2;
				green = max(0,min(255,255-abs((i + led_counter*6)-510)))/2;
				blue  = max(0,min(255,255-abs((i + led_counter*6)-765)))/2;

				set_led_color(i, red, green, blue);
			}


		// Single rainbow runner
		case 7:
			char index = rand() % 9;

			red = rand() % 255;
			green = rand() % 255;
			blue = rand() % 255;

			// Turn off other LEDs
			for (int i=0; i<=8; i++) { 
				if (i != index) { 
					set_led_color(i, 0, 0, 0);
				} else { 
					// Set designated LED to that color
					set_led_color(index, red, green, blue);
				}
			}

			break;

			break;

		// One-at-a-time rainbow puke (should keep the others the same)
		case 8:
			red = rand() % 255;
			green = rand() % 255;
			blue = rand() % 255;

			set_led_color(rand() % 9, red, green, blue);

			break;

	}
}

