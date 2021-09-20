#define _CRT_SECURE_NO_WARNINGS
#define MAX_POS_SIZE 100001
#include <stdio.h>

typedef struct {
	int pos[MAX_POS_SIZE];
	int front, rear;
}Queuetype;

Queuetype x;
int visited[MAX_POS_SIZE];
int time[MAX_POS_SIZE];

void InitQueue(Queuetype* q) {
	q->front = q->rear = 0;
}

int IsEmpty(Queuetype* q) {
	return q->front == q->rear;
}

int IsFull(Queuetype* q) {
	return (q->rear + 1) % MAX_POS_SIZE == q->front;
}

void Enqueue(Queuetype* q, int x) {
	if (IsFull(q))
		return;
	q->rear = (q->rear + 1) % MAX_POS_SIZE;
	q->pos[q->rear] = x;
}

int Dequeue(Queuetype* q) {
	if (IsEmpty(q))
		return -1;
	q->front = (q->front + 1) % MAX_POS_SIZE;
	return q->pos[q->front];
}

int SeekBro(Queuetype* q, int n, int k) {
	int cur_x;
	int cnt = 0;
	int next_x;

	InitQueue(q);
	Enqueue(q, n);

	/* BFS */
	while (!IsEmpty(q)) {
		cur_x = Dequeue(q);

		for (int i = 0; i < 3; i++) {
			switch (i) {
			case 0:
				next_x = cur_x - 1;
				break;
			case 1:
				next_x = cur_x + 1;
				break;
			case 2:
				next_x = cur_x * 2;
				break;
			}

			/* 범위 내에서 */
			if (next_x >= 0 && next_x < MAX_POS_SIZE) {
				
				/* 방문하지 않은 곳 방문 */
				if (!visited[next_x]) {
					visited[next_x] = 1;
					time[next_x] = time[cur_x] + 1;

					/* 동생을 찾은 경우 */
					if (next_x == k)
						return time[next_x];

					Enqueue(q, next_x);
				}
			}
		}
	}
    return -1;
}


int main() {
	int n, k;
	scanf("%d %d", &n, &k);

	/* 같은 곳에 있을 경우 */
	if (n == k)
		printf("%d\n", 0);
	/* 다른 곳에 있을 경우 */
	else
		printf("%d\n", SeekBro(&x, n, k));
	return 0;
}