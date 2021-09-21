#define _CRT_SECURE_NO_WARNINGS
#define MAX_MAP_LEN 1001
#define MAX_QUEUE_SIZE 1000001
#include <stdio.h>

typedef struct {
	int r, c;
	int crashed;
}Postype;

typedef struct {
	Postype pos[MAX_QUEUE_SIZE];
	int front, rear;
}Queuetype;

char map[MAX_MAP_LEN][MAX_MAP_LEN];
int visited[MAX_MAP_LEN][MAX_MAP_LEN][2];  // 0 - 부수지 않고 방문, 1 - 부수고 방문
int cost[MAX_MAP_LEN][MAX_MAP_LEN][2];
int dr[4] = { -1, 0, 1, 0 };
int dc[4] = { 0, 1, 0, -1 };
int cur_r, cur_c, cur_crashed;
Queuetype pos_q;

void InitQueue(Queuetype* q) {
	q->front = q->rear = 0;
}

int IsEmpty(Queuetype* q) {
	return q->front == q->rear;
}

int IsFull(Queuetype* q) {
	return (q->rear + 1) % MAX_QUEUE_SIZE == q->front;
}

void Enqueue(Queuetype* q, int new_r, int new_c, int new_crashed) {
	if (IsFull(q))
		return;

	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->pos[q->rear].r = new_r;
	q->pos[q->rear].c = new_c;
	q->pos[q->rear].crashed = new_crashed;
}

void Dequeue(Queuetype* q) {
	if (IsEmpty(q))
		return;

	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	cur_r = q->pos[q->front].r;
	cur_c = q->pos[q->front].c;
	cur_crashed = q->pos[q->front].crashed;
}

int GetMin(int a, int b) {
	if (a == -1)
		return b;
	return a < b ? a : b;
}


/* 도착지까지 가는 최단 경로 함수 */
int ToDestination(int start_r, int start_c, int dest_r, int dest_c, int n, int m) {
	int next_r = -1, next_c = -1;
	int answer = -1;
	
	InitQueue(&pos_q);
	visited[start_r][start_c][0] = 1;
	cost[start_r][start_c][0] = 1;
	Enqueue(&pos_q, start_r, start_c, 0);

	while (!IsEmpty(&pos_q)) {
		Dequeue(&pos_q);

		/* 도착 시 가장 작은 비용 저장 */
		if (cur_r == dest_r && cur_c == dest_c)
			answer = GetMin(answer, cost[dest_r][dest_c][cur_crashed]);

		for (int i = 0; i < 4; i++) {
			next_r = cur_r + dr[i];
			next_c = cur_c + dc[i];

			/* 범위 내에서 */
			if (next_r >= 0 && next_c >= 0 && next_r < n && next_c < m) {
				
				/* 벽이고 부술 기회가 있을 때 */
				if (map[next_r][next_c] == '1' && !cur_crashed) {
					visited[next_r][next_c][cur_crashed + 1] = 1;
					cost[next_r][next_c][cur_crashed + 1] = cost[cur_r][cur_c][cur_crashed] + 1;
					Enqueue(&pos_q, next_r, next_c, cur_crashed + 1);
				}

				/* 벽이 아니고 방문하지 않은 칸일 때 */
				else if (map[next_r][next_c] == '0' && !visited[next_r][next_c][cur_crashed]) {
					visited[next_r][next_c][cur_crashed] = 1;
					cost[next_r][next_c][cur_crashed] = cost[cur_r][cur_c][cur_crashed] + 1;
					Enqueue(&pos_q, next_r, next_c, cur_crashed);
				}
			}
		}
	}
	return answer;
}

int main() {
	int n, m;

	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%s", map[i]);
	}

	printf("%d\n", ToDestination(0, 0, n - 1, m - 1, n, m));

	return 0;
}