#define _CRT_SECURE_NO_WARNINGS
#define MAX_MAP_LEN 8
#define MAX_QUEUE_SIZE 65
#include <stdio.h>

int lab_map[MAX_MAP_LEN][MAX_MAP_LEN];
int virus_map[MAX_MAP_LEN][MAX_MAP_LEN];
int visited[MAX_MAP_LEN][MAX_MAP_LEN];
int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { -1, 1, 0, 0 };
int pop_x, pop_y;
int max_safezone = 0;

typedef struct {
	int x;
	int y;
}Pos;

typedef struct {
	Pos pos[MAX_QUEUE_SIZE];
	int front;
	int rear;
}Queue;

Queue q;

void InitQueue(Queue* q) {
	q->front = q->rear = 0;
}

int IsEmpty(Queue* q) {
	return q->front == q->rear;
}

int IsFull(Queue* q) {
	return (q->rear + 1) % MAX_QUEUE_SIZE == q->front;
}

void Enqueue(Queue* q, int x_pos, int y_pos) {
	if (IsFull(q)) {
		printf("Queue Full");
		return;
	}
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->pos[q->rear].x = x_pos;
	q->pos[q->rear].y = y_pos;
}

void Dequeue(Queue* q) {
	if (IsEmpty(q)) {
		printf("Queue Empty");
		return;
	}
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	pop_x = q->pos[q->front].x;
	pop_y = q->pos[q->front].y;
}

int GetMax(int a, int b) {
	return a < b ? b : a;
}

/* 방문 초기화 함수 */
void InitVisited(int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			visited[i][j] = 0;
		}
	}
}

/* 지도 복사 함수 */
void CopyMap(int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			virus_map[i][j] = lab_map[i][j];
		}
	}
}

/* 안전 지역 개수 세기 함수 */
int CountSafeZone(int n, int m) {
	int cnt = 0;
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (virus_map[i][j] == 0)
				cnt++;
		}
	}
	return cnt;
}

/* 바이러스 확산 함수 */
void SpreadVirus(int n, int m) {
	int cur_x, cur_y, next_x, next_y;

	InitQueue(&q);
	CopyMap(n, m);

	/* 연구실 내 바이러스 찾아서 큐에 넣기 */
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			if (lab_map[i][j] == 2)
				Enqueue(&q, i, j);
	}

	/* 너비 우선 탐색 시작 */
	while (!IsEmpty(&q)) {
		Dequeue(&q);
		cur_x = pop_x;
		cur_y = pop_y;

		/* 인접한 칸 탐색 시작 */
		for (int i = 0; i < 4; i++) {
			next_x = cur_x + dx[i];
			next_y = cur_y + dy[i];

			/* 범위 내에서*/
			if (next_x >= 0 && next_y >= 0 && next_x < n && next_y < m) {

				/* 방문하지 않은 빈 칸이면 바이러스 감염 */
				if (virus_map[next_x][next_y] == 0 && !visited[next_x][next_y]) {
					visited[next_x][next_y] = 1;
					virus_map[next_x][next_y] = 2;
					Enqueue(&q, next_x, next_y);
				}
			}
		}
	}
	
}

/* 벽 세우기 힘수 */
void BuildWall(int cnt, int n, int m) {
	
	/* 벽 3개 */
	if (cnt == 3) {
		SpreadVirus(n, m);
		max_safezone = GetMax(max_safezone, CountSafeZone(n, m));
		InitVisited(n, m);
		return;
	}

	/* 벽 세우기 */
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (lab_map[i][j] == 0) {
				lab_map[i][j] = 1;
				BuildWall(cnt + 1, n, m);
				lab_map[i][j] = 0;
			}
		}
	}
}

int main() {
	int n, m;   // 가로, 세로

	/* 연구실 지도 입력 */
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &lab_map[i][j]);
		}
	}

	BuildWall(0, n, m);
	printf("%d\n", max_safezone);
	return 0;
}