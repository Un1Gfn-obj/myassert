#include "./myassert.h"
#include <stdio.h> // fprintf()
#include <stdint.h> // int64_t
#include <stdlib.h> // abort()

#define eprintf(...) fprintf(stderr,__VA_ARGS__)

// __assert_rtn() -> myassert_rtn()
// https://opensource.apple.com/tarballs/Libc/Libc-1439.40.11.tar.gz
// https://opensource.apple.com/source/Libc/Libc-1439.40.11/gen/FreeBSD/assert.c.auto.html
void myassert_rtn(func, file, line, failedexpr)
  const char *const func;
  const char *const file;
  const int line;
  const char *const failedexpr;
{

  if(!( sizeof(int64_t)==sizeof(const char*) && (int64_t)func>=0 && func )){
    abort();
  }
  // eprintf("Assertion failed: (%s), file %s, line %d.\n", failedexpr, file, line);
  eprintf("Assertion failed: (%s), function %s, file %s, line %d.\n", failedexpr, func, file, line);

  // bt

  abort();

}

