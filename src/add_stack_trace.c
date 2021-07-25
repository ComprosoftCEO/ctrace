//
// Add a new entry to the stack trace
//
#include <trace_p.h>
#include <stdlib.h>

void _add_stack_trace(TRACE_PARAMS) {

	pErrorInfo_t errInfo = (pErrorInfo_t) trace_get_tls(&ERRINFO_KEY) ;

	if (errInfo == NULL) { // Must be new thread.
		errInfo = (pErrorInfo_t) calloc(1,sizeof(ErrorInfo_t)) ;
		if (!errInfo) {return; /* Should not happen */}

		trace_set_tls(&ERRINFO_KEY,errInfo) ;
	}


	//Make sure there is space left to trace
	if (errInfo->traceLevel < MAX_TRACE) {
		pTraceEntry_t entry = errInfo->stackTrace + errInfo->traceLevel;
		strncpy(entry->file, file, TRACE_BUFLEN);
		strncpy(entry->func, func, TRACE_BUFLEN);
		entry->line = line;

		++errInfo->traceLevel;
	}
}
