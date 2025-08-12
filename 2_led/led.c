#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <asm/io.h>

#define LEDMAJOR 1001
#define LEDNAME "LED"
#define IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03 (0x020E0068)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03 (0x020E02F4)
#define CCM_CCGR1 (0x020C406C)
#define GPIO1_GD (0x0209C000)
#define GPIO1_GDIR (0x0209C004)

static void __iomem *IMX6ULL_MUX_GPIO1_IO03;
static void __iomem *IMX6ULL_PAD_GPIO1_IO03;
static void __iomem *IMX6ULL_CCM_CCGR1;
static void __iomem *IMX6ULL_GPIO1_GD;
static void __iomem *IMX6ULL_GPIO1_GDIR;

int led_open(struct inode *inode, struct file *filp)
{
    return 0;
}
int led_release(struct inode *inode, struct file *file)
{
    return 0;
}
ssize_t led_read(struct file *filp, char __user *data, size_t count, loff_t *off)
{
    return 0;
}
ssize_t led_write(struct file *filp, const char __user *data, size_t count, loff_t *off)
{
    char led_buf;
    uint32_t reg;
    int ret;
    ret = copy_from_user(&led_buf, data, count);
    if (ret < 0)
    {
        printk("kernel write fail\n");
        return 1;
    }
    if (led_buf == 1)
    {
        reg = readl(IMX6ULL_GPIO1_GD);
        reg &= ~(1 << 3);
        writel(reg, IMX6ULL_GPIO1_GD);
    }
    else
    {
        reg = readl(IMX6ULL_GPIO1_GD);
        reg |= (1 << 3);
        writel(reg, IMX6ULL_GPIO1_GD);
    }
    return 0;
}
static const struct file_operations ops =
    {
        .owner = THIS_MODULE,
        .open = led_open,
        .release = led_release,
        .read = led_read,
        .write = led_write};
static int __init led_init(void)
{
    uint32_t reg;

    IMX6ULL_CCM_CCGR1 = ioremap(CCM_CCGR1, 4);
    IMX6ULL_PAD_GPIO1_IO03 = ioremap(IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03, 4);
    IMX6ULL_MUX_GPIO1_IO03 = ioremap(IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03, 4);
    IMX6ULL_GPIO1_GDIR = ioremap(GPIO1_GDIR, 4);
    IMX6ULL_GPIO1_GD = ioremap(GPIO1_GD, 4);

    reg = readl(IMX6ULL_CCM_CCGR1);
    reg &= ~((0x3) << 26);
    reg |= (0x3) << 26;
    writel(reg, IMX6ULL_CCM_CCGR1);

    writel(0x10B0, IMX6ULL_PAD_GPIO1_IO03);

    reg = readl(IMX6ULL_MUX_GPIO1_IO03);
    reg |= 0x5;
    writel(reg, IMX6ULL_MUX_GPIO1_IO03);

    reg = readl(IMX6ULL_GPIO1_GDIR);
    reg |= 0x8;
    writel(reg, IMX6ULL_GPIO1_GDIR);

    reg = readl(IMX6ULL_GPIO1_GD);
    reg &= ~0x8;
    writel(reg, IMX6ULL_GPIO1_GD);

    if (register_chrdev(LEDMAJOR, LEDNAME, &ops) < 0)
    {
        printk("register %s fail!", LEDNAME);
        return 1;
    }
    return 0;
}
static void __exit led_exit(void)
{
    iounmap(IMX6ULL_CCM_CCGR1);
    iounmap(IMX6ULL_PAD_GPIO1_IO03);
    iounmap(IMX6ULL_MUX_GPIO1_IO03);
    iounmap(IMX6ULL_GPIO1_GDIR);
    iounmap(IMX6ULL_GPIO1_GD);
    unregister_chrdev(LEDMAJOR, LEDNAME);
}
module_init(led_init);
module_exit(led_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("CuteKitten");