#ifndef LIBCAM_SIGNAL_H
#define LIBCAM_SIGNAL_H

#include <signal.h>
#include <stdbool.h>

typedef void (*cam_sig_handler)(int signum);

typedef enum {
    CAM_SIGHOW_BLOCK = SIG_BLOCK,
    CAM_SIGHOW_UNBLOCK = SIG_UNBLOCK,
    CAM_SIGHOW_SETMASK = SIG_SETMASK
} cam_sighow;

void cam_kill(pid_t pid, int signum);

unsigned int cam_alarm(unsigned int delay_secs);

cam_sig_handler cam_signal(int signum, cam_sig_handler handler);

void cam_sigprocmask(cam_sighow how, const sigset_t *set, sigset_t *oldset);

void cam_sigemptyset(sigset_t *set);

void cam_sigfillset(sigset_t *set);

void cam_sigaddset(sigset_t *set, int signum);

void cam_sigdelset(sigset_t *set, int signum);

bool cam_sigismember(const sigset_t *set, int signum);

int cam_sigsuspend(const sigset_t *set);

#endif // LIBCAM_SIGNAL_H
