#define _CRT_SECURE_NO_WARNINGS
#define MAX_ROOM_LEN 50
#define MAX_QUEUE_SIZE (MAX_ROOM_LEN * MAX_ROOM_LEN + 1)
#include <stdio.h>

int room[MAX_ROOM_LEN][MAX_ROOM_LEN];
int cleaned[MAX_ROOM_LEN][MAX_ROOM_LEN];
int pop_r, pop_c;
int clean_cnt = 0;

typedef struct {
	int r, c;
}Pos;

typedef struct {
	Pos pos[MAX_QUEUE_SIZE];
	int front, rear;
	int r;  // 북쪽으로부터의 거리
	int c;  // 서쪽으로부터의 거리
	int d;  // 방향
}Robot;

Robot robo;

void InitRobo(Robot* q, int r, int c, int d) {
	q->front = q->rear = 0;
	q->r = r, q->c = c,	q->d = d;
}

int IsEmpty(Robot* q) {
	return q->front == q->rear;
}

int IsFull(Robot* q) {
	return (q->rear + 1) % MAX_QUEUE_SIZE == q->front;
}

void Enqueue(Robot* q, int r, int c) {
	if (IsFull(q)) {
		printf("Full\n");
		return;
	}
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->pos[q->rear].r = r;
	q->pos[q->rear].c = c;
}

void Dequeue(Robot* q) {
	if (IsEmpty(q)) {
		printf("Empty\n");
		return;
	}
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	pop_r = q->pos[q->front].r;
	pop_c = q->pos[q->front].c;
}

void TurnLeft(int d) {
	switch (d) {
	case 0: 
		robo.d = 3;
		break;
	case 1: 
		robo.d = 0;
		break;
	case 2: 
		robo.d = 1;
		break;
	case 3: 
		robo.d = 2;
		break;
	}
}


void Cleaning(int r, int c) {
	int cur_r, cur_c, next_r, next_c;
	int clean_flag = 0;
	
	cleaned[r][c] = 1;
	clean_cnt++;
	Enqueue(&robo, r, c);

	while (!IsEmpty(&robo)) {
		Dequeue(&robo);
		cur_r = pop_r;
		cur_c = pop_c;

		/* 동서남북 탐색 */
		for (int i = 0; i < 4; i++) {

			switch (robo.d) {
			case 0:
				next_r = cur_r;
				next_c = cur_c - 1;
				break;
			case 1:
				next_r = cur_r - 1;
				next_c = cur_c;
				break;
			case 2:
				next_r = cur_r;
				next_c = cur_c + 1;
				break;
			case 3:
				next_r = cur_r + 1;
				next_c = cur_c;
				break;
			}

			/* 왼쪽을 청소할 수 있는 경우 */
			if (room[next_r][next_c] == 0 && !cleaned[next_r][next_c]) {
				TurnLeft(robo.d);
				cleaned[next_r][next_c] = 1;
				clean_cnt++;
				clean_flag = 1;
				Enqueue(&robo, next_r, next_c);
				break;
			}

			/* 왼쪽을 청소할 수 없는 경우 */
			TurnLeft(robo.d);
		}

		/* 청소를 못 할 경우 뒤쪽 검사*/
		if (!clean_flag) {
			switch (robo.d) {
			case 0:
				next_r = cur_r + 1;
				next_c = cur_c;
				break;
			case 1:
				next_r = cur_r;
				next_c = cur_c - 1;
				break;
			case 2:
				next_r = cur_r - 1;
				next_c = cur_c;
				break;
			case 3:
				next_r = cur_r;
				next_c = cur_c + 1;
				break;
			}

			/* 뒤가 벽이면 종료 */
			if (room[next_r][next_c] == 1)
				return;
			
			/* 뒤가 벽이 아니면 뒤로 */
			Enqueue(&robo, next_r, next_c);
		}
		clean_flag = 0;
	}
}


int main() {
	int n, m;      // 세로, 가로;
	int r, c, d;   // 북쪽으로부터의 거리, 서쪽으로부터의 거리, 바라보는 방향

	scanf("%d %d", &n, &m);
	scanf("%d %d %d", &r, &c, &d);

	InitRobo(&robo, r, c, d);


	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &room[i][j]);
		}
	}

	Cleaning(r, c);

	printf("%d\n", clean_cnt);
	return 0;
}