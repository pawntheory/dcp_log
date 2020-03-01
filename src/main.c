#include "dcp_log.h"

int
main(void)
{
    BeginLogging();

    SetUserLogType("CUSTOM");
    LogPrint(LTYPE_USER, "Error essage");
    ClearUserLogType();
    LogPrint(LTYPE_USER, "Not found: %s.", "lost");

    EndLogging();

    return 0;
}
