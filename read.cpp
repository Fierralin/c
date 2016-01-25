#include <iostream>
#include <cstdio>

int main(void) {
	FILE *fil;
	fil  = fopen("colour", "r");
	int c;
	c = fgetc(fil);
	while (c != EOF) {
		printf("|%c|%d|-", c, c);
		c = fgetc(fil);
	}
}
