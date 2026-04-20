
#include "backtrace.h"

void signal_handler(int sig_num, siginfo_t *info, void *ucontext)
{
    fprintf(stderr, "ERROR: SIGSEGV recieved (%s)\n", strsignal(sig_num));

    FILE *f_restore = fopen("restore.point", "w");
    if (!f_restore)
    {
        fprintf(stderr, "ERROR: could not set restore point.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(f_restore, "1");
    fclose(f_restore);

    sig_ucontext_t *uc = (sig_ucontext_t *)ucontext;
    void *caller_addr;
    #if defined(__i386__)
        caller_addr = (void *)uc->uc_mcontext.eip;
    #elif defined(__x86_64__)
        caller_addr = (void *)uc->uc_mcontext.rip;
    #endif

    #define BACKTRACE_ADDR_COUNT 64
    void *backtraceAddrs[BACKTRACE_ADDR_COUNT];
    int addrCount;
    char **backtraceMsgs;

    // output stack bactrace
    addrCount = backtrace(backtraceAddrs, BACKTRACE_ADDR_COUNT);
    backtraceAddrs[1] = caller_addr;
    // to output function names (from the dynamic symbols table) compiler flag -rdynamic
    // is required for clang (and gcc, apparantly)
    backtraceMsgs = backtrace_symbols(backtraceAddrs, addrCount);
    fprintf(stderr, "\x1b[1;37;41m--------------------- STACKTRACE ---------------------\x1b[0m\n");
    fprintf(stderr, "signal %d (%s) address is 0x%lx from 0x%lx.\n",
            sig_num, strsignal(sig_num), (uintptr_t)info->si_addr, (uintptr_t)caller_addr);
    for (int i = 1; i < addrCount && backtraceMsgs != NULL; i++)
        fprintf(stderr, "%3d : %s\n", i, backtraceMsgs[i]);
    free(backtraceMsgs);
    fprintf(stderr, "\x1b[1;37;41m------------------- END STACKTRACE -------------------\x1b[0m\n");

    exit(EXIT_FAILURE);
}
