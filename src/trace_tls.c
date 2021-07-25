//Thread-local storage functions
#include <trace_p.h>

//TLS Static Keys
TLS_KEY_T ERROR_KEY;
TLS_KEY_T ERRINFO_KEY;


//Platform-specific code
#ifdef _WIN32

	//Windows API Version
	#include <Windows.h>
	static bool trace_tls_once = false;

	static void trace_init_tls(void) {

		if (trace_tls_once) {return;}

		//Allocate all of the TLS keys
		ERROR_KEY = TlsAlloc();
		ERRINFO_KEY = TlsAlloc();
		trace_tls_once = true;
	}

	void *trace_get_tls(TLS_KEY_T* idx) {

		void* pTls = NULL;
		if (!trace_tls_once) {trace_init_tls();}
		if (idx != NULL) {
			pTls = TlsGetValue(*idx);
		}
		return(pTls);
	}

	void trace_set_tls(TLS_KEY_T* idx, void *add) {
		if (!trace_tls_once) {trace_init_tls();}
		if (idx) {TlsSetValue(*idx,add);}
	}



#else

	// Linux - Unix Version
	#include <pthread.h>
	static pthread_once_t trace_tls_once = PTHREAD_ONCE_INIT ;

	static void trace_init_tls(void) {
		pthread_key_create(&ERROR_KEY,NULL);
		pthread_key_create(&ERRINFO_KEY,NULL);
	}

	void *trace_get_tls(TLS_KEY_T* idx) {
		pthread_once(&trace_tls_once,trace_init_tls);

		void *pTls = NULL;
		if (idx) {
			pTls = pthread_getspecific(*idx);
		}
		return(pTls) ;
	}

	void trace_set_tls(TLS_KEY_T* idx, void *add) {
		pthread_once(&trace_tls_once,trace_init_tls);
		if (idx != NULL) {
			pthread_setspecific(*idx,add);
		}
	}

#endif
