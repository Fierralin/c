#include <stdio.h>

int main(void) {
 char buf[100];
 int tmp, tmpi;
 while (~scanf("%s", buf)) {
  tmp = 0; tmpi = 0;
  while (buf[tmpi] != '\0') {
   tmp = tmp * 100 + buf[tmpi] - '@';
   tmpi++;
  }
  printf("%s: %d\n", buf, tmp);
 }
}

