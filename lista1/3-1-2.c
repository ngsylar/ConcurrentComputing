/* UnB - CIC - 2019/2
Programacao Concorrente
Gabriel Sylar */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main () {
  pid_t pid;
  pid_t p0;
  pid_t p1;
  int p1_status;

  pid = fork();
  if (!pid)
    p1 = getpid();
  p0 = pid && fork();

  if (p0) {
    printf("P0: Sou pai de dois\n");
    waitpid(pid, &p1_status, WUNTRACED);
    while (1) {
      if (WIFEXITED(p1_status)) {
        printf("P0: Acho que meus filhos terminaram suas execuções.\n");
        break;
      }
    }
  } else if (getpid() == p1) {
    sleep(2);
    printf("P1: Sou o filho mais velho e dormi um pouco.\n");
    printf("P1: Sou o filho %d e estou terminando agora.\n", getpid());
  } else {
    printf("P2: Sou o filho mais novo.\n");
    printf("P2: Sou o filho %d e estou terminando agora.\n", getpid());
  }

  return 0;
}
