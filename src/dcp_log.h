#ifndef DCP_LOG_H_
#define DCP_LOG_H_

#include <stdio.h>

#define LOGLINE 80
#define USERLOG 16

enum ELogType
{
    LTYPE_INFO,
    LTYPE_ERROR,
    LTYPE_WARNING,
    LTYPE_FATAL,
    LTYPE_USER
};
typedef enum ELogType LogType;

int BeginLogging(void);
int EndLogging(void);

void LogPrint(LogType type, const char *msg, ...);

void SetUserLogType(const char *str);
void ClearUserLogType(void);
#endif /* DCP_LOG_H_ */
