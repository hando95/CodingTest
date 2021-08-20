#define _CRT_SECURE_NO_WARNINGS
#define MAX_ROOM_NUM 1000001
#define MAX_PEOPLE_NUM 1000001
#include <stdio.h>

int room[MAX_ROOM_NUM];
int sup_per_people[MAX_PEOPLE_NUM];


long long MemoSupNum(int people, int b, int c) {
	int remain;
	
	/* 이미 계산값이 있으면 리턴 */
	if (sup_per_people[people] != 0)
		return sup_per_people[people];

	/* 계산하기 */
	remain = people - b;

	/* 부감독관 불필요 */
	if (remain <= 0) {
		sup_per_people[people] = 1;
	}
	/* 부감독관 필요 */
	else {
		if (remain % c != 0)
			sup_per_people[people] = remain / c + 2;
		else
			sup_per_people[people] = remain / c + 1;
	}

	return sup_per_people[people];
}

int main() {
	int n;
	int b, c;
	long long sum = 0;

	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &room[i]);
	}
	scanf("%d %d", &b, &c);

	/* 총감독관 하나로 커버 가능한 시험장 계산 */
	for (int i = 1; i <= b; i++)
		sup_per_people[i] = 1;

	/* 감독관 수 계산 */
	for (int i = 1; i <= n; i++) {
		sum += MemoSupNum(room[i], b, c);
	}

	printf("%lld\n", sum);
	return 0;
}