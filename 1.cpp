
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    pid = fork();

    if(pid < 0){
        printf("Fork failed!\n");
        return 1;
    }

    else if(pid == 0){
        printf("Child PID: %d\n", getpid());
        printf("Parent Process ID (PPID) of child: %d\n", getppid());
    }

    else{
        printf("Parent PID: %d\n", getpid());
        printf("Child PID (from parent): %d\n", pid);
        wait(NULL);
    }

    return 0;
}
