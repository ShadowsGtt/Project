/*************************************************************************
	> File Name: tmp.c
	> Author: 
	> Mail: 
	> Created Time: 2017年06月16日 星期五 03时14分50秒
 ************************************************************************/

#include<stdio.h>

#include <stdlib.h>

int main()
{
    int i = 0 ;
    int j = 0;
    int n = 9;
    int k = 0;
    int a[20] = {1,7,12,16,50,60,80,87,95,100};
    printf("\n未插入数字的有序数列:\n");
    for(i = 0 ; i < 10 ; i ++)
    {
        printf("%-4d",a[i]);
    }
    putchar(10);
    for(k = 0 ; k < 10; k++)
    {
        if(k == 10)
            break;
        int ran = rand()%100;
        printf("ran%d:%-4d",k+1,ran);
        
        if (ran >= a[n])
        {
            a[n+1] = ran;
            n++;
        }
        else{
        for(j = 1; j < 20; j++)
        {
           if(n == 20)
            break;
            if(ran <= a[0])
            {
                for( i = n;i >= 0;i-- )
                {
                    a[i+1] = a[i];
                }
                a[0] = ran;
                n++;
                break;
            }
            if(ran <= a[j] && ran >= a[j-1])
            {
                for(i =  n;i >= j;i-- )
                {
                    a[i+1] = a[i];
                }
                a[j] = ran;
                n++;
                break;
            }
        }

        }
    }
    putchar(10);
        printf("\n插入数字后的有序数列:\n");
    for( i = 0 ; i < 20 ; i ++)
    {
        printf("%-4d",a[i]);
    }
    return 0;
}
