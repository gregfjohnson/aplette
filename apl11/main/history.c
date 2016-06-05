#include <stdio.h>
#include "config.h"

#ifdef HAVE_LIBREADLINE
    #include <readline/history.h>

    void readline_add_history(char *line) {
        add_history(line);
    }
#else
    void readline_add_history(char *line) {
    }
#endif
