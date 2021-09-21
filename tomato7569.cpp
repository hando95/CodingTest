#define _CRT_SECURE_NO_WARNINGS
#define MAX_BOX_LEN 100
#define MAX_QUEUE_SIZE 1000001
#include <stdio.h>

typedef struct {
	int r, c, h;
	int day;
}Postype;

typedef struct {
	Postype pos[MAX_QUEUE_SIZE];
	int front, rear;
}Queuetype;

Queuetype tomato;
int box[MAX_BOX_LEN][MAX_BOX_LEN][MAX_BOX_LEN];
int cur_r, cur_c, cur_h, cur_day;

/* 북, 동, 남, 서, 상, 하 */
int dr[6] = { -1, 0, 1, 0, 0, 0 };
int dc[6] = { 0 ,1, 0, -1, 0, 0 };
int dh[6] = { 0 ,0 ,0, 0, 1, -1 };


void InitQueue(Queuetype* q) {
	q->front = q->rear = 0;
}

int IsFull(Queuetype* q) {
	return (q->rear + 1) % MAX_QUEUE_SIZE == q->front;
}

int IsEmpty(Queuetype* q) {
	return q->rear == q->front;
}

void Enqueue(Queuetype* q, int new_r, int new_c, int new_h, int new_day) {
	if (IsFull(q))
		return;

	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->pos[q->rear].r = new_r;
	q->pos[q->rear].c = new_c;
	q->pos[q->rear].h = new_h;
	q->pos[q->rear].day = new_day;
}

void Dequeue(Queuetype* q) {
	if (IsEmpty(q))
		return;

	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	cur_r = q->pos[q->front].r;
	cur_c = q->pos[q->front].c;
	cur_h = q->pos[q->front].h;
	cur_day = q->pos[q->front].day;
}

/* 모두 익었는지 확인하는 함수 */
int CheckRipen(int n, int m, int h) {
	for (int k = 0; k < h; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (box[i][j][k] == 0)
					return 0;
			}
		}
	}
	return 1;
}

/* 토마토 익히기 함수 */
int LetsRipen(int n, int m, int h) {
	int next_r, next_c, next_h;

	while (!IsEmpty(&tomato)) {
		Dequeue(&tomato);

		for (int i = 0; i < 6; i++) {
			next_r = cur_r + dr[i];
			next_c = cur_c + dc[i];
			next_h = cur_h + dh[i];

			/* 범위 내에서 */
			if (next_r >= 0 && next_c >= 0 && next_h >= 0 && next_r < n && next_c < m && next_h < h) {
				if (box[next_r][next_c][next_h] == 0) {
					box[next_r][next_c][next_h] = 1;
					Enqueue(&tomato, next_r, next_c, next_h, cur_day + 1);
				}
			}
		}
	}

	if (CheckRipen(n, m, h))
		return cur_day;
	return -1;
}

int main() {
	int m, n, h;

	InitQueue(&tomato);

	scanf("%d %d %d", &m, &n, &h);

	for (int k = 0; k < h; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				scanf("%d", &box[i][j][k]);
				if (box[i][j][k] == 1)
					Enqueue(&tomato, i, j, k, 0);
			}
		}
	}
	printf("%d\n", LetsRipen(n, m, h));
	return 0;
}