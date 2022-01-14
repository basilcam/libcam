#include <cam/sys/process.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>

const int N = 2;

int main() {
   
    for (int i = 0; i < N; i++) {
        if (cam_fork() == 0) { // Child process
            exit(100 + i);
        }
    }

    pid_t pid;
    int status;
    while ((pid = wait(&status)) > 0) {
        if (WIFEXITED(status)) {
            printf("Child %d terminated normally with exit status %d\n", pid, WEXITSTATUS(status));
        } else {
            printf("Child %d terminated abnormally\n", pid);
        }
    }

    if (errno != ECHILD) {
        cam_handle_unix_error("waitpid error");
    }

    return EXIT_SUCCESS;
}

