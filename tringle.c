#include<stdio.h>
int main()
{
    float X,Y,Z, P,A;
    printf("\nInput the first number:");
    scanf("%f,&X");
    printf("\nInput the second number:");
    scanf("%f",&Y);
    printf("\nInput the third number:");
    scanf("%f",&Z);
    if(X<(Y+Z) &&Y<(X+Z) &&Z<(Y+Z))
    {
        P=X+Y+Z;
        printf("\nPerimeter =%.1f\n",P);
    }
    else
    {
        printf("Not Possibleto create a tringle..");
    }
   return 0;
}