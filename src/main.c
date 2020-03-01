#include <stdio.h>

#include "dcp_log.h"

int
main(void)
{
    BeginLogging(LOGTSTAMP | LOGLABELS, NULL);
    LogPrint(LTYPE_INFO, "This is an informative message.");
    LogPrint(LTYPE_WARNING, "This is a warning message.");
    LogPrint(LTYPE_ERROR, "This is an error message.");
    LogPrint(LTYPE_FATAL, "This is a fatal error message.");
    LogPrint(LTYPE_USER, "This is a user-defined message.");
    SetUserLogType("CUSTOM");
    LogPrint(LTYPE_USER, "This is a custom user-defined message.");
    EndLogging();

    BeginLogging(LOGNORMAL, NULL);
    LogPrint(LTYPE_INFO, "This is an informative message.");
    LogPrint(LTYPE_WARNING, "This is a warning message.");
    LogPrint(LTYPE_ERROR, "This is an error message.");
    LogPrint(LTYPE_FATAL, "This is a fatal error message.");
    LogPrint(LTYPE_USER, "This is a user-defined message.");
    SetUserLogType("CUSTOM");
    LogPrint(LTYPE_USER, "This is a custom user-defined message.");
    EndLogging();

    BeginLogging(LOGLABELS, "custom.log");
    LogPrint(LTYPE_INFO, "This is an informative message.");
    LogPrint(LTYPE_WARNING, "This is a warning message.");
    LogPrint(LTYPE_ERROR, "This is an error message.");
    LogPrint(LTYPE_FATAL, "This is a fatal error message.");
    LogPrint(LTYPE_USER, "This is a user-defined message.");
    SetUserLogType("CUSTOM");
    LogPrint(LTYPE_USER, "This is a custom user-defined message.");
    EndLogging();

    return 0;
}
