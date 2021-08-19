#define _CRT_SECURE_NO_WARNINGS
#define MAX_DAY 1500000
#include <stdio.h>

int time[MAX_DAY + 2];
int pay[MAX_DAY + 2];
long long total_pay[MAX_DAY + 2];

int GetMax(int a, int b) {
	return a < b ? b : a;
}

long long MaxPay(int n) {
	int deadline;
	/* 퇴사 전날부터 오늘까지 확인 */
	for (int i = n; i >= 1; i--) {
		deadline = i + time[i] - 1;

		/* 일할 수 있는 경우 */
		if (deadline <= n)
			/* 오늘 일을 안 할 때 vs 오늘 일을 할 때 */
			total_pay[i] = GetMax(total_pay[i + 1], pay[i] + total_pay[i + time[i]]);

		/* 일할 수 없는 경우 */
		else
			total_pay[i] = total_pay[i + 1];
	}
	return total_pay[1];
}


int main() {
	int n;

	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &time[i], &pay[i]);
	}

	printf("%lld\n", MaxPay(n));
	return 0;
}