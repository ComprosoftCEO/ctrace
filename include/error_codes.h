#ifndef ERROR_CODES_HEADER
#define ERROR_CODES_HEADER


#define IS_ERROR(x) ((x) != NOERROR)


//Example error codes
typedef enum error_code {
	NOERROR = 0,
	ERROR_1,
	ERROR_2,
	ERROR_3,
} error_code;


#endif	/* Error Codes Header included */
