#define NR_PGT 0x4
#define PGD_BASE (unsigned int *)0x1000//页总目录的基址，即首地址
#define PAGE_OFFSET//页的尾地址

#define PTE_PRE 0x01
#define PTE_RW  0x02
#define PTE_USR 0x04

void page_init(){

int page=NR_PGT;
unsigned int page_offset=PAGE_OFFSET;
unsigned int *pgd=PGD_BASE;
unsigned int phy_add=0x0000;

unsigned int *pgt_entry=（unsigned int *）0x2000;
while(pages--){

*pgd++=page_offset|PTE_USR|PTE_RW|PTE_PRE;
page_offset+=0x1000;
}

pgd=PGD_BASE;

while(phy_add<0x1000000){

*pgt_entry++=phy_add|PTE_USR|PTE_RW|PTE_PRE;
phy_add+=0x1000;
}

_asm__volatile_("movl %0,%%cr3;"
"movl %%cr0,%%eax;"
"orl $0x80000000,%%eax;"
"movl %%eax,%%cr0;"::"r"(pgd):"memory","%eax");
}


 

