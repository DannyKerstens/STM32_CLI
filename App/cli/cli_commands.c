#include <stdio.h>
#include "cli_commands.h"


void setGPIO(char *args)
{
    const char *arg1 = NULL;
    const char *arg2 = NULL;

    if (arg1 == NULL || arg2 == NULL) {
        //cli_printf("usage: get-led [arg1] [arg2]");
        return;
    }
    // Make sure to check if 'args' != NULL, printf's '%s' formatting does not like a null pointer.
    //cli_printf("LED with args: %s and %s", arg1, arg2);
}

