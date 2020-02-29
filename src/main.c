#include "dcp_log.h"

int
main(void)
{
    BeginLogging();

    SetUserLogType("PANIC!");
    LogPrint(LTYPE_USER, "At the disco?");
    ClearUserLogType();
    LogPrint(LTYPE_USER, "Not found: %s.", "lost");

    EndLogging();

    return 0;
}
