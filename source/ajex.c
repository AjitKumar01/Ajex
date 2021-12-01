/*

NAME: Ajit Kumar Sahu
R.No: 163213
Project: REGEX
DATE: 14.03.19

*/

#include"header.h"

#define PSIZE 500 

 int stack[size];
 int top=0;
 int CASE=0;
 int LEN_FLAG=0;                   //Global variables
 int LEN=0;
 int SLEN=0;
 int INI_FLAG=0;

void main(int argc,char *argv[])     //Input is taken with the help of command line arguments
{
  

if(argc!=3)
{
printf(RED);    
 if(argc>3)   
  printf("\nNot more than 3 arguments!!\n\n");  
 else                                               //Only 3 arguments are taken
  printf("\nToo few arguments!!\n\n");  
printf(RESET);     
  exit(-1);
}

system("clear");

if(!check_in(argv[1]) || !check_symbols(argv[1]))
 { 
     printf("\nIncorrect regular expression.\n\n");       //checks whether the regular expression is valid.
     exit(-1);
 }
 FILE *fp;

 fp=fopen(argv[2],"r");
 if(fp==NULL)
 {
     printf("\nCan,t access the file\n");       //Exits when the file can't be accessed
     exit(-1);
 }


char pattern[PSIZE],npattern[PSIZE];
char *temp,string[PSIZE];                        
int order=0,num=1,change,kj,i,kl,chan=0;

mystrcpy(pattern,argv[1]);

printf(RED"Your REGEX: "RESET);
printf(CYN);
puts(pattern);
printf(RESET);

if(strlen(pattern)>4 && pattern[0]=='(' && pattern[1]=='?' && pattern[2]==':' && pattern[3]==')')
{
  CASE=1;  
 int j=0;                                      //Trims the string when case check is encountered 
  for(;j<strlen(pattern)-3;j++)
      pattern[j]=pattern[j+4];
}
//puts(pattern);

place(0,1,npattern,"()",pattern);             //Encloses the regex with ()
//puts(npattern);                          


///////////////////////////////////////
while(ispresent(npattern,"\\d",&kl))
{ replace(npattern,"\\d","[0-9]");
  kl=-1;
}  
                                               
while(ispresent(npattern,"\\D",&kl))
{ replace(npattern,"\\D","[^0-9]");
  kl=-1;
}  
                                              //Strings are replaced with corresponding regex whenever \d \w \W \D are encounterd 
while(ispresent(npattern,"\\w",&kl))
 {
     replace(npattern,"\\w","[A-Za-z0-9_]");
 }

while(ispresent(npattern,"\\W",&kl))
 {
     replace(npattern,"\\W","[^A-Za-z0-9_]");
 }

printf("\n\n");
///////////////////////////////////

 while(1)
 {
  chan=0;
  order=0;
  LEN=0;
  LEN_FLAG=0;
  SLEN=0;

  fgets(string,300,fp);
    temp=string;
  
  SLEN=strlen(string);
  INI_FLAG=0;

    if(feof(fp))                       // A string is obtained fromthe file and sent to the function regex which further determines whether the substring is
        break;                          // present.
  
   kj=regex(temp,npattern,&order);
   temp=temp+LEN+1;
   chan+=(LEN+1);
   
   if(INI_FLAG==1 && kj==1)
   {
      i=LEN+1;
     while(i<strlen(string)-1)
     {
        printf("%c",string[i]); 
        i++;
     }
       
       printf("\n");

    }
    
   while(kj==1 && temp[0] && INI_FLAG==0) 
    {
        LEN_FLAG=1;
       kj=regex(temp,npattern,&order);
       temp=temp+LEN+1;
       chan+=(LEN+1);
    }
   chan-=(LEN+1); 
   if(LEN_FLAG)                       
   {                                             
    
      i=chan;
     while(i<strlen(string)-1)
     {
        printf("%c",string[i]); 
        i++;
     }
       
       printf("\n");
   }    

}
printf("\n\n"); 

}
