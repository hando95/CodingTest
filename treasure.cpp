#define _CRT_SECURE_NO_WARNINGS
#define MAX_ARRAY_SIZE 50
#include <stdio.h>

int a[MAX_ARRAY_SIZE];
int b[MAX_ARRAY_SIZE];
int a_sorted[MAX_ARRAY_SIZE];
int b_sorted[MAX_ARRAY_SIZE];


void Merge(int left, int mid, int right, char arraytype) {
	int i, j, k;
	i = left;
	j = mid + 1;
	k = left;

	/* 오름차순 */
	if (arraytype == 'a') {
		while (i <= mid && j <= right) {
			if (a[i] <= a[j])
				a_sorted[k++] = a[i++];
			else
				a_sorted[k++] = a[j++];
		}

		if (i > mid) {
			for (int l = j; l <= right; l++)
				a_sorted[k++] = a[l];
		}
		else {
			for (int l = i; l <= mid; l++)
				a_sorted[k++] = a[l];
		}

		for (int l = left; l <= right; l++)
			a[l] = a_sorted[l];
	}
	
	/* 내림차순 */
	else if (arraytype == 'b') {
		while (i <= mid && j <= right) {
			if (b[i] >= b[j])
				b_sorted[k++] = b[i++];
			else
				b_sorted[k++] = b[j++];
		}

		if (i > mid) {
			for (int l = j; l <= right; l++)
				b_sorted[k++] = b[l];
		}
		else {
			for (int l = i; l <= mid; l++)
				b_sorted[k++] = b[l];
		}

		for (int l = left; l <= right; l++)
			b[l] = b_sorted[l];
	}
}

void MergeSort(int left, int right, char arraytype) {
	int mid;
	if (left < right) {
		mid = (left + right) / 2;
		MergeSort(left, mid, arraytype);
		MergeSort(mid + 1, right, arraytype);
		Merge(left, mid, right, arraytype);
	}
}

int Calculate(int n) {
	int s = 0;
	for (int i = 0; i < n; i++)
		s += (a[i] * b[i]);
	return s;
}

int main() {
	int n;
	
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
	for (int i = 0; i < n; i++) {
		scanf("%d", &b[i]);
	}

	MergeSort(0, n - 1, 'a');
	MergeSort(0, n - 1, 'b');
	printf("%d\n", Calculate(n));
	return 0;
}