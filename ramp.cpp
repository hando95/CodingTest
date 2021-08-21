#define _CRT_SECURE_NO_WARNINGS
#define MAX_MAP_LEN 100
#include <stdio.h>

int map[MAX_MAP_LEN][MAX_MAP_LEN];

int ColRoad(int n, int l) {
	int road_cnt = 0;
	int cur_h;
	int down_ramp, up_ramp;
	int no_road;
	int top;                  
	/* 
	top 변수 
	오르막 -> 내리막 시 평지 확인을 건너뛰기 위한 장치
	*/

	for (int j = 0; j < n; j++) {
		cur_h = map[0][j];
		down_ramp = 0, up_ramp = 0;
		top = 1;
		no_road = 0;

		for (int i = 0; i < n; i++) {
			/* 평지 */
			if (map[i][j] == cur_h) {
				if (down_ramp > 0)
					down_ramp--;
				else
					up_ramp++;
			}

			/* 오르막 */
			else if (map[i][j] == cur_h + 1) {

				/* 경사로 길이 확인 */
				if (up_ramp >= l)
					up_ramp = 1;
				else {
					no_road = 1;
					break;
				}

				top = 1;
				cur_h++;
			}

			/* 내리막 */
			else if (map[i][j] == cur_h - 1) {

				/* 오르막 -> 내리막 */
				if (top) {
					down_ramp = l - 1;
				}

				/* 내리막 -> 내리막 */
				else {
					/* 경사로 길이 확인 */
					if (down_ramp == 0)
						down_ramp = l - 1;
					else {
						no_road = 1;
						break;
					}
				}

				top = 0;
				up_ramp = 0;
				cur_h--;
			}

			/* 2층 이상 차이 */
			else {
				no_road = 1;
				break;
			}
		}

		/* 지도 끝에서 아직 내리막 경사로가 끝나지 않았으면 */
		if (down_ramp > 0)
			no_road = 1;

		if (!no_road)
			road_cnt++;
	}
	return road_cnt;
}

int RowRoad(int n, int l) {
	int road_cnt = 0;
	int cur_h;
	int down_ramp, up_ramp;
	int no_road;
	int top;
	/*
	top 변수
	오르막 -> 내리막 시 평지 확인을 건너뛰기 위한 장치
	*/

	for (int i = 0; i < n; i++) {
		cur_h = map[i][0];
		down_ramp = 0, up_ramp = 0;
		top = 1;
		no_road = 0;

		for (int j = 0; j < n; j++) {
			/* 평지 */
			if (map[i][j] == cur_h) {
				if (down_ramp > 0)
					down_ramp--;
				else
					up_ramp++;
			}

			/* 오르막 */
			else if (map[i][j] == cur_h + 1) {

				/* 경사로 길이 확인 */
				if (up_ramp >= l)
					up_ramp = 1;
				else {
					no_road = 1;
					break;
				}

				top = 1;
				cur_h++;
			}

			/* 내리막 */
			else if (map[i][j] == cur_h - 1) {

				/* 오르막 -> 내리막 */
				if (top) {
					down_ramp = l - 1;
				}

				/* 내리막 -> 내리막 */
				else {
					/* 경사로 길이 확인 */
					if (down_ramp == 0)
						down_ramp = l - 1;
					else {
						no_road = 1;
						break;
					}
				}

				top = 0;
				up_ramp = 0;
				cur_h--;
			}

			/* 2층 이상 차이 */
			else {
				no_road = 1;
				break;
			}
		}

		/* 지도 끝에서 아직 내리막 경사로가 끝나지 않았으면 */
		if (down_ramp > 0)
			no_road = 1;

		if (!no_road)
			road_cnt++;
	}
	return road_cnt;
}

int main() {
	int n, l;

	scanf("%d %d", &n, &l);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &map[i][j]);
		}
	}

	printf("%d\n", ColRoad(n, l) + RowRoad(n, l));
	return 0;
}