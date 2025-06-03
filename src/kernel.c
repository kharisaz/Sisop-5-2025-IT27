#include "shell.h"
#include "kernel.h"

int main() {
  clearScreen();
  shell();
}

void printString(char *str) {
  while (*str) {
    interrupt(0x10, 0x0E00 + *str, textColor << 8, 0, 0);
    str++;
  }
}

void readString(char *buf) {
  int i = 0;
  char c;
  while (1) {
    c = interrupt(0x16, 0, 0, 0, 0);
    if (c == 13) break;
    if (c == 8 && i > 0) {
      i--;
      printString("\b \b");
    } else if (c != 8) {
      buf[i++] = c;
      interrupt(0x10, 0x0E00 + c, textColor << 8, 0, 0);
    }
  }
  buf[i] = 0;
  printString("\n");
}

void clearScreen() {
  int i;
  for (i = 0; i < 2000; i++) {
    putInMemory(0xB000, i * 2, ' ');
    putInMemory(0xB000, i * 2 + 1, textColor);
  }
  interrupt(0x10, 0x0200, 0, 0, 0);
}
