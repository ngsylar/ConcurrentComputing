/* UnB - CIC - 2019/2
Programacao Concorrente
Gabriel Sylar */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main () {
  int number;
  char letter[100];

  printf("Insira um numero de 1 a 9: ");
  scanf("%s", letter);
  while (strlen(letter) > 1 || letter[0] < 49 || letter[0] > 57) {
    printf("Eu disse de UM a NOVE: ");
    setbuf(stdin, NULL);
    scanf("%s", letter);
  }
  setbuf(stdin, NULL);
  number = letter[0] - 48;

  if (number > 1) {
    pid_t pid = fork();
    while (number != 2) {
      pid = pid && fork();
      wait(NULL);
      number--;
    }
  }
  printf("Sou o processo %d e o PID do meu criador eh %d\n", getpid(), getppid());

  return 0;
}
