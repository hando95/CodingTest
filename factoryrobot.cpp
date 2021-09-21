#define _CRT_SECURE_NO_WARNINGS
#define MAX_FACTORY_SIZE 101
#define MAX_QUEUE_SIZE 100000
#include <stdio.h>

int factory[MAX_FACTORY_SIZE][MAX_FACTORY_SIZE];
int watched[MAX_FACTORY_SIZE][MAX_FACTORY_SIZE][4];   // 동, 서, 남, 북 4방향 방문상태
int visited[MAX_FACTORY_SIZE][MAX_FACTORY_SIZE][3];   // 3, 2, 1칸 전진 방문상태
int cur_r, cur_c, cur_d, cur_cnt;

/* 동서남북 */
int dr[5] = { 0, 0, 0, 1, -1 };
int dc[5] = { 0, 1, -1, 0, 0 };

typedef struct {
	int r, c;
	int d;
}Robotype;

typedef struct {
	Robotype pos[MAX_QUEUE_SIZE];
	int count[MAX_QUEUE_SIZE];
	int front, rear;
}Queuetype;

Queuetype robo;

void InitQueue(Queuetype* q) {
	q->front = q->rear = 0;
}

int IsEmpty(Queuetype* q) {
	return q->front == q->rear;
}

int IsFull(Queuetype* q) {
	return (q->rear + 1) % MAX_QUEUE_SIZE == q->front;
}

void Enqueue(Queuetype* q, int new_r, int new_c, int new_d, int cnt) {
	if (IsFull(q))
		return;

	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->pos[q->rear].r = new_r;
	q->pos[q->rear].c = new_c;
	q->pos[q->rear].d = new_d;
	q->count[q->rear] = cnt;
}

void Dequeue(Queuetype* q) {
	if (IsEmpty(q))
		return;

	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	cur_r = q->pos[q->front].r;
	cur_c = q->pos[q->front].c;
	cur_d = q->pos[q->front].d;
	cur_cnt = q->count[q->front];
}

int GetMin(int a, int b) {
	if (a == -1)
		return b;
	return a < b ? a : b;
}

/* 해당 방향으로 직진할 수 있는 칸 세기 */
int CountFrontRoad(int r, int c, int d, int m ,int n) {
	int next_r = r, next_c = c;
	int cnt = 0;
	while (factory[next_r][next_c] == 0) {
		next_r += dr[d];
		next_c += dc[d];
		if (next_r < 1 || next_c < 1 || next_r > m || next_c > n || factory[next_r][next_c] == 1)
			break;
		cnt++;
	}
	return cnt;
}

/* 왼쪽 회전 함수 */
int TurnLeft(int r, int c, int d) {
	int next_d = -1;
	switch (d) {
	case 1:
		next_d = 4;
		break;
	case 2:
		next_d = 3;
		break;
	case 3:
		next_d = 1;
		break;
	case 4:
		next_d = 2;
		break;
	}
	return next_d;
}

/* 오른쪽 회전 함수 */
int TurnRight(int r, int c, int d) {
	int next_d = -1;
	switch (d) {
	case 1:
		next_d = 3;
		break;
	case 2:
		next_d = 4;
		break;
	case 3:
		next_d = 2;
		break;
	case 4:
		next_d = 1;
		break;
	}
	return next_d;
}

/* 로봇 이동 함수 */
int MoveRobot(int start_r, int start_c, int start_d, int dest_r, int dest_c, int dest_d, int m, int n) {
	int next_r = -1, next_c = -1, next_d = -1;
	int road_cnt, road_ok;
	int answer = -1;

	InitQueue(&robo);
	watched[start_r][start_c][start_d] = 1;
	Enqueue(&robo, start_r, start_c, start_d, 0);

	/* TurnLeft, TurnRight, Go 1, Go 2, Go 3 경우의 수 모두 탐색 */
	while (!IsEmpty(&robo)) {
		Dequeue(&robo);

		/* 도착 위치인 경우 - 동작 횟수 저장 */
		if (cur_r == dest_r && cur_c == dest_c && cur_d == dest_d)
			answer = GetMin(answer, cur_cnt);

		/* 전진할 수 있는 칸 세기 */
		road_cnt = CountFrontRoad(cur_r, cur_c, cur_d, m, n);

		/* 0 - 왼쪽 회전, 1 - 오른쪽 회전 */
		for (int i = 0; i < 2; i++) {

			/* 왼쪽 회전 */
			if (i == 0)
				next_d = TurnLeft(cur_r, cur_c, cur_d);
			/* 오른쪽 회전 */
			else
				next_d = TurnRight(cur_r, cur_c, cur_d);

			/* 한 번도 확인하지 않은 방향이면 방문 처리 */
			if (!watched[cur_r][cur_c][next_d]) {
				watched[cur_r][cur_c][next_d] = 1;
				Enqueue(&robo, cur_r, cur_c, next_d, cur_cnt + 1);
			}

		}

		/* 0 - 3칸 전진, 1 - 2칸 전진, 2 - 1칸 전진 */
		for (int i = 0; i < 3; i++) {
			road_ok = 0;  // 전진할 수 있는지 확인하는 변수 

			/* 3칸 전진 가능 시 */
			if (i == 0 && road_cnt >= 3) {
				next_r = cur_r + (dr[cur_d] * 3);
				next_c = cur_c + (dc[cur_d] * 3);
				road_ok = 1;
			}

			/* 2칸 전진 가능 시 */
			else if (i == 1 && road_cnt >= 2) {
				next_r = cur_r + (dr[cur_d] * 2);
				next_c = cur_c + (dc[cur_d] * 2);
				road_ok = 1;
			}

			/* 1칸 전진 가능 시 */
			else if (i == 2 && road_cnt >= 1) {
				next_r = cur_r + dr[cur_d];
				next_c = cur_c + dc[cur_d];
				road_ok = 1;
			}

			/* 전진할 수 있고 범위 내에서 방문 처리 */
			if (road_ok && next_r >= 1 && next_c >= 1 && next_r <= m && next_c <= n) {
				if (!visited[next_r][next_c][i]) {
					visited[next_r][next_c][i] = 1;
					Enqueue(&robo, next_r, next_c, cur_d, cur_cnt + 1);
				}
			}
		}
	}
	return answer;
}

int main() {
	int m, n;
	int start_r, start_c, start_d;
	int dest_r, dest_c, dest_d;

	scanf("%d %d", &m, &n);
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%d", &factory[i][j]);
		}
	}

	scanf("%d %d %d", &start_r, &start_c, &start_d);
	scanf("%d %d %d", &dest_r, &dest_c, &dest_d);

	printf("%d\n", MoveRobot(start_r, start_c, start_d, dest_r, dest_c, dest_d, m, n));
	return 0;
}