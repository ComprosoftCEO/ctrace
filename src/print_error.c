//
// Write error message to stderr
//
#include <trace_p.h>
#include <stdio.h>

static void print_trace();

void print_error(const char *str, bool show_trace) {
	fprintf(stderr,"%s: %s\n",(str ? str : ""),
		error_message(get_last_error()));

	if (show_trace) {print_trace();}

	return ;
}


//Print out the trace to standard error
void print_trace() {

	pErrorInfo_t errInfo = get_error_info();	
	if (errInfo) {
		fprintf(stderr,"\n%s\n",errInfo->msg);

		int i;
		for (i = 0; i < errInfo->traceLevel; ++i) {
			pTraceEntry_t trace = errInfo->stackTrace + i;
			char buf[32] = {0};

			snprintf(buf,sizeof(buf)-1,"%s()",trace->func);	//Add parenthesis after it

			fprintf(stderr,"  (%d)\tIn function: %-*s (%s, line %d)\n",
				i, (int) sizeof(buf), buf, trace->file, trace->line);
		}
	}
}
