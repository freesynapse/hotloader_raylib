#ifndef __BACKTRACE_H
#define __BACKTRACE_H

#ifndef __USE_GNU
#define __USE_GNU
#endif
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <signal.h>
#include <execinfo.h>
#include <ucontext.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

#include "dll.h"

//
typedef struct sig_ucontext_
{
    unsigned long     uc_flags;
    ucontext_t*       uc_link;
    stack_t           uc_stack;
    struct sigcontext uc_mcontext;
    sigset_t          uc_sigmask;
} sig_ucontext_t;

//
void signal_handler(int sig_num, siginfo_t *info, void *ucontext);


#endif // __BACKTRACE_H
