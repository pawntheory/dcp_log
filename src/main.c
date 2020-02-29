#include "dcp_log.h"

int
main(void)
{
    BeginLogging();

    LogPrint(LTYPE_INFO, "This is a test, %d", 123);
    LogPrint(LTYPE_ERROR, "This is a test, %08X", 8765309);
    LogPrint(LTYPE_WARNING, "This is a test %s", 
            "of the emergency broadcast system.  This is only a tddesttt.");
    LogPrint(LTYPE_FATAL, "This is a test, %0.2f", 1000.3234);
    LogPrint(LTYPE_USER, "This is a test");
    SetUserLogType("USERDEFINEDTYPE_THELIMIT");
    LogPrint(LTYPE_USER, "This is a test ");
    ClearUserLogType();
    LogPrint(LTYPE_USER, "This is a test ");

    EndLogging();

    return 0;
}
