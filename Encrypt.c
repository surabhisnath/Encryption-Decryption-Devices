//Encrypt

#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

MODULE_LICENSE("GPL");


static int t = 0;
static int pos = 0;
static char message[100] = {0};

static int device_open(struct inode *i, struct file *f)
{
	t = t + 1;
	printk(KERN_ALERT "Device opened %d times.\n", t);
	return 0;
}

static ssize_t device_read(struct file *f, char *c, size_t len, loff_t *o)
{
	int count = 0;

	while(len && message[pos] != 0)
	{
		put_user(message[pos], c++);
		count++; len--; pos++;
	}

	return count;
}

static ssize_t device_write(struct file *f, const char *c, size_t len, loff_t *o)
{
	int index = len - 1;
	int count = 0;

	memset(message, 0, 100);
	pos = 0;

	while(len > 0)
	{
		message[count] = c[index];
		count++; index--;
		len--;
	}


	//encryption


	return count;
}


static int device_release(struct inode *i, struct file *f)
{
	printk(KERN_ALERT "Device closed.\n");
	return 0;
}


static struct file_operations file_ops = 
{
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release,
};

int init_module(void)
{

	int ret;		//Initialize

	if(ret = register_chrdev(91, "Encryption", &file_ops) < 0)
	{
		printk(KERN_ALERT "Device registeration failed.\n");
	}

	else
	{
		printk(KERN_ALERT "Device registeration successful.\n");	
	}

	return ret;
}

void cleanup_module(void)
{
	unregister_chrdev(91, "Encryption");
}