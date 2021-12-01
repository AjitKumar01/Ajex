#include"header.h"

#define ESCAPE 92

//These functions check the identity of a character.  

int symbols(char temp)
{
   if(temp=='*' || temp=='+' || temp=='.' || temp=='?' || temp=='}'|| temp=='{' || temp==')')
       return 1;                                         
   return 0;                  //checks whether a symbol is metacharacter
}

int isliteral(char pattern[],int i)
{
   
   if( i>0 && (int)(pattern[i-1])!=ESCAPE && pattern[i]=='$' )
       return 0;
   if(pattern[i]=='[' || pattern[i]=='(' || pattern[i]=='|')
       return 0;                                                   //checks for a literal
   if( i>0 && (int)(pattern[i-1])!=ESCAPE && symbols(pattern[i]) )
   {                                                              
     return 0;
   } 
  return 1; 
}

int escape(char temp)
{

   if(symbols(temp) || temp=='{' || temp==']' || temp=='[' || temp==')' || temp=='(' || temp=='-' )//|| temp=='$')
       return 1;                                 
   return 0;                           //Required symbols are escaped
}

int limechar(char temp[],int pos)
{
  
  int i=0;
 while(i<pos)
 {    putchar(temp[i]);
    i++;
 }

printf(RED "%c",temp[pos]);
printf(RESET);
i++;                                      //A given character is highlighted

 while(i<strlen(temp))
  {    
      putchar(temp[i]);
      i++;
  }
 return 1;
}

int ismeta(char temp,char temp1)
{
   if((int)temp!=ESCAPE && symbols(temp1))
       return 1;                           //uses symbols to check for meta
   return 0;
}
