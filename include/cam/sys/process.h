#ifndef LIBCAM_SYS_H
#define LIBCAM_SYS_H

#include <sys/types.h>

pid_t cam_fork(void);
void cam_execve(const char *filename, char *const argv[], char *const envp[]);

pid_t cam_waitpid(pid_t pid, int *status_code, int options);
pid_t cam_wait(int *status);

unsigned int cam_sleep(unsigned int duration_seconds);
void cam_pause();

void cam_setpgid(pid_t pid, pid_t pgid);
pid_t cam_getpgrp();

char *cam_getenv(const char *name);
void cam_setenv(const char *name, const char *value, int overwrite);
void cam_unsetenv(const char *name);

#endif // LIBCAM_SYS_H
