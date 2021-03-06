#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
clock_t start, stop;
double duration;
int generateRandomNumber(int a) {
	return (rand() % a);
}
int calculate(int x[], int y[]) {
	int sum = 0;
	for (int i = 0; i < 4; i++) if (y[i] > 0 && y[i] < 5)sum++;
	for (int i = 0; i < sum; i++) {
		printf("%d", x[i]);
		if (y[i] == 1)printf("+");
		else if (y[i] == 2)printf("-");
		else if (y[i] == 3)printf("*");
		else if (y[i] == 4)printf("/");
	}
	printf("%d=", x[sum]);
	for (int i = 0; i <sum; i++) {
		if (y[i] == 3) {
			x[i + 1] = x[i] * x[i + 1];
			x[i] = 0;
			if (i == 0 || y[i - 1] != 2)y[i] = 1;
			else y[i] = 2;
		}
		else if (y[i] == 4) {
			x[i + 1] = x[i] / x[i + 1];
			x[i] = 0;
			if (i == 0 || y[i - 1] != 2)y[i] = 1;
			else y[i] = 2;
		}
	}
	for (int i = 0; i < sum; i++) {
		if (y[i] == 1) x[i + 1] = x[i] + x[i + 1];
		else if (y[i] == 2)x[i + 1] = x[i] - x[i + 1];
	}
	return x[sum];
}
int Number(char x[]) {
	int number = 0;
	if (x[0] == '-') {
		for (int i = 1; x[i] != '\0'; i++) number = number * 10 + (int)x[i] - 48;
		number = -number;
	}
	else for (int i = 0; x[i] != '\0'; i++) number = number * 10 + (int)x[i] - 48;
	return number;
}
void printRightAnswer(int x[], int y[], int m) {
	int sum = 0;
	for (int i = 0; i < 4; i++) if (y[i] > 0 && y[i] < 5)sum++;
	for (int i = 0; i < sum; i++) {
		printf("%d", x[i]);
		if (y[i] == 1)printf("+");
		else if (y[i] == 2)printf("-");
		else if (y[i] == 3)printf("*");
		else if (y[i] == 4)printf("/");
	}
	printf("%d=%d\n", x[sum],m);
}
int main() {
	start = clock();
	srand((unsigned)time(NULL));
	int a[10], b[10][4], c[10][5], x[10][4], y[10][5], m[10], n[10],  k = 1;
	char d[10];
	while (k != 2) {
		for (int i = 0; i < 10; i++)n[i] = m[i] = 0;
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 5; j++)c[i][j] = y[i][j] = 0;
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 4; j++)b[i][j] = x[i][j] = 0;
		int correct = 0 , h = 0 ;
		for (int i = 0; i < 10; i++) a[i] = generateRandomNumber(3) + 3;
		for (int i = 0; i < 10; i++) {
			if (a[i] == 3) {
				for (int j = 0; j < 2; j++) x[i][j] = b[i][j] = generateRandomNumber(4) + 1;
				for (int j = 0; j < 3; j++) y[i][j] = c[i][j] = generateRandomNumber(100);
			}
			else if (a[i] == 4) {
				for (int j = 0; j < 3; j++) x[i][j] = b[i][j] = generateRandomNumber(4) + 1;
				for (int j = 0; j < 4; j++) y[i][j] = c[i][j] = generateRandomNumber(100);
			}
			else if (a[i] == 5) {
				for (int j = 0; j < 4; j++) x[i][j] = b[i][j] = generateRandomNumber(4) + 1;
				for (int j = 0; j < 5; j++) y[i][j] = c[i][j] = generateRandomNumber(100);
			}
			m[i] = calculate(c[i], b[i]);
			gets_s(d, 10);
			if (d[0] != '\0') {
				if (Number(d) == m[i])correct++;
				else {
					n[h] = i;
					h++;
				}
			}
			else {
				n[h] = i;
				h++;
			}
		}
		printf("The number of correct answer: %d\n", correct);
		if (correct != 10) {
			printf("The following is the right answers of the questions you got wrong:\n");
			if (n[0] != 0) for (int i = 0; n[i] != 0; i++)printRightAnswer(y[n[i]], x[n[i]], m[n[i]]);
			else {
				printRightAnswer(y[n[0]], x[n[0]], m[n[0]]);
				for (int i = 1; n[i] != 0; i++)printRightAnswer(y[n[i]], x[n[i]], m[n[i]]);
			}
		}
		printf("Whether to proceed to the next round of testing? Please input:\n1.proceed\n2.exit");
		scanf_s("%d", &k);
		getchar();
	}
	stop = clock();
	duration = (double)(stop - start) / 1000;
	printf("The answer time is ��%lf��\n", duration);
	scanf_s("%d", &m);
}