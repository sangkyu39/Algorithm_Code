#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int H[100], n = 0;

void swap(int *x, int *y);
void insertItem(int key);
int removeMax();
void upHeap(int idx);
void downHeap(int idx);
void printHeap();

int main() {
	char cmd;
	int key = 0;

	while (1) {
		scanf("%c", &cmd);

		//finish
		if (cmd == 'q') {
			break;
		}
		//키 삽입
		else if (cmd == 'i') {
			scanf("%d", &key);
			getchar();
			insertItem(key);
			printf("0\n"); //
		}
		//키 삭제
		else if (cmd == 'd') {
			printf("%d\n", removeMax());
		}
		//인쇄
		else if (cmd == 'p') {
			printHeap();
		}
		
	}
}

void swap(int *x, int *y) {
	int tmp = *x;
	*x = *y;
	*y = tmp;
}

void insertItem(int key) {
	n += 1;
	H[n] = key;
	upHeap(n);
}

void upHeap(int idx) {
	if (idx == 1) {
		return;
	}
	else if (H[idx] > H[idx/2]) {
		swap(&H[idx/2], &H[idx]);
		upHeap(idx / 2);
	}
}

int removeMax() {
	int key = H[1];
	H[1] = H[n];
	n -= 1;
	downHeap(1);
	return key; 
}

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

void printHeap() {
	for (int i = 1;i <= n;i++) {
		printf(" %d", H[i]);
	}
	printf("\n");
}