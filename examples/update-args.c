#include <stdlib.h>
#include <stdio.h>
#include <cam/sys/process.h>

static const char *ENV_VAR_NAME = "CAM_TEST";
static const char *ENV_VAR_VALUE = "hello there";
static const char *ENV_VAR_VALUE_UPDATED = "goodbye now";

static void print_env_vars();
static char *nope_or_value(char *value);

int main(int argc, char *argv[], char *envp[]) {
    print_env_vars();

    printf("Setting it now\n");
    cam_setenv(ENV_VAR_NAME, ENV_VAR_VALUE, 1);
    print_env_vars();

    printf("Updating it to %s=%s\n", ENV_VAR_NAME, ENV_VAR_VALUE_UPDATED);
    cam_setenv(ENV_VAR_NAME, ENV_VAR_VALUE_UPDATED, 1);   
    print_env_vars(); 

    printf("Unsetting it\n");
    cam_unsetenv(ENV_VAR_NAME);
    print_env_vars();

    return EXIT_SUCCESS;
}

static void print_env_vars()
{
    printf("What is %s currently, if it exists? %s\n", ENV_VAR_NAME, nope_or_value(cam_getenv(ENV_VAR_NAME)));
}

static char *nope_or_value(char *value) {
    if (value == NULL) {
        return "Does not exist";
    } else {
        return value;
    }
}   

