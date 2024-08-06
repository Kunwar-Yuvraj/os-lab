#include<stdio.h>
#include<string.h>

void main()
{
    char fn[10],pat[10],temp[200];
    FILE *fp;

    printf("Enter file name: ");
    scanf("%s",fn);
    printf("Enter pattern to be searched: ");
    scanf("%s",pat);
    fp=fopen(fn,"r");

    while(!feof(fp))
    {   
        fgets(temp,100,fp);
        if(strstr(temp,pat))
            printf("%s",temp);
    }
    printf("\n");

    fclose(fp);
}