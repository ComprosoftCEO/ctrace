//
// Trace Public Header
//
#ifndef TRACE_PUBLIC_HEADER
#define TRACE_PUBLIC_HEADER

#ifdef __cplusplus
extern "C" {
#endif


#include <stdbool.h>		// For true and false
#include <string.h>			// For strchr()


//Error code is just an integer
typedef enum error_code error_code;



//Macros for the parameters used by add_stack_trace
#ifdef _WIN32
  #define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
  #define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif
#define TRACE_PARAMS     const char* file, const char* func, int line
#define TRACE_ARGS       file, func, line
#define TRACE_ENTRY      __FILENAME__, __func__, __LINE__



//Public Error Functions
error_code get_last_error(void);
error_code set_last_error(error_code error);
void clear_error(void);
void print_error(const char *str, bool show_trace);

const char *error_message(error_code errnum);
void set_error_message(const char* msg, ...);


//Stack trace methods
void reset_stack_trace(void);
void _add_stack_trace(TRACE_PARAMS);		// Call using macro add_stack_trace()


//---Error Macros:---
#define add_stack_trace()			_add_stack_trace(TRACE_ENTRY)
#define trace(...)					(_add_stack_trace(),##__VA_ARGS__)
#define new_trace(...)				((_reset_stack_trace()),(_add_stack_trace()),##__VA_ARGS__)
#define reset_trace()				reset_stack_trace()
#define set_error(err,msg,...)		set_last_error(err), set_error_message(msg,##__VA_ARGS__)



#ifdef __cplusplus
}
#endif

#endif	/* Trace public header included */
