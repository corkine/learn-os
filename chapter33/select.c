#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <winsock.h>

int main(int argc, char** argv) {
    while (1) {
        fd_set readFDs;
        FD_ZERO(&readFDs);
        int fd;
        for (fd = minFD; fd < maxFD; fd++)
            FD_SET(fd, &readFDs);
        int rc = select(maxFD+1,&readFDs, NULL,NULL,NULL);
        int fd;
        for (fd = minFD; fd < maxFD; fd++)
            if (FD_ISSET(fd, &readFDs))
                processFD(fd);
    }
}