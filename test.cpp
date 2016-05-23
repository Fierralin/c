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

typedef struct Nod1 {
    unsigned char tmpa;
    unsigned char tmpb;
    unsigned char tmpc;
    unsigned char tmpd;
} Nod1;

typedef struct Nod2 {
    int tmpa;
    int tmpb;
} Nod2;

inline int operatecase(char *operate) { /* ���T�Á� switch �ٿv���� */
	int tmpi = 0; int tmpj = 0;
	while (operate[tmpi] != '\0') {
		tmpj = tmpj * 100 + operate[tmpi] - '@';
		tmpi++;
	}
	return tmpj;
}

#define MAXFILEBUFF 100

typedef struct FileOpenBuff {
	char buff[MAXFILEBUFF];
	int indx;
	FILE *fileopen;
	int openfile(char *filename);
	char getc(); /* �����Ы@ȡһ���ַ� */
} FileOpenBuff;

typedef struct FileSaveBuff {
	char buff[MAXFILEBUFF + 1];
	int indx;
	FILE *fileopen;
	int openfile(char *filename);
	void putc(char chr); /* ������ݔ��һ���ַ� */
	int finally();
} FileSaveBuff;

int FileOpenBuff::openfile(char *filename)  { /* ʧ��������0 */
	fileopen = fopen(filename, "r");
	if (fileopen) {
		fread(buff, MAXFILEBUFF, 1, fileopen);
		indx = 0; return 1;
	}
	else return 0;
}

char FileOpenBuff::getc() { /* ע���@�e����EOF�����ǿհ׷���fread������һ��'\0' */
	if (indx < MAXFILEBUFF && buff[indx] != '\0') return buff[indx++];
	else if (buff[indx] == '\0') {
		fclose(fileopen);
		return EOF;
	}
	else if (indx == MAXFILEBUFF) {
		fread(buff, MAXFILEBUFF, 1, fileopen);
		indx = 0;
		return this->getc();
	}
}

int FileSaveBuff::openfile(char *filename) { /* ʧ��������0 */
	fileopen = fopen(filename, "w");
	if (fileopen) {
		indx = 0; return 1;
	}
	else return 0;
}

void FileSaveBuff::putc(char chr) {
	if (indx < MAXFILEBUFF) buff[indx++] = chr;
	else {
		fwrite(buff, MAXFILEBUFF, 1, fileopen);
		indx = 0;
	}
}

int FileSaveBuff::finally() {
	if (indx > 0) fwrite(buff, indx, 1, fileopen); /* finished writing */
	fclose(fileopen);
	return 1;
}

int main(void) {
    printf("%d %d", sizeof(char), sizeof(int));

}
