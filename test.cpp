#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <ctime>
#include <fstream>
#include <cmath>
#include <cstring>
#include <string.h>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
using std::ifstream;
using std::ofstream;
using std::cin;
using std::vector;
using std::list;

#define ENDING '\0'

typedef struct Pod {
    int aaa; char bbb;
    int init();
} Pod;

int Pod::init() {
    aaa = 0;
    bbb = '@';
}

int main(void) {
    Pod *tmpa[20];
    for (int tmpi = 0; tmpi < 20; tmpi++) tmpa[tmpi] = new Pod;
    for (int tmpi = 0; tmpi < 20; tmpi++) {
        printf("[%d, %d]\n", tmpi, tmpa[tmpi]);
        delete tmpa[tmpi];
    }
    memset(tmpa, 0, sizeof(Pod *) * 20);
    for (int tmpi = 0; tmpi < 20; tmpi++) {
            if (tmpa[tmpi] == NULL)
        printf("[%d, %d]\n", tmpi, tmpa[tmpi]);
    }
}
