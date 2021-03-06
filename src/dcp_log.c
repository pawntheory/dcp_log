#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

#include "dcp_log.h"

#define LOGLINE 80
#define USERLOG 16

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
    if (!LoggingEnabled) {
        IErrState = IERR_NONE;

        /* TODO: Check if file is directory  */
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

        return IERR_NONE;
    } else {
        fprintf(stderr, "WARNING: Tried to begin log with status %d.\n",
                LoggingEnabled);
        fprintf(stderr, "\tLogging already initialized.\n");

        IErrState = IERR_UNCLEAN_REINIT;
        return IERR_UNCLEAN_REINIT;
    }
}

int
EndLogging(void)
{
    if (LoggingEnabled) {
        fclose(Log.File);

        LogPrefix = LOGNORMAL;
        LoggingEnabled = 0;

        return IERR_NONE;
    } else {
        fprintf(stderr, "WARNING: Tried to end log with status %d.\n",
                LoggingEnabled);
        fprintf(stderr, "\tLogging not yet initialized.\n");

        IErrState = IERR_UNCLEAN_CLOSE;
        return IERR_UNCLEAN_CLOSE;
    }
}

void
LogPrint(LogType type, const char *msg, ...)
{
    if (!LoggingEnabled) {
        fprintf(stderr, "WARNING: Tried to print log with status %d.\n",
                LoggingEnabled);
        return;
    }

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
        switch (tempLogBuff[i]) {
            case '\n':
            case '\r':
            case '\t': {
                tempLogBuff[i] = ' ';
            } break;
        }
    }

    len = vsnprintf(Log.LineBuffer, 80, tempLogBuff, args);

    va_end(args);

    if (len < LOGLINE - 1) { strcat(Log.LineBuffer, "\n"); }
    else { Log.LineBuffer[LOGLINE - 1] = '\n'; }

    Log.LineBuffer[LOGLINE] = '\0';

    fprintf(Log.File, "%s", Log.LineBuffer);
    if (LogPrefix & LOGSTDOUT) { fprintf(stderr, "%s", Log.LineBuffer); }

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
