#include<iostream>
#include<stdio.h>
using namespace std;

int main()
{
	char ch;
	do
	{
		ch = getchar();
		cout << ch;
	}
	while(ch!=13);
	return 0;
}