#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/string.h>
#include<linux/errno.h>
#include<linux/mm.h>
#include<linux/vmalloc.h>
#include<linux/slab.h>
#include<asm/io.h>
#include<linux/mman.h>
#include "map_driver.h"

#define MAPLEN (PAGE_SIZE*10)

int mapdrv_open(struct inode *inode,struct file *file); //驱动打开
int mapdrv_release(struct inode *inode,struct file *file); //驱动关闭
int mapdrv_mmap(struct file *file,struct vm_area_struct *vma); //驱动的功能函数
void map_vopen(struct vm_area_struct *vma); //虚拟内存打开
void map_vclose(struct vm_area_struct *vma); //虚拟内存关闭

struct page *map_nopage(struct  vm_area_struct *vma,unsigned long address,int *type);//虚存区的缺页处理函数

static struct file_operation mapdrvo_fops={

.owner=THIS_MODULE, //拥有者
.mmap=mapdrvo_mmap, //下面三个是函数指针
.open=mapdrvo_open,
.release=mapdrvo_release, 
};

static struct vm_operation_struct map_vm_ops={

.open=map_vopen, //三个钩子函数
.close=map_vclose,
.nopage=map_nopage,
};

static int *vmalloc_area=NULL; //指针用来存内存地址
static int major;

volatile void *vaddr_to_kaddr(volatile void *address){ //虚拟地址变为内核地址 

pgd_t *pgd; //全局页目录
pmd_t *pmd; //中间页目录
pte_t *ptep,pte; //页表项

unsigned long va,ret=OUL; 
va=(unsigned long)address;
pgd=pgd_offset_k(va); //获取全局页目录首地址

f(!pgd_none(*pgd)){

pmd=pmd_offset(pgd,va); //获取中间页目录
if(!pmd_none(*pmd)){
ptep=pte_offset_kernel(pmd,va); //获取页表项
pte=*ptep;
if(pte_present(pte)){
ret=(unsigned long)page_address(pte_page(pte));
ret |=(va&(PAGE_SIZE-1));
}
}
}
return ((volatile void *)ret);
}

struct mapdrvo *md;
MODULE_LICENSE("GPL");

static int __init mapdrvo_init(void){

unsigned long virt_addr;
int result,err;
dev_t dev=0;
dev=MKDEV(0,0);
major=MAJOR(dev);
md=kmalloc(sizeof(struct mapdrvo),GFP_KERNEL);
if(!md){

goto fail1;
}
result=alloc_chrdev_region(&dev,0,1,"mapdrvo");
if(result<0){

printk(KERN_WARNING "MAPDRVO:can't get major %d\n",major);
goto fail2;
}
cdev_init(&md->mapdev,&mapdrvo_fops);
md->mapdev.owner=THIS_MODULE;
md->mapdev.ops=&mapdrvo_fops;
err=cdev_add(&md->mapdev,dev,1);
if(err){

printk(KERN_NOTICE "error %d adding mapdrvo",err);
goto fail3;
}
atomic_set(&md->usage,0);

vmalloc_area=vmalloc(MAPLEN);
if(!vmalloc_area)
goto fail4;
for(virt_addr=(unsigned long)vmalloc_area;virt_addr<(unsigned long)(&(vmalloc_area[MAPLEN/sizeof(int)]);virt_addr+=PAGE_SIZE){

SetPageReserved(virt_to_page(vaddr+to+kaddr((void *)virt_addr)));
}
strcpy((char *)vmalloc_area,"hello world from kernel space!");

printk("vmalloc_area at 0x%p(phys 0x%lx)\n",vmallo_area,virt_to_phys((void *)vaddr_to_kaddr(vmalloc_area)));
return 0;
fail4:
cdev_del(&md->mapdev);
fail3:
unregister_chrdev_region(dev,1);
fail2:
kfree(md);
fail1:
return -1;
}

static void __exit mapdrvo_exit(void){

unsigned long virt_addr;
dev_t devno=MKDEV(major,0);
for(virt_addr=(unsigned long)vmalloc_area;virt_addr<(unsigned long)(&(vmalloc_area[MAPLEN/sizeof(int)]));virt_addr+=PAGE_SIZE){
ClearPageReserved(virt_to_page(vaddr_to_kaddr((void *)vitr_addr)));
}

if(vmalloc_area)
vfree(vmalloc_area);
cdev_del(&md->mapdev);
unregister_chrdev_region(devno,1);
kfree(md);
}

int mapdrvo_open(struct inode *inode,struct file *file){

struct mapdrvo *md;
md=container_of(inode->i_cdev,struct mapdrvo,mapdev);
atomic_inc(&md->usage);
return 0;
}

int mapdrvo_release(struct inode *inode,struct file *file){

struct mapdrvo *md;
md=container_of(inode->i_cdev,struct mapdrvo,mapdev);
atomic_dec(&md->usage);
return 0;
}

int mapdrvo_mmap(struct file *file,struct vm_area_struct *vma){

unsigned long offset=vma->vm_pgoff<<PAGE_SHIFT;
unsigned long size=vma->vm_end-vma->vm_start;
if(offset & ~PAGE_MASK){
printk("offset not aligned:%ld\n",offset);
return -ENXIO;
}
if(size>MAPLEN){

printk("size too big\n");
return (-ENXIO);
}
if((vma->vm_flags & VM_WRITE) && !(vma->vm_flags & VM_SHARE)){

printk("writeable mappings must be shared,rejecting\n");
return -EINVAL;
}
vma->vm_flags |= VM_LOCKED;
if(offset==0){
vma->vm_ops=&map_vm_ops;
map_vopen(vma);
}
else{
printk("offset out of range\n");
return -ENXIO;
}
return 0;
}

void map_vopen(struct vm_area_atruct *vma){
}

void map_vclose(struct vm_area_struct *vma){
}

struct page *map_nopage(struct vm_area_struct *vma,unsigned long address,int *type){

unsigned long offset;
unsigned long virt_addr;
offset=address-vma->vm_start+(vms->vm_pgoff<<PAGE_SHIFT);
virt_addr=(unsigned long)vaddr_to_kaddr(&vmalloc_area[offset/sizeof(int)]);
if(virt_addr==OUL){
return ((struct page *)OUL);
}

get_page(virt(virt_addr));
printk("map_dev: page fault for offset 0x%lx(kseg x%lx)\n",offset,virt_addr);
return (virt_to_page(virt_addr));
}

module_init(mapdrvo_init);
module_exit(mapdrvo_exit);

