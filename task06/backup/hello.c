#include <linux/init.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>
#include <linux/fs.h>


#define MISCNAME	"eudyptula"
#define NAMELEN		10
#define ASSIGNED_ID	"09b0d224b5bb"
#define ID_LEN		20

MODULE_LICENSE("Dual BSD/GPL");

static ssize_t hello_misc_write(struct file *file, const char __user *buf,
				size_t count, loff_t *pos)
{
	int err;
	char id_buf[ID_LEN] = {};

	if (count < 1 || count > ID_LEN) {
		pr_err("ID length is too long!\n");
		return -EINVAL;
	}

	err = copy_from_user(id_buf, buf, count);
	if (err) {
		pr_err("copy_from_user failed!\n");
		return -EFAULT;
	}

	if (!strncmp(ASSIGNED_ID, id_buf, count)) {
		*pos += count;
		return count;
	}
	else
		return -EINVAL;
}

static ssize_t hello_misc_read(struct file *file, char __user *buf,
				size_t count, loff_t *pos)
{
	int err;
	
	if (*pos >= sizeof(ASSIGNED_ID))
		return 0;
	err = copy_to_user(buf, ASSIGNED_ID, sizeof(ASSIGNED_ID));
	if (err) {
		pr_err("copy_to_user failed!\n");
		return -EFAULT;
	}
	
	*pos += sizeof(ASSIGNED_ID);

	return *pos;
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
