#include"include/lib.h"
#include<stdio.h>
int main(int argc,char*argv[])
{
    int s2m = 1;
    int worktime = 9;
    if(argc > 1)
        sscanf(argv[1],"%d",&s2m);
    if(argc >2)
        sscanf(argv[2],"%d",&worktime);
    return clockin_machine_start(s2m,worktime);
}