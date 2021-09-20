#define _CRT_SECURE_NO_WARNINGS
#define MAX_QUEUE_SIZE 105000
#define MAX_BOARD_SIZE 10
#include <stdio.h>

typedef struct {
	int r, c;
}Postype;

typedef struct {
	Postype red_pos[MAX_QUEUE_SIZE];
	Postype blue_pos[MAX_QUEUE_SIZE];
	int count[MAX_QUEUE_SIZE];
	int rear, front;
}Queuetype;

Queuetype marbles;
char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
int fin = 0;
int ans = 0;

/* 현재 구슬 위치, 현재 기울인 횟수 */
Postype cur_red;
Postype cur_blue;
int cur_cnt;

/* 상, 우, 하, 좌 */
int dr[4] = { -1, 0, 1, 0 };
int dc[4] = { 0, 1, 0, -1 };

void InitQueue(Queuetype* q) {
	q->front = q->rear = 0;
}

int IsEmpty(Queuetype* q) {
	return q->front == q->rear;
}

int IsFull(Queuetype* q) {
	return (q->rear + 1) % MAX_QUEUE_SIZE == q->front;
}

void Enqueue(Queuetype* q, int red_r, int red_c, int blue_r, int blue_c, int cnt) {
	if (IsFull(q))
		return;
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->red_pos[q->rear].r = red_r;
	q->red_pos[q->rear].c = red_c;
	q->blue_pos[q->rear].r = blue_r;
	q->blue_pos[q->rear].c = blue_c;
	q->count[q->rear] = cnt;
}

void Dequeue(Queuetype* q) {
	if (IsEmpty(q))
		return;
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	cur_red.r = q->red_pos[q->front].r;
	cur_red.c = q->red_pos[q->front].c;
	cur_blue.r = q->blue_pos[q->front].r;
	cur_blue.c = q->blue_pos[q->front].c;
	cur_cnt = q->count[q->front];
}

/* 두 구슬이 같은 위치인지 확인하는 함수 */
int IsSame(Queuetype* q, int red_r, int red_c, int blue_r, int blue_c) {
	
	for (int i = 0; i <= q->rear; i++) {
		if (red_r == q->red_pos[i].r && red_c == q->red_pos[i].c) {
			if (blue_r == q->blue_pos[i].r && blue_c == q->blue_pos[i].c)
				return 1;
		}
	}
	return 0;
}

/* 구슬 이동 함수 */
void Move(int dir) {
	int red_nr = cur_red.r, red_nc = cur_red.c;
	int blue_nr = cur_blue.r, blue_nc = cur_blue.c;
	int red_steps = 0, blue_steps = 0;  // 같은 위치에 있을 때 비교하기 위한 변수
	int red_in = 0, blue_in = 0;

	/* 빨간 구슬 이동 */
	while (board[red_nr][red_nc] != '#') {
		red_nr += dr[dir];
		red_nc += dc[dir];
		red_steps++;

		/* 이동 중 구슬이 구멍에 빠진 경우 */
		if (board[red_nr][red_nc] == 'O') {
			red_in = 1;
			break;
		}
	}
	
	/* 파란 구슬 이동 */
	while (board[blue_nr][blue_nc] != '#') {
		blue_nr += dr[dir];
		blue_nc += dc[dir];
		blue_steps++;

		/* 이동 중 구슬이 구멍에 빠진 경우 */
		if (board[blue_nr][blue_nc] == 'O') {
			blue_in = 1;
			break;
		}
	}

	/* 파란 구슬이 구멍에 빠진 경우 제외 */
	if (blue_in)
		return;

	/* 빨간 구슬만 구멍에 빠진 경우 종료 */
	if (red_in) {
		fin = 1;
		cur_cnt++;
		return;
	}

	/* 모두 빠지지 않았을 때 구슬 위치 확인 */
	red_nr -= dr[dir];
	red_nc -= dc[dir];
	blue_nr -= dr[dir];
	blue_nc -= dc[dir];

	/* 빨간 구슬과 파란 구슬이 같은 위치인 경우 조정 */
	if (red_nr == blue_nr && red_nc == blue_nc) {
		if (red_steps < blue_steps) {
			blue_nr -= dr[dir];
			blue_nc -= dc[dir];
		}
		else {
			red_nr -= dr[dir];
			red_nc -= dc[dir];
		}
	}

	/* 이전 경우들과 비교해서 같은 위치면 제외, 새로운 위치면 큐에 넣기 */
	if (IsSame(&marbles, red_nr, red_nc, blue_nr, blue_nc))
		return;
	else
		Enqueue(&marbles, red_nr, red_nc, blue_nr, blue_nc, cur_cnt + 1);
}

/* 기울이는 함수 */
void LetsTilt(Queuetype* q, int red_sr, int red_sc, int blue_sr, int blue_sc) {

	/* 시작 위치 넣기 */
	InitQueue(q);
	Enqueue(q, red_sr, red_sc, blue_sr, blue_sc, 0);

	/* BFS */
	while (!IsEmpty(q)) {
		Dequeue(q);
		
		for (int dir = 0; dir < 4; dir++) {
			Move(dir);
			if (fin)
				return;
		}
	}
	return;
}

int main() {
	int n, m;
	Postype red_start, blue_start;
	
	/* 입력*/
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%s", board[i]);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (board[i][j] == 'R') {
				red_start.r = i;
				red_start.c = j;
			}
			if (board[i][j] == 'B') {
				blue_start.r = i;
				blue_start.c = j;
			}
		}
	}

	/* 기울이기 */
	LetsTilt(&marbles, red_start.r, red_start.c, blue_start.r, blue_start.c);

	/* 출력 */
	if (fin && cur_cnt <= 10)
		printf("%d\n", cur_cnt);
	else
		printf("-1\n");

	return 0;
}