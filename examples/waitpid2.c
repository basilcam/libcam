#include <cam/sys/process.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>

const int N = 10;

int main() {
    pid_t pids[N];
   
    for (int i = 0; i < N; i++) {
        if ((pids[i] = Cam_fork())== 0) {
            exit(100 + i);
        }
    }

    for (int i = 0; i < N; i++) {
        int status;
        pid_t pid = waitpid(pids[i], &status, 0);

        if (pid == -1) {
            Cam_handleUnixErrora("waitpid error");
        }
            
        if (WIFEXITED(status)) {
            printf("Child %d terminated normally with exit status %d\n", pid, WEXITSTATUS(status));
        } else {
            printf("Child %d terminated abnormally\n", pid);
        }
    }

    return EXIT_SUCCESS;
}

