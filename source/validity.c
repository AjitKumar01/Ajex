#include"header.h"

//These functions check the validity of a regex given.

extern int top;

int check_par(char pattern[])
{
  int i=0,k,jl=0;
  
  while(i<strlen(pattern))
  {
    if((i>0 && (int)pattern[i-1]!=92)||i==0) 
    {
   
     switch(pattern[i])
     {
         case '[':
                   push(1);
                   break;
         case '{':
                   push(2);
                   break;
         case '(':
                   push(3);                    //This function checks whether a given expression is properly parenthized.
                   break;
         case ']':
                   k=pop();
                    if(k!=1)
                    {
                      printf("\nMissed a square bracket: ");  
                      limechar(pattern,i);  
                        return 0;
                    }    
                   if(k==-1)
                   {
                      printf("\nMissed a square bracket: ");  
                      limechar(pattern,i);  
                       return 0;
                   }    
                   break;
         case '}':
                   k=pop();
                    if(k!=2)
                    {
                      printf("\nMissed a brace: ");  
                      limechar(pattern,i);  
                        return 0;
                    }    
                   if(k==-1)
                   {
                      printf("\nMissed a brace: ");  
                      limechar(pattern,i);  
                       return 0;
                   }    
                   break;
         case ')':
                   k=pop();
                    if(k!=3)
                    {
                      printf("\nMissed an open parenthesis: ");  
                      limechar(pattern,i);  
                        return 0;
                    }    
                   if(k==-1)
                   {
                      printf("\nMissed an open parenthesis: ");  
                      limechar(pattern,i);  
                       return 0;
                   }    
                   
     }
    } 
  
     i++;
  }
    
  
  if(top==0)
        return 1;
printf("\nMissed a parenthesis."); 
  return 0;
}

int check_symbols(char pattern[])      //This function checks whether the symbols are properly placed
{
  if(pattern[0])
  {
     if(pattern[0]=='+')
     {
       printf("\nCan't have the first character as +: "); 
       limechar(pattern,0);
         return 0;
     }    
              
      
  }    
  if(symbols(pattern[0]) && symbols(pattern[1]))
  {
      printf("\nConsecutive occurence of meta character: ");
      limechar(pattern,1);
      return 0;
  }                                            
  int i=2;
   while(i<strlen(pattern))
   {
       if(symbols(pattern[i]))
       {
           if(symbols(pattern[i-1]) && (int)pattern[i-2]!=92)
           {
                printf("\nConsecutive occurence of meta character: ");
                limechar(pattern,i);
               return 0;
           }    
       }
      i++; 
   }

  return 1; 
}

int check_in(char pattern[])    //This function checks for range error in []
{
  if(check_par(pattern))
  {
    int i=0;
     while(i<strlen(pattern))
     {
        if(pattern[i]=='[')
        {
            
            i+=1;
           while(pattern[i]!=']')
           {
             if((int)pattern[i-1]!=92 && (pattern[i]=='(' || pattern[i]==')'))
             {
                 printf("\nCan't have parenthesis inside square brackets: ");
                 limechar(pattern,i);
                 return 0;
             }    
             if(isalnum(pattern[i]) && pattern[i+1]=='-' && isalnum(pattern[i+2]))
                 if(pattern[i]>pattern[i+2])
                 {
                     printf("\nIncorrect use of range: ");
                     limechar(pattern,i+2);
                     return 0;
                 }    
               i++;  
           }
        }
        
        else if(pattern[i]=='{')
        {
         int count=0;
          i++;
            while(pattern[i]!='}')
            {
              if(pattern[i]==',') 
                  count++;
              else if(!isdigit(pattern[i]))
              {
                  printf("\nIs not a digit: ");
                  limechar(pattern,i);
                  return 0;
              }    
              if(count>1)
              {
                  printf("\nCan't have more than one comma: ");
                  limechar(pattern,i);
                  return 0;
              }    
              i++;
            }   
         
        }
        
        i++;
     }
    return 1; 
  }
  return 0;
}
