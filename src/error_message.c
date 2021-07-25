//
// Get char* associated with error number
//
#include <trace_p.h>

const char *error_message(error_code errnum) {

	if ((errnum < 0) | (errnum >= ERROR_COUNT)) {return INVALID_ERROR;}

	const char* err = ERROR_MESSAGES[errnum];
	if (!err) {return INVALID_ERROR;}
	return(err) ;
}
