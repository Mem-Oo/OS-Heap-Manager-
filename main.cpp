#include <iostream>
#include <ctime>
#include <boost/thread.hpp>
#include "heap.h"
using namespace std;
  
heap m(128000000); // 128MB HeapSize
double *a,*b,*c,*d,*e,*f;

void thread() // my thread thread
{
a=(double*)m.memalloc(300);
}

//...In this example we make two threads both of them requires the allocate function.
//and shows the thread ID on the display CMD.
//thread safe prevents other threads from taking ownership while a particular thread owns it.
//with the thread safe the two threads can run in parallel. 
//one thread can access the "allocate (or free) function" on the time.
//(For single core processors) the thread must wait until the another one leave the function.

int main()
{ 
  // start of the time
  //clock_t start=clock();
//for(long k=0;k<= 9999;k++)  
{
 cout<<"max parallel threads = "; 
 cout << boost::thread::hardware_concurrency() <<"\n";
 boost::thread t1(thread);
 boost::thread t2(thread);
 t1.join();
 t2.join();
}

//Calculating the average time in nsec :
// cout<<"avg. time ="<<pow (10.0,5)*((double)clock()-start)/CLOCKS_PER_SEC<<" ns"<<"\n"; 

   system("PAUSE");
   return EXIT_SUCCESS;
}