#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

#include "dcp_log.h"

/* TODO:
   - Predefined logging functions
   - Close the file stream and free the log line buffer on catchable failures
   - Logging callbacks for user-created functions  */

static _Bool LoggingEnabled = 0;

static _Bool UserLogEnabled = 0;
static char UserLogType[USERLOG + 1];

static unsigned int LogPrefix = 0;

static const char *LOGTYPES[5] = {
    "INFO", "WARNING", "ERROR", "FATAL", "USER"
};

/* Internal Error Handling */
static enum IErrorType
{
    IERR_NONE,
    IERR_DEFAULT,
    IERR_UNCLEAN_REINIT,
    IERR_UNCLEAN_CLOSE
} IErrState;

static struct ILogFile
{
    FILE *File;
    char LineBuffer[LOGLINE + 1];
    int LineNumber;
} Log;

int
BeginLogging(unsigned int logPrefix, const char *logFilename)
{
    /* TODO:
       - Initialize output methods
       - Check if file is directory
       - Check if file exceeds set limits and archive file if it does
       - Handle error checking  */

    if (!LoggingEnabled) {
        IErrState = IERR_NONE;

        if (logFilename != NULL) {
            if (!(Log.File = fopen(logFilename, "a+"))) {
                Log.File = fopen(logFilename, "w+");
            }
        } else {
            if (!(Log.File = fopen("default.log", "a+"))) {
                Log.File = fopen("default.log", "w+");
            }
        }

        memset(Log.LineBuffer, '\0', LOGLINE + 1);
        ClearUserLogType();

        LogPrefix = logPrefix;
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

        LogPrefix = LOGNORMAL;
        LoggingEnabled = 0;

        return 0;
    } else {
        /* TODO: Error message */
        return IERR_UNCLEAN_CLOSE;
    }
}

void
LogPrint(LogType type, const char *msg, ...)
{
    char tempLogBuff[1024] = { '\0' };
    int len = 0;

    va_list args;
    va_start(args, msg);

    if (LogPrefix & LOGTSTAMP) {
        char tempTimeBuff[128] = { '\0' };

        int hour, minute, second, day, month, year;
        time_t now;

        time(&now);
        struct tm *local = localtime(&now);

        hour = local->tm_hour;
        minute = local->tm_min;
        second = local->tm_sec;
        day = local->tm_mday;
        month = local->tm_mon + 1;
        year = local->tm_year + 1900;

        len += sprintf(tempTimeBuff, "[%02d%02d%d %02d:%02d:%02d] ",
                month, day, year, hour, minute, second);
        strcat(tempLogBuff, tempTimeBuff);
    }

    if (LogPrefix & LOGLABELS) {
        char tempLablBuff[128] = { '\0' };

        if (UserLogEnabled && (type == LTYPE_USER)) {
            len += sprintf(tempLablBuff, "%s: ", UserLogType);
        } else { len += sprintf(tempLablBuff, "%s: ", LOGTYPES[type]); }

        strcat(tempLogBuff, tempLablBuff);
    }

    strncat(tempLogBuff, msg, 1024 - len);

    /* NOTE: Remove newlines from message  */
    for (int i = 0; i < 1024; i++) {
        if (tempLogBuff[i] == '\n' || tempLogBuff[i] == '\r') {
            tempLogBuff[i] = ' ';
        }
    }

    len = vsnprintf(Log.LineBuffer, 80, tempLogBuff, args);

    va_end(args);

    if (len < LOGLINE - 1) { strcat(Log.LineBuffer, "\n"); }
    else { Log.LineBuffer[LOGLINE - 1] = '\n'; }

    Log.LineBuffer[LOGLINE] = '\0';

    fprintf(Log.File, Log.LineBuffer);
    /* TODO: Print to stderr/stdout via fprintf or user callback if set
       by initialize function  */

    /* NOTE: clear the LineBuffer for future use  */
    memset(Log.LineBuffer, '\0', LOGLINE + 1);
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
