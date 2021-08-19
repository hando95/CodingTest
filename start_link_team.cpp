#define _CRT_SECURE_NO_WARNINGS
#define MAX_MEMBER 20
#include <stdio.h>

int stat[MAX_MEMBER][MAX_MEMBER];
int team_member[MAX_MEMBER];
int ans = 1800;

int GetMin(int a, int b) {
	return a < b ? a : b;
}

/* 팀 차이 */
int TeamDifference(int n) {
	int start_stat = 0;
	int link_stat = 0;
	
	/* 1이면 start팀, 0이면 link팀 */
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {

			/* 스타트팀 스탯합 */
			if (team_member[i] && team_member[j])
				start_stat += (stat[i][j] + stat[j][i]);

			/* 링크팀 스탯합 */
			else if (!team_member[i] && !team_member[j])
				link_stat += (stat[i][j] + stat[j][i]);
		}
	}

	return start_stat < link_stat ? (link_stat - start_stat) : (start_stat - link_stat);
}


void MakeTeam(int n, int cnt, int idx) {

	/* 종료 조건 */
	if (cnt == n / 2) {
		ans = GetMin(ans, TeamDifference(n));
	}

	/* 팀 선택 후 다음 사람으로 넘어가기 */
	for (int i = idx; i < n; i++) {
		if (team_member[i] == 0) {
			team_member[i] = 1;
			MakeTeam(n, cnt + 1, i + 1);
			team_member[i] = 0;
		}
	}
}

int main() {
	int n;

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &stat[i][j]);
		}
	}

	MakeTeam(n, 0, 0);

	printf("%d\n", ans);
	return 0;
}