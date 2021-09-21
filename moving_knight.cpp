#define _CRT_SECURE_NO_WARNINGS
#define MAX_BOARD_SIZE 300
#define MAX_POS_NUM 90001
#include <stdio.h>

int visited[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
int cost[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
int cur_r, cur_c;
int dr[8] = { -1, -2, -2, -1, 1, 2, 2, 1 };
int dc[8] = { -2, -1, 1, 2, 2, 1, -1, -2 };

typedef struct {
	int r, c;
}Postype;

typedef struct {
	Postype pos[MAX_POS_NUM];
	int front, rear;
}Queuetype;

Queuetype chess;

void InitQueue(Queuetype* q) {
	q->front = q->rear = 0;
}

int IsEmpty(Queuetype* q) {
	return q->front == q->rear;
}

int IsFull(Queuetype* q) {
	return (q->rear + 1) % MAX_POS_NUM == q->rear;
}

void Enqueue(Queuetype* q, int new_r, int new_c) {
	if (IsFull(q))
		return;
	q->rear = (q->rear + 1) % MAX_POS_NUM;
	q->pos[q->rear].r = new_r;
	q->pos[q->rear].c = new_c;
}

void Dequeue(Queuetype* q) {
	if (IsEmpty(q))
		return;
	q->front = (q->front + 1) % MAX_POS_NUM;
	cur_r = q->pos[q->front].r;
	cur_c = q->pos[q->front].c;
}

int MoveKnight(int knt_r, int knt_c, int dest_r, int dest_c, int l) {
	int next_r, next_c;

	if (knt_r == dest_r && knt_c == dest_c)
		return 0;

	InitQueue(&chess);
	Enqueue(&chess, knt_r, knt_c);
	visited[knt_r][knt_c] = 1;

	while (!IsEmpty(&chess)) {
		Dequeue(&chess);

		for (int i = 0; i < 8; i++) {
			next_r = cur_r + dr[i];
			next_c = cur_c + dc[i];

			/* 범위 내에서 */
			if (next_r >= 0 && next_c >= 0 && next_r < l && next_c < l) {

				/* 미방문한 칸이면 */
				if (!visited[next_r][next_c]) {
					visited[next_r][next_c] = 1;
					cost[next_r][next_c] = cost[cur_r][cur_c] + 1;

					/* 도착한 경우 */
					if (next_r == dest_r && next_c == dest_c)
						return cost[next_r][next_c];
					/* 도착하지 않은 경우 */
					else
						Enqueue(&chess, next_r, next_c);
				}
			}
		}
	}
	return -1;
}

void InitVisandCost(int l) {
	for (int i = 0; i < l; i++) {
		for (int j = 0; j < l; j++) {
			cost[i][j] = 0;
			visited[i][j] = 0;
		}
	}
	for (int i = 0; i < l; i++) {
		for (int j = 0; j < l; j++) {
			
		}
	}
}


int main() {
	int test_case;
	int knt_r, knt_c;
	int dest_r, dest_c;
	int l;

	scanf("%d", &test_case);

	while (test_case--) {
		scanf("%d", &l);
		scanf("%d %d", &knt_r, &knt_c);
		scanf("%d %d", &dest_r, &dest_c);
		
		printf("%d\n", MoveKnight(knt_r, knt_c, dest_r, dest_c, l));
		InitVisandCost(l);
	}
	return 0;
}