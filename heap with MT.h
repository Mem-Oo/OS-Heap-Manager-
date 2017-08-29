#ifndef HEAP_H
#define HEAP_H
#define BB 16 //size of Block

class heap {
public:
      heap(unsigned long n);
     ~heap();
      void *memalloc(unsigned int reqsize);
      void memfree(void *allocptr);

private:
   struct block; //overhead
   typedef block *link;
   struct block // size of the block is 4+4+x = 8+x byte
      {
      unsigned int size;// Block size 
      union { //struct in the same address "space efficient"
      link nxt; //pointer to next block "4byte"
      char data[BB-4]; //reminder part of the block   
            };
      };
   link heapmem; 
   unsigned int nchunk;//number of chunks in the heap
   link prevptr, ptr, head, base;
};

#endif
