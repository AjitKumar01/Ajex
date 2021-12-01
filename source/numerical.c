#include"header.h"

//These functions perform numerical operations.

int ten(int count)
{
    if(count<0)
        return -1;
    if(count==0)
        return 1;
 int i=1,number=1;    
   while(i<=count)           //Returns the power of 10 i.e 10^count
   {
    number*=10;
    i++;
   }
 return number;  
}

int reverse(int number)
{
    int new=0,g=0,k=number;
   while(k!=0)
   {
       k/=10;
       g++;
   }                         //Reverses a number
   g--;
   while(number!=0)
   {
       new+=(number%10)*ten(g);
       g--;
       number/=10;
   }
  return new; 
}

int max(int a,int b)
{
  if(a>b)
      return a;                //Returns the maximum number
  return b;
}

int min(int a,int b)
{
  if(a>b)                    
      return b;              //Returns the minimum number
  return a;
}
