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

void critical_part(){
  // ALL_CFLAGS+=-E
  //   (__builtin_expect(!(0), 0) ? __assert_rtn(__func__, "main.c", 5, "0") : (void)0);
  myassert(0);
}

void execute(){
  critical_part();
}

void wrapper(){
  execute();
}

int main(){
  wrapper();
  return 0;
}
