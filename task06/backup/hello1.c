#include <linux/init.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>
#include <linux/fs.h>


#define MISCNAME	"eudyptula"
#define ASSIGNED_ID	"09b0d224b5bb"
#define ID_LEN		20

MODULE_LICENSE("Dual BSD/GPL");

static ssize_t hello_misc_write(struct file *file, const char __user *buf,
				size_t count, loff_t *pos)
{
	char id_buf[ID_LEN] = {};

	return (count < 1 || count > ID_LEN) ? -EINVAL :
		(copy_from_user(id_buf, buf, count) ? -EINVAL :
		(strncmp(ASSIGNED_ID, id_buf, count) ? -EINVAL : count));
}

static ssize_t hello_misc_read(struct file *file, char __user *buf,
				size_t count, loff_t *pos)
{
	return *pos ? 0 : (copy_to_user(buf, ASSIGNED_ID,
		sizeof(ASSIGNED_ID)) ? -EINVAL : (*pos = sizeof(ASSIGNED_ID)));
}

static const struct file_operations hello_misc_ops = {
	.owner =  THIS_MODULE,
	.write = hello_misc_write,
	.read = hello_misc_read,
};

static struct miscdevice hello_misc_device = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = MISCNAME,
	.fops = &hello_misc_ops,
};


static int hello_init(void)
{
	int err;

	pr_debug("Hello, World!\n");
	err = misc_register(&hello_misc_device);
	if (err)
		pr_err("misc_register failed\n");

	return 0;
}

static void hello_exit(void)
{
	pr_debug("See you, World!\n");
	misc_deregister(&hello_misc_device);
}

module_init(hello_init);
module_exit(hello_exit);
