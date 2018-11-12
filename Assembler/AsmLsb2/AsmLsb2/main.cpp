#include <stdio.h>
#include <string.h>
#include <conio.h>


extern "C"  void __stdcall FUNC(char *A, char S, int n);

void main()
{
	char str[100];
	char sym;
	int n;
	printf_s("Enter string: ");
	gets_s(str);
	printf_s("Enter symbol: ");
	scanf("%c", &sym);
	n = strlen(str);
	if (n > 0 && sym != '\n')
	{
		FUNC(str, sym, n);
		printf_s("%s", str);
	}
	else
		printf_s("Error: invalid line");
	_getch();
}

