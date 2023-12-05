// Physical memory allocator, for user processes,
// kernel stacks, page-table pages,
// and pipe buffers. Allocates whole 4096-byte pages.

#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "riscv.h"
#include "defs.h"

// the reference count of physical memory page
int reference_count_array[PHYSTOP / PGSIZE]; // EACH ELEMENT IN THIS ARRAY MAPS TO A PAGE IN THE PHYSICAL MEMORY
struct spinlock ref_count_lock;     // TO PROTECT THE ABOVE ARRAY

void freerange(void *pa_start, void *pa_end);

extern char end[]; // first address after kernel.
                   // defined by kernel.ld.

struct run
{
  struct run *next;
};

struct
{
  struct spinlock lock;
  struct run *freelist;
} kmem;

void kinit()
{
  initlock(&kmem.lock, "kmem");
  freerange(end, (void *)PHYSTOP);
}

void freerange(void *pa_start, void *pa_end)
{
  char *p;
  p = (char *)PGROUNDUP((uint64)pa_start);
  for (; p + PGSIZE <= (char *)pa_end; p += PGSIZE)
    kfree(p);
}

// Free the page of physical memory pointed at by pa,
// which normally should have been returned by a
// call to kalloc().  (The exception is when
// initializing the allocator; see kinit above.)
void kfree(void *pa)
{
  struct run *r;

  // CHECK FOR INVALID pa VALUES
  if (((uint64)pa % PGSIZE) != 0 || (char *)pa < end || (uint64)pa >= PHYSTOP)
    panic("kfree");

  // DECREASE THE REFERENCE COUNT OF THE PAGE
  acquire(&ref_count_lock);
  reference_count_array[(uint64)pa / PGSIZE] -= 1;
  int reference_count = reference_count_array[(uint64)pa / PGSIZE];
  release(&ref_count_lock);

  // IF REFERENCE COUNT OF PAGE IS NOT ZERO, THEN RETURN
  if (reference_count > 0) // condition ensures that pages in use during initialization, with a reference count of -1, are not accidentally released
    return;

  // FILL THE FREED PAGE WITH JUNK TO CATCH DANGLING REFERENCES
  memset(pa, 1, PGSIZE);

  // CONVERT THE FREED MEMORY INTO A RUN STRUCTURE
  r = (struct run *)pa;

  // ADD THE FREED MEMORY BLOCK TO THE FREELIST
  acquire(&kmem.lock);
  r->next = kmem.freelist;
  kmem.freelist = r;
  release(&kmem.lock);
}

// Allocate one 4096-byte page of physical memory.
// Returns a pointer that the kernel can use.
// Returns 0 if the memory cannot be allocated.
void *
kalloc(void)
{
  struct run *r;

  // ACQUIRE THE KERNEL MEMORY LOCK
  acquire(&kmem.lock);

  // GET A FREE MEMORY BLOCK FROM THE freelist
  r = kmem.freelist;
  if (r)
  {
    // UPDATE THE FREELIST TO POINT TO THE NEXT BLOCK
    kmem.freelist = r->next;

    // REFERENCE COUNT OF NEWLY ALLOCATED PAGE IS SET TO 1
    acquire(&ref_count_lock);
    reference_count_array[(uint64)r / PGSIZE] = 1;
    release(&ref_count_lock);
  }
  release(&kmem.lock);

  // FILL THE ALLOCATED PAGE WITH JUNK TO CATCH DANGLING REFERENCES
  if (r)
    memset((char *)r, 5, PGSIZE);
  return (void *)r;
}
