#ifndef DCP_LOG_H_
#define DCP_LOG_H_

#include <stdio.h>

enum ELogType
{
    LTYPE_INFO,
    LTYPE_USER
};
typedef enum ELogType LogType;

struct ELogFile
{
    FILE *File;
    char *LineBuffer;
    int LineNumber;
};
typedef struct ELogFile LogFile;

int BeginLogging(void);
int EndLogging(void);
void LogPrint(LogType type, char *msg, ...);
#endif /* DCP_LOG_H_ */