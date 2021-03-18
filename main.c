// Check for conflicts with myassert.h
#include <CFNetwork/CFNetwork.h>
#include <CoreFoundation/CoreFoundation.h>
#include <SystemConfiguration/SCNetworkConfiguration.h>
#include <assert.h>
#include <netinet/in.h> // INET6_ADDRSTRLEN
#include <pwd.h>
#include <stdarg.h>
#include <stdarg.h> // stdarg(3) one_man_army()
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// #include <assert.h>
#include "./myassert.h"

#define eprintf(...) fprintf(stderr,__VA_ARGS__)

void critical_part(){
  // ALL_CFLAGS+=-E
  //   (__builtin_expect(!(0), 0) ? __assert_rtn(__func__, "main.c", 5, "0") : (void)0);
  // asm("nop");
  // myassert(false);
  ++*((int*)(-1));
}

/*void ffff(){
  critical_part();
}

void fff(){
  ffff();
}

void ff(){
  fff();
}

void f(){
  ff();
}*/

void execute(){
  // f();
  critical_part();
}

void lowlevel(){
  execute();
}

void midlevel(){
  asm("nop");
  lowlevel();
}

void highlevel(){
  midlevel();
}

void wrapper(){
  highlevel();
}

void handler(const int sig){
  eprintf("\n");
  eprintf("received signal %d%s\n",sig,(sig==11)?" segmentation fault":"");
  myassert(false);
}

int main(){
  signal(SIGSEGV,handler);
  wrapper();
  return 0;
}
