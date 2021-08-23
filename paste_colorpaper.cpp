#define _CRT_SECURE_NO_WARNINGS
#define MAX_BOARD_LEN 10
#include <stdio.h>

int board[MAX_BOARD_LEN][MAX_BOARD_LEN];
int label[MAX_BOARD_LEN][MAX_BOARD_LEN];
int paper[6] = { 0, 5, 5, 5, 5, 5 };
int paper_cnt = 0;
int min = 100;

/* 붙이기 */
void Attach(int size, int r, int c) {
	paper[size]--;
	paper_cnt++;
	for (int i = r; i < r + size; i++) {
		for (int j = c; j < c + size; j++) {
			board[i][j] = 0;
		}
	}

}

/* 떼기 */
void Detach(int size, int r, int c) {
	paper[size]++;
	paper_cnt--;
	for (int i = r; i < r + size; i++) {
		for (int j = c; j < c + size; j++) {
			board[i][j] = 1;
		}
	}

}

/* 붙일 수 있는지 확인 */
int Check(int size, int r, int c) {
	if (r + size <= MAX_BOARD_LEN && c + size <= MAX_BOARD_LEN && paper[size] != 0) {
		for (int i = r; i < r + size; i++) {
			for (int j = c; j < c + size; j++) {
				if (board[i][j] == 0)
					return 0;
			}
		}
		return 1;
	}
	return 0;
}

/* 최소 색종이 수 구하기 */
void GetMinPaper(int r, int c) {
	
	/* 종료 조건 */
	if (r == 9 && c == 10) {
		min = min < paper_cnt ? min : paper_cnt;
		return;
	}

	if (c == 10) {
		GetMinPaper(r + 1, 0);
		return;
	}
	

	/* 1 발견 */
	if (board[r][c] == 1) {
		
		/* 붙일 수 있으면 붙이고 다음 칸으로 */
		for (int size = 5; size >= 1; size--) {
			if (Check(size, r, c)) {
				Attach(size, r, c);
				GetMinPaper(r, c + 1);
				Detach(size, r, c);
			}
		}
	}
	/* 1 미발견 */
	else
		GetMinPaper(r, c + 1);

}

int main() {

	for (int i = 0; i < MAX_BOARD_LEN; i++) {
		for (int j = 0; j < MAX_BOARD_LEN; j++) {
			scanf("%d", &board[i][j]);
		}
	}

	GetMinPaper(0, 0);
	if (min == 100)
		printf("-1\n");
	else
		printf("%d\n", min);
	return 0;
}