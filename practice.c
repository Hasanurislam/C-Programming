#include<stdio.h>
int sum(int,int);
int main(void)
{
   int total;
   total=sum(5,7);
   printf("the total is:%d",total);
   return 0;

}
int sum(int a,int b);
{
   int s;
   s=a+b;
   return s;
}