#include "std_lib.h"

int div(int a, int b) {
  int neg = 0, res = 0;
  if (a < 0) { a = -a; neg = !neg; }
  if (b < 0) { b = -b; neg = !neg; }
  while (a >= b) { a -= b; res++; }
  return neg ? -res : res;
}

int mod(int a, int b) {
  int neg = a < 0;
  if (a < 0) a = -a;
  if (b < 0) b = -b;
  while (a >= b) a -= b;
  return neg ? -a : a;
}

bool strcmp(char *s1, char *s2) {
  while (*s1 && *s2) {
    if (*s1 != *s2) return false;
    s1++; s2++;
  }
  return *s1 == *s2;
}

void strcpy(char *dst, char *src) {
  while (*src) *dst++ = *src++;
  *dst = 0;
}

void clear(byte *buf, unsigned int size) {
  for (int i = 0; i < size; i++) buf[i] = 0;
}

void atoi(char *str, int *num) {
  int sign = 1;
  *num = 0;
  if (*str == '-') { sign = -1; str++; }
  while (*str) *num = *num * 10 + (*str++ - '0');
  *num *= sign;
}

void itoa(int num, char *str) {
  int i = 0, neg = 0;
  if (num < 0) { neg = 1; num = -num; }
  do {
    str[i++] = num % 10 + '0';
    num /= 10;
  } while (num);
  if (neg) str[i++] = '-';
  str[i] = 0;
  for (int j = 0; j < i / 2; j++) {
    char t = str[j]; str[j] = str[i - j - 1]; str[i - j - 1] = t;
  }
}
