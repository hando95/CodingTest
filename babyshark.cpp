#define _CRT_SECURE_NO_WARNINGS
#define MAX_OCEAN_SIZE 20
#define MAX_QUEUE_SIZE 401
#include <stdio.h>

typedef struct {
	int r, c;
	int time;
}Postype;

typedef struct {
	Postype pos[MAX_QUEUE_SIZE];
	int front, rear;
}Queuetype;

Queuetype shark_q;
int cur_r, cur_c, cur_time;
int size = 2;
int eaten_r, eaten_c;
int total_time = 0, total_cnt = 0;
int ocean[MAX_OCEAN_SIZE][MAX_OCEAN_SIZE];
int visited[MAX_OCEAN_SIZE][MAX_OCEAN_SIZE];
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

void Enqueue(Queuetype* q, int new_r, int new_c, int new_time) {
	if (IsFull(q))
		return;

	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->pos[q->rear].r = new_r;
	q->pos[q->rear].c = new_c;
	q->pos[q->rear].time = new_time;
}

void Dequeue(Queuetype* q) {
	if (IsEmpty(q))
		return;

	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	cur_r = q->pos[q->front].r;
	cur_c = q->pos[q->front].c;
	cur_time = q->pos[q->front].time;
}

int FoundEdibleFish(int start_r, int start_c, int n) {
	int next_r = 0, next_c = 0;
	int final_r = -1, final_c = -1, final_time = -1;
	int found = 0;

	InitQueue(&shark_q);
	Enqueue(&shark_q, start_r, start_c, 0);

	while (!IsEmpty(&shark_q)) {
		Dequeue(&shark_q);

		for (int i = 0; i < 4; i++) {
			next_r = cur_r + dr[i];
			next_c = cur_c + dc[i];

			/* 범위 내에서 */
			if (next_r >= 0 && next_c >= 0 && next_r < n && next_c < n) {

				/* 빈 칸일 시 통과 */
				if (ocean[next_r][next_c] == 0 && !visited[next_r][next_c]) {
					visited[next_r][next_c] = 1;
					Enqueue(&shark_q, next_r, next_c, cur_time + 1);
				}

				/* 같은 물고기 발견 시 통과 */
				else if (ocean[next_r][next_c] == size && !visited[next_r][next_c]) {
					visited[next_r][next_c] = 1;
					Enqueue(&shark_q, next_r, next_c, cur_time + 1);
				}

				/* 작은 물고기 발견 시 시간, 위치 저장 */
				else if (ocean[next_r][next_c] < size && !visited[next_r][next_c]) {
					visited[next_r][next_c] = 1;
					found = 1;

					/* 처음 만난 물고기면 저장 */
					if (final_time == -1) {
						final_time = cur_time + 1;
						final_r = next_r;
						final_c = next_c;
					}

					/* 여러 물고기를 만나면 비교 */
					else {

						/* 가장 가까운 물고기 저장 */
						if (final_time > cur_time + 1) {
							final_time = cur_time + 1;
							final_r = next_r;
							final_c = next_c;
						}

						/* 거리가 가까운 물고기가 여러 마리일 경우 */
						else if (final_time == cur_time + 1) {

							/* 가장 위 저장 */
							if (final_r > next_r) {
								final_r = next_r;
								final_c = next_c;
							}

							/* 모두 위에 있다면 가장 왼쪽 저장 */
							else if (final_r == next_r && final_c > next_c) {
								final_r = next_r;
								final_c = next_c;
							}
						}
					}
				}

				/* 큰 물고기 발견 시 우회 */
				else
					continue;
			}
		}
	}

	/* 먹을 수 있는 물고기를 찾은 경우 */
	if (found) {
		eaten_r = final_r;
		eaten_c = final_c;
		total_time += final_time;
		total_cnt++;
		ocean[eaten_r][eaten_c] = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				visited[i][j] = 0;
			}
		}
		return 1;
	}
	/* 먹을 수 있는 물고기를 찾지 못 한 경우 */
	else
		return 0;
}

int LetsEat(int start_r, int start_c, int n) {

	/* 먹을 수 있는 물고기를 찾지 못 할 때까지 반복 */
	while (FoundEdibleFish(eaten_r, eaten_c, n)) {
		if (total_cnt == size) {
			total_cnt = 0;
			size++;
		}
	}
	return total_time;
}

int main() {
	int n;
	InitQueue(&shark_q);

	/* 입력 */
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &ocean[i][j]);

			if (ocean[i][j] == 9) {
				ocean[i][j] = 0;
				eaten_r = i;
				eaten_c = j;
			}
		}
	}

	/* 출력 */
	printf("%d\n", LetsEat(eaten_r, eaten_c, n));
	return 0;
}