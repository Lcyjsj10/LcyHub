#include<stdio.h>
#include<time.h>
#include<stdlib.h>
int main()
{
    srand((unsigned)time(0));
    for (int i = 0; i < 100; i++)
    {
         double r=(float)rand()/RAND_MAX;
        printf("%f\n",r);
    }
}