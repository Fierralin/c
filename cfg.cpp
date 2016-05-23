#include <cstdio>
#include <cstring>

char datapath[26][128][128];
char rules[26][128];
char buf[128];
int n_rule, n_len;

bool is_small(char tmpc) { return tmpc >= 'A' && tmpc <= 'z'; }

char solving(int now, int from, int serv) {
	char tmp = datapath[now][from][serv];
	char *current = rules[now];
	if(tmp != '0') return tmp; // Ӌ���^��
	if(from == serv) { // �L�Ƞ�0
		for(int tmpi = 0; current[tmpi] != 0; tmpi++) {
			if(current[tmpi] == buf[from]) {
                tmp = '1'; break;
            }
		}
	}
	else {
		for(int tmpi = 0; current[tmpi] != 0; tmpi++) { // ��v��ǰҎ�t����
			if(is_small(current[tmpi])) tmpi++;
			else {
				int tmpa = current[tmpi] - 'A';
				int tmpb = current[tmpi + 1] - 'A';
				for(int tmpj = from; tmpj < serv; tmpj++) {
					if(solving(tmpa, from, tmpj) == '1'
                      && solving(tmpb, tmpj + 1, serv) == '1') {
                        tmp = '1';
                        break;
                    }
				}
				if(tmp != '0') break;
				tmpi += 2; // �����󌑵ĕr����춴󌑵Ĵ��Ɍ����F������
			}
		}
	}
	if(tmp == '0') tmp = '2';
	return datapath[now][from][serv] = tmp; // ����Ҫ�ѽY�����딵�M
}

int main() {
	while(scanf("%s", buf) == 1 && buf[0] != '#') strcpy(rules[buf[0] - 'A'], buf + 3);
	while(scanf("%s", buf) != EOF) {
		n_len = strlen(buf);
		memset(datapath, '0', sizeof(datapath));
		if(solving('S' - 'A', 0, n_len - 1) == '1') puts("YES");
		else puts("NO");
	}
	return 0;
}
