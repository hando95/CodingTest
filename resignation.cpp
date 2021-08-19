#define _CRT_SECURE_NO_WARNINGS
#define MAX_DAY 15
#include <stdio.h>

int time[MAX_DAY + 1];
int pay[MAX_DAY + 1];
int worked[MAX_DAY + 1];
int max_pay = 0;


int GetMax(int a, int b) {
	return a < b ? b : a;
}

void MaxPay(int day, int n, int total_pay) {

	/* 퇴사 */
	if (day > n) {
		max_pay = GetMax(total_pay, max_pay);
		return;
	}
	
	/* day 날에 상담을 하는 경우 */
	if (day + time[day] - 1 <= n) {
		MaxPay(day + time[day], n, total_pay + pay[day]);
	}

	/* day 날에 상담을 하지 않는 경우 */
	if (day <= n) {
		MaxPay(day + 1, n, total_pay);
	}
	
}

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &time[i], &pay[i]);
	}

	MaxPay(1, n, 0);

	printf("%d\n", max_pay);
	return 0;
}