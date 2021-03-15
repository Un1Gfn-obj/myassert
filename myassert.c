#include "./myassert.h"
#include <stdio.h> // fprintf()
#include <stdint.h> // int64_t
#include <stdlib.h> // abort()

#define eprintf(...) fprintf(stderr,__VA_ARGS__)

void myassert_rtn(func, file, line, failedexpr)
  const char *const func;
  const char *const file;
  const int line;
  const char *const failedexpr;
{

  if(!( sizeof(int64_t)==sizeof(const char*) && (int64_t)func>=0 )){
    eprintf("illegal funcname pointer\n");
    abort();
  }
  // "%s:%d: failed assertion `%s'\n",file, line, failedexpr
  if(func)
    eprintf("Assertion failed: (%s), function %s, file %s, line %d.\n", failedexpr, func, file, line);
  else
    eprintf("Assertion failed: (%s), file %s, line %d.\n", failedexpr, file, line);

  // bt

  abort();

}

