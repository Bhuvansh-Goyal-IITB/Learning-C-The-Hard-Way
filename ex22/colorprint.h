#ifndef __colorprint_h__
#define __colorprint_h__

#define RESET "\x1b[0m"

#ifdef NCOLOR
#define BLACK(M) M
#define RED(M) M
#define GREEN(M) M
#define YELLOW(M) M
#define BLUE(M) M
#define MAGENTA(M) M
#define CYAN(M) M
#define WHITE(M) M
#define GRAY(M) M

#define BRIGHT_RED(M) M
#define BRIGHT_GREEN(M) M
#define BRIGHT_YELLOW(M) M
#define BRIGHT_BLUE(M) M
#define BRIGHT_MAGENTA(M) M
#define BRIGHT_CYAN(M) M
#define BRIGHT_WHITE(M) M

#else
#define BLACK(M) "\x1b[30m" M RESET
#define RED(M) "\x1b[31m" M RESET
#define GREEN(M) "\x1b[32m" M RESET
#define YELLOW(M) "\x1b[33m" M RESET
#define BLUE(M) "\x1b[34m" M RESET
#define MAGENTA(M) "\x1b[35m" M RESET
#define CYAN(M) "\x1b[36m" M RESET
#define WHITE(M) "\x1b[37m" M RESET
#define GRAY(M) "\x1b[90m" M RESET

#define BRIGHT_RED(M) "\x1b[91m" M RESET
#define BRIGHT_GREEN(M) "\x1b[92m" M RESET
#define BRIGHT_YELLOW(M) "\x1b[93m" M RESET
#define BRIGHT_BLUE(M) "\x1b[94m" M RESET
#define BRIGHT_MAGENTA(M) "\x1b[95m" M RESET
#define BRIGHT_CYAN(M) "\x1b[96m" M RESET
#define BRIGHT_WHITE(M) "\x1b[97m" M RESET
#endif

#endif
