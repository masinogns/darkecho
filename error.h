/*
*error.h
*/

#include "common.h"

void error_output(char *message)
{
fputs(message, stderr);
fputc('\n',stderr);
exit(1);
}

