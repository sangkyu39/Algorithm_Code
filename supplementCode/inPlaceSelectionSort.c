#include <stdio.h>
#include <stdio.h>
#include <string.h>

#define swap(a, b) \
	do               \
	{                \
		int tmp = (a); \
		(a) = (b);     \
		(b) = tmp;     \
	} while (0)

/// @brief 배열 arr을 오름차순으로 정렬 (선택정렬)
/// @param arr
/// @param n
void inPlaceSelectionSort(int *arr, int n)
{
	for (int pass = 0; pass < n - 1; pass++)
	{
		int minLoc = pass;
		for (int j = pass + 1; j < n; j++)
		{
			if (arr[j] < arr[minLoc])
				minLoc = j;
		}
		swap(arr[pass], arr[minLoc]);
	}
}

int main()
{
	int n;

	scanf("%d", &n);
	int *arr = (int *)calloc(n, sizeof(int));

	for (int i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
	}

	inPlaceSelectionSort(arr, n);

	for (int i = 0; i < n; i++)
	{
		printf(" %d", arr[i]);
	}

	return 0;
}