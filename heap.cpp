#include "heap.h"
#include <iostream>
#include <cassert>
using namespace std;
//============== constructor =================================================
 
heap::heap(unsigned long n)
{
nchunk =(n+sizeof(block)-1U)/sizeof(block);//number of chunks in the heap according to block size        
heapmem= new block [nchunk+1];//heap Memory storage of size = nchunks * block size + base block
//the Base block act as atail for the heap 
//new block[nchunk] like  new char [1>>27].
//but the heap is seen as constructed of a number of blocks
//cout<<heapmem<<"\n";
assert(heapmem); // check if the address is allocated or not
base =&heapmem[nchunk];// Base of the heap
head =heapmem; // Now the Heap is a big chunk ...
head->size =nchunk; 
head->nxt =NULL;
base->nxt =head;
base->size =0;
}
//============== Deconstructor ===============================================
 
heap ::~heap()
    { delete [] heapmem; } // delete the heap from the main memory
//=============== memalloc  ==================================================
 
 void *heap::memalloc(unsigned int reqsize)
{
   unsigned int nblock=(reqsize+ sizeof (block)+ sizeof(link)-1U) /sizeof (block); //number of Req. blocks 
   prevptr=base; //intializing 
   ptr=prevptr->nxt; // now ptr starts at the head of the heap
 while (ptr != NULL && ptr->size < nblock) // loop check for first fit block 
    {
	prevptr = ptr; // prevptr will point to non fit"free" block
	ptr = ptr->nxt; // start again from next free block to check for the fit block 
    }
    if (ptr==NULL|| reqsize <= 0) //the search for a free area is unsuccessful or invalid size
    {
	return NULL;//OR throw bad_alloc ("out of memory"); //exception 
    }
    if (ptr->size > nblock) // check if the heap has anumber of blocks > number of required blocks
    {
	link newblock = &ptr [nblock]; //address of "new head" will be ptr + number of alloc. blocks
	newblock->size= ptr->size - nblock; //new head size= new size 
	newblock->nxt = ptr->nxt; // copying info of prev head ...
	ptr->size = nblock; // preparing alloc. block ... 
	ptr->nxt = newblock; 
    }
    prevptr->nxt = ptr->nxt;
	return ptr->data; // address of start Writing data -in the alloc. block- 
}
//================= memfree ==================================================
  
void heap::memfree (void* allocptr)
{   link freeblock;
    int *to; to=(int*)allocptr-1U;// the allocptr points to data array address, 
    //we need to point it to the address of the block "shift it" 
    freeblock=(link)to; //now we find the address of the alloc. block  
	//cout<<"free="<<freeblock->size<<"\n";
    if ( freeblock< heapmem || freeblock >= (heapmem + nchunk)) //Out of the heap area
    { 
	 return ;// throw invalid_argument ("invalid Block"); //not alloc. address 
    }
     prevptr = base; // starting ...
     ptr = prevptr->nxt;
    while (ptr != NULL && ptr < freeblock) //search for the location of the block 
    {
	prevptr = ptr; //store address of previous checked block 
	ptr = ptr->nxt; // points to the next block(its address)
    }
    if (ptr != NULL && freeblock + freeblock->size == ptr) // the last alloc. block    
    {
	freeblock->size += ptr->size; //**Bounce** (prev+current)block
	freeblock->nxt = ptr->nxt; //linking the free blocks
    }
    else //not the last alloc. block (unlinking)
	freeblock->nxt = ptr;// linking the block that will be free with the free list 
    if (prevptr + prevptr->size == freeblock)//**Bounce** 
    {
	prevptr->size += freeblock->size; // aggregates the free blocks to one big chunk (next+current) block 
	prevptr->nxt = freeblock->nxt;// linking ...
    }
    else
	prevptr->nxt = freeblock; 
}
//=============================== Done =======================================