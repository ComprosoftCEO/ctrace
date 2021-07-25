//
// Include a formatted message with the data
//
#include <trace_p.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void set_error_message(const char* msg, ...) {

	va_list vl;
	pErrorInfo_t errInfo = (pErrorInfo_t) trace_get_tls(&ERRINFO_KEY) ;

	if (errInfo == NULL) { // Must be new thread.
		errInfo = (pErrorInfo_t) calloc(1,sizeof(ErrorInfo_t)) ;
		if (!errInfo) {return; /* Should not happen */}

		trace_set_tls(&ERRINFO_KEY,errInfo) ;
	}

	//Message can be formatted string:
	va_start(vl,msg);
	  vsnprintf(errInfo->msg, ERROR_BUFLEN, msg ? msg : "", vl);
	va_end(vl);
}
