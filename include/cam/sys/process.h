#ifndef __CAM_SYS_H__
#define __CAM_SYS_H__

#include <sys/types.h>

////////////////////////////////////////////////////////////////
// Logging
////////////////////////////////////////////////////////////////

void cam_handle_unix_error(char *msg);

////////////////////////////////////////////////////////////////
// Process control 
////////////////////////////////////////////////////////////////

pid_t cam_fork(void);
void cam_execve(const char *filename, char *const argv[], char *const envp[]);

pid_t cam_waitpid(pid_t pid, int *statusCode, int options);
pid_t cam_wait(int *status);

void cam_kill(pid_t pid, int signalNumber);

unsigned int cam_sleep(unsigned int durationSeconds);
void cam_pause();
unsigned int cam_alarm(unsigned int delaySeconds);

void cam_setpgid(pid_t pid, pid_t groupId);
pid_t cam_getpgrp();

char *cam_getenv(const char *name);
void cam_setenv(const char *name, const char *value, int overwrite);
void cam_unsetenv(const char *name);

#endif // __CAM_SYS_H__
