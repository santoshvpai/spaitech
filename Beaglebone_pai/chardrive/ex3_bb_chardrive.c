/**
 * @file    ex3_bb_chardrive.c
 * @author  Santosh Pai
 * @date    15 may 2018
 * @version 0.1
 * @brief  An introductory "Char device driver" loadable kernel module (LKM) that can display a message
 * in the /var/log/kern.log file when the module is loaded and removed. The module can accept an
 * we used fs.h file system, /dev to register device
*/
#include<linux/init.h>		// Macros used to mark up functions e.g., __init __exit
#include<linux/module.h>	// Core header for loading LKMs into the kernel
#include<linux/kernel.h>	// Contains types, macros, functions for the kernel
#include<linux/gpio.h>		// contains B3B GPIO pin informations
#include<linux/delay.h>     // Using this header for the msleep() function
#include<linux/moduleparam.h> //< Use the Macros to get the parameters during loading of module
#include<linux/fs.h>        // Contains file system used for the device driver

MODULE_LICENSE("GPL");		// The license type -- this affects runtime behavior
MODULE_AUTHOR("SANTOSH PAI");// The author -- visible when you use modinfo
MODULE_DESCRIPTION("SIMPLE Character Device Driver");// The description -- see modinfo
MODULE_VERSION("V0.1");		// The version of the module

/* Definition of deriver file operation */
int ex3_open_file(struct inode *pinode, struct file *pfile){
	printk(KERN_INFO "we have %s \n ",__FUNCTION__);
	return 0;
}
int ex3_close_file(struct inode *pinode, struct file *pfile){
	printk(KERN_INFO "we have %s \n ",__FUNCTION__);
	return 0;
}
ssize_t ex3_read_file(struct file *pfile, char __user *buffer, size_t length, loff_t *offset){
	/* length is count size of buffer we are going to red  */
	printk(KERN_INFO "we have %s \n ",__FUNCTION__);
	return 0;	/* We assume file is empty */
}
ssize_t ex3_write_file(struct file *pfile, const char __user *buffer, size_t length, loff_t *offset){
	/* length is write buffer size */
	printk(KERN_INFO "we have %s \n ",__FUNCTION__);
	return length;
}

/* Declare your ex3_file_operation here for your simple char drive */
/* Look in to linux/fs.h => lib/modules/$(uname -r)/build/include/linux/fs.h */
/* It is a structure variable basically contains type of operation the we
 * perform on the our simple char drive devices
 */
struct file_operations ex3_file_operation = {
		.owner  = THIS_MODULE,  /* Owner of file */
		.open   = ex3_open_file,/* Open the file */
		.read   = ex3_read_file,/* Read the file */
		.write  = ex3_write_file,/* Write the file */
		.release= ex3_close_file,/* Close the file */
};


static int __init ex3_bb_charderive_init( void ){
	printk(KERN_INFO "--Ex3 Char Driver: Initialization of Char Device Driver %s--\n",__FUNCTION__);
	/* Inform kernel : we are registering a char device driver */
	register_chrdev( 240                 /* Major Number */,
			         "simple char drive" /* Char driver name */,
					 &ex3_file_operation  /* Address of File operation */ );
	return 0;
}

/** @brief The LKM cleanup function
 *  Similar to the initialization function, it is static. The __exit macro notifies that if this
 *  code is used for a built-in driver (not a LKM) that this function is not required.
 */
static void __exit ex3_bb_charderive_exit( void ){

	printk(KERN_INFO "Good bye of %s \n ",__FUNCTION__);
	unregister_chrdev(240, "simple char drive");

}

module_init(ex3_bb_charderive_init);
module_exit(ex3_bb_charderive_exit);

