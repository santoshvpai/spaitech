/**
 * @file    ex1_bb_ledblink.c
 * @author  Santosh Pai
 * @date    17 Oct 2015
 * @version 0.1
 * @brief  An introductory "led blinking" loadable kernel module (LKM) that can display a message
 * in the /var/log/kern.log file when the module is loaded and removed. The module can accept an
 * argument when it is loaded -- the name, which appears in the kernel log files.
*/
#include<linux/init.h>		// Macros used to mark up functions e.g., __init __exit
#include<linux/module.h>	// Core header for loading LKMs into the kernel
#include<linux/kernel.h>	// Contains types, macros, functions for the kernel
#include<linux/gpio.h>		// contains B3B GPIO pin informations
#include <linux/delay.h>    // Using this header for the msleep() function

MODULE_LICENSE("GPL");		//< The license type -- this affects runtime behavior
MODULE_AUTHOR("SANTOSH PAI");//< The author -- visible when you use modinfo
MODULE_DESCRIPTION("SIMPLE LED BLINKING DRIVER");//< The description -- see modinfo
MODULE_VERSION("V0.1");		//< The version of the module

static unsigned int gpioLED49 = 49; //< hard coding the LED gpio for this example to P9_23 (GPIO49)
static bool ledstate = 0;			//< default state of led is OFF
static unsigned int loop = 100;		//< set led blinking for 20 times

/** @brief The LKM initialization function
 *  The static keyword restricts the visibility of the function to within this C file. The __init
 *  macro means that for a built-in driver (not a LKM) the function is only used at initialization
 *  time and that it can be discarded and its memory freed up after that point.
 *  Here we use gpio_is_valid(Pin_No) to check the availability of gpio pin
 *       we use gpio_rquest(Pin_No, "requester") for the port pin request
 *       we use gpio_direction_output(Pin_No, Value) to set pin direction as output
 *       we use gpio_set_value(Pin_No, value) to send the value to pin
 *  @return returns 0 if successful
 */
static int __init ex1_bb_ledblink_init( void ){
	printk(KERN_INFO "--Ex1 LED: Initialization of LED_BLINKING Program --\n");
	// Is the GPIO a valid GPIO number ?
	if (!gpio_is_valid(gpioLED49)){
	    printk(KERN_INFO "GPIO_TEST: invalid LED GPIO\n");
	    return -ENODEV;
	}
	gpio_request(gpioLED49, "LED_Blink"); // request for gpio49 port
	gpio_direction_output(gpioLED49,1);// set gpio pin as output pin

	// run the led loop for 20 times
	while(loop){
		gpio_set_value(gpioLED49,ledstate); //< send the ON/OFF state to gpio pin 49
		printk(KERN_INFO "Port Pin 49 LED is --> %d \n", gpio_get_value(gpioLED49)); // Print the state of LED
		msleep(1000);		//< wait for 1s
		ledstate = !ledstate; //< Toggle the state of LED
		loop --;// decrement the loop count
	}

	ledstate = 0;	//< reset the state
	return 0;
}

/** @brief The LKM cleanup function
 *  Similar to the initialization function, it is static. The __exit macro notifies that if this
 *  code is used for a built-in driver (not a LKM) that this function is not required.
 */
static void __exit ex1_bb_ledblink_exit( void ){

	gpio_set_value(gpioLED49, 0);	//< Turn the LED off, indicates device was unloaded
	gpio_free(gpioLED49);         // Free the LED GPIO
	printk(KERN_INFO "Ex1 LED: Goodbye from the BBB LED LKM!\n");

}

module_init(ex1_bb_ledblink_init);
module_exit(ex1_bb_ledblink_exit);

