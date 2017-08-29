#include <iostream>
#include <ctime>
#include <cmath>
#include "heap.h"
using namespace std;

int main()
{
  int x; 
  cout<<"...WELCOME..."<<"\nThis is a free storage Manager <Heap Manager>\n";
  cout<<"the heap uses the first fit allocation strategy\n";
  cout<<"Enter Heap manager size< in MB >: ";
  cin>>x;
  heap m(x*1000000);
  double *a,*b,*c,*d,*e,*f;
  clock_t start = clock(); // start of count 
//for(long k=0;k<= 9999;k++) //activate it for calc. time only
{
  a=(double*)m.memalloc(300);
  b=(double*)m.memalloc(100);
  c=(double*)m.memalloc(100);
  d=(double*)m.memalloc(100);
  cout<<"a="<<a<<"\n"<<"b="<<b<<"\n"<<"c="<<c<<"\n"<<"d="<<d<<"\n";
  m.memfree(a);
  m.memfree(b);
  m.memfree(c);
  e=(double*)m.memalloc(524); //check bounce
  cout<<"e="<<e<<"\n";
  f=(double*)m.memalloc(300);
  cout<<"f="<<f<<"\n";
}

   //Calculating the average time in nsec :
   cout<<"avg. time ="<<pow (10.0,5)*((double)clock()-start)/CLOCKS_PER_SEC<<" ns\n"; 

   system("PAUSE");
   return EXIT_SUCCESS;
}
