#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "dcp_log.h"

/* TODO:
   - Predefined logging functions
   - Logging callbacks for user-created functions  */

#define LOGLINE 80

/* Internal Error Handling */
static enum IErrorType
{
    IERR_NONE,
    IERR_DEFAULT
} IErrState;

static LogFile Log;

int
BeginLogging(void)
{
    IErrState = IERR_NONE;
    /* TODO:
       - Initialize output methods
       - Check if file exists
       - Check if file exceeds set limits and archive file if it does
       - Include using alternate log file locations/names
       - Handle error checking  */
    Log.File = fopen("lcurrent.log", "w+");
    Log.LineBuffer = (char *)calloc(LOGLINE + 1, sizeof(char));

    return 0;
}

int
EndLogging(void)
{
    /* TODO: Handle error checking  */
    fclose(Log.File);
    free(Log.LineBuffer);

    return 0;
}

void
LogPrint(LogType type, char *msg, ...)
{
    va_list args;

    switch (type) {
        case LTYPE_INFO: {
            sprintf(Log.LineBuffer, "[INFO]: ");
        } break;

        case LTYPE_USER: {
            /* TODO: replace USER with user-given */
            sprintf(Log.LineBuffer, "[USER]: ");
        } break;
    }

    fprintf(Log.File, msg, args);
    /* TODO: print to stderr/stdout/user callback if set by initialize */

    memset(Log.LineBuffer, '\0', LOGLINE + 1);
}
