// meld /opt/theos/sdks/iPhoneOS14.4.sdk/usr/include/assert.h myassert.h

#ifndef MYASSERT_H
#define MYASSERT_H

#include <sys/cdefs.h> // __dead2 __cold __disable_tail_calls

// NO other assertion headers should be allowed
// #if defined assert || defined __assert || defined static_assert || defined _ASSERT_H_ || defined __ASSERT_H__ || defined ASSERT_H
// #error
// #endif

// The following macros should NOT be defined
#if defined NDEBUG || defined __OBJC__ || defined __cplusplus || defined __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__
#error
#endif

// The following macros should be defined
#if defined __GNUC__ && defined __DARWIN_UNIX03 && __DARWIN_UNIX03 == 1 && defined __STDC_VERSION__ && __STDC_VERSION__ >= 201112L
#else
#error
#endif

// __assert_rtn() -> myassert_rtn()
// https://opensource.apple.com/tarballs/Libc/Libc-1439.40.11.tar.gz
// https://opensource.apple.com/source/Libc/Libc-1439.40.11/gen/FreeBSD/assert.c.auto.html
void myassert_rtn(const char *, const char *, int, const char *) __dead2 __cold __disable_tail_calls;

// e !e  b
// 0  1  myassert_rtn()
// N  0  (void)0
#define myassert(e) (__builtin_expect(!(e), 0) ? myassert_rtn(__func__, __FILE__, __LINE__, #e) : (void)0)

#endif /* MYASSERT_H */
