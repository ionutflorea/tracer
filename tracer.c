/*
 * SO2 kprobe based tracer header file
 * 2013, Operating Systems 2 - Ixia Challenge
 *
 * this is shared with user space
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#include <linux/fs.h>
#include <linux/miscdevice.h>

#include "tracer.h"

MODULE_DESCRIPTION("kprobe based tracer");
MODULE_AUTHOR("Florea Ionut");
MODULE_LICENSE("GPL");

/**
 * This function will be invoked each time a user process attempts
 * to open our misc device.
 */
static int tracer_open(struct inode *inode, struct file *file)
{
	printk (KERN_DEBUG "tracer: open\n");
	return 0;
}

/**
 * This function, in turn, will be called when a user process
 * closes our device.
 */
static int tracer_release(struct inode *inode, struct file *file)
{
	printk (KERN_DEBUG "tracer: close\n");
	return 0;
}

/**
 * This function will handle ioctl calls performed on the misc device.
 */
static int tracer_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	switch (cmd) {
	case TRACER_ADD_PROCESS:
		printk (KERN_DEBUG "add process %ld\n", arg);
		break;

	case TRACER_REMOVE_PROCESS:
		printk (KERN_DEBUG "remove process %ld\n", arg);
		break;

	default:
		return -ENOTTY;
	}

	return 0;
}

static const struct file_operations tracer_fops = {
	.owner		= THIS_MODULE,
	.open		= tracer_open,
	.release	= tracer_release,
	.unlocked_ioctl = (void*)&tracer_ioctl
};

static struct miscdevice tracer_misc_dev = {
	.minor  = TRACER_DEV_MINOR,
	.name   = TRACER_DEV_NAME,
	.fops   = &tracer_fops
};

static int __init tracer_init(void)
{
	int rc = misc_register (&tracer_misc_dev);
	if (rc < 0) {
		printk (KERN_DEBUG "misc_register: fail\n");
		return rc;
	} else {
		printk (KERN_DEBUG "Miscellaneous device successfully registered!\n");
	}

	return 0;
}

static void __exit tracer_exit(void)
{
	misc_deregister (&tracer_misc_dev);
}

module_init(tracer_init);
module_exit(tracer_exit);
