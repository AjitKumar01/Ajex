#include"header.h"

//These functions are associated with stack operations.

extern int stack[size];
extern int top;

void display_stack()
{
  int i=0;
  printf("\nStack: ");
   while(i<=top)
   {
       printf("%d ",stack[i]);         //Function for displaying a stack
      i++; 
   }
} 

void push(int data)
{
  if(top!=size-1)
  {
      top++;
      stack[top]=data;             //Push function
  }
  else
  {
      printf("\nStack Full!!");
  }
}

int pop()
{
   if(top!=-1)
   {
      int temp=stack[top];
      top--;                       //Pop function
       return temp;   
   }
   
   return -1;
}
