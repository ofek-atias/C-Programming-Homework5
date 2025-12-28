#include <stdio.h>

unsigned int largest_power_of_2(unsigned int n) {
  
  unsigned int res = n;

  res |= res >> 1;
  res |= res >> 2;
  res |= res >> 4;
  res |= res >> 8;
  res |= res >> 16;
  
  return res - (res >> 1); 
}

int main() {

  unsigned int n, L = 0;

  // get unsigned number from the user
  printf("Please enter an unsigned integer n:\n");
  scanf("%u", &n);

  // perform calculation
  L = largest_power_of_2(n);

  // print the result to the user
  printf("The Largest Power of 2 Smaller or Equal to %u is: %u\n", n, L);

  return 0;
}
