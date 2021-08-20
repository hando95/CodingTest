#define _CRT_SECURE_NO_WARNINGS
#define MAX_MAP_LEN 20
#define CMD_MAX_SIZE 1000
#include <stdio.h>

int map[MAX_MAP_LEN][MAX_MAP_LEN];
int dir[CMD_MAX_SIZE];
int cur_r, cur_c;

typedef struct {
	int forward;
	int left;
	int top;
	int right;
	int back;
	int bottom;
}Dicetype;

Dicetype dice;

void RollDice(int direction) {
	int temp;

	switch (direction) {
	case 1:
		temp = dice.top;
		dice.top = dice.left;
		dice.left = dice.bottom;
		dice.bottom = dice.right;
		dice.right = temp;
		break;
	case 2:
		temp = dice.top;
		dice.top = dice.right;
		dice.right = dice.bottom;
		dice.bottom = dice.left;
		dice.left = temp;
		break;
	case 3:
		temp = dice.top;
		dice.top = dice.back;
		dice.back = dice.bottom;
		dice.bottom = dice.forward;
		dice.forward = temp;
		break;
	case 4:
		temp = dice.top;
		dice.top = dice.forward;
		dice.forward = dice.bottom;
		dice.bottom = dice.back;
		dice.back = temp;
		break;
	}
}

void MoveDice(int n, int m, int r, int c, int direction) {
	int next_r = 0, next_c = 0;

	/* 명령에 따라 이동 */
	switch (direction) {
	case 1:
		next_r = cur_r;
		next_c = cur_c + 1;
		break;
	case 2:
		next_r = cur_r;
		next_c = cur_c - 1;
		break;
	case 3:
		next_r = cur_r - 1;
		next_c = cur_c;
		break;
	case 4:
		next_r = cur_r + 1;
		next_c = cur_c;
		break;
	}

	/* 범위 내면 이동 */
	if (next_r >= 0 && next_c >= 0 && next_r < n && next_c < m) {

		/* 주사위에 써 있는 수 지도로 복사 */
		if (map[next_r][next_c] == 0) {
			RollDice(direction);
			map[next_r][next_c] = dice.bottom;
			cur_r = next_r;
			cur_c = next_c;
		}

		/* 지도에 써 있는 수 주사위로 복사 후 지도는 0으로 초기화 */
		else {
			RollDice(direction);
			dice.bottom = map[next_r][next_c];
			map[next_r][next_c] = 0;
			cur_r = next_r;
			cur_c = next_c;
		}

		printf("%d\n", dice.top);
	}

}



int main() {
	int n, m, start_r, start_c, k;

	scanf("%d %d %d %d %d", &n, &m, &start_r, &start_c, &k);

	cur_r = start_r;
	cur_c = start_c;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &map[i][j]);
		}
	}

	for (int i = 0; i < k; i++) {
		scanf("%d", &dir[i]);
	}

	for (int i = 0; i < k; i++) {
		MoveDice(n, m, cur_r, cur_c, dir[i]);
	}
	return 0;
}