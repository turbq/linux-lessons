#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <dlfcn.h>
#include <string.h>

int (*someSecretFunctionPrototype)(int);

bool init_library(const char *libname, const char *funcname){
  int *hdl = dlopen(libname, RTLD_LAZY);
//	printf("trying dlopen with name = %s\n", libname);
  if(NULL == hdl){
//		printf("hdl fault\n");
		return false;
	}
	someSecretFunctionPrototype = (int (*)(int))dlsym(hdl, funcname);
//	printf("trying get pointer for funcname = %s\n",funcname);
	if(NULL == someSecretFunctionPrototype){
//		printf("pointer get fault\n");
		return false;
	}
}

int main(int argc, char *argv[])
{
  int result; 
	char *funcname = argv[2];
  char *libname = NULL;
	
 // printf("result = %d\n", result);
  libname = malloc(sizeof(argv[1])+2);
  sprintf(libname,"./%s",argv[1]);
  //printf("libname = %s\n ", libname);

	if(init_library(libname, funcname)){
		result = someSecretFunctionPrototype(atoi(argv[3]));
    printf("%d\n",result);
	} else {
		printf("Library was not loaded\n");
  }
	return 0;
}
