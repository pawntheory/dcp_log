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

struct ELogFile
{
    FILE *File;
    char LineBuffer[LOGLINE + 1];
    int LineNumber;
};
typedef struct ELogFile LogFile;

int BeginLogging(void);
int EndLogging(void);
void SetUserLogType(const char *str);
void ClearUserLogType(void);
void LogPrint(LogType type, const char *msg, ...);
#endif /* DCP_LOG_H_ */
