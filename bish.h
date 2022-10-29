#ifndef BISH_HEADER
#define BISH_HEADER

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <sys/wait.h>

#include "shell.h"

#define CD ("cd")
#define EXIT ("exit")
#define FG ("fg")

Shell *shell;

#endif