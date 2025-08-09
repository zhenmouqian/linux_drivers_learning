#include <linux/module.h>
#include <linux/fs.h>
#define CHRDEVBASE_MAJOR 1000
#define CHRDEVBASE_NAME "chrdev"

int chrdevbase_open(struct inode *inode, struct file *flip)
{
    printk("i am in chrdevbase_open\r\n");
    return 0;
}
int chrdevbase_realse(struct inode *inode, struct file *flip)
{
    printk("i am in chrdevbase_realse\r\n");
    return 0;
}
ssize_t chrdevbase_read(struct file *flip, char __user *buf, size_t count, loff_t *off)
{
    printk("i am in chrdevbase_read\r\n");
    return 0;
}
ssize_t chrdevbase_write(struct file *flip, const char __user *buf, size_t count, loff_t *off)
{
    printk("i am in chrdevbase_write\r\n");
    return 0;
}

static const struct file_operations ops = {
    .owner = THIS_MODULE,
    .open = chrdevbase_open,
    .read = chrdevbase_read,
    .write = chrdevbase_write,
    .release = chrdevbase_realse};
static int __init chrdevbase_init(void)
{
    int ret = 0;
    printk("i am in chrdevbase_init\r\n");
    ret = register_chrdev(CHRDEVBASE_MAJOR, CHRDEVBASE_NAME, &ops);
    if (ret < 0)
    {
        printk("chrdevbase init fail!\r\n");
    }
    return 0;
}
static void __exit chrdevbase_exit(void)
{
    printk("i am in chrdevbase_exit\r\n");
    unregister_chrdev(CHRDEVBASE_MAJOR, CHRDEVBASE_NAME);
}

module_init(chrdevbase_init);
module_exit(chrdevbase_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("CuteKitten");