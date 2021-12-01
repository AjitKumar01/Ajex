
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>


#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"             
#define BLU   "\x1B[34m"           //These macros are defined to color text.
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

#define size 33

    
    
    
void display_stack();
void push(int data);           //stack functions
int pop();

int ten(int count);
int reverse(int number);     
int max(int a,int b);         //numerical functions
int min(int a,int b);

int strlen(char string[]);
int ispresent(const char *string,const char *sub,int *pre) ;
void concat(char *p,char q);                                           //String functions
void mystrcpy(char p[],char q[]);
void replace(char *temp,const char *text1,const char *text2);

int case_check(char c1,char c2,int flag);
int symbols(char temp);
int isliteral(char pattern[],int i);               //identity functions
int escape(char temp);
int limechar(char temp[],int pos);
int ismeta(char temp,char temp1);

int check_par(char pattern[]);
int check_symbols(char pattern[]);                //checks validity of an expression
int check_in(char pattern[]);

int square(char temp,char pattern[],int *pat,int star_flag);
int literal(char temp[],char pattern[],int *pos,int *pat);
int plus(char temp[],char pattern[],int *pat,int *pos);   
int curly(char temp[],char pattern[],int *pat,int *pos);               //Functions for metacharacter
int star(char temp[],char pattern[],int *pat,int *pos);
int question(char temp[],char pattern[],int *pat,int *pos);
int grouping(char temp[],char pattern[],int *pat,int *pos);
int trim(char string[]);                                
int regex(char temp[],char pattern[],int *order);

int parent_pos(char pattern[],int pos);
void mprintf(char temp[],int in,int fi);
int get_string(char temp[],char new[],int pos1,int pos2);             //Auxillary functions     
int encounter(char pattern[],int pos);
int place(int in,int fi,char newp[],char pattern[],char new[]);

