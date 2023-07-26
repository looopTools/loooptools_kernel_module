#include <linux/init.h>
#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>

MODULE_AUTHOR("Lars Nielsen");
MODULE_DESCRIPTION("looopTools Test Module");
MODULE_LICENSE("GPL");

static struct proc_dir_entry* proc_entry;

static ssize_t loooptools_read(struct file* file, char __user* user_buffer, size_t count, loff_t* offset)
{

    printk(KERN_INFO "call to looopTools kernel module");
    char greeting[] = "Hello Master looopTools";
    int greeting_length = strlen(greeting);

    if (*offset > 0)
    {
        return 0; 
    }

    // Copy the greeting to the user buffer
    copy_to_user(user_buffer, greeting, greeting_length);
    *offset = greeting_length;
    return greeting_length;
}

static struct proc_ops fops =
{
    .proc_read = loooptools_read
};

static int __init loooptools_init(void)
{
    proc_entry = proc_create("loooptoolsdriver", 0666, NULL, &fops);
    printk(KERN_INFO "Hello looopTools");
    return 0; 
}

static void __exit loooptools_exit(void)
{
    proc_remove(proc_entry);
    printk(KERN_INFO "Bye looopTools");    
}


module_init(loooptools_init);
module_exit(loooptools_exit);

