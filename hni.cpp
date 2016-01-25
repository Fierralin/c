#include <iostream>
#include <cstdio>

void hni(char a, char b, char c, int n) {
	if (n == 1) printf("%c>%c ", a, c);
	else {
		hni(a, c, b, n - 1);
		printf("%c>%c ", a, c);
		hni(b, a, c, n - 1);
	}
}

int main(void) {
	int n;
	while (~scanf("%d", &n)) hni('a', 'b', 'c', n), printf("\n");
}
