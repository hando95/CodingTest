#define _CRT_SECURE_NO_WARNINGS
#define MAX_BOARD_SIZE 51
#define MIN_BOARD_SIZE 8
#include <stdio.h>

char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
int cnt = 0;

void CheckBoard(int start_r, int start_c, int r, int c, char color) {

	/* 모두 검사 시 종료 */
	if (r == 7 && c == 8)
		return;
	
	/* 줄 바꿈*/
	if (c == 8) {
		r += 1;
		c = 0;
		CheckBoard(start_r, start_c, r, c, color);
		return;
	}

	/* 같은 색이어야 하는 칸 색이 다른 경우 */
	if ((r + c) % 2 == 0) {
		if (board[start_r + r][start_c + c] != color)
			cnt++;
	}
	/* 다른 색이어야 하는 칸 색이 같은 경우 */
	else {
		if (board[start_r + r][start_c + c] == color)
			cnt++;
	}

	CheckBoard(start_r, start_c, r, c + 1, color);
	return;
}

int GetMin(int a, int b) {
	return a < b ? a : b;
}


int main() {
	int n, m;
	int min = 64;

	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%s", board[i]);
	}


	for (int i = 0; i <= n - MIN_BOARD_SIZE; i++) {
		for (int j = 0; j <= m - MIN_BOARD_SIZE; j++) {
			
			/* 시작색을 검은색으로 할 경우 */
			CheckBoard(i, j, 0, 0, 'B');
			min = GetMin(min, cnt);
			cnt = 0;

			/* 시작색을 하얀색으로 할 경우 */
			CheckBoard(i, j, 0, 0, 'W');
			min = GetMin(min, cnt);
			cnt = 0;
		}
	}
	printf("%d\n", min);
	return 0;

}