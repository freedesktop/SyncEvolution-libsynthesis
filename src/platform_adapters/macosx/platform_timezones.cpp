/*
 *  File:         platform_timezones.cpp
 *
 *  Author:       Lukas Zeller
 *
 *  Time zone dependent routines for Mac OS X
 *
 *  Copyright (c) 2004-2011 by Synthesis AG + plan44.ch
 *
 *  2009-04-02 : Created by Lukas Zeller
 *
 */

#include "timezones.h"

namespace sysync {

/* Note: this is ugly poor man's implementation and only uses plain Unix facilities to hopefully
 *       find the time zone (by name).
 *       The plan is to enhance this using Foundation APIs later
 */


/*! @brief platform specific loading of time zone definitions
 *  @return true if this list is considered complete (i.e. no built-in zones should be used additionally)
 *  @param[in/out] aGZones : the GZones object where system zones should be loaded into
 */
bool loadSystemZoneDefinitions(GZones* aGZones)
{
  // load zones from system here
  // ...
  // return true if this list is considered complete (i.e. no built-in zones should be used additionally)
  return false; // we need the built-in zones
} // loadSystemZoneDefinitions


/*! @brief we use this callback to add and log libical time zone handling
 *
 * The advantage is that this handling can be logged. The disadvantage
 * is that these time zones cannot be used in the configuration. Builtin
 * time zones (if any) have to be used there.
 */
void finalizeSystemZoneDefinitions(GZones* aGZones)
{
  /* nop for now */
} // finalizeSystemZoneDefinitions



/*! @brief get current system time zone
 *  @return true if successful
 *  @param[out] aContext : the time zone context representing the current system time zone.
 *  @param[in] aGZones : the GZones object.
 */
bool getSystemTimeZoneContext(timecontext_t &aContext, GZones* aGZones)
{
  tz_entry t;
  bool ok = true;

  tzset();
  t.name = tzname[ 0 ];
  if (strcmp( t.name.c_str(),tzname[ 1 ] )!=0) {
    t.name+= "/";
    t.name+= tzname[ 1 ];
  } // if

  //if (isDbg) PNCDEBUGPRINTFX( DBG_SESSION, ( "Timezone: %s", sName.c_str() ));

  // search based on name before potentially using offset search
  ok = TimeZoneNameToContext( t.name.c_str(),aContext, aGZones );

  return ok;
} // getSystemTimeZoneContext





} // namespace sysync

/* eof */