#pragma once

#ifdef NDEBUG

#define assert_m(expr, msg) (__ASSERT_VOID_CAST(0))

#else

#define assert_m(expr, msg) \
  ((expr) \
   ? __ASSERT_VOID_CAST(0) \
   : __assert_fail(msg, __FILE__, __LINE__, __ASSERT_FUNCTION))

#endif
