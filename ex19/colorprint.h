#ifndef __colorprint_h__
#define __colorprint_h__

#define RESET "\x1b[0m"

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
