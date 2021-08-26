#define _CRT_SECURE_NO_WARNINGS
#define MAX_CHEESE_LEN 100
#define MAX_CHEESE_SIZE 10001
#include <stdio.h>

int cheese[MAX_CHEESE_LEN][MAX_CHEESE_LEN];
int visited[MAX_CHEESE_LEN][MAX_CHEESE_LEN];
int dr[4] = { -1, 0, 1, 0 };
int dc[4] = { 0, 1, 0 ,-1 };
int pop_r, pop_c;

typedef struct {
	int r, c;
}Pos;

typedef struct {
	Pos pos[MAX_CHEESE_SIZE];
	int front, rear;
}Queuetype;

Queuetype chz;

void InitQueue(Queuetype* q) {
	q->front = q->rear = 0;
}

int IsEmpty(Queuetype* q) {
	return q->front == q->rear;
}

int IsFull(Queuetype* q) {
	return (q->rear + 1) % MAX_CHEESE_SIZE == q->front;
}

void Enqueue(Queuetype* q, int r, int c) {
	if (IsFull(q))
		return;
	q->rear = (q->rear + 1) % MAX_CHEESE_SIZE;
	q->pos[q->rear].r = r;
	q->pos[q->rear].c = c;
}

void Dequeue(Queuetype* q) {
	if (IsEmpty(q))
		return;
	q->front = (q->front + 1) % MAX_CHEESE_SIZE;
	pop_r = q->pos[q->front].r;
	pop_c = q->pos[q->front].c;
}

/* 가장자리 녹이기 */
void MeltingEdge(int n, int m) {
	int cur_r, cur_c, nr, nc;
	InitQueue(&chz);
	Enqueue(&chz, 0, 0);
	Enqueue(&chz, 0, m - 1);
	Enqueue(&chz, n - 1, 0);
	Enqueue(&chz, n - 1, m - 1);
	visited[0][0] = 1;
	visited[0][m - 1] = 1;
	visited[n - 1][0] = 1;
	visited[n - 1][m - 1] = 1;

	while (!IsEmpty(&chz)) {
		Dequeue(&chz);
		cur_r = pop_r;
		cur_c = pop_c;

		for (int i = 0; i < 4; i++) {
			nr = cur_r + dr[i];
			nc = cur_c + dc[i];

			/* 범위 내에서 */
			if (nr >= 0 && nc >= 0 && nr < MAX_CHEESE_LEN && nc < MAX_CHEESE_LEN) {
				/* 외부 공기 */
				if (cheese[nr][nc] == 0 && !visited[nr][nc]) {
					visited[nr][nc] = 1;
					Enqueue(&chz, nr, nc);
				}
				/* 가장자리 치즈 */
				else if (cheese[nr][nc] == 1 && !visited[nr][nc]) {
					visited[nr][nc] = 1;
					cheese[nr][nc] = 0;
				}
			}
		}
	}
}

/* 남은 치즈 개수 확인하면서 미방문 처리 */
int CountCheese(int n, int m) {
	int remain = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (cheese[i][j] == 1)
				remain++; 
			visited[i][j] = 0;
		}
	}
	return remain;
}

/* 치즈 녹이기 */
void MeltingCheese(int n, int m) {
	int cur_chz;
	int before_chz = 0;
	int time = 0;

	while (1) {
		cur_chz = CountCheese(n, m);
		if (cur_chz == 0) {
			printf("%d\n", time);
			printf("%d\n", before_chz);
			break;
		}

		MeltingEdge(n, m);
		time++;
		before_chz = cur_chz;
	}
}

int main() {
	int n, m;

	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &cheese[i][j]);
		}
	}

	MeltingCheese(n, m);
	return 0;
}