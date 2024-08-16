#include<stdio.h>
int main()
{
    FILE*fp;
    fp=fopen("file.txt","r");
    fprintf(fp,"%s","Welcome to file system");
    fclose(fp);

    return 0;
}