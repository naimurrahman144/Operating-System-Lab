#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(){
    pid_t child1,child2;

    child1=fork();

    if(child1<0){
        printf("faild fork of child 1");
        return 1;
    }
    if(child1==0){
        printf("child 1 : %d",getpid());
        printf(" | parent : %d \n",getppid());
        return 0;
    }

    child2=fork();

    if(child2<0){
        printf("faild fork of child 2");
        return 1;
    }
    if(child2==0){
        printf("child 2 : %d",getpid());
        printf(" | parent : %d \n",getppid());
        return 0;
    }

    // parent process
    printf("parent : %d\n",getpid());
    printf("|-child 1 : %d\n",child1);
    printf("|-child 2 : %d\n",child2);

    wait(NULL);
    wait(NULL);

    return 0;

}
