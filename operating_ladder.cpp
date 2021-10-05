#define _CRT_SECURE_NO_WARNINGS
#define MAX_VERTICAL 12
#define MAX_HORIZONTAL 31
#include <stdio.h>

int ladder[MAX_VERTICAL][MAX_HORIZONTAL];
int ans = -1;

/* 결과 확인 함수 */
int Check(int n, int h) {
	int result = 1;
	
	/* 세로선 n개 검사 */
	for (int i = 1; i <= n; i++) {
		result = i;
		
		/* 사다리 타기 */
		for (int j = 1; j <= h; j++) {
			if (result >= 1 && result <= n) {
				if (ladder[result][j])
					result++;
				else if (ladder[result - 1][j])
					result--;
			}
		}

		/* 자기 번호와 같은 결과가 아닐 경우 */
		if (result != i)
			return 0;
	}

	/* 모두 자기 번호와 같은 결과일 경우 */
	return 1;
}

/* 사다리 놓기 */
void Operation(int cnt, int idx, int n, int h, int lad_cnt) {
	
	/* 원하는 개수의 사다리를 놓았으면 확인 */
	if (cnt == lad_cnt) {
		if (Check(n, h))
			ans = lad_cnt;
		return;
	}

	/* 사다리 놓기 */
	for (int i = 1; i <= n - 1; i++) {
		for (int j = idx; j <= h; j++) {

			/* 사다리를 놓을 수 있는 경우 */
			if (!ladder[i - 1][j] && !ladder[i][j] && !ladder[i + 1][j]) {
				ladder[i][j] = 1;
				Operation(cnt + 1, j, n, h, lad_cnt);
				ladder[i][j] = 0;
			}
		}
	}

	return;
}

int main() {
	int n, m, h;    // 세로선, 가로선, 놓을 수 있는 가로선 
	int a, b;

	/* 입력 */
	scanf("%d %d %d", &n, &m, &h);
	for (int i = 1; i <= m; i++) {
		scanf("%d %d", &a, &b);
		ladder[b][a] = 1;
	}

	/* 사다리 조작 */
	for (int i = 0; i <= 3; i++) {
		if (ans != -1)
			break;
		Operation(0, 1, n, h, i);
	}

	/* 출력 */
	printf("%d\n", ans);
	return 0;
}
