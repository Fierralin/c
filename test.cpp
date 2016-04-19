#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <ctime>
#include <fstream>
#include <cmath>
#include <cstring>
#include <vector>
using std::ifstream;
using std::ofstream;
using std::cin;
using std::vector;

struct Node {
    int ta;
    int tb;
    double tc;
};

int main() {
    vector<int> vct;
    //vct.reserve(10);
    printf("\ncapacity: %d\n", vct.capacity());
    for (int tmpi = 0; tmpi < 10; tmpi++) {
        vct.push_back(tmpi * tmpi + tmpi);
        printf("\ncapacity: %d\n", vct.capacity());
    }
    vct.clear();
    vct.resize(10);
    printf("\ncapacity: %d\n", vct.capacity());
}

