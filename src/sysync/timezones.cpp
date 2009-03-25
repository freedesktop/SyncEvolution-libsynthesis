/*
 *  File:         timezones.cpp
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


/* ToDo / open issues
 *
 * 1) done 04/04/18  <aISOstr> does not contain TZ info, how to bring it in ? -> new param
 * 2)      04/04/18  <aOffsetSecs> not yet limited to one day
 * 3) done 04/04/18  Is 20040101Z a valid 8601 ? (yes it is)
 * 4) done 04/04/20  Fill in all valid time zones
 * 5) done 04/04/20  Adapt straight forward conversions Enum <=> Name
 * 6) done 04/06/14  System time zone calculation for Linux
 * 7) done 04/06/14  InsertTZ / RemoveTZ implementation
 * 8)      06/04/12  Offset calculation for more complicated vTZ ("$") records
 * 9) done 07/02/26  Multi year list support
 */

// must be first in file, everything above is ignored by MVC compilers
#include "prefix_file.h"

#define TIMEZONES_INTERNAL 1

#if defined _WIN32 && !defined __EPOC_OS__
  #include <windows.h>
#endif

// do not import the whole thing to make life easier for standalone apps
#ifdef FULLY_STANDALONE
  #include "sysync_globs.h"
  #include "sysync_debug.h"
#else
  #include "sysync.h"
#endif

#include "lineartime.h"
#include "timezones.h"
#include "iso8601.h"
#include "stringutils.h"

#ifdef __EPOC_OS__
  #include <sys/time.h>
  #include <t32wld.h>
#endif

#ifdef LINUX
  extern char *tzname[ 2 ];
  #ifndef BSD
    extern long  timezone;
  #endif
  extern int   daylight;
#endif


namespace sysync {


/*
// ---- global structure -----------------------------------------------------------
#ifndef __EPOC_OS__
  GZones global_gz;
#endif


static GZones* gz()
{
  #ifdef __EPOC_OS__
    return NULL; // %%%% not yet implemented
  #else
    return &global_gz;
  #endif
} // gz
*/

// ---------------------------------------------------------------------------------
// GZones

void GZones::ResetCustomTZ(void)
{
  TZList::iterator pos;
  for (pos=tzP.begin(); pos!=tzP.end(); pos++) {
    delete (*pos);
  }
  tzP.clear();
} // GZones::ResetCustomTZ


void GZones::CopyCustomTZFrom(GZones &aSourceZones)
{
  TZList::iterator pos;
  // delete my existing custom TZ, if any
  ResetCustomTZ();
  // copy from source zones
  for (pos=aSourceZones.tzP.begin(); pos!=aSourceZones.tzP.end(); pos++) {
    // create empty info record
    TZInfo *tzInfoP = new TZInfo;
    // copy eventually predefined system zone
    predefinedSysTZ = aSourceZones.predefinedSysTZ;
    // copy from source zones
    *tzInfoP = *(*pos);
    // append to my own list
    tzP.push_back(tzInfoP);
  }
} // GZones::CopyCustomTZFrom




// ---------------------------------------------------------------------------------
// Get signed minute offset
sInt16 TCTX_MINOFFSET( timecontext_t tctx ) {
  return (sInt16)(tctx & TCTX_OFFSETMASK );
} // TCTX_MINOFFSET


// Get time zone enum
TTimeZones TCTX_TZENUM( timecontext_t tctx ) {
  return (TTimeZones)(tctx & TCTX_OFFSETMASK );
} // TCTX_TZENUM


// Check if <tctx> is a symbolic TZ info
bool TCTX_IS_TZ( timecontext_t tctx ) {
  return (tctx & TCTX_SYMBOLIC_TZ)!=0;
} // TCTX_IS_TZ


// Check if <tctx> is a built-in symbolic TZ info
bool TCTX_IS_BUILTIN( timecontext_t tctx ) {
  return
    (tctx & TCTX_SYMBOLIC_TZ) && // is a symbolic time zone
    (TCTX_TZENUM(tctx)<tctx_numtimezones); // and is in the internal list
} // TCTX_IS_BUILTIN


// Check if <tctx> has TCTX_DATEONLY mode set (but not TIMEONLY - both set means same as both not set)
bool TCTX_IS_DATEONLY( timecontext_t tctx ) {
  return (tctx  & TCTX_DATEONLY) && !(tctx  & TCTX_TIMEONLY);
} // TCTX_IS_DATEONLY


// Check if <tctx> has TCTX_TIMEONLY mode set (but not DATEONLY - both set means same as both not set)
bool TCTX_IS_TIMEONLY( timecontext_t tctx ) {
  return (tctx  & TCTX_TIMEONLY) && !(tctx  & TCTX_DATEONLY);
} // TCTX_IS_TIMEONLY


// Check if <tctx> has TCTX_DURATION mode set
bool TCTX_IS_DURATION( timecontext_t tctx ) {
  return ( tctx  & TCTX_DURATION )!=0;
} // TCTX_IS_DURATION


// Check if <tctx> is a unknown time zone
bool TCTX_IS_UNKNOWN( timecontext_t tctx ) {
  return TCTX_IS_TZ( tctx ) && ( TCTX_TZENUM( tctx )==tctx_tz_unknown );
} // TCTX_IS_UNKNOWN


// Check if <tctx> is the system time zone
bool TCTX_IS_SYSTEM ( timecontext_t tctx ) {
  return TCTX_IS_TZ( tctx ) && ( TCTX_TZENUM( tctx )==tctx_tz_system );
} // TCTX_IS_SYSTEM


// Check if <tctx> is the UTC time zone
bool TCTX_IS_UTC ( timecontext_t tctx ) {
  return TCTX_IS_TZ( tctx ) && ( TCTX_TZENUM( tctx )==tctx_tz_UTC );
} // TCTX_IS_SYSTEM


//! result is render flags from <aRFlagContext> with zone info from <aZoneContext>
timecontext_t TCTX_JOIN_RFLAGS_TZ ( timecontext_t aRFlagContext, timecontext_t aZoneContext )
{
  return
    (aRFlagContext &  TCTX_RFLAGMASK) |
    (aZoneContext  & ~TCTX_RFLAGMASK);
} // TCTX_JOIN_RFLAGS_TZ



#ifdef OLD_TIME_HANDLING
// %%% obsolete with new iso8601.cpp implementation


bool ISO8601ToLineartimeAndContext( const char*    aISOstr,
                                    lineartime_t  &aValue,
                                    timecontext_t &aContext,
                                    timecontext_t  aDefault )
{
  bool      ok, aWithTime, aIsUTC, aWithOffset;
  long      aOffsetSecs;
  struct_tm tim;

       ok= ISO8601ToTm( aISOstr, tim, aWithTime, aIsUTC, aWithOffset, aOffsetSecs );
  if (!ok) return false;

  aValue= tm2lineartime( &tim );

  /* special case, if <aTZ> is defined already */
  if (aIsUTC && aDefault!=TCTX_UNKNOWN
             && tim.tm_hour==0
             && tim.tm_min ==0
             && tim.tm_sec ==0) { aIsUTC= false; aWithOffset= false; }

  if (aIsUTC || aWithOffset) aContext=  TCTX_OFFSETMASK & (aOffsetSecs/SecsPerMin);
  else                       aContext=  aDefault;
  if (!aWithTime)            aContext|= TCTX_DATEONLY;

  return true;
} /* ISO8601ToLineartimeAndContext */



bool LineartimeAndContextToISO8601( lineartime_t  aValue,
                                    timecontext_t aContext,
                                    string       &aISOstr,
                                    bool          aWithTZ,
                                    bool          aExtendedFormat )
{
  bool      aWithTime, aIsUTC, aWithOffset;
  long      aOffsetSecs= 0;
  struct_tm tim;

  lineartime2tm( aValue, &tim );

  aWithTime  = !TCTX_IS_DATEONLY(aContext);
  aWithOffset= !TCTX_IS_TZ      (aContext);

  if     (aWithOffset)   aOffsetSecs= TCTX_MINOFFSET(aContext)*SecsPerMin;
  aIsUTC= aWithOffset && aOffsetSecs==0;

  tmToISO8601( tim, aISOstr, aWithTime,aIsUTC,aWithOffset,aOffsetSecs );
  return true;
} /* LineartimeAndContextToIso8601 */



bool ISO8601ToTzContext( const char*    aISOstr,
                         timecontext_t &aContext,
                         timecontext_t  aDefault )
{
  lineartime_t aValue;
  return ISO8601ToLineartimeAndContext( aISOstr, aValue,aContext, aDefault );
} /* ISO8601ToTzContext */



bool TzContextToISO8601( timecontext_t aContext,
                         string       &aISOstr,
                         lineartime_t  aRefForUTCplusNformat,
                         bool          aExtendedFormat )
{
  return LineartimeAndContextToISO8601( aRefForUTCplusNformat, aContext,
                                        aISOstr, aExtendedFormat );
} /* TzContextToISO8601 */


#endif // OLD_TIME_HANDLING


// ---- utility functions --------------------------------------------------------------
// Specific bias string. Unit: hours
string BiasStr( int bias )
{
  char hrs[ 80 ];
  float f= (float)bias/MinsPerHour;

  if          (bias % MinsPerHour == 0) sprintf( hrs,"%3.0f    ", f ); // not with .0
  else if (abs(bias % MinsPerHour)==30) sprintf( hrs,"%5.1f  ",   f );
  else                                  sprintf( hrs,"%6.2f ",    f );

  return hrs;
} // BiasStr


// Clear the DST info of <t>
void ClrDST( tz_entry &t )
{
  memset( &t.dst, 0, sizeof(t.dst) );
  memset( &t.std, 0, sizeof(t.std) );
} // ClrDST


// -------------------------------------------------------------------------------------
// Special cases: <year> =  0, the one w/o dynYear
//                       = -1, direct index
bool GetTZ( timecontext_t aContext, tz_entry &t, GZones* g, int year )
{
  if (!TCTX_IS_TZ( aContext )) return false;

  int           aTZ= aContext & TCTX_OFFSETMASK;
  if (aTZ>=0 && aTZ<tctx_numtimezones) {
    while (true) {
      t= tz[ aTZ ]; if (strcmp( t.dynYear,"" )==0 || year==-1) break; // replace it by a non-dynYear
      if    (aTZ==0)                                           break;
             aTZ--;
    } // while

    if (year<=0) return true;

    int    nx=  aTZ+1;
    while (nx<tctx_numtimezones) { // search for the dynamic year
      if (strcmp( t.name, tz[ nx ].name )!=0) break; // no or no more
      t=                  tz[ nx ];
      if (year<=atoi( t.dynYear )) break; // this is the year line we are looking for
      nx++;
    } // while

    return true; // this is it !!
  } // if

  t= tz[ tctx_tz_unknown ];  // default, if not yet ok
  if (g==NULL) return false; // If there is no <g>, it is definitely false

  // -----------------------
  bool ok= false;
//if (g==NULL) g= gz();      // either <g> or global list

  #ifdef MUTEX_SUPPORT
    lockMutex( g->muP );
  #endif

  int  i = tctx_numtimezones;
  TZList::iterator pos;
  for (pos= g->tzP.begin();          // go thru the additional list
       pos!=g->tzP.end(); pos++) {
    if   (aTZ==i &&                  // no removed elements !!
         !((*pos)->tIdent=="-")) {
      t =  (*pos)->t;
      ok= true;
      if (year<=0) break; // pass unlock now

             pos++;
      while (pos!=g->tzP.end()) { // search for the dynamic year
        if (strcmp( t.name, (*pos)->t.name )!=0) break; // no or no more
        t=                  (*pos)->t;
        if (year<=atoi( t.dynYear )) break; // this is the year line we are looking for
        pos++;
      } // while

      break; // pass unlock now
    } // if

    i++;
  } // for

  #ifdef MUTEX_SUPPORT
    unlockMutex( g->muP );
  #endif
  // -----------------------

  return ok;
} /* GetTZ */



static void Get_tChange( lineartime_t tim, tChange &v, bool asDate= false )
{
  sInt16 y, day, d, sec, ms;

  lineartime2date( tim, &y,       &v.wMonth,  &day );
  lineartime2time( tim, &v.wHour, &v.wMinute, &sec, &ms );

  if (asDate) {
    v.wDayOfWeek=  -1; // use it as date directly
    v.wNth      = day;
  }
  else {
    v.wDayOfWeek= lineartime2weekday( tim );
    v.wNth      = ( day-1 ) / DaysPerWk + 1;

    if (v.wNth==4) { // the last one within month ?
                 d= day + DaysPerWk;
      AdjustDay( d, v.wMonth, y );
      if       ( d==day ) v.wNth= 5;
    } // if
  } // if
} // Get_tChange



static bool Fill_tChange( string iso8601, int bias, int biasDST, tChange &tc, bool isDST )
{
  lineartime_t  l;
  timecontext_t c;
//sInt16        y, day, d, sec, ms;

  string::size_type rslt= ISO8601StrToTimestamp( iso8601.c_str(), l, c );
  if    (rslt!=iso8601.length()) return false;

  int                     bMins = bias;
  if (!isDST)             bMins+= biasDST;
  l+= seconds2lineartime( bMins*SecsPerMin );

  Get_tChange( l, tc );

  /*
  lineartime2date( l, &y,        &tc.wMonth,  &day );
  lineartime2time( l, &tc.wHour, &tc.wMinute, &sec, &ms );
  tc.wDayOfWeek= lineartime2weekday( l );
  tc.wNth      = ( day-1 ) / DaysPerWk + 1;

  if (tc.wNth==4) { // the last one within month ?
               d= day + DaysPerWk;
    AdjustDay( d, tc.wMonth, y );
    if       ( d==day ) tc.wNth= 5;
  } // if
  */

  return true;
} // Fill_tChange


bool GetTZ( string std, string dst, int bias, int biasDST, tz_entry &t, GZones* g )
{
  t.name   = "";
  t.bias   = bias;
  t.biasDST= biasDST;
  t.ident  = "";
  t.dynYear= "";

  return Fill_tChange( std, bias,biasDST, t.std, false ) &&
         Fill_tChange( dst, bias,biasDST, t.dst, true  );
} // GetTZ


static bool Same_tChange( const tChange &tCh1, const tChange &tCh2 )
{
  return tCh1.wMonth    ==tCh2.wMonth     &&
         tCh1.wDayOfWeek==tCh2.wDayOfWeek &&
         tCh1.wNth      ==tCh2.wNth       &&
         tCh1.wHour     ==tCh2.wHour      &&
         tCh1.wMinute   ==tCh2.wMinute;
} // Same_tChange


/*! Compare time zone information */
static bool tzcmp( tz_entry &t, const tz_entry &tzi )
{
  if         (t.name[ 0 ]!='\0' &&
     strucmp( t.name, tzi.name )!=0) return false;

  bool idN=  t.ident==NULL;
  if (!idN && strcmp ( t.ident,"?"       )==0 && // search for the name only
              strucmp( t.name, tzi.name  )==0) return true;

  if (!idN && strcmp ( t.ident,"$"       )==0 &&
              strcmp ( t.ident,tzi.ident )==0 &&
              strucmp( t.name, tzi.name  )==0) return true;

  /*
  PNCDEBUGPRINTFX( DBG_SESSION,( "tS   m=%d dw=%d n=%d h=%d M=%d\n",   t.std.wMonth,   t.std.wDayOfWeek,   t.std.wNth,
                                                                       t.std.wHour,    t.std.wMinute ) );
  PNCDEBUGPRINTFX( DBG_SESSION,( "tD   m=%d dw=%d n=%d h=%d M=%d\n",   t.dst.wMonth,   t.dst.wDayOfWeek,   t.dst.wNth,
                                                                       t.dst.wHour,    t.dst.wMinute ) );
  PNCDEBUGPRINTFX( DBG_SESSION,( "tziS m=%d dw=%d n=%d h=%d M=%d\n", tzi.std.wMonth, tzi.std.wDayOfWeek, tzi.std.wNth,
                                                                     tzi.std.wHour,  tzi.std.wMinute ) );
  PNCDEBUGPRINTFX( DBG_SESSION,( "tziD m=%d dw=%d n=%d h=%d M=%d\n", tzi.dst.wMonth, tzi.dst.wDayOfWeek, tzi.dst.wNth,
                                                                     tzi.dst.wHour,  tzi.dst.wMinute ) );

  PNCDEBUGPRINTFX( DBG_SESSION,( "t    bs=%d bd=%d\n",   t.bias,   t.biasDST ) );
  PNCDEBUGPRINTFX( DBG_SESSION,( "tzi  bs=%d bd=%d\n", tzi.bias, tzi.biasDST ) );
  */

  if (t.bias!=tzi.bias) return false; // bias must be identical

  bool   tIsDst= DSTCond( t   );
  bool tziIsDst= DSTCond( tzi );
  if (tIsDst!=tziIsDst) return false; // DST cond must be on or off for both

  if (tIsDst) {
  //if (memcmp(&t.dst,    &tzi.dst, sizeof(t.dst))!=0 ||
  //    memcmp(&t.std,    &tzi.std, sizeof(t.std))!=0 ||
    if (!Same_tChange( t.dst,     tzi.dst ) ||
        !Same_tChange( t.std,     tzi.std ) ||
                       t.biasDST!=tzi.biasDST) return false;
  } // if

  return strcmp( "-",       tzi.ident )!=0 && // not removed
               (   idN                     ||
         strcmp( t.ident,   ""        )==0 ||
         strcmp( t.ident,   tzi.ident )==0 );

  /*
  return memcmp(&t.dst,    &tzi.dst, sizeof(t.dst))==0 &&
         memcmp(&t.std,    &tzi.std, sizeof(t.std))==0 &&
                 t.bias   ==tzi.bias                   &&
                 t.biasDST==tzi.biasDST                && //%%% luz: this must be compared as well
         strcmp( "-",       tzi.ident )!=0             && // removed
               (   idN                     ||
         strcmp( t.ident,   ""        )==0 ||
         strcmp( t.ident,   tzi.ident )==0 );
  */
} // tzcmp



sInt16 MyYear( GZones* g )
{
  sInt16 y, m, d;

  lineartime_t     t= getSystemNowAs( TCTX_UTC, g, true );
  lineartime2date( t, &y,&m,&d );
  return y;
} // MyYear


static bool YearFit( tz_entry t, int i, GZones* g )
{
  int                               yearS;
  if (strcmp( t.dynYear,"CUR" )==0) yearS= MyYear( g );
  else                              yearS= atoi( t.dynYear );
  if                               (yearS==0) return true;

  int yearI= atoi( tz[ i ].dynYear );
  if (yearI==0) return true;

  bool          last= i==(int)tctx_numtimezones-1;
  bool another= last || strcmp( tz[ i ].name, tz[ i+1 ].name )!=0; // another group coming ?
  if  (another) return yearS>=yearI;
  else          return yearS<=yearI;
} // YearFit



/*  Returns true, if the given TZ is existing already
 *    <t>            tz_entry to search for:
 *                   If <t.name> == "" search for any entry with these values.
 *                      <t.name> != "" name must fit
 *                   If <t.ident>== "" search for any entry with these values
 *                      <t.ident>!= "" name must fit
 *    <aName>        is <t.name> of the found record
 *    <aContext>     is the assigned context
 *    <createIt>     create an entry, if not yet existing / default: false
 *    <searchOffset> says, where to start searching       / default: at the beginning
 *
 *    supported <t.ident> values:
 *      ""   any       (to search)
 *      "?"  name only (to search)
 *
 *      "x"  unknown/system
 *      "m"  military zones
 *      "s"  standard zones
 *      "d"  daylight zones
 *      "-"  removed  zones
 *      "$"  not converted zones (pure text)
 *      " "  all others
 */
bool FoundTZ( tz_entry t, string        &aName,
                          timecontext_t &aContext, GZones* g, bool createIt,
                          timecontext_t searchOffset )
{
  aName    = "";
  aContext = TCTX_UNKNOWN;
  int offs = TCTX_OFFSCONTEXT( searchOffset );
  bool  ok = false;

  if (        t.ident      !=NULL && // specific items will not contain more info
      strcmp( t.ident,""  )!=0    &&
    //strcmp( t.ident,"$" )!=0    &&
      strcmp( t.ident," " )!=0) {
    ClrDST  ( t );
  } // if

  int  i; // search hard coded elements first
  for (i= offs+1; i<(int)tctx_numtimezones; i++) {
    if (tzcmp  ( t, tz[ i ]  ) &&
        YearFit( t,     i, g )) {
      aName=        tz[ i ].name;
      ok   = true; break;
    } // if
  } // for

  // don't go thru the mutex, if not really needed
  if (!ok && g!=NULL) {
    // -------------------------------------------
  //if (g==NULL) g= gz();

    #ifdef MUTEX_SUPPORT
      lockMutex( g->muP );
    #endif

    TZList::iterator pos;
    int j= offs-(int)tctx_numtimezones; // remaining gap to be skipped

    // Search for all not removed elements first
    for (pos= g->tzP.begin();
         pos!=g->tzP.end(); pos++) {
      if (j<0 &&
          strcmp(   (*pos)->t.ident,"-" )!=0 && // element must not be removed
          tzcmp( t, (*pos)->t )) {
        aName= (*pos)->t.name;
        ok   = true; break;
      } // if

      i++;
      j--;
    } // for

    // now check, if an already removed element can be reactivated
    if (createIt && !ok) {
      i=      (int)tctx_numtimezones;
      j= offs-(int)tctx_numtimezones; // remaining gap to be skipped

      for (pos= g->tzP.begin();
           pos!=g->tzP.end(); pos++) {
        if (j<0 &&
            strcmp(   (*pos)->t.ident,"-" )==0 && // removed element ?
            tzcmp( t, (*pos)->t )) {
          (*pos)->tIdent= t.ident; // reactivate the identifier
          aName = (*pos)->t.name;  // should be the same
          ok    = true; break;
        } // if

        i++;
        j--;
      } // for
    } // if

    // no such element => must be created
    if (createIt && !ok) { // create it, if not yet ok
      TZInfo*           tx= new TZInfo;
                        tx->t     = t;
                        tx->tName = t.name; // create local copies
                        tx->tIdent= t.ident;
                        tx->tDynY = t.dynYear;

                        tx->t.name   = tx->tName.c_str();
                        tx->t.ident  = tx->tIdent.c_str();
                        tx->t.dynYear= tx->tDynY.c_str();
      g->tzP.push_back( tx );
      ok= true;
    } // if

    #ifdef MUTEX_SUPPORT
      unlockMutex( g->muP );
    #endif
    // -------------------------------------------
  } // if

  if (ok) aContext= TCTX_ENUMCONTEXT( i );
  return  aContext!=TCTX_UNKNOWN;
} /* FoundTZ */



/* Remove a time zone definition, if already existing
 * NOTE: Currently only dynamic entries can be removed
 */
bool RemoveTZ( tz_entry t, GZones* g )
{
//printf( "RemoveTZ '%s' %d\n", t.name, t.bias );
  bool ok= false;

  // ---------------------------
  if (g==NULL) return ok;
//if (g==NULL) g= gz();

  #ifdef MUTEX_SUPPORT
    lockMutex( g->muP );
  #endif

  TZList::iterator pos;
  for (pos= g->tzP.begin();
       pos!=g->tzP.end(); pos++) {
    if (strcmp(   (*pos)->t.ident,"-" )!=0 && // element must not be removed
        tzcmp( t, (*pos)->t )) {
      (*pos)->tIdent= "-";
    //gz()->tzP.erase( pos ); // do not remove it, keep it persistent
      ok= true; break;
    } // if
  } // for

  #ifdef MUTEX_SUPPORT
    unlockMutex( g->muP );
  #endif
  // ---------------------------

  return ok;
} /* RemoveTZ */



bool TimeZoneNameToContext( cAppCharP aName, timecontext_t &aContext, GZones* g )
{
  // check some special cases
  if (strucmp(aName,"DATE")==0) {
    aContext = TCTX_UNKNOWN|TCTX_DATEONLY;
    return true;
  }
  else if (strucmp(aName,"DURATION")==0) {
    aContext = TCTX_UNKNOWN|TCTX_DURATION;
    return true;
  }
  else if (*aName==0 || strucmp(aName,"FLOATING")==0) {
    aContext = TCTX_UNKNOWN;
    return true;
  }

  const char* GMT= "GMT";
  const char* UTC= "UTC";

  int      v, n;
  char*    q;
  tz_entry t;

  t.name   = aName; // prepare searching
  t.ident  = "?";
  t.dynYear= "";    // luz: must be initialized!

  string          tName;
  if (FoundTZ( t, tName, aContext, g )) return true;

  /*
  int  i;     aContext= TCTX_UNKNOWN;
  for (i=0; i<(int)tctx_numtimezones; i++) {
    if (strucmp( tz[i].name,aName )==0) { aContext= TCTX_ENUMCONTEXT(i); break; }
  } // for

  if (aContext!=TCTX_UNKNOWN) return true;
  */

  // calculate the UTC offset
  n= 1;        q= (char *)strstr( aName,UTC );
  if (q==NULL) q= (char *)strstr( aName,GMT );
  if (q!=NULL  &&   strlen( q )>strlen( UTC )) {
    q+= strlen( UTC );
    n= MinsPerHour;
  }
  else {
    q= (char*)aName;
  } // if

      v= atoi( q );
  if (v!=0 || strcmp( q, "0" )==0
           || strcmp( q,"+0" )==0
           || strcmp( q,"-0" )==0) {
    aContext= TCTX_OFFSCONTEXT(v*n); return true;
  } // if

  return false;
} /* TimeZoneNameToContext */



bool TimeZoneContextToName( timecontext_t aContext, string &aName, GZones* g,
                                cAppCharP aPrefIdent )
{
  // check some special cases
  if (TCTX_IS_UNKNOWN(aContext)) {
    aName = TCTX_IS_DURATION(aContext) ? "DURATION" : (TCTX_IS_DATEONLY(aContext) ? "DATE" : "FLOATING");
    return true;
  }

  tz_entry t;
  aName= "UNKNOWN";

  // %%% <aPrefIdent> has not yet any influence
  if (TCTX_IS_TZ( aContext ) &&
           GetTZ( aContext, t, g )) {
    if (strcmp( t.ident,"$" )==0) return false; // unchanged elements are not yet supported
    aName= t.name;
  } // if

  return true;
} /* TimeZoneContextToName */



/*! Is it a DST time zone ? (both months must be defined for DST mode) */
bool DSTCond( tz_entry t ) {
  return (t.dst.wMonth!=0 &&
          t.std.wMonth!=0);
} // DSTCond



/* adjust to day number within month <m>, %% valid till year <y> 2099 */
void AdjustDay( sInt16 &d, sInt16 m, sInt16 y )
{
  while (d>31)                                    d-= DaysPerWk;
  if    (d>30 && (m==4 || m==6 || m==9 || m==11)) d-= DaysPerWk;
  if    (d>29 &&  m==2)                           d-= DaysPerWk;
  if    (d>28 &&  m==2 && (y % 4)!=0)             d-= DaysPerWk;
} // AdjustDay


/* Get the day where STD <=> DST switch will be done */
static sInt16 DaySwitch( lineartime_t aTime, tChange* c )
{
  sInt16 y, m, d, ds;
  lineartime2date( aTime, &y, &m, &d );

  if   (c->wDayOfWeek==-1) {
    ds= c->wNth;
  }
  else {
    sInt16 wkDay= lineartime2weekday( aTime );
    ds = ( wkDay +  5*DaysPerWk -   ( d-1 )     ) % DaysPerWk;     /* wkday of 1st  */
    ds = ( DaysPerWk - ds       + c->wDayOfWeek ) % DaysPerWk + 1; /* 1st occurance */
    ds+= ( c->wNth-1 )*DaysPerWk;

    AdjustDay( ds, c->wMonth, y );
  } // if

  return ds;
} // DaySwitch


/*! Get lineartime_t of <t> for a given <year>, either from std <toDST> or vice versa */
lineartime_t DST_Switch( tz_entry t, int bias, sInt16 aYear, bool toDST )
{
  sInt16 ds;

  tChange*   c;
  if (toDST) c= &t.dst;
  else       c= &t.std;

  lineartime_t tim= date2lineartime( aYear, c->wMonth, 1 );

  ds= DaySwitch( tim, c );

  sInt32      bMins = t.bias;
  if (!toDST) bMins+= t.biasDST;

  return    date2lineartime( aYear,    c->wMonth,  ds  )
       +    time2lineartime( c->wHour, c->wMinute, 0,0 )
       - seconds2lineartime( bMins*SecsPerMin );
} /* DST_Switch */



/* Check whether <aValue> of time zone <t> is DST based */
static bool IsDST( lineartime_t aTime, tz_entry t )
{
  bool   ok;
  sInt16 y, m, d, h, min, ds;

  if (!DSTCond( t )) return false;

  lineartime2date( aTime, &y, &m, &d );
  lineartime2time( aTime, &h, &min, NULL, NULL );

  tChange*             c= NULL;
  if (m==t.std.wMonth) c= &t.std;
  if (m==t.dst.wMonth) c= &t.dst;

  /* calculation is a little bit more tricky within the two switching months */
  if (c!=NULL) {
    /*
    if   (c->wDayOfWeek==-1) {
      ds= c->wNth;
    }
    else {
      sInt16 wkDay= lineartime2weekday( aTime );
      ds = ( wkDay +   5*DaysPerWk - (d-1)          ) % DaysPerWk;     // wkday of 1st
      ds = ( DaysPerWk  - ds       + c->wDayOfWeek  ) % DaysPerWk + 1; // 1st occurance
      ds+= ( c->wNth-1 )*DaysPerWk;

      AdjustDay( ds, m, y );
    } // if
    */

    /* <ds> is the day when dst<=>std takes place */
        ds= DaySwitch( aTime, c );
    if (ds        < d   ) return c==&t.dst;
    if (ds        > d   ) return c==&t.std;

    /* day  correct => compare hours */
    if (c->wHour  < h   ) return c==&t.dst;
    if (c->wHour  > h   ) return c==&t.std;

    /* hour correct => compare minutes */
    if (c->wMinute< min ) return c==&t.dst;
    if (c->wMinute> min ) return c==&t.std;

    /* decide for the margin, if identical */
    return c==&t.dst;
  } /* if */

  /* northern and southern hemnisphere supported */
  if (t.dst.wMonth<t.std.wMonth)
         ok= m>t.dst.wMonth && m<t.std.wMonth;
  else   ok= m<t.std.wMonth || m>t.dst.wMonth;
  return ok;
} /* IsDST */



static sInt32 DST_Offs( lineartime_t aValue, tz_entry t, bool backwards )
{
  if (backwards) aValue+= (lineartime_t)(t.bias*SecsPerMin)*secondToLinearTimeFactor;
  if (IsDST( aValue,t )) return t.bias + t.biasDST;
  else                   return t.bias;
} /* DST_Offs */



/* get offset in minutes */
static bool TimeZoneToOffs( lineartime_t aValue, timecontext_t aContext,
                                 bool backwards, sInt32 &offs, GZones* g )
{
  tz_entry t;

  if (TCTX_IS_TZ( aContext )) {
    offs= 0; // default

    sInt16                     year;
    lineartime2date( aValue,  &year, NULL, NULL );
    if (GetTZ( aContext, t, g, year )) {
      if (strcmp( t.ident,"$" )==0) return false; // unchanged elements are not yet supported
      offs= DST_Offs( aValue, t, backwards );
    } // if
  }
  else {
    offs= TCTX_MINOFFSET(aContext);
  } // if

  return true;
} /* TimeZoneToOffs */



#if defined(_WIN32) && !defined __EPOC_OS__
static void FillValues( tChange &tc, SYSTEMTIME s )
{
  tc.wMonth    = s.wMonth;
  tc.wDayOfWeek= s.wDayOfWeek;
  tc.wNth      = s.wDay;
  tc.wHour     = s.wHour;
  tc.wMinute   = s.wMinute;
} // FillValues
#endif



timecontext_t SelectTZ( TDaylightSavingZone zone, int bias, int biasDST, lineartime_t tNow, bool isDbg )
{
  bool dst, ok;
  bool withDST= zone!=EDstNone;
  timecontext_t t= tctx_tz_unknown;
  bool special= false; // eventually needed true for NGage

  int  i; // go thru the whole list of time zones
  for (i=(int)tctx_tz_system+1; i<(int)tctx_numtimezones; i++) {
    bool tCond= DSTCond( tz[ i ] ); // are there any DST rules ?
    if  (tCond==withDST) {
      if (withDST) dst= IsDST( tNow, tz[ i ] ); // check, if now in DST
      else         dst= false;

      int                 b= bias;
      if (dst && special) b= bias - biasDST;
      if (tz[ i ].bias==b) { // the bias must fit exactly
        switch (zone) {
          case EDstEuropean :
          case EDstNorthern : ok= tz[ i ].dst.wMonth<tz[ i ].std.wMonth; break;
          case EDstSouthern : ok= tz[ i ].dst.wMonth>tz[ i ].std.wMonth; break;
          default           : ok= true;
        } // switch

        if (isDbg) PNCDEBUGPRINTFX( DBG_SESSION,( " %d %d dst=%d cond=%d '%s'",
                                        i, bias, dst, tCond, tz[ i ].name ));
        if   (ok) { // check, if european time zone
              ok= (zone==EDstEuropean) == (strstr( tz[ i ].name,"Europe"   )!=NULL ||
                                           strcmp( tz[ i ].name,"CET/CEST" )==0    ||
                                           strcmp( tz[ i ].name,"Romance"  )==0    ||
                                           strcmp( tz[ i ].name,"GMT"      )==0);
          if (ok) { t= i; break; }
        } // if
      } // if
    } // if
  } // for

  if (isDbg) PNCDEBUGPRINTFX( DBG_SESSION,( "SelectTZ: zone=%s bias=%d",
                                             tz[ t ].name, bias ) );
  return TCTX_SYMBOLIC_TZ+t;
} // SelectTZ



timecontext_t SystemTZ( GZones *g, bool isDbg )
{
  TDaylightSavingZone zone= EDstNone;
  int                 bias= 0;
  lineartime_t        tNow = 0;

  #ifdef __EPOC_OS__
    TLocale                 tl;
    zone=                   tl.HomeDaylightSavingZone();
    TTimeIntervalSeconds o= tl.UniversalTimeOffset();
    bias=                o.Int() / SecsPerMin; // bias is based on minutes
    bool             isDst= tl.QueryHomeHasDaylightSavingOn();
    isDbg= true;

    const char* zs;
    switch (zone) {
      case EDstHome     : zs= "EDstHome";     break;
      case EDstNone     : zs= "EDstNone";     break;
      case EDstEuropean : zs= "EDstEuropean"; break;
      case EDstNorthern : zs= "EDstNorthern"; break;
      case EDstSouthern : zs= "EDstSouthern"; break;
      default           : zs= "???";          break;
    } // switch

    PNCDEBUGPRINTFX( DBG_SESSION,( "SystemTZ (EPOC): %s %d dst=%s", zs,bias, isDst ? "on":"off" ));

    #ifdef _WIN32
      PNCDEBUGPRINTFX( DBG_SESSION,( "SystemTZ (EPOC): on emulator" ));
    #endif
  #endif

  #if defined _WIN32 && !defined __EPOC_OS__
    TIME_ZONE_INFORMATION tzi;
    DWORD rslt= GetTimeZoneInformation( &tzi );
    zone= EDstEuropean;
    bias= -tzi.Bias; /* as negative value */
    PNCDEBUGPRINTFX( DBG_SESSION,( "SystemTZ (WIN): %s %d", "", bias ) );
  #endif

  // is only dependendent on current time/date, if any DST zone
  if (zone!=EDstNone) tNow= getSystemNowAs(TCTX_SYSTEM, g);
  return SelectTZ( zone,bias,tNow, isDbg );
} // SystemTZ


// just for test
/*
#ifdef MACOSX
  static bool getSystemTimeZone( string &aName, sInt16      &bias,
                                                sInt16   &biasDST,
                                                lineartime_t &std,
                                                lineartime_t &dst ) { return false; }
#endif
*/


// Get int value <i> as string
static string IntStr( sInt32 i )
{
  const int    FLen= 15;    /* max length of (internal) item name */
  char      f[ FLen ];
  // cheating: this printf format assumes that sInt32 == int
  sprintf ( f, "%d", int(i) );
  string s= f;
  return s;
} // IntStr


/* get system's time zone */
static bool MyContext( timecontext_t &aContext, GZones* g )
{
  string sName, s;
  tz_entry t;

  bool isDbg= false;
  if      (g) {
    isDbg= g->isDbg;
    // luz: added safety here to avoid that incorrectly initialized GZone
    //      (with tctx_tz_unknown instead of TCTX_UNKNOWN, as it was in timezones.h)
    //      does not cause that system timezone is assumed known (as UTC) and returned WRONG!)
    //      Note: rearranged to make non-locked writing to g->sysTZ is safe (for hacks needed pre-3.1.2.x!)
    timecontext_t   curSysTZ= g->sysTZ;
    if    (!(TCTX_IS_UNKNOWN( curSysTZ ) ||
             TCTX_IS_SYSTEM ( curSysTZ )
            ))    { aContext= curSysTZ; return true; }
  } // if

  bool chkNameFirst= true;
  #if defined __EPOC_OS__
                        aContext= SystemTZ( isDbg );
    t= tz[ TCTX_TZENUM( aContext ) ];
    sName= t.name;

  #elif defined _WIN32
    chkNameFirst= false;

    const int MaxLen= 32;
    char  nam[ 32 ];
    DWORD rslt;
    TIME_ZONE_INFORMATION tzi;
    rslt= GetTimeZoneInformation( &tzi );
    /* %%% what is the <rslt> ? */
    /* seems to be: 0: no DST / 1: outside DST / 2: inside DST */

    /* straight unicode conversion, there might be better ways to do this */
    int  i;
    for (i=0; i<31; i++) nam[ i ]= tzi.StandardName[ i ];
    sName= nam;
    for (i=0; i<31; i++) nam[ i ]= tzi.DaylightName[ i ];
    sName+= "/";
    sName+= nam;

    //%%% luz: added use of StandardBias/DaylightBias (biasDST was NOT INITIALIZED otherwise)
    t.bias          = -tzi.Bias-tzi.StandardBias; /* as negative value */
    t.biasDST       = -tzi.DaylightBias;
    FillValues( t.dst, tzi.DaylightDate );
    FillValues( t.std, tzi.StandardDate );

    /*
    sName= "EST"; // make a strange timezone which must be created for test
    t.dst.wMonth= 7;
    */

  #elif defined MOBOSX
    chkNameFirst= false;
    sName       = "";
    t.bias      = 0;
    t.biasDST   = 0;
    t.dst.wMonth= 0;

    lineartime_t stdTime, dstTime;
    if (getSystemTimeZone( sName, t.bias,t.biasDST, stdTime,dstTime )) {
      Get_tChange( stdTime, t.std );
      Get_tChange( dstTime, t.dst );

      if (isDbg) PNCDEBUGPRINTFX( DBG_SESSION, ( "Timezone: %s", sName.c_str() ));
    } // if

  #elif defined LINUX || defined MACOSX
    tzset();
    sName= tzname[ 0 ];
    if (strcmp( sName.c_str(),tzname[ 1 ] )!=0) {
      sName+= "/";
      sName+= tzname[ 1 ];
    } // if

    if (isDbg) PNCDEBUGPRINTFX( DBG_SESSION, ( "Timezone: %s", sName.c_str() ));

    /* no formulas for Linux until now */
    t.bias      = 0;
    t.biasDST   = 0;
    t.dst.wMonth= 0;
  #else
    #error unknown operating system
  #endif

  bool ok= true;
  do {
    if (chkNameFirst &&       !sName.empty() &&
        TimeZoneNameToContext( sName.c_str(),aContext, g )) break;

    // if there are no rules defined => switch it off
    if (t.dst.wMonth==0 ||
        t.std.wMonth==0 ||
      //memcmp( &t.dst,&t.std, sizeof(t.dst))==0) {
        Same_tChange( t.dst, t.std )) {
      ClrDST( t );
    } // if

                 t.name   = (char*)sName.c_str();
                 t.ident  = "";
                 t.dynYear= ""; // MUST be set as this is assigned unchecked to a string
                                // (which crashes when assigned NULL or low number)
    if (FoundTZ( t, s, aContext, g )) break; // with this name

                 t.name   = "";
                 t.dynYear= "CUR";
    if (FoundTZ( t, s, aContext, g )) break; // with different name

    int i= 0;
    if (sName.empty()) sName= "unassigned";

    string v;
    while (true) {
               v = sName.c_str();
      if (i>0) v+= "_" + IntStr( i );
      if (!TimeZoneNameToContext( v.c_str(),aContext, g )) break; // A timezone with this name must not exist
      i++;
    } // while

    t.name= (char*)v.c_str();

    string      tz_Name;
    FoundTZ( t, tz_Name, aContext, g, true ); // create it
    if (TimeZoneNameToContext( v.c_str(),aContext, g )) break;
    ok= false;

    /*
    t.name= (char*)sName.c_str();

    string      tzName;
    FoundTZ( t, tzName, aContext, g, true ); // create it
    if (TimeZoneNameToContext( sName.c_str(),aContext, g )) break;
    ok= false;
    */
  } while (false);

  if (isDbg) PNCDEBUGPRINTFX( DBG_SESSION, ( "MyContext: %08X ok=%d", aContext, ok ));
  if (g && ok) g->sysTZ= aContext; // assign the system context
  return   ok;
} /* MyContext */



/* returns true, if the context rules are identical */
static bool IdenticalRules( timecontext_t aSourceContext,
                            timecontext_t aTargetContext, GZones* g )
{
  tz_entry ts, tt;

  /* only performed in TZ mode */
  if (!GetTZ( aSourceContext, ts, g, 0 ) ||
      !GetTZ( aTargetContext, tt, g, 0 )) return false;

  TTimeZones asTZ= TCTX_TZENUM( aSourceContext );
  TTimeZones atTZ= TCTX_TZENUM( aTargetContext );
  if  (asTZ==atTZ) return true; // identical

  if (strcmp( ts.ident,"$" )==0 ||
      strcmp( tt.ident,"$" )==0) return false;

  if              (ts.bias==tt.bias  &&
  // memcmp( &ts.dst, &tt.dst, sizeof(tChange))==0 &&
  // memcmp( &ts.std, &tt.std, sizeof(tChange))==0) return true;
     Same_tChange( ts.dst,  tt.dst ) &&
     Same_tChange( ts.std,  tt.std )) return true;

  /*
  if (!TCTX_IS_TZ( aSourceContext ) ||
      !TCTX_IS_TZ( aTargetContext )) return false;

  // get the time zones for calculation
  TTimeZones asTZ= TCTX_TZENUM(aSourceContext);
  TTimeZones atTZ= TCTX_TZENUM(aTargetContext);

  if (asTZ==atTZ) return true;

  if (         tz[ asTZ ].bias==tz[ atTZ ].bias &&
      memcmp( &tz[ asTZ ].dst, &tz[ atTZ ].dst, sizeof(tChange))==0 &&
      memcmp( &tz[ asTZ ].std, &tz[ atTZ ].std, sizeof(tChange))==0) {
    return true;
  } // if
  */

  return false;
} /* IdenticalRules */



/*! get system's time zone context (i.e. resolve the TCTX_SYSTEM meta-context)
 *  @param[in,out] aContext : context will be made non-meta, that is, if input is TCTX_SYSTEM,
 *                            actual time zone will be determined.
 */
bool TzResolveMetaContext( timecontext_t &aContext, GZones* g )
{
  if (!TCTX_IS_SYSTEM(aContext))
    return true; // no meta zone, just return unmodified
  // is meta-context TCTX_SYSTEM, determine actual symbolic context
  return MyContext(aContext,g);
} // TzResolveMetaContext


/* make time context non-symbolic (= calculate minute offset east of UTC for aRefTime) */
bool TzResolveContext( timecontext_t &aContext, lineartime_t aRefTime, bool aRefTimeUTC, GZones* g )
{
  sInt32 offs;
  // resolve eventual meta context (TCTX_SYSTEM at this time)
  if (!TzResolveMetaContext(aContext,g)) return false;
  // check if already an offset (non-symbolic)
  if (!TCTX_IS_TZ(aContext))
    return true; // yes, no conversion needed
  // is symbolic, needs conversion to offset
  bool ok = TimeZoneToOffs(
    aRefTime, // reference time for which we want to know the offset
    aContext, // context
    aRefTimeUTC, // "backwards" means refTime is UTC and we want know offset to go back to local
    offs, // here we get the offset
    g
  );
  if (ok) {
    aContext = TCTX_JOIN_RFLAGS_TZ(
      aContext, // join original rendering flags...
      TCTX_OFFSCONTEXT(offs) // ...with new offset based context
    );
  }
  return ok;
} // TzResolveContext


/*! calculate minute offset east of UTC for aRefTime
 *  @param[in] aContext       : time context to resolve
 *  @param[out] aMinuteOffset : receives minute offset east of UTC
 *  @param[in] aRefTime       : reference time point for resolving the offset
 *  @param[in] aRefTimeUTC    : if set, reference time must be UTC,
 *                              otherwise, reference time must be in context of aContext
 */
bool TzResolveToOffset( timecontext_t aContext, sInt16 &aMinuteOffset, lineartime_t aRefTime, bool aRefTimeUTC, GZones* g )
{
  bool ok = TzResolveContext(aContext, aRefTime, aRefTimeUTC, g);
  if (ok) {
    aMinuteOffset = TCTX_MINOFFSET(aContext);
  }
  return ok;
} // TzResolveToOffset



/*! Offset between two contexts (in seconds)
 *  Complex time zones (type "$") can't be currently resolved, they return false
 *  @param[in] aSourceValue   : reference time for which the offset should be calculated
 *  @param[in] aSourceContext : source time zone context
 *  @param[in] aTargetContext : source time zone context
 *  @param[out] sDiff         : receives offset east of UTC in seconds
 */
bool TzOffsetSeconds( lineartime_t aSourceValue, timecontext_t aSourceContext,
                                                 timecontext_t aTargetContext,
                                                 sInt32        &sDiff, GZones* g,
                                                 timecontext_t aDefaultContext )
{
  bool         sSys,  tSys,
               sUnk,  tUnk;
  sInt32       sOffs= 0, tOffs= 0; // initialize them for sure
  lineartime_t aTargetValue;

  bool      ok= true;
  bool   isDbg= false;
  if (g) isDbg= g->isDbg;

  // set default context for unknown zones
  if (TCTX_IS_UNKNOWN(aSourceContext)) aSourceContext=aDefaultContext;
  if (TCTX_IS_UNKNOWN(aTargetContext)) aTargetContext=aDefaultContext;

  do {
    sDiff= 0;
    if (aSourceContext==aTargetContext) break; /* no conversion, if identical context */

    /* both unknown or system is still ok */
    if   (TCTX_IS_UNKNOWN( aSourceContext ) &&
          TCTX_IS_UNKNOWN( aTargetContext )) break;
    sSys= TCTX_IS_SYSTEM ( aSourceContext );
    tSys= TCTX_IS_SYSTEM ( aTargetContext ); if (sSys && tSys) break;

    /* calculate specifically for the system's time zone */
    if (sSys)   MyContext( aSourceContext, g );
    if (tSys)   MyContext( aTargetContext, g );

    /* if both are unknown now, then it's good as well */
    sUnk= TCTX_IS_UNKNOWN( aSourceContext );
    tUnk= TCTX_IS_UNKNOWN( aTargetContext ); if (sUnk && tUnk)              break;
    /* this case can't be resolved: */       if (sUnk || tUnk) { ok= false; break; }

    if (IdenticalRules( aSourceContext,aTargetContext, g )) break;

    /* now do the "hard" things */
    if (!TimeZoneToOffs( aSourceValue, aSourceContext, false, sOffs, g )) return false;
                         aTargetValue= aSourceValue
                                     - (lineartime_t)(sOffs*SecsPerMin)*secondToLinearTimeFactor;
    if (!TimeZoneToOffs( aTargetValue, aTargetContext,  true, tOffs, g )) return false;

    sDiff= ( tOffs - sOffs )*SecsPerMin;
  } while (false);

  if (isDbg) {
    PNCDEBUGPRINTFX( DBG_SESSION,( "sSys=%d tSys=%d / sUnk=%d tUnk=%d / sOffs=%d tOffs=%d",
                                    sSys,tSys, sUnk,tUnk, sOffs,tOffs ));
    PNCDEBUGPRINTFX( DBG_SESSION,( "TzOffsetSeconds=%d", sDiff ));
  } // if

  return ok;
} /* TzOffsetSeconds */


/*! Converts timestamp value from one zone to another
 *  Complex time zones (type "$") can't be currently resolved, they return false
 *  @param[in/out] aValue     : will be converted from source context to target context. If==noLinearTime==0, no conversion is done
 *  @param[in] aSourceContext : source time zone context
 *  @param[in] aTargetContext : source time zone context
 *  @param[in] aDefaultContext: default context to use if source or target is TCTX_UNKNOWN
 */
bool TzConvertTimestamp( lineartime_t &aValue,   timecontext_t aSourceContext,
                                                 timecontext_t aTargetContext,
                                                                       GZones* g,
                                                 timecontext_t aDefaultContext )
{
  sInt32 sdiff;
  if (aValue==noLinearTime) return true; // no time, don't convert
  bool ok = TzOffsetSeconds( aValue, aSourceContext, aTargetContext, sdiff, g, aDefaultContext );
  if (ok)
    aValue += (lineartime_t)(sdiff)*secondToLinearTimeFactor;
  return ok;
} /* TzConvertTimestamp */



} // namespace sysync


/* eof */

