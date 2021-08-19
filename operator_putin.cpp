#define _CRT_SECURE_NO_WARNINGS
#define MAX_NUMBER_CNT 11
#include <stdio.h>

int num[MAX_NUMBER_CNT];      // 수열
int oper[4];                  // 연산자
int max = -1000000000, min = 1000000000;

int GetMax(int a, int b) {
	return a < b ? b : a;
}

int GetMin(int a, int b) {
	return a < b ? a : b;
}

void Calculate(int n, int result, int cnt) {
	/* 종료 조건 */
	if (cnt == n) {
		max = GetMax(max, result);
		min = GetMin(min, result);
		return;
	}

	/* 연산자 깊이 우선 탐색 */
	for (int i = 0; i < 4; i++) {
		if (oper[i]) {
			oper[i]--;
			switch (i) {
			case 0:
				Calculate(n, result + num[cnt], cnt + 1);
				break;
			case 1:
				Calculate(n, result - num[cnt], cnt + 1);
				break;
			case 2:
				Calculate(n, result * num[cnt], cnt + 1);
				break;
			case 3:
				Calculate(n, result / num[cnt], cnt + 1);
				break;
			}
			oper[i]++;
		}
	}
}

int main() {
	int n;                        // 수의 개수

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &num[i]);
	}
	scanf("%d %d %d %d", &oper[0], &oper[1], &oper[2], &oper[3]);

	Calculate(n, num[0], 1);
	printf("%d\n", max);
	printf("%d\n", min);
	return 0;
}