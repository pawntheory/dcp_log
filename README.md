# `dcp_log` - a logging thing for things

Logging library.

Include `dcp_log.h` in whatever file you want to have logging enabled.

Initalize the logging stream with `BeginLogging()` and call `EndLogging()` when you're done.

The types of logs are currently:
- `LTYPE_INFO`
- `LTYPE_WARNING`
- `LTYPE_ERROR`
- `LTYPE_FATAL`
- `LTYPE_USER` - can be changed to another <= 16 character type with `SetUserLogType()`

`BeginLogging()` takes two arguments, the first is the type of prefix, the possible prefixes are:
- `LOGLABELS` - Shows the above labels (without `LTYPE_`) before your log line.
- `LOGTSTAMP` - Shows a date/time stamp before your log line.

These prefixes can be or'd together to include both, to have neither use `LOGNORMAL`.

The second argument in `BeginLogging()` is the file name for your log file.  If `NULL` this uses a file named `default.log` in whichever directory you envoke your program.
