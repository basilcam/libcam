#include <unistd.h>
#include <errno.h>
#include "cam/sys/signal.h"
#include "cam/error.h"

void cam_kill(pid_t pid, int signum) {
    if (kill(pid, signum) < 0) {
        cam_handle_unix_error("kill error");
    }
}

unsigned int cam_alarm(unsigned int delay_secs) {
    return alarm(delay_secs);
}


cam_sig_handler cam_signal(int signum, cam_sig_handler handler) {
    struct sigaction action, old_action;

    action.sa_handler = handler;
    sigemptyset(&action.sa_mask); // block all signals
    action.sa_flags = SA_RESTART; // restart syscalls if possible

    if (sigaction(signum, &action, &old_action) < 0) {
        cam_handle_unix_error("signal error");
    }

    return old_action.sa_handler;
}

void cam_sigprocmask(cam_sighow how, const sigset_t *set, sigset_t *oldset) {
    if (sigprocmask(how, set, oldset) < 0) {
        cam_handle_unix_error("sigprocmask error");
    }
}

void cam_sigemptyset(sigset_t *set) {
    if (sigemptyset(set) < 0) {
        cam_handle_unix_error("sigemptyset error");
    }
}

void cam_sigfillset(sigset_t *set) {
    if (sigfillset(set) < 0) {
        cam_handle_unix_error("sigfillset error");
    }
}

void cam_sigaddset(sigset_t *set, int signum) {
    if (sigaddset(set, signum) < 0) {
        cam_handle_unix_error("sigaddset error");
    }
}

void cam_sigdelset(sigset_t *set, int signum) {
    if (sigdelset(set, signum) < 0) {
        cam_handle_unix_error("sigdelset error");
    }
}

bool cam_sigismember(const sigset_t *set, int signum) {
    int rc = sigismember(set, signum);

    if (rc < 0) {
        cam_handle_unix_error("sigismember error");
    }

    return rc;
}

int cam_sigsuspend(const sigset_t *set) {
    int rc = sigsuspend(set);
    if (errno != EINTR) {
        cam_handle_unix_error("sigsuspend error");
    }
    return rc;
}
