#include<stdio.h>
#include <stdlib.h>
#include<cstring>
#include<vector>
#include<bits/stdc++.h>
#define MAX_LINE 100
using namespace std;
int main()
{
	char buf[MAX_LINE];
	FILE* fp;
	int len;
	if ((fp=fopen("D:\\input.txt","r"))==NULL)
	{
		perror("fail to read!");
		exit(1);
	}
	while (fgets(buf,MAX_LINE,fp)!=NULL)
	{
		len = strlen(buf);
		/*buf[len - 1] = '\0';*/       //若不加这个buf[len-1]默认为换行符
		// printf("%s %d\n", buf, len - 1);
		printf("%s",buf);
		char buf1[MAX_LINE],buf2[MAX_LINE];
		// for (int i = 0; i < len; i++)
		// {
		// 	buf1[i]=buf[i];
		// 	if(buf[i]==" ")
		// 	{
		// 		break;
		// 	}
		// }
		//cout<<buf1<<endl;
		
		
	}
	
}