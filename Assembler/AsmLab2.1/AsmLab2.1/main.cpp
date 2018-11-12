#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <conio.h>

extern "C"  void __stdcall FUNC(char *A, char S, int n);

int main()
{
	char str[100];
	char sym;
	int n;
	printf_s("Enter string: ");
	gets_s(str);
	printf_s("Enter symbol: ");
	scanf("%c", &sym);
	n = strlen(str);
	FUNC(str, sym, n);
	printf_s("%s", str);
	
	_getch();

	return 0;
}

