# `dcp_log` - a logging thing for things

## Building

To build, just run `make`.  Once built, both static and shared library files
are created:

- `libdcplog.a`
- `libdcplog.so`

It should just compile without issue if you have
GNU make and GCC set up correctly.  If not, let me know.  I've probably
overlooked something.

## Using

Include `dcp_log.h` in whatever file you want to have logging enabled.

- Each printed line removes any included newlines, carriage returns, and tabs.
- Each printed line is a maximum of 80 characters.

### Log Prefix Types

The types of log prefixes are currently:
- `LTYPE_INFO`
- `LTYPE_WARNING`
- `LTYPE_ERROR`
- `LTYPE_FATAL`
- `LTYPE_USER`†

> † Uses `SetUserLogType()` to change to a user-defined type (<= 16 characters)

### `BeginLogging()`

> `int BeginLogging(unsigned int logPrefix, const char *logFilename);`

Begins the logging session, opens a logging stream (`default.log` if
the logFilename argument is NULL), and determines the log prefixes.

The types of log prefixes are currently:
- `LOGLABELS` - Shows the label before your log line.
- `LOGTSTAMP` - Shows a date/timestamp before your log line.

### `EndLogging()`

> `int EndLogging(void);`

Self Explanatory.  Ends the logging session and closes the logging stream.

### `LogPrint()`

> `void LogPrint(LogType type, const char *msg, ...);`

Prints your log message to both the log stream and stderr.
Maximum 80 characters (including any prefixes).

### `SetUserLogType()`

> `void SetUserLogType(const char *str);`

### `ClearUserLogType()`

> `void ClearUserLogType(void);`
