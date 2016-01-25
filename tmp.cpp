#include <iostream>
#include <cstdio>

struct Node {
	int tmi;
	int tmj;
	int init(int tma, int tmb);
};

int Node::init(int tma, int tmb) {
	tmi = tma; tmj = tmb;
}

int main(void) {
	struct Node tmn;
	tmn.init(3, 4);
	printf("%d, %d\n", tmn.tmi, tmn.tmj);
}

