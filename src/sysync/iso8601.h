/*
 *  File:         iso8601.h
 *
 *  Author:			  Lukas Zeller (luz@synthesis.ch)
 *
 *  conversion from/to linear time scale.
 *
 *  Copyright (c) 2002-2009 by Synthesis AG (www.synthesis.ch)
 *
 *  2002-05-02 : luz : extracted from sysync_utils
 *
 */

#ifndef ISO8601_H
#define ISO8601_H

#include <string>
#include "lineartime.h"
#include "timezones.h"

using namespace std;

namespace sysync {

/// @brief convert ISO8601 to timestamp
/// @return number of successfully converted characters
/// @param[in] aISOString input string in ISO8601
/// @param[out] aTimestamp representation of ISO time spec as is (no time zone conversions)
/// @param[out] aTimeContext:
///             TCTX_UNKNOWN if ISO8601 does not include a time zone specification
///             TCTX_UTC if ISO8601 ends with the "Z" specifier
///             TCTX_DATEONLY if ISO8601 only contains a date, but no time
///             TCTX_OFFSCONTEXT(xx) if ISO8601 explicitly specifies a UTC offset
sInt16 ISO8601StrToTimestamp(cAppCharP aISOString, lineartime_t &aTimestamp, timecontext_t &aTimeContext);


/// @brief convert ISO8601 zone offset to internal time context
/// @param[in] aISOString input string in ISO8601
/// @param[out] aTimeContext context, TCTX_UNKNOWN if none found
sInt16 ISO8601StrToContext(cAppCharP aISOString, timecontext_t &aTimeContext);


/// @brief convert timestamp to ISO8601 representation
/// @param[out] aISOString will receive ISO8601 formatted date/time
/// @param[in] aTimestamp representation of ISO time spec as is (no time zone conversions)
/// @param[in] aExtFormat if set, extended format is generated
/// @param[in] aTimeContext:
///            TCTX_UNKNOWN : time is shown as relative format (no "Z", no explicit offset)
///            TCTX_UTC     : time is shown with "Z" specifier
///            TCTX_DATEONLY: only date part is shown
///            TCTX_OFFSCONTEXT(xx) : time is shown with explicit UTC offset (but not with "Z", even if offset is 0:00)
/// @param[in] aWithFracSecs if set, factional parts of the second are shown in the output
void TimestampToISO8601Str(string &aISOString, lineartime_t aTimestamp, timecontext_t aTimeContext, bool aExtFormat=false, bool aWithFracSecs=false);


/// @brief append internal time context as ISO8601 zone offset to string
/// @param[out] aISOString ISO8601 time zone spec will be appended to this string
/// @param[in] aTimeContext
/// @param[in] aExtFormat if set, extended format is generated
/// @return true if time zone spec appended, false if not
bool ContextToISO8601StrAppend(string &aISOString, timecontext_t aTimeContext, bool aExtFormat);



#ifdef OLD_TIME_HANDLING
// %%% Should be obsolete soon

// convert timestamp to ISO8601 string representation (default to UTC)
sInt32 timeStampToISO8601(lineartime_t aTimeStamp, string &aString, bool aWithTime=true, bool aAsUTC=true, bool aWithOffset=false, sInt32 aOffsetSecs=0, bool aShowOffset=false);

// convert struct tm time to ISO8601 string representation (assume tim is in UTC)
void tmToISO8601(const struct_tm &tim, string &aString, bool aWithTime=true, bool aIsUTC=true, bool aWithOffset=false, sInt32 aOffsetSecs=0);

// convert number of seconds into ISO8601 zone offset
void ZoneOffsToISO8601Append(sInt32 aOffsetSecs,string &aString);


// convert ISO8601 string representation to timestamp
bool ISO8601ToTimeStamp(const char *aString, lineartime_t &aTimeStamp);

// convert ISO8601 string representation to struct tm time
bool ISO8601ToTm(const char *aString, struct_tm &utc, bool &aWithTime, bool &aIsUTC, bool &aWithOffset, sInt32 &aOffsetSecs);

// convert ISO8601 zone offset to number of seconds
bool ISO8601ToZoneOffs(const char *aString, sInt32 &aOffsetSecs);

#endif // OLD_TIME_HANDLING

} // namespace sysync

#endif // ISO8601_H

/* eof */
