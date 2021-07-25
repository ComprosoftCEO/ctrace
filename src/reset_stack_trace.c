//
// Reset the stack trace
//
#include <trace_p.h>
#include <stdlib.h>

void reset_stack_trace(void) {

	pErrorInfo_t perr = (pErrorInfo_t) trace_get_tls(&ERRINFO_KEY);
	if (perr == NULL) { // Must be new thread.
		perr = (pErrorInfo_t) calloc(1,sizeof(ErrorInfo_t)) ;
		if (!perr) {return; /* Alloc Error - Should not happen */}
		trace_set_tls(&ERRINFO_KEY,perr) ;
	}

	perr->traceLevel = 0;
}
