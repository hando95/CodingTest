#define _CRT_SECURE_NO_WARNINGS
#define MAX_BOARD_SIZE 20
#define MAX_PLAY_CNT 1024
#include <stdio.h>

int board[MAX_BOARD_SIZE][MAX_BOARD_SIZE][6];
int ans = -1;

int GetMax(int a, int b) {
	if (a == -1)
		return b;
	return a < b ? b : a;
}

int IsSame(int a, int b) {
	return a == b;
}

/* 왼쪽으로 보드 움직이기 */
void MoveBoardLeft(int play_cnt, int n) {
	int idx, num1, num2;

	for (int i = 0; i < n; i++) {
		num1 = 0, num2 = 0, idx = 0;
		for (int j = 0; j < n; j++) {

			/* 비교인자1 발견 */
			if (board[i][j][play_cnt] != 0 && num1 == 0)
				num1 = board[i][j][play_cnt];

			/* 비교인자2 발견 */
			else if (board[i][j][play_cnt] != 0 && num2 == 0) {
				num2 = board[i][j][play_cnt];

				/* 같으면 합치고 이동 */
				if (IsSame(num1, num2)) {
					board[i][idx++][play_cnt + 1] = (num1 + num2);
					num1 = 0;
					num2 = 0;
				}

				/* 다르면 처음 숫자만 이동 */
				else {
					board[i][idx++][play_cnt + 1] = num1;
					num1 = num2;
					num2 = 0;
				}
			}
		}
		if (num1 != 0) {
			board[i][idx][play_cnt + 1] = num1;
		}
	}
}

/* 오른쪽으로 보드 움직이기 */
void MoveBoardRight(int play_cnt, int n) {
	int idx, num1, num2;

	for (int i = n - 1; i >= 0; i--) {
		num1 = 0, num2 = 0, idx = n - 1;
		for (int j = n - 1; j >= 0; j--) {

			/* 비교인자1 발견 */
			if (board[i][j][play_cnt] != 0 && num1 == 0)
				num1 = board[i][j][play_cnt];

			/* 비교인자2 발견 */
			else if (board[i][j][play_cnt] != 0 && num2 == 0) {
				num2 = board[i][j][play_cnt];

				/* 같으면 합치고 이동 */
				if (IsSame(num1, num2)) {
					board[i][idx--][play_cnt + 1] = (num1 + num2);
					num1 = 0;
					num2 = 0;
				}

				/* 다르면 처음 숫자만 이동 */
				else {
					board[i][idx--][play_cnt + 1] = num1;
					num1 = num2;
					num2 = 0;
				}
			}
		}
		if (num1 != 0) {
			board[i][idx][play_cnt + 1] = num1;
		}
	}
}

/* 위쪽으로 보드 움직이기 */
void MoveBoardUp(int play_cnt, int n) {
	int idx, num1, num2;

	for (int j = 0; j < n; j++) {
		num1 = 0, num2 = 0, idx = 0;
		for (int i = 0; i < n; i++) {

			/* 비교인자1 발견 */
			if (board[i][j][play_cnt] != 0 && num1 == 0)
				num1 = board[i][j][play_cnt];

			/* 비교인자2 발견 */
			else if (board[i][j][play_cnt] != 0 && num2 == 0) {
				num2 = board[i][j][play_cnt];

				/* 같으면 합치고 이동 */
				if (IsSame(num1, num2)) {
					board[idx++][j][play_cnt + 1] = (num1 + num2);
					num1 = 0;
					num2 = 0;
				}

				/* 다르면 처음 숫자만 이동 */
				else {
					board[idx++][j][play_cnt + 1] = num1;
					num1 = num2;
					num2 = 0;
				}
			}
		}
		if (num1 != 0) {
			board[idx][j][play_cnt + 1] = num1;
		}
	}
}

/* 아래쪽으로 보드 움직이기 */
void MoveBoardDown(int play_cnt, int n) {
	int idx, num1, num2;

	for (int j = n - 1; j >= 0; j--) {
		num1 = 0, num2 = 0, idx = n - 1;
		for (int i = n - 1; i >= 0; i--) {

			/* 비교인자1 발견 */
			if (board[i][j][play_cnt] != 0 && num1 == 0)
				num1 = board[i][j][play_cnt];

			/* 비교인자2 발견 */
			else if (board[i][j][play_cnt] != 0 && num2 == 0) {
				num2 = board[i][j][play_cnt];

				/* 같으면 합치고 이동 */
				if (IsSame(num1, num2)) {
					board[idx--][j][play_cnt + 1] = (num1 + num2);
					num1 = 0;
					num2 = 0;
				}

				/* 다르면 처음 숫자만 이동 */
				else {
					board[idx--][j][play_cnt + 1] = num1;
					num1 = num2;
					num2 = 0;
				}
			}
		}
		if (num1 != 0) {
			board[idx--][j][play_cnt + 1] = num1;
		}
	}
}

/* 가장 큰 블록 저장 */
void CheckMaxBlock(int play_cnt, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			ans = GetMax(ans, board[i][j][play_cnt]);
		}
	}
}

/* 다음을 위한 보드 지우기 */
void ClearBoard(int play_cnt, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			board[i][j][play_cnt] = 0;
		}
	}
}

/* 2048게임 함수 */
void LetsPlay(int play_cnt, int n) {

	/* 5번 이동 완료 */
	if (play_cnt == 5) {
		CheckMaxBlock(play_cnt, n);
		return;
	}

	/* 상, 하, 좌, 우 이동 */
	for (int i = 0; i < 4; i++) {
		switch (i) {
		case 0: 
			MoveBoardUp(play_cnt, n);
			LetsPlay(play_cnt + 1, n);
			ClearBoard(play_cnt + 1, n);
			break;
		case 1:
			MoveBoardDown(play_cnt, n);
			LetsPlay(play_cnt + 1, n);
			ClearBoard(play_cnt + 1, n);
			break;
		case 2:
			MoveBoardLeft(play_cnt, n);
			LetsPlay(play_cnt + 1, n);
			ClearBoard(play_cnt + 1, n);
			break;
		case 3:
			MoveBoardRight(play_cnt, n);
			LetsPlay(play_cnt + 1, n);
			ClearBoard(play_cnt + 1, n);
			break;
		}
	}
	return;
}

int main() {
	int n;
	
	/* 보드 초기상태 입력 */
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &board[i][j][0]);
		}
	}

	LetsPlay(0, n);
	printf("%d\n", ans);
	
	return 0;

}