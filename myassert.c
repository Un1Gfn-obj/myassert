#include "./myassert.h"
#include <stdio.h> // fprintf()
#include <stdint.h> // int64_t
#include <stdlib.h> // abort()
#include <execinfo.h> // -lexecinfo

#define MAX_FRAMES 32
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

  void *addrlist[MAX_FRAMES]={};
  const int frames_found=backtrace(addrlist,MAX_FRAMES);
  // printf("%d\n",frames_found);
  if(frames_found>=MAX_FRAMES){
    eprintf("frame overflow\n");
    abort();
  }
  // 0 myassert_rtn
  // 1            ?
  // 2            ?
  if(frames_found<3){
    eprintf("frame underflow\n");
    abort();
  }

  char **const ss=backtrace_symbols(addrlist,frames_found);
  for(int i=0;i<frames_found;++i)
    eprintf("%s\n",ss[i]);
  free(ss);
  eprintf("\n");

  // printf("0x%tx",1UL); // 'unsigned ptrdiff_t' (aka 'unsigned long')
  // char **const fs=backtrace_symbols_fmt(addrlist,frames_found,"%a %n %d %D %f");
  // for(int i=0;i<frames_found;++i)
  //   eprintf("%s\n",fs[i]);
  // free(fs);
  for(int i=0;i<frames_found;++i){
    eprintf("%d ",i);
    eprintf("%p ",addrlist[i]);
    eprintf("\n");
  }

  abort();

}

