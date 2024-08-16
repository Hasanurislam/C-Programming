#include<stdio.h>
#define DATA_SIZE 1000;
int main()
{
    char data[100];
    FILE *fptr;
    fptr=fopen("hh.txt","w");

    if(fptr==NULL)
    {
       printf("Error opening file");
       
    }

    printf("Enter to be store in the file:\n");
    fgets(data,100,stdin);

    fputs(data,fptr);
    fclose(fptr);
    printf("the file has been created succesfully");

    return 0;
}