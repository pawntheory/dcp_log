#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "dcp_log.h"

/* TODO:
   - Timestamps
   - Predefined logging functions
   - Close the file stream and free the log line buffer on catchable failures
   - Logging callbacks for user-created functions  */

#define LOGLINE 80
#define USERLOG 16

static _Bool LoggingEnabled = 0;

static _Bool UserLogEnabled = 0;
static char UserLogType[USERLOG + 1];

static const char *LOGTYPES[5] = {
    "INFO", "WARN", "ERROR", "FATAL", "USER"
};

/* Internal Error Handling */
static enum IErrorType
{
    IERR_NONE,
    IERR_DEFAULT,
    IERR_UNCLEAN_REINIT,
    IERR_UNCLEAN_CLOSE
} IErrState;

static LogFile Log;

int
BeginLogging(void)
{
    /* TODO:
       - Initialize output methods
       - Check if file exists/if file is directory
       - Check if file exceeds set limits and archive file if it does
       - Include using alternate log file locations/names
       - Handle error checking  */

    if (!LoggingEnabled) {
        IErrState = IERR_NONE;
        Log.File = fopen("lcurrent.log", "a+");
        Log.LineBuffer = (char *)calloc(LOGLINE + 1, sizeof(char));
        ClearUserLogType();

        LoggingEnabled = 1;

        return 0;
    } else {
        /* TODO: Error message */
        return IERR_UNCLEAN_REINIT;
    }
}

int
EndLogging(void)
{
    /* TODO: Handle error checking  */

    if (LoggingEnabled) {
        fclose(Log.File);
        free(Log.LineBuffer);

        LoggingEnabled = 0;

        return 0;
    } else {
        /* TODO: Error message */
        return IERR_UNCLEAN_CLOSE;
    }
}

void
SetUserLogType(const char *str)
{
    UserLogEnabled = 1;
    snprintf(UserLogType, USERLOG, "%s", str);
}

void
ClearUserLogType(void)
{
    UserLogEnabled = 0;
    memset(UserLogType, '\0', USERLOG + 1);
}

void
LogPrint(LogType type, const char *msg, ...)
{
    char tempLogBuff[1024] = { '\0' };
    int len = 0;

    va_list args;
    va_start(args, msg);

    if (UserLogEnabled && (type == LTYPE_USER)) {
        sprintf(tempLogBuff, "%s: ", UserLogType);
    } else { sprintf(tempLogBuff, "%s: ", LOGTYPES[type]); }

    strncat(tempLogBuff, msg, 1000);
    len = vsnprintf(Log.LineBuffer, 80, tempLogBuff, args);

    if (len < LOGLINE - 1) { strcat(Log.LineBuffer, "\n"); }
    else { Log.LineBuffer[LOGLINE - 1] = '\n'; }

    va_end(args);

    Log.LineBuffer[LOGLINE] = '\0';

    fprintf(Log.File, Log.LineBuffer);
    /* TODO: Print to stderr/stdout via fprintf or user callback if set
       by initialize function  */

    /* NOTE: clear the LineBuffer for future use  */
    memset(Log.LineBuffer, '\0', LOGLINE + 1);
}
