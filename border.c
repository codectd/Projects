#include<stdio.h>
#include <stdbool.h>
int main(int argc, char const *argv[])
{
  char inString[20];

  printf("William\n");//my name print out
  printf("Please enter a string: \n");
  scanf("%s", inString);
  int inStringLen = 0;
  while(true)
  {
    if (inString[inStringLen] == 0)
      break;
    else
      inStringLen++;
  }
  for(int i = 0; i < inStringLen + 2; i++)
  {
    printf("*");
  }
  printf("\n");
  printf("*%s*\n", inString);
  for(int i = 0; i < inStringLen + 2; i++)
  {
    printf("*");
  }
  printf("\n");

  return 0;
}
