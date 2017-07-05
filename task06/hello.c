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
	uint8_t id_buf[ID_LEN] = {0};
	ssize_t res;

	res = simple_write_to_buffer(id_buf, ID_LEN, pos, buf, count);
	if (res < 0)
		return res;

	if (!strncmp(ASSIGNED_ID, id_buf, ID_LEN))
		return res;
	else
		return -EINVAL;
}

static ssize_t hello_misc_read(struct file *file, char __user *buf,
				size_t count, loff_t *pos)
{
	return simple_read_from_buffer(buf, count, pos,
			ASSIGNED_ID, sizeof(ASSIGNED_ID));
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
	int ret;

	pr_debug("Hello, World!\n");
	ret = misc_register(&hello_misc_device);
	if (ret) {
		pr_err("misc_register failed\n");
		return ret;
	}

	return 0;
}

static void hello_exit(void)
{
	pr_debug("See you, World!\n");
	misc_deregister(&hello_misc_device);
}

module_init(hello_init);
module_exit(hello_exit);
