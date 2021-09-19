#define _CRT_SECURE_NO_WARNINGS
#define MAX_DISTANCE 1000000000
#define MAX_CITY_LEN 51
#define MAX_HOUSE_NUM 100
#define MAX_STORE_NUM 13
#include <stdio.h>
#include <math.h>

/* 좌표형 구조체 */
typedef struct {
	int r, c;
}Coordtype;

int city[MAX_CITY_LEN][MAX_CITY_LEN];
int selected[MAX_STORE_NUM];
int ans = MAX_DISTANCE;

Coordtype house[MAX_HOUSE_NUM];
Coordtype store[MAX_STORE_NUM];

/* 최소값 반환 함수 */
int GetMin(int a, int b) {
	return a < b ? a : b;
}

/* 치킨집 m개 선정 함수 */
void FindChkHouse(int cnt, int idx, int m, int store_num, int house_num) {
	int dis, min_dis;
	int dis_sum = 0;

	/* 인덱스가 치킨집을 넘어가면 종료 */
	if (idx > store_num)
		return;

	/* 치킨집 m개 선택 완료 */
	if (cnt == m) {
		for (int i = 0; i < house_num; i++) {
			min_dis = MAX_DISTANCE;

			for (int j = 0; j < store_num; j++) {
				if (selected[j]) {
					dis = abs(store[j].r - house[i].r) + abs(store[j].c - house[i].c);
					min_dis = GetMin(min_dis, dis);
				}
			}

			dis_sum += min_dis;
		}

		ans = GetMin(ans, dis_sum);
		return;
	}

	/* 해당 치킨집 선정 */
	selected[idx] = 1;
	FindChkHouse(cnt + 1, idx + 1, m, store_num, house_num);

	/* 해당 치킨집 미선정 */
	selected[idx] = 0;
	FindChkHouse(cnt, idx + 1, m, store_num, house_num);

	return;
}

int main() {
	int n;              // 도시 길이
	int m;              // 치킨집 선정 수
	int store_num = 0;  // 치킨집 수
	int house_num = 0;  // 가정집 수

	/* 도시 정보 */
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%d", &city[i][j]);

			if (city[i][j] == 1) {
				house[house_num].r = i;
				house[house_num].c = j;
				house_num++;
			}

			else if (city[i][j] == 2) {
				store[store_num].r = i;
				store[store_num].c = j;
				store_num++;
			}
		}
	}

	/* 최소 치킨 거리 구하기 */
	FindChkHouse(0, 0, m, store_num, house_num);
	printf("%d\n", ans);
	return 0;
}