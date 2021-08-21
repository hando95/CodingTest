#define _CRT_SECURE_NO_WARNINGS
#define MAX_BOARD_LEN 100
#define MAX_TIME 10000
#include <stdio.h>

int board[MAX_BOARD_LEN][MAX_BOARD_LEN];
int visited[MAX_BOARD_LEN][MAX_BOARD_LEN];
char turn[MAX_BOARD_LEN][MAX_BOARD_LEN];
char cmd[MAX_TIME];

typedef struct {
	int hx, hy;
	int tx, ty;
	int hdx, hdy;
	int tdx, tdy;
}Snaketype;

Snaketype snake;

void InitSnake(Snaketype* snake) {
	snake->hx = snake->hy = 0;
	snake->tx = snake->ty = 0;
	snake->hdy = 1;
	snake->hdx = 0;
	snake->tdy = 1;
	snake->tdx = 0;
	visited[0][0] = 1;
}

/* 머리 방향전환 */
void ChangeHeadDir(Snaketype* snake, char c) {
	/* 오른쪽 이동 중 */
	if (snake->hdy == 1 && snake->hdx == 0) {
		if (c == 'L') {           // 왼쪽
			snake->hdy = 0;
			snake->hdx = -1;
		}
		else if (c == 'D') {      // 오른쪽
			snake->hdy = 0;
			snake->hdx = 1;
		}
	}
	/* 아래쪽 이동 중 */
	else if (snake->hdy == 0 && snake->hdx == 1) {
		if (c == 'L') {           // 왼쪽
			snake->hdy = 1;
			snake->hdx = 0;
		}
		else if (c == 'D') {      // 오른쪽
			snake->hdy = -1;
			snake->hdx = 0;
		}
	}
	/* 왼쪽 이동 중 */
	else if (snake->hdy == -1 && snake->hdx == 0) {
		if (c == 'L') {           // 왼쪽
			snake->hdy = 0;
			snake->hdx = 1;
		}
		else if (c == 'D') {      // 오른쪽
			snake->hdy = 0;
			snake->hdx = -1;
		}
	}
	/* 위쪽 이동 중 */
	else if (snake->hdy == 0 && snake->hdx == -1) {
		if (c == 'L') {           // 왼쪽
			snake->hdy = -1;
			snake->hdx = 0;
		}
		else if (c == 'D') {      // 오른쪽
			snake->hdy = 1;
			snake->hdx = 0;
		}
	}
}

/* 꼬리 방향전환 */
void ChangeTailDir(Snaketype* snake, char c) {
	/* 오른쪽 이동 중 */
	if (snake->tdy == 1 && snake->tdx == 0) {
		if (c == 'L') {           // 왼쪽
			snake->tdy = 0;
			snake->tdx = -1;
		}
		else if (c == 'D') {      // 오른쪽
			snake->tdy = 0;
			snake->tdx = 1;
		}
	}
	/* 아래쪽 이동 중 */
	else if (snake->tdy == 0 && snake->tdx == 1) {
		if (c == 'L') {           // 왼쪽
			snake->tdy = 1;
			snake->tdx = 0;
		}
		else if (c == 'D') {      // 오른쪽
			snake->tdy = -1;
			snake->tdx = 0;
		}
	}
	/* 왼쪽 이동 중 */
	else if (snake->tdy == -1 && snake->tdx == 0) {
		if (c == 'L') {           // 왼쪽
			snake->tdy = 0;
			snake->tdx = 1;
		}
		else if (c == 'D') {      // 오른쪽
			snake->tdy = 0;
			snake->tdx = -1;
		}
	}
	/* 위쪽 이동 중 */
	else if (snake->tdy == 0 && snake->tdx == -1) {
		if (c == 'L') {           // 왼쪽
			snake->tdy = -1;
			snake->tdx = 0;
		}
		else if (c == 'D') {      // 오른쪽
			snake->tdy = 1;
			snake->tdx = 0;
		}
	}
}

int Move(int n) {
	int next_hx = 0, next_hy = 0;
	int next_tx = 0, next_ty = 0;
	int time = 0;

	InitSnake(&snake);

	/* 범위 내에서 */
	while (snake.hx >= 0 && snake.hy >= 0 && snake.hx <= n - 1 && snake.hy <= n - 1) {
		
		/* 머리 방향 전환 및 꼬리가 나중에 방향 전환할 수 있게 표시 */ 
		if (cmd[time] != 0) {
			ChangeHeadDir(&snake, cmd[time]);
			turn[snake.hx][snake.hy] = cmd[time];
		}

		/* 꼬리 방향 전환 및 표시 제거 */
		if (turn[snake.tx][snake.ty] != 0) {
			ChangeTailDir(&snake, turn[snake.tx][snake.ty]);
			turn[snake.tx][snake.ty] = 0;
		}
		
		/* 다음 칸 검사 */
		next_hx = snake.hx + snake.hdx;
		next_hy = snake.hy + snake.hdy;

		/* 자기 몸에 닿거나 보드 밖을 나가면 종료 */
		if (visited[next_hx][next_hy] || next_hx < 0 || next_hy < 0 || next_hx > n - 1 || next_hy > n - 1) {
			time++;
			break;
		}

		/* 사과가 없으면 꼬리가 위치한 칸 비우기 */
		if (board[next_hx][next_hy] == 0) {
			visited[next_hx][next_hy] = 1;
			visited[snake.tx][snake.ty] = 0;
			next_tx = snake.tx + snake.tdx;
			next_ty = snake.ty + snake.tdy;
		}

		/* 사과가 있으면 머리가 위치한 칸 방문 처리 및 사과 제거 */
		else if (board[next_hx][next_hy] == 1) {
			visited[next_hx][next_hy] = 1;
			board[next_hx][next_hy] = 0;
		}

		snake.hx = next_hx;
		snake.hy = next_hy;
		snake.tx = next_tx;
		snake.ty = next_ty;
		time++;
	}

	return time;
}



int main() {
	int n, k, l, x;
	int apple_x, apple_y;
	char c;

	scanf("%d", &n);
	scanf("%d", &k);
	for (int i = 0; i < k; i++) {
		scanf("%d %d", &apple_x, &apple_y);
		board[apple_x - 1][apple_y - 1] = 1;
	}
	scanf("%d", &l);
	for (int i = 0; i < l; i++) {
		scanf("%d %c", &x, &c);
		cmd[x] = c;
	}

	printf("%d\n", Move(n));
	return 0;
}