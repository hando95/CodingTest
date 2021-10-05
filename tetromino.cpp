#define _CRT_SECURE_NO_WARNINGS
#define MAX_BOARD_LEN 500
#include <stdio.h>

/* DFS로 ㅗ, ㅏ, ㅜ, ㅓ 제외한 모든 테트로미노 검사 가능 */

int board[MAX_BOARD_LEN][MAX_BOARD_LEN];
int visited[MAX_BOARD_LEN][MAX_BOARD_LEN];
int dr[4] = { -1, 0, 1, 0 };
int dc[4] = { 0, 1, 0, -1 };
int ans = 0;

int GetMax(int a, int b) {
	return a < b ? b : a;
}

void TetrominoPlayOne(int r, int c, int sum, int cnt, int n, int m) {
	int next_r, next_c;

	if (cnt == 4) {
		ans = GetMax(ans, sum);
		return;
	}

	for (int i = 0; i < 4; i++) {
		next_r = r + dr[i];
		next_c = c + dc[i];

		if (next_r >= 0 && next_c >= 0 && next_r < n && next_c < m) {
			if (!visited[next_r][next_c]) {
				visited[next_r][next_c] = 1;
				TetrominoPlayOne(next_r, next_c, sum + board[next_r][next_c], cnt + 1, n, m);
				visited[next_r][next_c] = 0;
			}
		}
	}
	return;
}

void TetrominoPlayTwo(int r, int c, int n, int m) {
	int sum = 0;

	// ㅜ
	if (r <= n - 2 && c <= m - 3) {
		sum = board[r][c] + board[r][c + 1] + board[r][c + 2] + board[r + 1][c + 1];
		ans = GetMax(ans, sum);
	}

	// ㅏ
	if (r <= n - 3 && c <= m - 2) {
		sum = board[r][c] + board[r + 1][c] + board[r + 2][c] + board[r + 1][c + 1];
		ans = GetMax(ans, sum);
	}

	// ㅗ
	if (r >= 1 && c <= m - 3) {
		sum = board[r][c] + board[r][c + 1] + board[r][c + 2] + board[r - 1][c + 1];
		ans = GetMax(ans, sum);
	}

	// ㅓ
	if (r <= n - 3 && c >= 1) {
		sum = board[r][c] + board[r + 1][c] + board[r + 2][c] + board[r + 1][c - 1];
		ans = GetMax(ans, sum);
	}
}


int main() {
	int n, m;

	/* 입력 */
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &board[i][j]);
		}
	}

	/* 검사 */
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			TetrominoPlayOne(i, j, 0, 0, n, m);
			TetrominoPlayTwo(i, j, n, m);
		}
	}

	/* 출력*/
	printf("%d\n", ans);
	return 0;
}