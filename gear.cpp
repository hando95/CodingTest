#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef struct {
	int s[8];
}Geartype;

Geartype gear[4];

void RotateOneGear(int g_num, int dir) {
	int temp;

	switch (dir) {
	case 1:
		temp = gear[g_num].s[0];
		gear[g_num].s[0] = gear[g_num].s[7];
		gear[g_num].s[7] = gear[g_num].s[6];
		gear[g_num].s[6] = gear[g_num].s[5];
		gear[g_num].s[5] = gear[g_num].s[4];
		gear[g_num].s[4] = gear[g_num].s[3];
		gear[g_num].s[3] = gear[g_num].s[2];
		gear[g_num].s[2] = gear[g_num].s[1];
		gear[g_num].s[1] = temp;
		break;
	case -1:
		temp = gear[g_num].s[0];
		gear[g_num].s[0] = gear[g_num].s[1];
		gear[g_num].s[1] = gear[g_num].s[2];
		gear[g_num].s[2] = gear[g_num].s[3];
		gear[g_num].s[3] = gear[g_num].s[4];
		gear[g_num].s[4] = gear[g_num].s[5];
		gear[g_num].s[5] = gear[g_num].s[6];
		gear[g_num].s[6] = gear[g_num].s[7];
		gear[g_num].s[7] = temp;
		break;
	default:
		break;
	}
}

void RotateAllGears(int g_num, int dir) {
	int direction[4] = { 0, };

	if (g_num == 0) {
		direction[0] = dir;

		/* 0-1번, 1-2번, 2-3번 */
		if (gear[0].s[2] != gear[1].s[6])
			direction[1] = (-1 * direction[0]);
		if (gear[1].s[2] != gear[2].s[6])
			direction[2] = (-1 * direction[1]);
		if (gear[2].s[2] != gear[3].s[6]) {
			direction[3] = (-1 * direction[2]);
		}
	}

	if (g_num == 1) {
		direction[1] = dir;

		/* 1-0번, 1-2번, 2-3번 */
		if (gear[1].s[6] != gear[0].s[2])
			direction[0] = (-1 * direction[1]);
		if (gear[1].s[2] != gear[2].s[6])
			direction[2] = (-1 * direction[1]);
		if (gear[2].s[2] != gear[3].s[6]) {
			direction[3] = (-1 * direction[2]);
		}
	}

	if (g_num == 2) {
		direction[2] = dir;

		/* 2-1번, 1-0번, 2-3번 */
		if (gear[2].s[6] != gear[1].s[2])
			direction[1] = (-1 * direction[2]);
		if (gear[1].s[6] != gear[0].s[2])
			direction[0] = (-1 * direction[1]);
		if (gear[2].s[2] != gear[3].s[6]) {
			direction[3] = (-1 * direction[2]);
		}
	}

	if (g_num == 3) {
		direction[3] = dir;

		/* 3-2번, 2-1번, 1-0번 */
		if (gear[3].s[6] != gear[2].s[2])
			direction[2] = (-1 * direction[3]);
		if (gear[2].s[6] != gear[1].s[2])
			direction[1] = (-1 * direction[2]);
		if (gear[1].s[6] != gear[0].s[2]) {
			direction[0] = (-1 * direction[1]);
		}
	}



	for (int i = 0; i < 4; i++) {
		RotateOneGear(i, direction[i]);
	}
}

int GetPoint() {
	int point = 0;
	if (gear[0].s[0] == 1)
		point += 1;
	if (gear[1].s[0] == 1)
		point += 2;
	if (gear[2].s[0] == 1)
		point += 4;
	if (gear[3].s[0] == 1)
		point += 8;
	return point;
}

int main() {
	char temp[4][9];
	int k;
	int g_num, dir;

	/* 입력 */
	for (int i = 0; i < 4; i++) {
		scanf("%s", temp[i]);
		for (int j = 0; j < 8; j++) {
			gear[i].s[j] = temp[i][j] - '0';
		}
	}

	/* 회전 입력 시마다 톱니바퀴 돌리기 */
	scanf("%d", &k);
	for (int i = 0; i < k; i++) {
		scanf("%d %d", &g_num, &dir);
		RotateAllGears(g_num - 1, dir);
	}

	/* 출력 */
	printf("%d\n", GetPoint());
	return 0;
}