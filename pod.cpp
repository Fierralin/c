#include <cstdio>
#include <cstdlib>
#include <list>

typedef struct Pod {

} Pod;

typedef struct PodList {
	int podsize;
	int podremain;
	
	bool *chainrecord;
	int size_chainrc;
} PodList;

typedef struct Chain {

} Chain;

typedef struct ChainList {
	std::list<Chain> chainlist;
	
} ChainList;


int main(void) {

}
