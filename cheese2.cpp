#define _CRT_SECURE_NO_WARNINGS
#define MAX_CHEESE_LEN 100
#define MAX_CHEESE_SIZE 10001
#include <stdio.h>

int board[MAX_CHEESE_LEN][MAX_CHEESE_LEN];
int visited[MAX_CHEESE_LEN][MAX_CHEESE_LEN];
int dr[4] = { -1, 0, 1, 0 };
int dc[4] = { 0, 1, 0, -1 };
int pop_r, pop_c;


typedef struct {
	int r, c;
}Pos;

typedef struct {
	Pos chz[MAX_CHEESE_SIZE];
	int front, rear;
}Queuetype;

Queuetype cheese;

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
	q->chz[q->rear].r = r;
	q->chz[q->rear].c = c;
}

void Dequeue(Queuetype* q) {
	if (IsEmpty(q))
		return;
	q->front = (q->front + 1) % MAX_CHEESE_SIZE;
	pop_r = q->chz[q->front].r;
	pop_c = q->chz[q->front].c;
}

void MeltingEdge(int n, int m) {
	int nr, nc;

	InitQueue(&cheese);
	Enqueue(&cheese, 0, 0);
	Enqueue(&cheese, 0, m - 1);
	Enqueue(&cheese, n - 1, 0);
	Enqueue(&cheese, n - 1, m - 1);
	visited[0][0] = 1;
	visited[0][m - 1] = 1;
	visited[n - 1][0] = 1;
	visited[n - 1][m - 1] = 1;

	while (!IsEmpty(&cheese)) {
		Dequeue(&cheese);

		for (int i = 0; i < 4; i++) {
			nr = pop_r + dr[i];
			nc = pop_c + dc[i];

			/* 범위 내에서 */
			if (nr >= 0 && nc >= 0 && nr < n && nc < m) {
				
				/* 외부 공기 */
				if (board[nr][nc] == 0 && !visited[nr][nc]) {
					visited[nr][nc] = 1;
					Enqueue(&cheese, nr, nc);
				}

				/* 공기와 한 번도 맞닿지 않은 치즈 발견 */
				else if (board[nr][nc] == 1 && !visited[nr][nc]) {
					visited[nr][nc] = 1;
				}

				/* 이미 공기와 맞닿은 치즈 발견 */
				else if (board[nr][nc] == 1 && visited[nr][nc] == 1) {
					visited[nr][nc] = 2;
					board[nr][nc] = 0;
				}
				
			}
		}
	}
}

/* 남은 치즈 개수 세면서 미방문 처리 */
int CountingCheese(int n, int m) {
	int count = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (board[i][j] == 1)
				count++;
			visited[i][j] = 0;
		}
	}
	return count;
}

/* 치즈가 모두 없어질 때까지 시간 재기 */
int MeltingCheese(int n, int m) {
	int time = 0;
	while (CountingCheese(n, m)) {
		MeltingEdge(n, m);
		time++;
	}
	return time;
}

int main() {
	int n, m;
	
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &board[i][j]);
		}
	}

	printf("%d\n",MeltingCheese(n, m));

}