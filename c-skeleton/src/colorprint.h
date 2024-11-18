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
#define BLACK_ANSI "\x1b[30m"
#define RED(M) "\x1b[31m" M RESET
#define RED_ANSI "\x1b[31m"
#define GREEN(M) "\x1b[32m" M RESET
#define GREEN_ANSI "\x1b[32m"
#define YELLOW(M) "\x1b[33m" M RESET
#define YELLOW_ANSI "\x1b[33m"
#define BLUE(M) "\x1b[34m" M RESET
#define BLUE_ANSI "\x1b[34m"
#define MAGENTA(M) "\x1b[35m" M RESET
#define MAGENTA_ANSI "\x1b[35m"
#define CYAN(M) "\x1b[36m" M RESET
#define CYAN_ANSI "\x1b[36m"
#define WHITE(M) "\x1b[37m" M RESET
#define WHITE_ANSI "\x1b[37m"
#define GRAY(M) "\x1b[90m" M RESET
#define GRAY_ANSI "\x1b[90m"

#define BRIGHT_RED(M) "\x1b[91m" M RESET
#define BRIGHT_RED_ANSI "\x1b[91m"
#define BRIGHT_GREEN(M) "\x1b[92m" M RESET
#define BRIGHT_GREEN_ANSI "\x1b[92m"
#define BRIGHT_YELLOW(M) "\x1b[93m" M RESET
#define BRIGHT_YELLOW_ANSI "\x1b[93m"
#define BRIGHT_BLUE(M) "\x1b[94m" M RESET
#define BRIGHT_BLUE_ANSI "\x1b[94m"
#define BRIGHT_MAGENTA(M) "\x1b[95m" M RESET
#define BRIGHT_MAGENTA_ANSI "\x1b[95m"
#define BRIGHT_CYAN(M) "\x1b[96m" M RESET
#define BRIGHT_CYAN_ANSI "\x1b[96m"
#define BRIGHT_WHITE(M) "\x1b[97m" M RESET
#define BRIGHT_WHITE_ANSI "\x1b[97m"
#endif

#endif
