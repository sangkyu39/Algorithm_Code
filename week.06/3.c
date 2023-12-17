#include <stdio.h>
#include <stdlib.h>

int main()
{
  int left, right, cnt;
  char answer;

  scanf("%d %d %d", &left, &right, &cnt);
  getchar();

  for (int i = 0; i < cnt; i++)
  {
    int mid = (left + right) / 2;
    scanf("%c", &answer);

    if (answer == 'Y')
    {
      left = mid + 1;
    }
    else if (answer == 'N')
    {
      right = mid;
    }
  }
  printf("%d", left);
  return 0;
}