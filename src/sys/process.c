#include <cam/sys/process.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

void cam_handle_unix_error(char *message)
{
    fprintf(stderr, "%s: %s\n", message, strerror(errno));
    exit(EXIT_SUCCESS);
}

pid_t cam_fork() {
    pid_t pid = fork();

    if (pid < 0) {
        cam_handle_unix_error("fork error");
    }

    return pid;
}

void cam_execve(const char *filename, char *const argv[], char *const envp[]) {
    if (execve(filename, argv, envp) < 0) {
        cam_handle_unix_error("execve error");
    }
}

pid_t cam_waitpid(pid_t pid, int *status_code, int options) {
    pid_t retpid = waitpid(pid, status_code, options);

    if (retpid < 0) {
        cam_handle_unix_error("waitpid error");
    }

    return retpid;
}

pid_t cam_wait(int *status) {
    pid_t pid = wait(status);

    if (pid < 0) {
        cam_handle_unix_error("wait error");
    }

    return pid;
}

void cam_kill(pid_t pid, int signal_number) {
    if (kill(pid, signal_number) < 0) {
        cam_handle_unix_error("kill error");
    }
}

unsigned int cam_sleep(unsigned int duration_secs) {
    unsigned int return_code = sleep(duration_secs);

    if (return_code < 0) {
        cam_handle_unix_error("sleep error");
    }

    return return_code;
}

void cam_pause() {
    pause();
}

unsigned int cam_alarm(unsigned int delay_secs) {
    return alarm(delay_secs);
}

void cam_setpgid(pid_t pid, pid_t group_id) {
    int return_code = setpgid(pid, group_id);

    if (return_code < 0) {
        cam_handle_unix_error("setpgid error");
    } 

    return;
}

pid_t cam_getpgrp() {
    return getpgrp();
}

char *cam_getenv(const char *name) {
    return getenv(name);
}

void cam_setenv(const char *name, const char *value, int overwrite) {
    if (setenv(name, value, overwrite) != 0) {
        cam_handle_unix_error("setenv error");
    }
}

void cam_unsetenv(const char *name) {
    if (unsetenv(name) != 0) {
        cam_handle_unix_error("unsetenv error");
    }
}
