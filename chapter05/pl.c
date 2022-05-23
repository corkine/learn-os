#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char **argv) {
    printf("current is (pid:%d)\n", 
            (int)getpid());
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("on child (pid:%d)\n", 
                (int)getpid());
        close(STDOUT_FILENO);
        open("./output.log", O_CREAT|O_WRONLY|O_TRUNC,S_IRWXU);
        char *myargs[3];
        myargs[0] = strdup("wc");
        myargs[1] = strdup("pl.c");
        myargs[2] = NULL;
        execvp(myargs[0], myargs);
        printf("never exec here!\n");
    } else {
        int wc = wait(NULL); //wait all
        printf("on parent %d (wc:%d) (pid:%d)\n", 
                rc, wc, (int)getpid());
    }
    return 0;
}