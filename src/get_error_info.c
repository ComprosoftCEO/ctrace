//
// Return an error info object from TLS
//
#include <trace_p.h>
#include <stdlib.h>

pErrorInfo_t get_error_info(void) {

	pErrorInfo_t errInfo = (pErrorInfo_t) trace_get_tls(&ERRINFO_KEY) ;

	if (errInfo == NULL) { // Must be new thread.
		errInfo = (pErrorInfo_t) calloc(1,sizeof(ErrorInfo_t)) ;
		if (!errInfo) {return NULL; /* Should not happen */}

		trace_set_tls(&ERRINFO_KEY,errInfo) ;
	}

	return errInfo;
}
