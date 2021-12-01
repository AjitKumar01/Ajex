#include"header.h"

//These functons take care of each metacharacter separately.

extern int stack[size];
extern int top;
extern int CASE;
extern int LEN_FLAG;
extern int LEN;
extern int SLEN;
extern int INI_FLAG;

#define MAX_INT 31000
#define ESCAPE 92
#define DIFF 32
#define CSIZE 200

////////////////////////////Square-'[]'/////////////////////////
int square(char temp,char pattern[],int *pat,int star_flag)
{ 
    
    int i=*pat+1,flag=0,negation=0;
  if(star_flag==1) 
  { while(pattern[i]!=']' && i<strlen(pattern))
   {
      i++;
   }
    if(pattern[i+1]=='+' || pattern[i+1]=='?') 
    {
       *pat=i+1;                                     //If square brackets are immmediately followed by + { ? *
     return 1;                                       //then it returns with a change in pattern position
    }  
    if( pattern[i+1]=='*' || pattern[i+1]=='{')
    {

       *pat=i+1;
      return 1;
    }
  }
   i=*pat+1;
   if(pattern[i]=='^')
   {
       i+=1;
       negation=1;
   }    
  while(pattern[i]!=']' && flag==0)
  {   
     if((int)pattern[i]==ESCAPE && escape(pattern[i+1]))
       { i++;
       } 
     if(isalnum(pattern[i]) && pattern[i+1]=='-')
      {   
          if(temp>=pattern[i] && temp<=pattern[i+2])
              flag=1;
          if(CASE==1)
          {
             if(pattern[i]>91)                                         //Checks whether a character is present in a range of values
                if(temp>=pattern[i]-DIFF && temp<=pattern[i+2]-DIFF)
                    flag=1;
            else
                if(temp>=pattern[i]+DIFF && temp<=pattern[i+2]+DIFF)
                    flag=1;
          }
         i+=1;     
      }
      else
      {
         if(case_check(pattern[i],temp,CASE))
             flag=1;
      }   
   i++;   
  }  
  while(pattern[i]!=']')
      i++;
  if(negation==1 && flag==0)
  {
     *pat=i+1;
    return 1;
  }
  if(flag==1)
      *pat=i+1;
  return flag;

}

////////////////////////////LITERAL////////////////////////////////////
int literal(char temp[],char pattern[],int *pos,int *pat)
{
   int i=*pat,flag=1,kl=(int)pattern[*pat];
  
   while(isliteral(pattern,i) && i<strlen(pattern)) 
   {       
    
    if((int)pattern[i]!=ESCAPE && (pattern[i+1]=='*' || pattern[i+1]=='?'))
      break; 
        if((int)pattern[i]==ESCAPE && escape(pattern[i+1]))
         { i+=1; 
         } 
                                                           
       if(!case_check(pattern[i],temp[*pos],CASE)) 
         { 
            flag=0;                                           
            break;
         }                                            //Matches literals  
       (*pos)++;                         
       i++;
    
    }
 
 if((int)pattern[i]!=ESCAPE && (pattern[i+1]=='*' || pattern[i+1]=='?'))
     i+=1;
 if(flag==1)
 {  *pat=i;
 
 }
 return flag;
}

///////////////////////// Plus //////////////////////////////////////////////

int plus(char temp[],char pattern[],int *pat,int *pos)
{
   int i=*pat,j=*pos,tpos=*pat,flag=0;
   
   if(pattern[0]=='+') 
       return -1;                     //If the first character is + then returns invalid

   if(pattern[i-1]!=']')
   {
     j--;
       while(temp[j]==pattern[*pat-1] && j<strlen(temp))
       { 
         flag=1; 
         j++;
       }
                               //checks and moves if the previous character repeats 1 or more times
     if(flag==1) 
     {
       *pos=j;
       (*pat)++;
       return 1;
     } 
  }
   
  else 
   {
     int fp,k=1;  
     j-=1;
     
      for(;pattern[tpos]!='[';tpos--);
       fp=tpos;
      
                                                     
     while(k==1 && j<strlen(temp))                     
      {
        tpos=fp;
         k=square(temp[j],pattern,&tpos,0);
                                                 //Checks whether the trailing characters are one of the optional character 
                                                      
        if(k==1 && j<strlen(temp))  
         { 
           j++;                                   
         flag=1;
         }    
      }
     
     
     if(flag==1) 
     {
       *pos=j;
       (*pat)++;
       return 1;
     } 
      
   }
  
 return flag; 
}

///////////////////////////////CURLY {2,3}/{2} /////////////////////////////////////

int curly(char temp[],char pattern[],int *pat,int *pos)
{
    
   if(pattern[0]=='{') 
       return -1;              //Returns invalid if the first character is '{'
   
   int i=*pat,j=*pos,tpos=*pat,flag=0,flag_comma=0;
   
   int k=(*pat)+1,max=0,min=0,digit=0,g=0;
    
     while(pattern[k]!='}')
     {
        digit=(int)pattern[k]-48;
       min=digit*ten(g);
       k++;
       g++;
        if(pattern[k]==',')                 
        {flag_comma=1;
            break;
        }   
     }                 
                                          
   if(flag_comma)
    { k+=1;
    g=0;
     while(pattern[k]!='}')
     {
        digit=(int)pattern[k]-48;
       max=digit*ten(g);
       k++;
       g++;
     }
   }                                            //The number is obtained from the string {23,23}
   else
   {
       max=min;
   }   
   min=reverse(min);
   max=reverse(max);
      
   
   if(min>max || (max==0 && min==0))
   {
       printf("\nCurly error\n");
       exit(-1);
   }
    if(max==0)
    {
        max=MAX_INT;
    }
    if(min<0)
    {
        min=0;
    }
   
   int count=0; 
   if(pattern[i-1]!=']')
   {
     j--;
       while(temp[j]==pattern[*pat-1] && j<strlen(temp))
       {  
         j++;
         count++;
          if(count==max)                             //checks whether the character is repeated min<=x<=max number of times
              break;
       }
       
     if(count>=min && count<=max) 
         flag=1;
     if(flag==1) 
     {
       *pos=j;
      
       while(pattern[*pat]!='}')                     
        (*pat)++;
       
      (*pat)++;
       return 1;
     } 
  }
   
  else 
   {
     int fp,k=1;  
     j-=1;
     
      for(;pattern[tpos]!='[';tpos--);
       fp=tpos;
      
        
     while(k==1 && j<strlen(temp))
      {
        tpos=fp;
         k=square(temp[j],pattern,&tpos,0);
              
                                            //Checks whether the trailing characters are repeated min<=x<=max number of times          
        if(k==1 && j<strlen(temp))  
         { 
           j++;
          count++;
         }    
      }
     
                                           
     if(count>=min && count<=max) 
         flag=1;
     if(flag==1) 
     {
       *pos=j;
      while(pattern[*pat]!='}') 
       (*pat)++;
      (*pat)++;
       return 1;
     } 
      
   }
  
 return flag; 
}

//////////////////////////// Star *///////////////////////////////////////

int star(char temp[],char pattern[],int *pat,int *pos)
{
   int i=*pat,j=*pos,tpos=*pat;
   
   if(pattern[0]=='*' && strlen(pattern)==1)
   {
      (*pat)=strlen(pattern);
     return 1;
   } 
   if(pattern[0]=='*')
   {
        if(strlen(pattern)>=3 && (int)pattern[tpos+1]==ESCAPE && escape(pattern[tpos+2]))
            tpos+=1;

      while(temp[j]!=pattern[tpos+1] && j<strlen(temp))
      {
         j++;
      }                                          
      if(j==strlen(temp))                      
          return -1;                            //Takes care of *abcd 
      else
      {                                  
        *pos=j+1;
        (*pat)+=2;
        return 1;
      }                                                    

   }

   if(pattern[i-1]!=']')
   {
     while(temp[j]==pattern[*pat-1])
         j++;                                   
    
   }
   else 
   {
     int fp,k=1;  
     
     for(;pattern[tpos]!='[';tpos--);
     fp=tpos;
        
     while(k==1 && j<strlen(temp))
      {
        tpos=fp;                                  //Checks whether trailing characters is repeated
         k=square(temp[j],pattern,&tpos,0);
       if(k==1)  
        j++; 
      }
   }
   *pos=j;
   (*pat)++;
  return 1; 
}

//////////////////////////Question ?////////////////////////////////////////////////
int question(char temp[],char pattern[],int *pat,int *pos)
{
    
  int tpos=*pat,j=*pos; 
   if(pattern[0]=='?' && strlen(pattern)==1)
   {
      (*pat)=strlen(pattern)+1;
     return 1;
   }
   if(pattern[0]=='?')
   {
        if(strlen(pattern)>=3 && (int)pattern[tpos+1]==ESCAPE && escape(pattern[tpos+2]))
            tpos+=1;
        
      while(temp[j]!=pattern[tpos+1] && j<strlen(temp))
      {
         j++;
      }    
      if(j==strlen(temp))
          return -1;                         //takes care of ?abcd
      else
      {
        *pos=j+1;
        (*pat)+=2;
        return 1;
      }
   }
   
   if(pattern[tpos-1]!=']')
   {
       
      if(pattern[tpos-1]==temp[j])            //checks whether the character is present(optional)
          j++;
      
   }
   else
   {  
    j-=1; 
      printf("%c",temp[j]);
     for(;pattern[tpos]!='[';tpos--);  
         
     if(square(temp[j],pattern,&tpos,0))   //checks whether the character is present in the set of optional characters. 
             j++;
      printf("%c",temp[j]);
   }
  *pos=j;
  (*pat)++;
 return 1; 
}
///////////////////////////////// Grouping ////////////////////////////////////
int grouping(char temp[],char pattern[],int *pat,int *pos)
{
  if(*pat>0 && (int)pattern[*pat-1]==ESCAPE) 
  {
      printf("\nNOT a valid entry");
  }
   int flag=0; 
 
    int final_len,max=0,move,tr=*pat,erro,kk,init=*pat,x;
    int next_parent=parent_pos(pattern,*pat);
    char new[CSIZE],newp[CSIZE];
                                                             
    while(1)
    { 
        move=0;
          final_len=encounter(pattern,init+1);
           if(final_len==0)
               break;
                                                          //This function extracts a regex and calls the function regex to check whether a substring satisfies
                                                          //the given regular expression.
     erro=get_string(pattern,new,init+1,final_len-1);
      
       place(*pat-1,next_parent+1,newp,pattern,new);
      
     if(erro==-1)
      {
          printf("\nTrouble with strings1");
          exit(-1);
      }
     
     kk=regex(temp,newp,&move);
       if( kk==1)
       {
           flag=1;
           break;
       }
      init=final_len;
    }
    
    for(x=next_parent-1;x>0;x--)
    {
       if(pattern[x]==')')
       {
          while(pattern[x]!='(')
              x--;
          x--;
       }
       if(pattern[x]=='|' || pattern[x]=='(')
       {
          init=x;
          break;
       }
    }
    
      erro=get_string(pattern,new,init+1,next_parent-1);
       
      place(*pat-1,next_parent+1,newp,pattern,new);
        
      if(erro==-1)
      {
          printf("\nTrouble with strings2");
          exit(-1);
      }
      move=0;
     
     if(flag==0) 
       kk=regex(temp,newp,&move);
       
     if( kk==1 && flag==0)
       {
           flag=1;
       }

       
       *pat=strlen(pattern);
      return flag; 
}
///////////////////////////////////////////////// Function regex /////////////////////
int regex(char temp[],char pattern[],int *order)
{
  
  while(trim(pattern));
  //puts(pattern);
   
  if((strlen(pattern)==1)&&(pattern[0]=='*' || pattern[0]=='?' || pattern[0]=='.'))// || pattern[0]=='$'))
  {
    int i=0;  
      while(i<strlen(temp))
      {
          putchar(temp[i]);                  //returns 1 if the only character is * . ? 
        i++;
      }
      LEN=0;
      return 0;
  }
   
   int pos=0,pat=0,flag=0,pat_pos=0;
   int initial=0,final=0;                   //pos specifies the movement of marker for the string, pat specifies the movement of marker for pattern 
   int bracket_flag=0;                      //and pat_pos is the temporary marker. 
                                            //initial and final mark the first character and final character respectively.
                                            
   if(pattern[0]=='^' || pattern[strlen(pattern)-1]=='$')
    INI_FLAG=1;
   
  while(pat<strlen(pattern))
  {
     if( pattern[pat]=='(')
     {
      if(!(pat>0 && (int)pattern[pat-1]==ESCAPE))   
      {bracket_flag=1;
        break;
      }                                       //Directly takes the marker pat to '(' (if present).
     }
    pat++;    
  }
 
  if(!bracket_flag)
      pat=0;                                 
  
  while(pos<strlen(temp) && pat<strlen(pattern)) 
  {
      //printf("Sairam");
    if(pattern[0]=='^' && pat==0)
    {
       flag=1; 
       pat++;
    }
    /*else if((int)pattern[strlen(pattern)-2]!=ESCAPE && pattern[strlen(pattern)-1]=='$' && pat==strlen(pattern)-1)
    {       
         if (pat_pos==strlen(temp)-1) 
          { flag=1;
           pat++;                                 //This section has been omitted for cmd problems
          }
         else
             flag=0;
    } */  
    else if(pattern[pat]=='.') 
    {
        flag=1;
        pat_pos++;
        pat++;
    }
    else  if(pattern[pat]=='[')
    {
        flag=square(temp[pat_pos],pattern,&pat,1);
        if(flag)                                           //This function coordinates the parsing of a string with different metacharacters. 
            pat_pos++;

    }
    else if(pattern[pat]=='(' )
    {
        flag=grouping(temp,pattern,&pat,&pat_pos);
       return flag; 
    }
    else if(pattern[pat]=='*')
    {
        flag=star(temp,pattern,&pat,&pat_pos);
    }
    else if(pattern[pat]=='?')
    {
        flag=question(temp,pattern,&pat,&pat_pos);
    }
    else if(pattern[pat]=='+')
    {
        flag=plus(temp,pattern,&pat,&pat_pos);
    }
    else if(pattern[pat]=='{')
    {
        flag=curly(temp,pattern,&pat,&pat_pos);
    }
    else 
    {
        flag=literal(temp,pattern,&pat_pos,&pat); 
    }    

   if(flag==0)
   { 
        initial=pos+1;
   }
     if(pat>=strlen(pattern))
     {
        final=pat_pos-1; 
         break;
    }
   if(flag==0)
   {
       pat=0;
       pos++;
       pat_pos=pos;
   }
   if(flag==-1)
   {
       break;
   }

  }
 ////////////////
 if(flag!=-1)
 { 
     if(pat==strlen(pattern))
     {
       if(pattern[0]=='^' && SLEN==strlen(temp)) 
         { 
          if(initial==0)     
           mprintf(temp,initial,final);
          else
           return 0;   
         } 
       
 /*      else if(pattern[strlen(pattern)-1]=='$' && SLEN==strlen(temp)) 
           { 
               if(final==strlen(temp)-2)
                 mprintf(temp,initial,final);
               else                                  //this section has been omitted for cmd problems.
                 return 0;
            }*/
       else
          mprintf(temp,initial,final);
       
     
      *order=final;
      LEN=final;
      return 1;
    } 
 }   
  
 return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
 void mprintf(char temp[],int in,int fi)
{
 int i=0;   
  while(temp[i] && i<=fi)                        
  {
     if(i>=in && i<=fi)
     {printf(GRN "%c",temp[i]);
         printf(RESET);                   //this function prints the required string with the colored substring. 
     }
     else 
         putchar(temp[i]); 
     i++;
  }
}
