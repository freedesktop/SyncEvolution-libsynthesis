/*
 *  File:         timezones.h
 *
 *  Author:       Beat Forster
 *
 *  Timezones conversion from/to linear time scale.
 *
 *  Copyright (c) 2004-2009 by Synthesis AG (www.synthesis.ch)
 *
 *  2004-04-18 : bfo : initial version
 *
 */

#ifndef TIMEZONES_H
#define TIMEZONES_H

#include <string>
#include <list>

#include "lineartime.h"
#include "debuglogger.h"

#ifdef MUTEX_SUPPORT
  #include "platform_mutex.h"
#endif


using namespace std; // for string and list

namespace sysync {

#include "tz_table.h"


//const int DST_Bias= 60; // General DST offset (in minutes)

// Symbian timezone categories
// visible for all other systems as well
#ifndef __EPOC_OS__
  enum TDaylightSavingZone {
    EDstHome    =0x40000000,
    EDstNone    =0,
    EDstEuropean=1,
    EDstNorthern=2,
    EDstSouthern=4
  };
#endif


// Offset mask
const uInt32 TCTX_OFFSETMASK = 0x0000FFFF;

// time context flags
// - symbolic zone flag
const uInt32 TCTX_SYMBOLIC_TZ= 0x00010000;
// - rendering flags
const uInt32 TCTX_DATEONLY   = 0x00020000;
const uInt32 TCTX_TIMEONLY   = 0x00040000;
const uInt32 TCTX_DURATION   = 0x00080000;

const uInt32 TCTX_RFLAGMASK = TCTX_DATEONLY+TCTX_TIMEONLY+TCTX_DURATION;

//! Get signed minute offset
sInt16  TCTX_MINOFFSET( timecontext_t tctx );

//! Get time zone enum
TTimeZones TCTX_TZENUM( timecontext_t tctx );


// macro to get time zone context
#define TCTX_ENUMCONTEXT( tzenum ) ((timecontext_t)      (tzenum | TCTX_SYMBOLIC_TZ))
#define TCTX_UNKNOWN                           TCTX_ENUMCONTEXT( tctx_tz_unknown )
#define TCTX_SYSTEM                            TCTX_ENUMCONTEXT( tctx_tz_system  )
#define TCTX_UTC                               TCTX_ENUMCONTEXT( tctx_tz_UTC  )
#define TCTX_OFFSCONTEXT( offs )   ((timecontext_t)((sInt16)(offs) & TCTX_OFFSETMASK ))


/*
// macro to get time zone and other flags
#define TCTX_IS_TZ( tctx )         ((bool)(tctx  & TCTX_SYMBOLIC_TZ))
#define TCTX_IS_DATEONLY( tctx )   ((bool)(tctx  & TCTX_DATEONLY   ))
*/

//! Check if <tctx> is a symbolic TZ info
bool TCTX_IS_TZ      ( timecontext_t tctx );

// Check if <tctx> is a built-in symbolic TZ info
bool TCTX_IS_BUILTIN ( timecontext_t tctx );

//! Check if <tctx> has TCTX_DATEONLY mode set
bool TCTX_IS_DATEONLY( timecontext_t tctx );

//! Check if <tctx> has TCTX_TIMEONLY mode set
bool TCTX_IS_TIMEONLY( timecontext_t tctx );

//! Check if <tctx> has TCTX_DURATION mode set
bool TCTX_IS_DURATION( timecontext_t tctx );

//! Check if <tctx> is a unknown time zone
bool TCTX_IS_UNKNOWN ( timecontext_t tctx );

//! Check if <tctx> is the system time zone
bool TCTX_IS_SYSTEM  ( timecontext_t tctx );

//! Check if <tctx> is the UTC time zone
bool TCTX_IS_UTC  ( timecontext_t tctx );

//! result is render flags from <aRFlagContext> with zone info from <aZoneContext>
timecontext_t TCTX_JOIN_RFLAGS_TZ ( timecontext_t aRFlagContext, timecontext_t aZoneContext );



#ifdef OLD_TIME_HANDLING
// %%% obsolete with new iso8601.cpp implementation

//! Convert ISO8601 string into lineartime value and context info
bool ISO8601ToLineartimeAndContext( const char    *aISOstr,
                                    lineartime_t  &aValue,
                                    timecontext_t &aContext,
                                    timecontext_t  aDefault= TCTX_UNKNOWN );

//! Convert lineartime value and context info into ISO8601 string
bool LineartimeAndContextToISO8601( lineartime_t   aValue,
                                    timecontext_t  aContext,
                                    string        &aISOstr,
                                    bool           aWithTZ= false,
                                    bool           aExtendedFormat= false );


//! Get context info out of ISO8601 string
bool ISO8601ToTzContext           ( const char    *aISOstr,
                                    timecontext_t &aContext,
                                    timecontext_t  aDefault= TCTX_UNKNOWN );

//! Get ISO8601 string out of context info
bool TzContextToISO8601           ( timecontext_t  aContext,
                                    string        &aISOstr,
                                    lineartime_t   aRefForUTCplusNformat= 0,
                                    bool           aExtendedFormat= false );

#endif


// ---- utility functions -------------------------------------------------------------
/*! Specific bias string. Unit: hours */
string BiasStr( int bias );

/*! Clear the DST info of <t> */
void ClrDST( tz_entry &t );


// ---- list definition for additional time zones -------------------------------------
class TZInfo {
  public:
    tz_entry t;
    string   tName;
    string   tIdent;
    string   tDynY;
}; // TZInfo

typedef std::list<TZInfo*> TZList;

class GZones {
  public:
    GZones() {
      #ifdef MUTEX_SUPPORT
        muP= newMutex();
      #endif

      predefinedSysTZ= TCTX_UNKNOWN; // no predefined system time zone
      sysTZ= predefinedSysTZ; // default to predefined zone, if none, this will be obtained from OS APIs
      isDbg= false; // !!! IMPORTANT: do NOT enable this except for test targets, as it leads to recursions (debugPrintf calls time routines!)

      #ifdef SYDEBUG
        getDbgMask  = 0;
        getDbgLogger= NULL;
      #endif
    } // constructor

    void ResetCustomTZ(void);

    void ResetCache(void) {
      sysTZ= predefinedSysTZ; // reset cached system time zone to make sure it is re-evaluated
    }

    void CopyCustomTZFrom(GZones &aSourceZones);

    #ifdef MUTEX_SUPPORT
      MutexPtr_t muP; // mutex for the thread list
    #endif

    TZList                    tzP; // the list of additional time zones
    timecontext_t predefinedSysTZ; // can be set to a specific zone to override zone returned by OS API
    timecontext_t           sysTZ; // the system's time zone, will be calculated,
                                   // if set to tctx_tz_unknown
    bool                    isDbg; // write debug information

    #ifdef SYDEBUG
      uInt32        getDbgMask; // allow debugging in a specific context
      TDebugLogger* getDbgLogger;
    #endif
}; // GZones



// visible for debugging only
timecontext_t SystemTZ( GZones *g, bool isDbg= false );
timecontext_t SelectTZ( TDaylightSavingZone zone, int bias, int biasDST, lineartime_t tNow,
                                   bool isDbg= false );



/*! Get <tz_entry> from <aContext>
 *                   or <std>/<dst>
 */
bool GetTZ( timecontext_t aContext,                        tz_entry &t, GZones* g, int year= 0 );
bool GetTZ( string std, string dst, int bias, int biasDST, tz_entry &t, GZones* g );

/*! Get the current year
 */
sInt16 MyYear( GZones* g );


/*! Returns true, if the given TZ is existing already
 *    <t>            tz_entry to search for:
 *                   If <t.name> == ""  search for any entry with these values.
 *                      <t.name> != ""  name must fit
 *                   If <t.ident>== ""  search for any entry with these values
 *                      <t.ident>!= ""  ident must fit
 *                      <t.ident>== "?" search for the name <t.name> only.
 *
 *    <aName>        is <t.name> of the found record
 *    <aContext>     is the assigned context
 *    <g>            global list of additional time zones
 *    <createIt>     create an entry, if not yet existing / default: false
 *    <searchOffset> says, where to start searching       / default: at the beginning
 */
bool FoundTZ( tz_entry t, string        &aName,
                          timecontext_t &aContext,
                          GZones*       g,
                          bool          createIt    = false,
                          timecontext_t searchOffset= tctx_tz_unknown );


/*! Remove an existing entry
 *  Currently, elements of the hard coded list can't be removed
 */
bool RemoveTZ( tz_entry t, GZones* g );


/*! Is it a DST time zone ? (both months must be defined for DST mode) */
bool DSTCond( tz_entry t );

/*! Adjust to day number within month <m>, %% valid till year <y> 2099 */
void AdjustDay( sInt16 &d, sInt16 m, sInt16 y );

/*! Get lineartime_t of <t> for a given <year>, either from std <toDST> or vice versa */
lineartime_t DST_Switch( tz_entry t, int bias, sInt16 aYear, bool toDST );

/*! Convert time zone name into context
 *  @param[in]  aName    : context name to resolve
 *  @param[out] aContext : context for this aName
 *  @param[in]  g        : global list of additional time zones
 *
 */
bool TimeZoneNameToContext( cAppCharP aName, timecontext_t &aContext, GZones* g );

/*! Convert context into time zone name, a preferred name can be given
 *  @param[in]  aContext   : time context to resolve
 *  @param[out] aName      : context name for this aContext
 *  @param[in]  g          : global list of additional time zones
 *  @param[in]  aPrefIdent : preferred name, if more than one is fitting
 *
 */
bool TimeZoneContextToName( timecontext_t aContext, string &aName, GZones* g, cAppCharP aPrefIdent= "" );



/*! get system's time zone context (i.e. resolve the TCTX_SYSTEM meta-context)
 *  @param[in,out] aContext : context will be made non-meta, that is, if input is TCTX_SYSTEM,
 *                            actual time zone will be determined.
 *  @param[in] g            : global list of additional time zones
 */
bool TzResolveMetaContext( timecontext_t &aContext, GZones* g );

/*! make time context non-symbolic (= calculate minute offset east of UTC for aRefTime)
 *  but retain other time context flags in aContext
 *  @param[in,out] aContext : context will be made non-symbolic, that is resolved to minute offset east of UTC
 *  @param[in] aRefTime     : reference time point for resolving the offset
 *  @param[in] aRefTimeUTC  : if set, reference time must be UTC,
 *                            otherwise, reference time must be in context of aContext
 *  @param[in] g            : global list of additional time zones
 */
bool TzResolveContext( timecontext_t &aContext, lineartime_t aRefTime, bool aRefTimeUTC, GZones* g );

/*! calculate minute offset east of UTC for aRefTime
 *  @param[in] aContext       : time context to resolve
 *  @param[out] aMinuteOffset : receives minute offset east of UTC
 *  @param[in] aRefTime       : reference time point for resolving the offset
 *  @param[in] aRefTimeUTC    : if set, reference time must be UTC,
 *                              otherwise, reference time must be in context of aContext
 *  @param[in] g              : global list of additional time zones
 */
bool TzResolveToOffset( timecontext_t aContext, sInt16      &aMinuteOffset,
                                                lineartime_t aRefTime,
                                                bool         aRefTimeUTC,
                                                GZones*      g );


/*! Offset between two contexts (in seconds)
 *  Complex time zones (type "$") can't be currently resolved, they return false
 *  @param[in] aSourceValue   : reference time for which the offset should be calculated
 *  @param[in] aSourceContext : source time zone context
 *  @param[in] aTargetContext : source time zone context
 *  @param[out] sDiff         : receives offset east of UTC in seconds
 *  @param[in] g              : global list of additional time zones
 *  @param[in] aDefaultContext: default context to use if source or target is TCTX_UNKNOWN
 */
bool TzOffsetSeconds( lineartime_t aSourceValue, timecontext_t aSourceContext,
                                                 timecontext_t aTargetContext,
                                                 sInt32        &sDiff,
                                                 GZones*       g,
                                                 timecontext_t aDefaultContext= TCTX_UNKNOWN);



/*! Converts timestamp value from one zone to another
 *  Complex time zones (type "$") can't be currently resolved, they return false
 *  @param[in/out] aValue     : will be converted from source context to target context
 *  @param[in] aSourceContext : source time zone context
 *  @param[in] aTargetContext : source time zone context
 *  @param[in] g              : global list of additional time zones
 *  @param[in] aDefaultContext: default context to use if source or target is TCTX_UNKNOWN
 */
bool TzConvertTimestamp( lineartime_t &aValue,   timecontext_t aSourceContext,
                                                 timecontext_t aTargetContext,
                                                 GZones*       g,
                                                 timecontext_t aDefaultContext = TCTX_UNKNOWN);


/*! Prototypes for platform-specific implementation of time-zone-related routines
 *  which are implemented in platform_time.cpp
 */

/*! @brief get system real time
 *  @return system's real time in lineartime_t scale, in specified time zone context
 *  @param[in] aTimeContext : desired output time zone
 *  @param[in] g            : global list of additional time zones
 *  @param[in] aNoOffset    : no offset calculation, if true (to avoid recursive calls)
 */
lineartime_t getSystemNowAs( timecontext_t aTimeContext, GZones* g, bool aNoOffset= false );




} // namespace sysync

#endif
/* eof */
