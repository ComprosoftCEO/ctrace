# C Trace

Function tracing for C applications

## Embedding into Library

These code files are designed to be embedded into an existing C library, not used as an external library.
To add trace functionality to your library, simply compile the contents of `src/` along with your library and include the contents of `include/` in your include path.
All library-specific error codes should be defined in `error_codes.h` and string error messages should be defined in `error_messages.h`.
Embedding the code files into your library allows you the flexibility to adjust how errors are handled specifically to each library.

Errors and stack traces are stored in thread-local storage, making this library safe for multithreaded programs (Unlike ERRNO).
Thread-local storage is designed to compile on both Windows using TLS in `windows.h` and Linux using `pthreads`.
Storage is allocated for up to 32 traces, which should be sufficient for any library.
However, this value can be adjusted by modifying `MAX_TRACE` in the private header `trace_p.h`.

<br />

## Tracing Examples:

```c
#include "trace.h"
#include "error_codes.h"

int main(int argc, char** argv) {

  // Check arguments
  if (argc < 3) {
    printf("Usage: %s <data> <file>", argv[0]);
    return 0;
  }

  struct Data* data = load_data(argv[1]);
  if (data == NULL) {
    print_error("Load Data", true);
    return -1;
  }

  if (!export_to_file(argv[2], data)) {
    print_error("Export Data", true);
    return -2;
  }

  return 0;
}

// Returns "true" on success or "false" on error
bool export_to_file(const char* fname, struct Data* data) {

  int fp = open(fname, O_WRONLY | O_CREAT | O_TRUNC, -1);
  if (fp < 0) {
    set_error(ERROR_FOPEN, "Opening CSV File %s for Export", fname);
    return new_trace(false);
  }

  error_code error = write_to_file(fp, data);
  if (IS_ERROR(error)) {
    return trace(false);
  }

  return true;
}
```

<br />

## Headers

- **Public:** `trace.h` - Exports all of the trace functions and macros
- **Public:** `error_codes.h` - Contains the enum of all error codes
- **Private:** `trace_p.h` - Internal functions and data structures
- **Private:** `error_messages.h` - String error messages used by the library, should be updated when changing the error codes

## Data Types

- `error_code` - Enum structure that lists every single error code (defined in `error_code.h`)

## Macros

- `add_stack_trace()` - Create a new stack trace entry at the given position in the code file
- `trace(...)` - Create a new stack trace entry, then evaluate all arguments in the `...`. Should be used with `return trace(RETURN_VALUE);`.
- `new_trace(...)` - Similar to trace, but resets the stack trace first. Should be used with `return new_trace(RETURN_VALUE);`.
- `reset_trace()` - Alias for `reset_stack_trace()`.
- `set_error(err, msg, ...)` - Macro to call both `set_last_error` and `set_error_message` using an error code and a `printf` string
- `IS_ERROR(e)` - Test if a given `error_code` is an error

## Functions

- `get_last_error()` - Retrieve the last error code as stored in thread-local storage
- `set_last_error(error_code error)` - Set the last error code in thread-local storage
- `clear_error()` - Clear any stored errors
- `print_error(const char* str, bool show_trace)` - Print out the error with an additional string message, optionally also show the full stack trace
- `const char* error_message(error_code errnum)` - Get an error string for the given error code
- `set_error_message(const char* msg, ...)` - Set a custom error message using a `printf` string with arguments
- `reset_stack_trace()` - Clear the current stack trace
