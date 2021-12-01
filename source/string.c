#include"header.h"

#define ESCAPE 92
#define DIFF 32
#define CSIZE 300

//These functions perform the required string operations.

extern int stack[size];
extern int top;

int strlen(char string[])
{
   int i=0;
  while(string[i]!='\0')
      i++;                     //returns the string length of a function
  return i;
}

int ispresent(const char *string,const char *sub,int *pre) 
{
  char *mv,*mv2;
   *pre=0; 
   
  while(*string)
   {
     if(*string==*sub)  
     {
       mv=string+1;
       mv2=sub+1;

      while((*mv==*mv2) && *mv)     //checks whether a given string is present
      {
        mv++;
        mv2++;
      }
       if(!*mv2)
           return 1;
     }
    string++;
    (*pre)++;
   }  
  return 0; 
}

void concat(char *p,char q)
{
  while(*p)
      p++;
  *p=q;                   //concatenates a character to a string
  *(p+1)='\0';
}

void mystrcpy(char p[],char q[])
{
 int i=0;
    while(q[i])
    {
        p[i]=q[i];
        i++;             //copies one string to another
    }
  p[i]='\0';  
}

void replace(char *temp,const char *text1,const char *text2)
{
 char p[CSIZE];  
  int pos;
  
  if(ispresent(temp,text1,&pos))
    {
      char *s1=temp;
      p[0]='\0';
      int i=0;  
       while(i<pos)
        {
            concat(p,*temp);
            temp++;
          i++;
        }
       while(*text2)
       {
         concat(p,*text2);      
         text2++;                    //Replaces text1 in temp by temp2
       }

       while(*temp==*text1)
       {
           temp++;
           text1++;
           i++;
       }

       while(*temp && i<strlen(s1))
       {
          concat(p,*temp);
          temp++;
         i++;
       }
      temp=s1;
      mystrcpy(temp,p);
    }
}

int case_check(char c1,char c2,int flag)
{
   if(c1==c2)
     return 1;
   if(flag==0)
   {
      return 0;  
   }
   else
   {
       if(isalpha(c1) && isalpha(c2))
          {
             if(max((int)c1,(int)c2)-min((int)c1,(int)c2)==DIFF)  //Checks the case of a variable
                 return 1;
           }
      
   }
  return 0; 
    
}

int get_string(char temp[],char new[],int pos1,int pos2)
{
  if(strlen(temp)<pos1 || strlen(temp)<pos2)
      return -1;
  int i=pos1-1;
  while(i<=pos2)
  {
   new[i-pos1]=temp[i];
   i++;                             //Gets a string from temp and puts it in new
  }                             
  new[i-pos1]='\0';                   

  return 1;
}

int encounter(char pattern[],int pos)
{
    int i=pos;

    while(pattern[i]!=')' && i<strlen(pattern))
    {
      if(pattern[i]=='(')
      {
        while(pattern[i]!=')')
          i++;
        i++;
      }                         //checks whether '|' is encountered
      if(pattern[i]=='|')
          return i;
      i++;
    }

   return 0; 
}

int place(int in,int fi,char newp[],char pattern[],char new[])
{
  if(in>strlen(pattern) || fi>strlen(pattern))
      return -1;
  
  int i=0;
  newp[0]='\0';
   while(i<=in)
   {
     concat(newp,pattern[i]); 
     i++;
   }
   i=0;                        
   while(i<strlen(new))
   {                             //places a new string in newp with specified positions
     concat(newp,new[i]);                         
     i++;
   }
   
   i=fi;
   
   while(i<=strlen(pattern))
   {
     concat(newp,pattern[i]);   
     i++;
   }
    
  return 1;

}

 
int trim(char string[])
{
     
  int final_len,erro,next_parent,i=0,init,flag=0;
  char newp[CSIZE],new[CSIZE];

 if(string[0]=='(') 
 {
     if(!encounter(string,1))
     {
         init=0;
         flag=1;
     }
 }
  while(i<strlen(string) && flag==0)
   {
     if( i>0 && (int)string[i-1]!=ESCAPE && string[i]=='(') 
     {
                                                      //Trims redundant '(' and ')'
       init=i;
       if(!encounter(string,init+1))
       { 
           break;
       }    
     }
    i++; 
   }
    

  if(i==strlen(string))
      return 0;

       final_len=encounter(string,init+1);
    if(final_len==0)
    {   
        
     next_parent=parent_pos(string,init);
      erro=get_string(string,new,init+1,next_parent-1);
      
       place(init-1,next_parent+1,newp,string,new);
     // puts(newp); 
    mystrcpy(string,newp); 
    flag=1;
    }  

 return flag;   
    
}

int parent_pos(char pattern[],int pos)
{
   top=-1;
  if(pattern[pos]=='(')
  {
    int i=pos,count=1,k;  
     while(i<strlen(pattern))
     {
       if((int)pattern[i-1]!=ESCAPE && (pattern[i]=='(' || pattern[i]==')'))
       {
          if(pattern[i]=='(')
          {
              push(count); 
              count++;
          }
          else                       //Returns the position of opposite parenthesis
          {
              k=pop();
              count--;
              if(k==1)
                  return i;
          }
       }
      i++; 
     }
  }
  else
  {
    int i=pos,count=1,k;  
     while(i>=0)
     {
       if((int)pattern[i-1]!=ESCAPE && (pattern[i]=='(' || pattern[i]==')'))
       {
          if(pattern[i]==')')
          {
              push(count); 
              count++;
          }
          else
          {
              k=pop();
              count--;
              if(k==1)
                  return i;
          }
       }
      i--; 
     }
  }
      
 return -1; 
   
}
