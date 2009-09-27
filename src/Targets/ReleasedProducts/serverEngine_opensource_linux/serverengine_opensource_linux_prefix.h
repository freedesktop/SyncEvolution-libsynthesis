/* prefix file
 * ===========
 *
 */


// override default in global_options.h:
// use SySync_ as prefix for external C functions
//
// This is the same as in the client engine. As soon
// as the SDK (UI_util.cpp) can handle a different
// server prefix this should be changed so that
// client and server engines can both be linked
// into the same app (other name clashes notwithstanding).
#define SYSYNC_EXTERNAL(_x) SySync_ ## _x
#define SYSYNC_PREFIX "SySync_"

// required before time.h to get tm_gmtoff in struct tm:
// this is used to find standard and daylight saving offset
// of the system, see timezones.cpp
#define _BSD_SOURCE 1
#define USE_TM_GMTOFF 1

#ifdef __cplusplus
  // include all headers that are suitable for precompiled use
  // - target options can incfluence everything
  #include "target_options.h"
  // - platform specifics
  #include "platform_headers.h"
  // - precompilable headers
  #include "serverengine_custom_precomp.h"
#else
  // include all headers that are suitable for precompiled
  // C version use
  // - target options can incfluence everything
  #include "target_options.h"
  // - platform specifics
  #include "platform_headers.h"
#endif

/* eof */
