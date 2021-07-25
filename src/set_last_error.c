//
// Set last error code in TLS
//
#include <trace_p.h>
#include <stdlib.h>

error_code set_last_error(error_code error) {

	error_code *perr = (error_code*) trace_get_tls(&ERROR_KEY) ;

	if (perr == NULL) { // Must be new thread.
		perr = (error_code*) calloc(1,sizeof(error_code)) ;
		if (!perr) {return error; /* Should not happen */}

		trace_set_tls(&ERROR_KEY,perr) ;
	}

	*perr = error;
	return (*perr);
}
