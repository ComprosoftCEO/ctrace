//
// Last error code for this thread
//
#include <trace_p.h>
#include <stdlib.h>

error_code get_last_error() {

	error_code *perr = (error_code*) trace_get_tls(&ERROR_KEY) ;

	if (perr == NULL) { // Must be new thread.
		perr = (error_code*) calloc(1,sizeof(error_code));
		if (!perr) {return NOERROR; /* Should not happen */}

		trace_set_tls(&ERROR_KEY,perr);
	}

	return(*perr);
}
