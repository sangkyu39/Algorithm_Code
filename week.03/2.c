#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int H[100], n = 0;

void swap(int *x, int *y);
void printHeap();
void downHeap(int idx);
void rBuildHeap(int idx);
void BuildHeap();

int main() {

	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		scanf("%d", &H[i]);
	}
	rBuildHeap(1);
	printHeap();

	return 0;
}

void printHeap() {
	for (int i = 1;i <= n;i++) {
		printf(" %d", H[i]);
	}
	printf("\n");
}

void swap(int *x, int *y) {
	int tmp = *x;
	*x = *y;
	*y = tmp;
}
// downHeap은 해당 위치에 맞는 값을 가져오는 것이 아는 처음 있던 값을 알맞은 위치에 옮기는 과정
void downHeap(int idx) {
	int left = idx * 2;
	int right = idx * 2 + 1;

	//자식 노드가 없는 경우
	if (left > n) {
		return;
	}
	
	int biggerIdx = left;
	
	//오른쪽 자식 노드가 있는 경우 -> 왼쪽과 오른쪽 중 더 큰 자식 노드 선택
	if (right <= n) {
		biggerIdx = (H[right] > H[left]) ? right : left;
	}

	//자식 노드가 더 클 시 swap
	if (H[biggerIdx] > H[idx]) {
		swap(&H[biggerIdx], &H[idx]);
		downHeap(biggerIdx);
	}
}
//재귀 방식 알고리즘
void rBuildHeap(int idx) {
	if (idx > n) {
		return;
	}
	rBuildHeap(2 * idx);
	rBuildHeap(2 * idx + 1);
	downHeap(idx);
}
//비재귀 방식 알고리즘
void BuildHeap() {
	for (int i = n / 2;i >= 1;i--) {
		downHeap(i);
	}
}