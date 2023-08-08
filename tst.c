#include <stdio.h>

#ifndef P1
#define P1 2
#define P2 9
#define P3 5
#endif

#ifndef TEST
#define TEST xoroshiro
#endif

#define MASK (0777777777777ULL)
typedef unsigned long long word_t;
static word_t s[2];

static word_t rotl(word_t x, int n)
{
  x &= MASK;
  x = (x << n) | (x >> (36 - n));
  return x & MASK;
}

word_t xoroshiro(void)
{
  word_t s0 = s[0];
  word_t s1 = s[1];
  word_t result_plus = s0 + s1;
  word_t result_plusplus = rotl(s0 + s1, 11) + s0;
  s1 ^= s0;
  s[0] = rotl(s0, P1) ^ s1 ^ ((s1 << P2) & MASK);
  s[1] = rotl(s1, P3);
  //word_t result_plusplus = rotl(s[0] + s[1], 11) + s[0];
  //printf("%012llo\n", result_plusplus & MASK);
  return result_plusplus & MASK;
}

word_t xorshift(void)
{
  word_t s1 = s[0];
  word_t s0 = s[1];
  word_t result = (s0 + s1) & MASK;
  s[0] = s0;
  s1 ^= (s1 << P1) & MASK;
  s1 ^= s0;
  s1 ^= s1 >> P2;
  s1 ^= s0 >> P3;
  s[1] = s1;
  return result;
}

int main(void)
{
  int i;
  word_t result;
  s[0] = 0777777000000ULL;
  s[1] = 1ULL;
  for (i = 0; i < 1000000; i++)
    TEST();
  for (;;) {
    result = TEST();
    result >>= 0;
    putchar(result & 0xFF);
    result >>= 8;
    putchar(result & 0xFF);
    result >>= 8;
    putchar(result & 0xFF);
    result >>= 8;
    putchar(result & 0xFF);
  }
}
