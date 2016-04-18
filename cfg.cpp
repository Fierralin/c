#include <cstdio>
#include <cstring>

char dp[26][128][128];
char rules[26][128];
char buf[128];
int n_rule, n_len;

bool is_small(char ch) {
	return ch >= 'a' && ch <= 'z';
}

char solve(int now, int from, int to) {
	char tmp = dp[now][from][to];
	char *pr = rules[now];
	if(tmp != '0')
		return tmp;
	if(from == to) {
		for(int i = 0; pr[i] != 0; i++) {
			if(pr[i] == buf[from]) {
			tmp = '1';
			break;
			}
		}
	}
	else {
		for(int i = 0; pr[i] != 0; i++) {
			if(is_small(pr[i])) {
			i++;
			}
			else {
				int a = pr[i] - 'A';
				int b = pr[i + 1] - 'A';
				for(int j = from; j < to; j++) {
					if(solve(a, from, j) == '1' && solve(b, j + 1, to) == '1') {
						tmp = '1';
						break;
					}
				}
				if(tmp != '0') break;
				i += 2;
			}
		}
	}
	if(tmp == '0')
		tmp = '2';
	return dp[now][from][to] = tmp;
}

int main() {
	while(scanf("%s", buf) == 1 && buf[0] != '#')
		strcpy(rules[buf[0] - 'A'], buf + 3);
	while(scanf("%s", buf) != EOF) {
		n_len = strlen(buf);
		memset(dp, '0', sizeof(dp));
		if(solve('S' - 'A', 0, n_len - 1) == '1')
			puts("YES");
		else
			puts("NO");
	}
	return 0;
}
