#include "shell.h"
#include "kernel.h"
#include "std_lib.h"

char username[32] = "user";
char gcname[32] = "";
int textColor = 0x07; // putih

void shell() {
  char buf[128];
  char cmd[64];
  char arg[2][64];

  printString("Welcome to EorzeOS!\n");

  while (true) {
    printString(username);
    if (gcname[0] != 0) {
      printString("@");
      printString(gcname);
    }
    printString("> ");
    readString(buf);
    parseCommand(buf, cmd, arg);

    if (strcmp(cmd, "user")) {
      if (arg[0][0] == 0) {
        strcpy(username, "user");
        printString("Username changed to user\n");
      } else {
        strcpy(username, arg[0]);
        printString("Username changed to ");
        printString(arg[0]);
        printString("\n");
      }
    } else if (strcmp(cmd, "grandcompany")) {
      if (strcmp(arg[0], "maelstrom")) {
        clearScreen();
        textColor = 0x04; // merah
        strcpy(gcname, "Storm");
      } else if (strcmp(arg[0], "twinadder")) {
        clearScreen();
        textColor = 0x0E; // kuning
        strcpy(gcname, "Serpent");
      } else if (strcmp(arg[0], "immortalflames")) {
        clearScreen();
        textColor = 0x01; // biru
        strcpy(gcname, "Flame");
      } else {
        printString("Unknown Grand Company\n");
      }
    } else if (strcmp(cmd, "clear")) {
      clearScreen();
      textColor = 0x07;
      gcname[0] = 0;
    } else if (strcmp(cmd, "add") || strcmp(cmd, "sub") || strcmp(cmd, "mul") || strcmp(cmd, "div")) {
      int a, b, res;
      char resStr[32];
      atoi(arg[0], &a);
      atoi(arg[1], &b);
      if (strcmp(cmd, "add")) res = a + b;
      if (strcmp(cmd, "sub")) res = a - b;
      if (strcmp(cmd, "mul")) res = a * b;
      if (strcmp(cmd, "div")) res = div(a, b);
      itoa(res, resStr);
      printString(resStr);
      printString("\n");
    } else if (strcmp(cmd, "yogurt")) {
      char *replies[] = {"yo", "ts unami gng </3", "sygau"};
      int tick = getBiosTick();
      printString("gurt> ");
      printString(replies[mod(tick, 3)]);
      printString("\n");
    } else {
      printString(buf);
      printString("\n");
    }
  }
}

void parseCommand(char *buf, char *cmd, char arg[2][64]) {
  int i = 0, j = 0, k = 0;
  while (buf[i] != ' ' && buf[i] != 0) {
    cmd[i] = buf[i];
    i++;
  }
  cmd[i] = 0;
  if (buf[i] == ' ') i++;
  while (buf[i] != ' ' && buf[i] != 0) {
    arg[0][j++] = buf[i++];
  }
  arg[0][j] = 0;
  if (buf[i] == ' ') i++;
  while (buf[i] != 0) {
    arg[1][k++] = buf[i++];
  }
  arg[1][k] = 0;
}
