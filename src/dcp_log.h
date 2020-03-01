#ifndef DCP_LOG_H_
#define DCP_LOG_H_

#include <stdio.h>

#define LOGLINE 80
#define USERLOG 16

#define LOGNORMAL 0x0
#define LOGLABELS 0x1
#define LOGTSTAMP 0x2

enum ELogType
{
    LTYPE_INFO,
    LTYPE_WARNING,
    LTYPE_ERROR,
    LTYPE_FATAL,
    LTYPE_USER
};
typedef enum ELogType LogType;

int BeginLogging(unsigned int LogPrefix);
int EndLogging(void);

void LogPrint(LogType type, const char *msg, ...);

void SetUserLogType(const char *str);
void ClearUserLogType(void);
#endif /* DCP_LOG_H_ */
