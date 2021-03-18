#include "./myassert.h"
#include <stdio.h> // fprintf()
#include <stdint.h> // int64_t
#include <stdlib.h> // abort()
#include <execinfo.h> // backtrace() backtrace_symbols()
#include <dlfcn.h> // dladdr()
#include <libgen.h> // basename()
#include <string.h>
#include <unistd.h> // STDERR_FILENO

#define MAX_FRAMES 32
#define MY_MAX_PATH 1024
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
  eprintf("\n");
  // eprintf("Assertion failed: (%s), file %s, line %d.\n", failedexpr, file, line);
  eprintf("Assertion failed: (%s), function %s, file %s, line %d.\n", failedexpr, func, file, line);
  eprintf("\n");

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

  // https://stackoverflow.com/q/77005#comment15654678_77005
  // don't use backtrace_symbols() in a signal handler as it might malloc() 
  // char **const ss=backtrace_symbols(addrlist,frames_found);
  // for(int i=0;i<frames_found;++i)
  //   eprintf("%s\n",ss[i]);
  // free(ss);
  backtrace_symbols_fd(addrlist,frames_found,STDERR_FILENO);
  eprintf("\n");

  // backtrace_symbols_fmt() unavailable on macOS
  // char **const fs=backtrace_symbols_fmt(addrlist,frames_found,"%a %n %d %D %f");
  // for(int i=0;i<frames_found;++i)
  //   eprintf("%s\n",fs[i]);
  // free(fs);

  for(int i=0;i<frames_found;++i){
    eprintf("%-3d ",i);

    Dl_info dli={};
    if(1!=dladdr(addrlist[i],&dli)){
      eprintf("dladdr() failure\n");
      abort();
    }

    char path[MY_MAX_PATH]={};
    strcpy(path,dli.dli_fname);
    if(path[MY_MAX_PATH-1]){
      eprintf("path overflow\n");
      abort();
    }
    eprintf("%-35s ",basename(path));
    // eprintf("+ %lu ",addrlist[i]-dli.dli_fbase);

    // eprintf("%p ",addrlist[i]);

    eprintf("%s() ",dli.dli_sname);
    // https://www.freebsd.org/cgi/man.cgi?query=backtrace&format=html#DESCRIPTION
    // 'unsigned ptrdiff_t' (aka 'unsigned long')
    // eprintf("+0x%tx ",addrlist[i]-dli.dli_saddr);
    eprintf("+ %lu ",addrlist[i]-dli.dli_saddr);

    eprintf("\n");
  }
  eprintf("\n");

  abort();

}

