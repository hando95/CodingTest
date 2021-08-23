#define _CRT_SECURE_NO_WARNINGS
#define MAX_MAP_LEN 8
#include <stdio.h>

int map[MAX_MAP_LEN][MAX_MAP_LEN];
int watched[MAX_MAP_LEN][MAX_MAP_LEN];
int dr[4] = { -1, 0, 1, 0 };
int dc[4] = { 0, 1, 0, -1 };
int ans = 64;

int GetMin(int a, int b) {
	return a < b ? a : b;
}

/* CCTV 켜기 */
void CCTVOn(int dir, int r, int c, int n, int m) {
	int nr, nc;
	nr = r;
	nc = c;
	watched[nr][nc] = map[nr][nc];
	
	/* 해당 방향 방문 처리 */
	while (1) {
		nr += dr[dir];
		nc += dc[dir];

		/* 범위 밖이거나 벽을 만나면 탈출 */
		if (nr < 0 || nc < 0 || nr >= n || nc >= m || map[nr][nc] == 6)
			break;

		watched[nr][nc] += 1;
	}
}

/* CCTV 끄기 */
void CCTVOff(int dir, int r, int c, int n, int m) {
	int nr, nc;
	nr = r;
	nc = c;

	/* 해당 방향 미방문 처리 */
	while (1) {
		nr += dr[dir];
		nc += dc[dir];

		/* 범위 밖이거나 벽을 만나면 탈출 */
		if (nr < 0 || nc < 0 || nr >= n || nc >= m || map[nr][nc] == 6)
			break;

		watched[nr][nc] -= 1;
	}
}

/* 사각지대 개수 */
int CountBlindZone(int n, int m) {
	int count = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (watched[i][j] == 0)
				count++;
		}
	}
	return count;
}


void Surveillance(int r, int c, int n, int m) {
	/* 탐색 완료*/
	if (r == MAX_MAP_LEN - 1 && c == MAX_MAP_LEN) {
		ans = GetMin(ans, CountBlindZone(n, m));
		return;
	}

	/* 행 변경 */
	if (c == MAX_MAP_LEN) {
		Surveillance(r + 1, 0, n, m);
		return;
	}

	/* CCTV 아니면 벽 발견 */
	if (map[r][c] != 0) {
		/* 1번 CCTV */
		if (map[r][c] == 1) {
			for (int i = 0; i < 4; i++) {
				CCTVOn(i, r, c, n, m);
				Surveillance(r, c + 1, n, m);
				CCTVOff(i, r, c, n, m);
			}
		}
		/* 2번 CCTV */
		else if (map[r][c] == 2) {
			for (int i = 0; i < 2; i++) {
				CCTVOn(i, r, c, n, m);
				CCTVOn((i + 2) % 4, r, c, n, m);
				Surveillance(r, c + 1, n, m);
				CCTVOff(i, r, c, n, m);
				CCTVOff((i + 2) % 4, r, c, n, m);
			}
		}
		/* 3번 CCTV */
		else if (map[r][c] == 3) {
			for (int i = 0; i < 4; i++) {
				CCTVOn(i, r, c, n, m);
				CCTVOn((i + 1) % 4, r, c, n, m);
				Surveillance(r, c + 1, n, m);
				CCTVOff(i, r, c, n, m);
				CCTVOff((i + 1) % 4, r, c, n, m);
			}
		}
		/* 4번 CCTV */
		else if (map[r][c] == 4) {
			for (int i = 0; i < 4; i++) {
				CCTVOn(i, r, c, n, m);
				CCTVOn((i + 3) % 4, r, c, n, m);
				CCTVOn((i + 1) % 4, r, c, n, m);
				Surveillance(r, c + 1, n, m);
				CCTVOff(i, r, c, n, m);
				CCTVOff((i + 3) % 4, r, c, n, m);
				CCTVOff((i + 1) % 4, r, c, n, m);
			}
		}
		/* 5번 CCTV */
		else if (map[r][c] == 5) {
			CCTVOn(0, r, c, n, m);
			CCTVOn(1, r, c, n, m);
			CCTVOn(2, r, c, n, m);
			CCTVOn(3, r, c, n, m);
			Surveillance(r, c + 1, n, m);
			CCTVOff(0, r, c, n, m);
			CCTVOff(1, r, c, n, m);
			CCTVOff(2, r, c, n, m);
			CCTVOff(3, r, c, n, m);
		}
		/* 벽 */
		else {
			watched[r][c] = 1;
			Surveillance(r, c + 1, n, m);
		}
	}
	/* 빈 공간 */
	else
		Surveillance(r, c + 1, n, m);

}


int main() {
	int n, m;

	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &map[i][j]);
		}
	}

	Surveillance(0, 0, n, m);
	printf("%d\n", ans);
	return 0;
}