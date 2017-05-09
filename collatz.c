#include<stdio.h>
#include <stdbool.h>
int main(int argc, char const *argv[])
{
  int n;

  printf("William\n");//my name print out
  printf("Please enter an integer: \n");
  scanf("%d", &n);

  while(true)
  {
    if((n % 2) != 0)
      n = 3 * n + 1;
    else
      n = n / 2;
    printf("The integer is: %d\n", n);

    if(n == 1)
      break;
  }
  exit(0);
  return 0;
}
