#include <stdbool.h>
#include <stdio.h>

bool is_binary_palindrome(unsigned int n) 
{
  int msb_idx = -1;
  unsigned int temp = n;
  unsigned int reversed = 0;
  while (temp != 0)
  {
    temp >>= 1;
    msb_idx += 1;
  }

  if (msb_idx == -1)
    msb_idx = 0;

  temp = n;

  for (int j = 0; j <= msb_idx; j++)
  {
    reversed <<= 1;
    reversed |= (temp & 1);
    temp >>= 1;
  }

  if (n == reversed)
    return true;
  else 
    return false;
}

int main() {

  unsigned int n;
  bool result;

  // get unsigned number from the user
  printf("Please enter an unsigned integer n:\n");
  scanf("%u", &n);

  // check condition
  result = is_binary_palindrome(n);

  // print the result to the user
  printf("The binary representation of %u is %s\n", n,
         result ? "a palindrome" : "not a palindrome");

  return 0;
}
