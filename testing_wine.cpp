#define _CRT_SECURE_NO_WARNINGS
#define MAX_GLASSES 10000
#include <stdio.h>

int wine_sum[MAX_GLASSES];
int wine[MAX_GLASSES];

int GetMax(int a, int b) {
	return a < b ? b : a;
}

int GetTheMax(int a, int b, int c) {
	return GetMax(GetMax(a, b), c);
}

int SelectMaxWineSum(int n) {

	/* 처음 3잔 계산 */
	wine_sum[0] = wine[0];
	wine_sum[1] = wine[0] + wine[1];
	wine_sum[2] = GetTheMax(wine[0] + wine[2], wine[0] + wine[1], wine[1] + wine[2]);

	/* 현재 잔을 마실 때, 안 마실 때로 나누어 모든 경우 고려 */
	for (int i = 3; i < n; i++) {
		/* 마시는 경우 case 2개와 안 마시는 경우 case 1개, 총 3 경우 비교 */
		wine_sum[i] = GetTheMax(wine_sum[i - 3] + wine[i - 1] + wine[i], wine_sum[i - 2] + wine[i], wine_sum[i - 1]);
	}

	return wine_sum[n - 1];
}

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &wine[i]);
	}

	printf("%d\n", SelectMaxWineSum(n));
	return 0;
}