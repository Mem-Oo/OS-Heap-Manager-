#ifndef HEAP_H
#define HEAP_H
#define Bsize 16 //size of Block

class heap {
public:
      heap(unsigned long n);
     ~heap();
      void *memalloc(unsigned int reqsize); //allocate function 
      void memfree(void *allocptr); // free function

private:
   struct block; //overhead of the allocated area "Alloc. Area ID"
   typedef block *link;
   struct block 
      {
      unsigned int size;// allocated area size 
      union { //struct in the same address "space efficient"
      link nxt; //pointer to next block "4byte"
      char data[Bsize-4]; //reminder part of the block   
            };
      };
   link heapmem; 
   unsigned int nchunk;//number of chunks in the heap
   link prevptr, ptr, head, base;
};

#endif