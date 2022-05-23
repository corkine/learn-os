#include <stdio.h>
#include <unistd.h> //for fork, getpid
#include <sys/wait.h> //for wait
#include <fcntl.h> //for open
#include <stdlib.h> //for exit
#include "common.h"
#include <string.h>

/// fork 本质意味着复制和隔离
void question1() {
    int x = 100;
    printf("x in father: %d\n", x);
    pid_t sub = fork();
    if (sub == 0) {
        x = 10;
        printf("x in sub: %d\n", x);
    } else {
        x = 200;
        printf("x in father after sub fork: %d\n", x);
        wait(NULL);
        printf("x in father after sub return: %d\n", x);
    }
}

/// 但是文件描述符可以共享
void question2() {
    int fd = open("temp.log",O_CREAT|O_WRONLY|O_TRUNC,S_IRWXU);
    write(fd, "hello", 5);
    pid_t p = fork();
    if (p == 0) {
        write(fd, " with sub\n", 10);
        close(fd);
        exit(0);
    } else {
        write(fd, " with father\n", 13);
        wait(NULL);
        write(fd, " after sub close\n", 17);
    }
}

/// 如何保证父进程在子进程之后 printf? 换言之，如何通信？
/// kill or read pipe or read file or just spin
void question3() {
    //volatile int afterSubWait = 0;
    pid_t p = fork();
    if (p == 0) {
        fprintf(stdout, "hello");
        //afterSubWait = 1;
        exit(0);
    } else {
        // while (!afterSubWait) {
        //     Spin(1);
        //     printf("res is %d\n", afterSubWait);
        // }
        Spin(1);
        fprintf(stdout, "goodbye");
    }
}

void question3_2() {
    int pipe_fd[2]; //I&O
    pipe(pipe_fd);
    pid_t p = fork();
    if (p == 0) {
        printf("HELLO\n");
        close(pipe_fd[0]);
        //stdin as output write c
        write(pipe_fd[1], "c", 1); 
        close(pipe_fd[1]);
    } else {
        close(pipe_fd[1]);
        char c;
        //stdin as input read c, block
        read(pipe_fd[0], &c, 1);
        close(pipe_fd[0]);
        printf("goodbye\n");
    }
}

/// exec 系列函数的变体展示
void question4() {
    int rc = fork();
    if (rc == 0) {
        char *myargs[3];
        myargs[0] = strdup("ls");
        myargs[1] = strdup("-lh");
        myargs[2] = NULL;
        //xxxxl with list args and NULL at end
        //xxxxv with variable arg
        //xxxxp not need path, search path
        //xxxxe with environ variables

        execl("/bin/ls","ls","-lh",NULL);
        execle("/bin/ls", "ls", NULL);
        execlp("ls", "-lh", NULL);
        execv("/bin/ls", myargs);
        execvp("ls", myargs);
        execvP("ls", "/bin", myargs);
    } else {
        wait(NULL);
    }
}

/// wait 默认返回第一个退出的子进程，子进程 wait 会失败返回 -1
/// waitpid 相比较 wait 提供了更精细的能力和更丰富的策略
void question5_6() {
    pid_t p = fork();
    if (p == 0) {
        printf("s pid is %d\n", (int)getpid());
        pid_t r = wait(NULL);
        printf("in sub wait returns %d\n", (int)r);
        exit(0);
    } else {
        printf("f pid is %d\n", (int)getpid());
        //pid_t r = wait(NULL);
        //printf("wait returns %d\n", (int)r);
        // f pid is 66135
        // s pid is 66155
        // in sub wait returns -1
        // wait returns 66155
        //wait 仅等待任意一个子进程结束
        //waitpid pid>0 则等待特定进程, 反之等待所有子进程，
        //options WNOHANG 子进程均未终止则立刻返回 0, 反之挂起并等待
        //WUNTRACED 等待任一终止，返回其 pid
        //WCONTINUED 挂起并等待一个运行进程终止或停止进程启动
        //WNOHANG|WUNTRACED 全部都在运行，返回0，任一停止，返回其PID
        pid_t r = waitpid(-1, NULL, WNOHANG);
        printf("wait returns %d\n", (int)r);
    }
}

/// 关闭子进程输入后 printf 数据会丢失
void question7() {
    printf("current is (pid:%d)\n", (int)getpid());
    int rc = fork();
    if (rc == 0) {
        printf("on child (pid:%d)\n", (int)getpid());
        close(STDOUT_FILENO);
        //open("./output.log", O_CREAT|O_WRONLY|O_TRUNC,S_IRWXU);
        printf("never exec no stdout!\n");
    } else {
        int wc = wait(NULL); //wait all
        printf("on parent %d (wc:%d) (pid:%d)\n", rc, wc, (int)getpid());
    }
}

void question8() {
    printf("current is (pid:%d)\n", (int)getpid());
    int rc = fork();
    int rc2 = fork();
    if (rc == 0 && rc2 != 0) {
        printf("on child (pid:%d)\n", (int)getpid());
        exit(0);
    } else if (rc2 == 0 && rc != 0) {
        printf("on child2 (pid:%d)\n", (int)getpid());
        exit(0);
    } else if (rc != 0 && rc2 != 0) {
        int wc = wait(NULL); //wait all
        printf("on parent (wc:%d) (pid:%d)\n", wc, (int)getpid());
    }
}

/// 使用管道在两个子进程之间传递数据
/// 这里也展示了创建多个子进程的方法，不能写成上面的样子↑
void question8_2() {
    int pipe_fd[2];
    pid_t rc[2];
    pipe(pipe_fd);
    rc[0] = fork();
    if (rc[0] == 0) { //sub1 here
        close(pipe_fd[0]);
        dup2(pipe_fd[1], STDOUT_FILENO);
        printf("hello");
    } else {
        rc[1] = fork();
        if (rc[1] == 0) { //sub2 here
            close(pipe_fd[1]);
            dup2(pipe_fd[0], STDIN_FILENO);
            char pipe_data[6];
            read(STDIN_FILENO, pipe_data, 6);
            printf("read from pipe result is: %s\n", pipe_data);
        }
        //father here
        waitpid(rc[0], NULL, 0);
        waitpid(rc[1], NULL, 0);
        printf("end of code\n");
        //read from pipe result is: HELLO
        //end of code
    }
}

int main() {
    question7();
}