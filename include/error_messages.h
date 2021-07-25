//
// List of all error message strings
//
#ifndef ERROR_MESSAGE_HEADER
#define ERROR_MESSAGE_HEADER

#include <stddef.h>	/* For size_t */

#include "error_codes.h"

static const char* ERROR_MESSAGES[] = {
  [NOERROR]		= "No Error",
  [ERROR_1]		= "Error Code 1",
  [ERROR_2]		= "Error Code 2",
  [ERROR_3]		= "Error Code 3",
};


static const size_t ERROR_COUNT = sizeof(ERROR_MESSAGES) / sizeof(ERROR_MESSAGES[0]) ;
static const char* INVALID_ERROR = "Invalid error code";

#endif	/* Error Message Header Included */
