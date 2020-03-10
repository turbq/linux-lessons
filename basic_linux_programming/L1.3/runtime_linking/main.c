#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <dlfcn.h>
#include <string.h>

int (*someSecretFunctionPrototype)(int);

bool init_library(const char *name){
  int *hdl = dlopen(name, RTLD_LAZY);
  if(NULL == hdl)
		return false;
	someSecretFunctionPrototype = (int (*)(int))dlsym(hdl, name);
	if(NULL == someSecretFunctionPrototype)
		return false;
}

int main(int argc, char *argv[])
{
  int result = atoi(argv[2]);

  printf("result = %d\n", result);
  char *libname = NULL;
  libname = malloc(sizeof(argv[1])+2);
  sprintf(libname,"./%s",argv[1]);
  printf("libname = %s\n ", libname);

	if(init_library(libname)){
		result = someSecretFunctionPrototype;
    printf("%d\n",result);
	} else {
		printf("Library was not loaded\n");
  }
	return 0;
}
