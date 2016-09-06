#include <iostream>
#include <cstdio>

using namespace std;

int data[9999];
int indx;

void printf_data(int nstart, int nend) {
	printf("### ");
	for (int tmpi = nstart; tmpi <= nend; tmpi++) {
		printf("%d ", data[tmpi]);
	}
	printf("\n");
}

int main(int argc, char *argv[]) {
	cout << "Hello World!" << endl;

	FILE *fil = NULL;
	if (argc > 1) fil = fopen(argv[1], "r");

	indx = 0;
	if (fil != NULL) {
		while (!feof(fil)) {
			fscanf(fil, "%x", &data[indx++]);
		}
	}
	printf("length of data: %d \n", indx);

	printf("source addr: ");
	printf_data(0, 5); // source address
	printf("dest addr: ");
	printf_data(6, 11); // dest address

	printf("IP type: ");
	printf("%.2x %.2x", data[13], data[12]); // 13 12 ip type

	printf("source IP addr: ");
	printf_data(26, 29);
	printf("dest IP addr: ");
	printf_data(30, 33);

	printf("max length: ");
	printf_data(34, 35);

	printf("head jiaoyanma");
	printf_data(24, 25);

	printf("source port");
	printf_data(34, 35);

	printf("dest port");
	printf_data(36, 37);

	printf("window size: ");
	printf_data(48, 49);

	return 0;
}
