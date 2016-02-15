#include <stdio.h>
#include<string.h>
#include<stdlib.h>

struct stack{
int top;
int capacity;
int *data;
};
struct stack* create(int capacity)
{
    struct stack* s = (struct stack*) malloc(sizeof(struct stack));
 
    if (!s) 
        return NULL;
 
    s->top = -1;
    s->capacity = capacity;
 
    s->data = (int*) malloc(s->capacity * sizeof(int));
 
    if (!s->data)
        return NULL;
    return s;
}
int isEmpty(struct stack* s)
{
    return s->top == -1 ;
}
char top(struct stack* s)
{
    return s->data[s->top];
}
char pop(struct stack* s)
{
    if (!isEmpty(s))
        return s->data[s->top--] ;
    return '#';
  }
void push(struct stack* s, char op)
{
    s->data[++s->top] = op;
}

int isOperand(char ch)
{
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
    return 1;
    return 0;
}

int Prec(char op){
switch(op){
case '+':
case '-':
return 1;
case '*':
case '/':
return 2;
}
return -1;
}

int pop1(struct stack* stack)
{
if(!isEmpty(stack))
return stack->data[stack->top--];
return -1;
}

void push1(struct stack* stack, int op)
{
stack->data[++stack->top] = op;
}
int main() {
 //printf("a\n");
char *in=(char *) malloc(sizeof(char)*100);
scanf("%s",in);
 //printf("a\n");
struct stack* s=create(strlen(in));
if(!s) return -1;
int i,j,len;
 //printf("a\n");
for(i = 0, j = -1; in[i]; i++)
    {
        if (isOperand(in[i]))
            in[++j] = in[i];
         
        else if (in[i] == '(')
            push(s,in[i]);
        
        else if (in[i] == ')')
        {
            while (!isEmpty(s) && top(s) != '(')
                in[++j] = pop(s);
            if (!isEmpty(s) && top(s) != '(')
                return -1;                
            else
                pop(s);
        }
        else 
        {
            while (!isEmpty(s) && Prec(in[i]) <= Prec(top(s)))
                in[++j] = pop(s);
            push(s, in[i]);
        }
 
    }

    while (!isEmpty(s))
        in[++j] = pop(s);
 
    in[++j] = '\0';
    printf("%s\n",in);
    
    while(!isEmpty(s)){
    pop(s);
    }
    
    len = strlen(in);
   int k=1;
    for(i = 0; i<len; i++)
    {
    
       if (isOperand(in[i])){
       
            push1(s,(int) in[i]);
       }
 
       else
        {
       
       
        char val2 = pop1(s);
            char val1 = pop1(s);
            
           
            switch (in[i])
            {
             case '+':
             	if((val1 >= 65 && val1 <=90) || (val1>=97 && val1<=122))
printf("LD %c\n",val1);
else
printf("LD TEMP%d\n",val1);    
if((val2 >= 65 && val2 <=90) || (val2>=97 && val2<=122))
printf("AD %c\n",val2);
else
printf("AD TEMP%d\n",val2);
printf("ST TEMP%d\n",k);
push1(s,k);k++;
break;
case '-': 
if((val1 >= 97 && val1 <=122) || (val1>=65 && val1<=90))
printf("LD %c\n",val1);
else
printf("LD TEMP%d\n",val1);    
if((val2 >= 97 && val2 <=122) || (val2>=65 && val2<=90))
printf("SB %c\n",val2);
else
printf("SB TEMP%d\n",val2);
printf("ST TEMP%d\n",k);
push1(s,k);
k++;
break;
             case '*':
if((val1 >= 97 && val1 <=122) || (val1>=65 && val1<=90))
printf("LD %c\n",val1);
else
printf("LD TEMP%d\n",val1);    
if((val2 >= 97 && val2 <=122) || (val2>=65 && val2<=90))
printf("ML %c\n",val2);
else
printf("ML TEMP%d\n",val2);
printf("ST TEMP%d\n",k);
push1(s,k);
k++;
break;
            case '/': 
if((val1 >= 97 && val1 <=122) || (val1>=65 && val1<=90))
printf("LD %c\n",val1);
else
printf("LD TEMP%d\n",val1);    
if((val2 >= 97 && val2 <=122) || (val2>=65 && val2<=90))
printf("DV %c\n",val2);
else
printf("DV TEMP%d\n",val2);
printf("ST TEMP%d\n",k);
push1(s,k);
k++;
break;
            }
        }
        
    }
return 0;
}
