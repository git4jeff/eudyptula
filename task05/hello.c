#include <linux/init.h>
#include <linux/module.h>
#include <linux/usb.h>
#include <linux/hid.h>

MODULE_LICENSE("Dual BSD/GPL");

static int hello_init(void)
{
	pr_debug("Hello, World!\n");
	return 0;
}

static void hello_exit(void)
{
	pr_debug("See you, World!\n");
}

static struct usb_device_id usb_mouse_idtab[] = {
	{USB_INTERFACE_INFO(USB_INTERFACE_CLASS_HID,
		USB_INTERFACE_SUBCLASS_BOOT,
		USB_INTERFACE_PROTOCOL_MOUSE)},
	{},
};

MODULE_DEVICE_TABLE(usb, usb_mouse_idtab);

module_init(hello_init);
module_exit(hello_exit);
