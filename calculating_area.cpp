#define _CRT_SECURE_NO_WARNINGS
#define MAX_BOARD_LEN 100
#define MAX_QUEUE_SIZE 10001
#include <stdio.h>

int board[MAX_BOARD_LEN][MAX_BOARD_LEN];
int visited[MAX_BOARD_LEN][MAX_BOARD_LEN];
int bot_y, bot_x, top_y, top_x;
int cur_y, cur_x;
int square_cnt = 0;
int square[MAX_QUEUE_SIZE];
int sorted[MAX_QUEUE_SIZE];
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };


typedef struct {
	int y, x;
}Pos;

typedef struct {
	Pos square[MAX_QUEUE_SIZE];
	int front, rear;
}Queuetype;

Queuetype sq;

void InitQueue(Queuetype* q) {
	q->front = q->rear = 0;
}

int IsEmpty(Queuetype* q) {
	return q->front == q->rear;
}

int IsFull(Queuetype* q) {
	return (q->rear + 1) % MAX_QUEUE_SIZE == q->front;
}

void Enqueue(Queuetype* q, int y, int x) {
	if (IsFull(q))
		return;
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->square[q->rear].y = y;
	q->square[q->rear].x = x;
}

void Dequeue(Queuetype* q) {
	if (IsEmpty(q))
		return;
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	cur_y = q->square[q->front].y;
	cur_x = q->square[q->front].x;
}

/* 합병 */
void Merge(int left, int mid, int right) {
	int i, j, k;
	i = left;
	j = mid + 1;
	k = left;

	while (i <= mid && j <= right) {
		if (square[i] <= square[j])
			sorted[k++] = square[i++];
		else
			sorted[k++] = square[j++];
	}

	if (i > mid) {
		for (int l = j; l <= right; l++)
			sorted[k++] = square[l];
	}
	else {
		for (int l = i; l <= mid; l++)
			sorted[k++] = square[l];
	}

	for (int l = left; l <= right; l++)
		square[l] = sorted[l];
}

/* 합병 정렬 */
void MergeSort(int left, int right) {
	int mid;
	if (left < right) {
		mid = (left + right) / 2;
		MergeSort(left, mid);
		MergeSort(mid + 1, right);
		Merge(left, mid, right);
	}
}

/* 사각형 크기 재기 */
int CalculateSquareSize(int y, int x, int m, int n) {
	int ny, nx;
	int cnt = 0;

	InitQueue(&sq);
	Enqueue(&sq, y, x);
	visited[y][x] = 1;
	cnt ++;

	while (!IsEmpty(&sq)) {
		Dequeue(&sq);

		for (int i = 0; i < 4; i++) {
			ny = cur_y + dy[i];
			nx = cur_x + dx[i];

			/* 범위 내에서 */
			if (ny >= 0 && nx >= 0 && ny < m && nx < n) {
				
				/* 사각형 개수 세기 */
				if (board[ny][nx] == 0 && !visited[ny][nx]) {
					visited[ny][nx] = 1;
					Enqueue(&sq, ny, nx);
					cnt++;
				}
			}
		}
	}
	return cnt;
}

int main() {
	int m, n, k;
	int temp = 0;

	/* 입력 */
	scanf("%d %d %d", &m, &n, &k);
	for (int i = 0; i < k; i++) {
		scanf("%d %d %d %d", &bot_x, &bot_y, &top_x, &top_y);
		
		/* 직사각형 1로 표시 */
		for (int j = bot_y; j < top_y; j++) {
			for (int k = bot_x; k < top_x; k++) {
				board[j][k] = 1;
			}
		}
	}

	/* 영역 세기 & 영역 크기 재기 */
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (board[i][j] == 0 && !visited[i][j]) {
				square[square_cnt] = CalculateSquareSize(i, j, m, n);
				square_cnt++;
			}
		}
	}

	/* 합병 정렬 */
	MergeSort(0, square_cnt - 1);

	/* 출력 */
	printf("%d\n", square_cnt);
	for (int i = 0; i < square_cnt; i++) {
		printf("%d ", square[i]);
	}
	printf("\n");
	return 0;
}