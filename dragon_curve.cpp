#define _CRT_SECURE_NO_WARNINGS
#define MAX_DRAGON_NUM 20
#define MAX_MAP_SIZE 101
#include <stdio.h>

typedef struct {
	int x, y;
	int d, g;
}DragonCurvetype;

DragonCurvetype dg[MAX_DRAGON_NUM];
int map[MAX_MAP_SIZE][MAX_MAP_SIZE];
int dirs[1024];
int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, -1, 0, 1 };

int SaveDirections(DragonCurvetype* dg) {
	int bound = 1;
	int gen = 0;
	int idx;
	dirs[0] = dg->d;

	/* 해당 세대까지 반복 */
	while (gen != dg->g) {
		idx = bound;

		/* 가장 최근 방향부터 가장 처음 방향까지 전환하면서 뒤에 삽입 */
		for (int i = bound - 1; i >= 0; i--) {
			dirs[idx++] = (dirs[i] + 1) % 4;
		}
		bound *= 2;
		gen++;
	}
	return bound;
}

void DrawCurves(DragonCurvetype* dg, int bound) {
	int cur_x = dg->x, cur_y = dg->y;
	map[cur_y][cur_x] = 1;

	for (int i = 0; i < bound; i++) {
		switch (dirs[i]) {
		case 0: 
			cur_x += dx[0];
			cur_y += dy[0];
			break;
		case 1:
			cur_x += dx[1];
			cur_y += dy[1];
			break;
		case 2:
			cur_x += dx[2];
			cur_y += dy[2];
			break;
		case 3:
			cur_x += dx[3];
			cur_y += dy[3];
			break;
		}

		map[cur_y][cur_x] = 1;
	}
}

int CountSquares() {
	int cnt = 0;
	for (int i = 0; i < MAX_MAP_SIZE - 1; i++) {
		for (int j = 0; j < MAX_MAP_SIZE - 1; j++) {
			if (map[i][j] && map[i + 1][j] && map[i][j + 1] && map[i + 1][j + 1])
				cnt++;
		}
	}
	return cnt;
}


int main() {
	int n;
	
	/* 입력 */
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d %d %d %d", &dg[i].x, &dg[i].y, &dg[i].d, &dg[i].g);
		DrawCurves(&dg[i], SaveDirections(&dg[i]));
	}
	
	/* 출력 */
	printf("%d\n", CountSquares());

	return 0;
}