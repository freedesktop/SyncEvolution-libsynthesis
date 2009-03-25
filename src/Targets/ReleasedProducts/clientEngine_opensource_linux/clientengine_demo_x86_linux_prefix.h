/* prefix file
 * ===========
 *
 */


// override default in global_options.h:
// use SySync_ as prefix for external C functions
#define SYSYNC_EXTERNAL(_x) SySync_ ## _x
#define SYSYNC_PREFIX "SySync_"

#ifdef __cplusplus
  // include all headers that are suitable for precompiled use
  // - target options can incfluence everything
  #include "target_options.h"
  // - platform specifics
  #include "platform_headers.h"
  // - precompilable headers
  #include "clientengine_custom_precomp.h"
#else
  // include all headers that are suitable for precompiled
  // C version use
  // - target options can incfluence everything
  #include "target_options.h"
  // - platform specifics
  #include "platform_headers.h"
#endif

/* eof */
