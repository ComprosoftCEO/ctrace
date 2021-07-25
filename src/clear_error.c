//
// Clear any stored error
//
#include <trace.h>

void clear_error() {
	set_last_error(NOERROR);
	set_error_message("");
	reset_stack_trace();
}
