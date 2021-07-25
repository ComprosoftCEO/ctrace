//
// Trace Private Header
//
#ifndef TRACE_PRIVATE_HEADER
#define TRACE_PRIVATE_HEADER

//Include the public trace header
#include "trace.h"


//Configuraiton variables
#define TRACE_BUFLEN 160
#define ERROR_BUFLEN 200
#define MAX_TRACE    32



//Single trace entry
typedef struct {
	char file[TRACE_BUFLEN+1];		// File in which the error occured
	char func[TRACE_BUFLEN+1];		// Name of the function
	int line;						// Line on which the error occured
} TraceEntry_t, *pTraceEntry_t;


//Set of all trace entries
typedef struct {
	char msg[ERROR_BUFLEN+1];				// Custom message associated with this error
	int traceLevel;							// Current position in the StackTrace array
	TraceEntry_t stackTrace[MAX_TRACE];		// Array of StackTrace entries
} ErrorInfo_t, *pErrorInfo_t;



//Internal methods
pErrorInfo_t get_error_info(void);



// Thread Local Storage
#ifdef _WIN32
  #define TLS_KEY_T int
#else
  #include <pthread.h>
  #define TLS_KEY_T pthread_key_t
#endif


//Internal trace TLS keys
extern TLS_KEY_T ERROR_KEY;
extern TLS_KEY_T ERRINFO_KEY;

void *trace_get_tls(TLS_KEY_T* idx);
void trace_set_tls(TLS_KEY_T* idx, void *add) ;


#endif	/* Trace Private Header Included */
