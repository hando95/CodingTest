#define _CRT_SECURE_NO_WARNINGS
#define MAX_BOX_LEN 1000
#define MAX_QUEUE_SIZE 1000001
#include <stdio.h>

typedef struct {
	int r, c;
	int day;
}Postype;

typedef struct {
	Postype pos[MAX_QUEUE_SIZE];
	int front, rear;
}Queuetype;

Queuetype tomato;
int box[MAX_BOX_LEN][MAX_BOX_LEN];
int cur_r, cur_c, cur_day;
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

void Enqueue(Queuetype* q, int new_r, int new_c, int new_day) {
	if (IsFull(q))
		return;

	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->pos[q->rear].r = new_r;
	q->pos[q->rear].c = new_c;
	q->pos[q->rear].day = new_day;
}

void Dequeue(Queuetype* q) {
	if (IsEmpty(q))
		return;

	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	cur_r = q->pos[q->front].r;
	cur_c = q->pos[q->front].c;
	cur_day = q->pos[q->front].day;
}

/* 모든 토마토가 익었는지 확인하는 함수 */
int CheckRipen(int n, int m) {
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (box[i][j] == 0)
				return 0;
		}
	}
	return 1;
}

/* 토마토 익히기 함수 */
int LetsRipen(int n, int m) {
	int next_r = 0, next_c = 0;

	while (!IsEmpty(&tomato)) {
		Dequeue(&tomato);
		
		for (int i = 0; i < 4; i++) {
			next_r = cur_r + dr[i];
			next_c = cur_c + dc[i];

			/* 범위 내에서 */
			if (next_r >= 0 && next_c >= 0 && next_r < n && next_c < m) {
				
				/* 안 익은 토마토 발견 -> 익히기 */
				if (box[next_r][next_c] == 0) {
					box[next_r][next_c] = 1;
					Enqueue(&tomato, next_r, next_c, cur_day + 1);
				}
			}
		}
	}

	/* 다 익었으면 익힌 일수, 다 안 익었으면 -1 */
	if (CheckRipen(n, m))
		return cur_day;
	return -1;
}

int main() {
	int m, n;
	scanf("%d %d", &m, &n);
	InitQueue(&tomato);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &box[i][j]);
			if (box[i][j] == 1)
				Enqueue(&tomato, i, j, 0);
		}
	}

	printf("%d\n", LetsRipen(n, m));
	return 0;
}