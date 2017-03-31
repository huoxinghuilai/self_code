static struct page *my_follow_page(struct vm_area_struct *vma,unsigned long addr){
pud_t *pud;
pmd_t *pmd;
pte_t *pte;
spinlock_t *ptl;
unsigned long full_addr;
struct page *page=NULL;
struct mm_struct **mm=vma->vm_mm;
pgd=pgd_offset(mm,addr);
if(pgd_none(*pgd)||unlikely(pgd_bad(*pgd))){
goto out;
}
pud=pud_offset(pgd,addr);
if(pud_none(*pud)||unlikely(pud_bad(*pud)))
goto out;
pmd=pmd_offsert(pud,addr);
if(pmd_none(*pmd)||unlikely(pmd_bad(*pmd))){
goto out;
}
pte=pte_offset_map_lock(mm.pmd,addr,&pt1);
if(!pte)
goto out;
if(!pte_present(*pte))
goto unlock;
page=pfn_to_page(pte_pfn(*pte));
if(!page)
goto unlock;
full_addr=(*pte).pte_low&PAGE_MASK;
full_addr+=addr&(~PAGE_MASK);
printk("full_addr=%lx..\n",full_addr);
printk("pte=%lx.....\n",full_addr);
printk("page=%p..\n",page);
get_page(page);
unlock:
pte_unmap_unlock(pte,ptl);
out:
return page;
}
