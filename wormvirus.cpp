#define _CRT_SECURE_NO_WARNINGS
#define MAX_HOST_NUM 101
#include <stdio.h>

int networks[MAX_HOST_NUM][MAX_HOST_NUM];
int visited[MAX_HOST_NUM];
int cnt = 0;

/* 감염된 컴퓨터 수 세기 */
void CountInfected(int com, int v) {
	visited[com] = 1;

	for (int i = 1; i <= v; i++) {
		if (networks[com][i] == 1 && !visited[i]) {
			cnt++;
			CountInfected(i, v);
		}
	}
}

int main() {
	int v, e;
	int com1, com2;

	scanf("%d", &v);
	scanf("%d", &e);

	for (int i = 0; i < e; i++) {
		scanf("%d %d", &com1, &com2);
		networks[com1][com2] = 1;
		networks[com2][com1] = 1;
	}

	CountInfected(1, v);
	printf("%d\n", cnt);
	return 0;
}