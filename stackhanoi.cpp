#include <cstdio>
#include <cstdlib>

struct Node {
	struct Node *nxt; // next disk
	int num; // disk number
	char pia; // 
	char pib;
	char pic;
	Node() {
		nxt = NULL;
		num = 0;
	}
	void set(struct Node *tmpnxt, int tmpnum, char tmpa, char tmpb, char tmpc) {
		nxt = tmpnxt;
		num = tmpnum; pia = tmpa; pib = tmpb; pic = tmpc;
	}
};

struct Hni {
	struct Node *stk; // stack
	int num;

	Hni() { stk = NULL; }
	void push(struct Node *ptr) {
		ptr->nxt = stk;
		stk = ptr;
	}
	void pop() {
		if (stk != NULL) stk = stk->nxt;
	}
	void hni(int tmpn) {
		struct Node *tmpnode;
		struct Node *current;
		tmpnode = (struct Node *)malloc(sizeof(struct Node));
		tmpnode->set(NULL, tmpn, 'a', 'b', 'c');
		push(tmpnode);
		while (stk != NULL) {
			current = stk; pop();
			if (current->num > 1) {
				tmpnode = (struct Node *)malloc(sizeof(struct Node));
				tmpnode->set(NULL, current->num - 1, current->pib, current->pia, current->pic);
				push(tmpnode);
				tmpnode = (struct Node *)malloc(sizeof(struct Node));
				tmpnode->set(NULL, 1, current->pia, current->pib, current->pic);
				push(tmpnode);
				tmpnode = (struct Node *)malloc(sizeof(struct Node));
				tmpnode->set(NULL, current->num - 1, current->pia, current->pic, current->pib);
				push(tmpnode);
			}
			else printf("%c>%c ", current->pia, current->pic), free(current);
		}
	}
};

int main(void) {
	struct Hni hni;
	int n;
	while (~scanf("%d", &n)) hni.hni(n), printf("\n");
}
