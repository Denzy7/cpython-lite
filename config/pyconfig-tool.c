#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

#ifdef __SIZEOF_INT128__
#warning "int 128 yes"
#else
#warning "int 128 no"
#endif

int main()
{
	long double ld = 3.45155;
	ld+=1.3;

	int sz = sizeof(double);
	printf("SIZEOF_DOUBLE:%d\n", sz);
	
	sz = sizeof(float);
	printf("SIZEOF_FLOAT:%d\n", sz);
	
	sz = sizeof(fpos_t);
	printf("SIZEOF_FPOS_T:%d\n", sz);
	
	sz = sizeof(int);
	printf("SIZEOF_INT:%d\n", sz);
	
	sz = sizeof(long);
	printf("SIZEOF_LONG:%d\n", sz);
	
	sz = sizeof(long double);
	printf("SIZEOF_LONG_DOUBLE:%d\n", sz);
	
	sz = sizeof(long);
	printf("SIZEOF_LONG_LONG:%d\n", sz);
	
	sz = sizeof(off_t);
	printf("SIZEOF_OFF_T:%d\n", sz);
	
	sz = sizeof(pid_t);
	printf("SIZEOF_PID_T:%d\n", sz);
	
	sz = sizeof(pthread_key_t);
	printf("SIZEOF_PTHREAD_KEY_T:%d\n", sz);
	
	sz = sizeof(pthread_t);
	printf("SIZEOF_PTHREAD_T:%d\n", sz);
	
	sz = sizeof(short);
	printf("SIZEOF_SHORT:%d\n", sz);
	
	sz = sizeof(size_t);
	printf("SIZEOF_SIZE_T:%d\n", sz);
	
	sz = sizeof(time_t);
	printf("SIZEOF_TIME_T:%d\n", sz);
	
	sz = sizeof(uintptr_t);
	printf("SIZEOF_UINTPTR_T:%d\n", sz);
	
	sz = sizeof(void*);
	printf("SIZEOF_VOID_P:%d\n", sz);
	
	sz = sizeof(wchar_t);
	printf("SIZEOF_WCHAR_T:%d\n", sz);
	
	sz = sizeof(_Bool);
	printf("SIZEOF__BOOL:%d\n", sz);
	

	printf("Hello World!\n");
	int s = mbstowcs(NULL, "text", 0);
	printf("%d, %s", s, "asdas");
		
}
