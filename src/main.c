#include "dcp_log.h"

int
main(void)
{
    BeginLogging(LOGNORMAL);

    LogPrint(LTYPE_WARNING, "There is no reason for you to continue");
    LogPrint(LTYPE_WARNING, "Resistance is %s",
            "futile.  You are the stupidest person I have ever met.");
    SetUserLogType("CUSTOM");
    LogPrint(LTYPE_USER, "Error essage");
    ClearUserLogType();
    LogPrint(LTYPE_USER, "Not found: %s.", "lost");

    EndLogging();

    BeginLogging(LOGLABELS);
    LogPrint(LTYPE_WARNING, "Resistance is %s",
            "futile.  You are the stupidest person I have ever met.");
    EndLogging();

    return 0;
}
