/*
 *  File:         VCalendarItemType.cpp
 *
 *  Author:			  Lukas Zeller (luz@synthesis.ch)
 *
 *  TVCalendarItemType
 *    vCalendar item type, based on MIME-DIR Item Type, uses
 *    TMultiFieldItem as data item.
 *
 *  Copyright (c) 2001-2009 by Synthesis AG (www.synthesis.ch)
 *
 *  2001-09-25 : luz : created
 *
 */

// includes
#include "prefix_file.h"

#include "sysync.h"
#include "vcalendaritemtype.h"

#include "rrules.h"

using namespace sysync;

namespace sysync {

/* version info table */
const struct {
  sInt32 profilemode;
  const char* typetext;
  const char* versiontext;
} VCalendarVersionInfo[numVCalendarVersions-1] = {
  // vCalendar 1.0
  { PROFILEMODE_OLD, "text/x-vcalendar","1.0" },
  // iCalendar 2.0
  { PROFILEMODE_MIMEDIR, "text/calendar","2.0" }
};


// available vCard versions
const char * const vCalendarVersionNames[numVCalendarVersions] = {
  "1.0",
  "2.0",
  "none"
};


// VCalendar config

// init defaults
void TVCalendarTypeConfig::clear(void)
{
  // clear properties
  fVCalendarVersion=vcalendar_vers_none;
  // clear inherited
  inherited::clear();
} // TVCalendarTypeConfig::clear


// create Sync Item Type of appropriate type from config
TSyncItemType *TVCalendarTypeConfig::newSyncItemType(TSyncSession *aSessionP, TSyncDataStore *aDatastoreP)
{
  return
    new TVCalendarItemType(
      aSessionP,
      this,
      fTypeName.c_str(),
      fTypeVersion.c_str(),
      aDatastoreP,
      fMIMEProfileP->fFieldListP
    );
} // TVCalendarTypeConfig::newSyncItemType


// resolve (note: needed even if not configurable!)
void TVCalendarTypeConfig::localResolve(bool aLastPass)
{
  // pre-set profile mode if a predefined vCard mode is selected
  if (fVCalendarVersion!=vcalendar_vers_none) {
    fProfileMode = VCalendarVersionInfo[fVCalendarVersion].profilemode;
    // also set these, but getTypeName()/getTypeVers() do not use them (but required for syntax check)
    fTypeName = VCalendarVersionInfo[fVCalendarVersion].typetext;
    fTypeVersion = VCalendarVersionInfo[fVCalendarVersion].versiontext;
  }
  // resolve inherited
  inherited::localResolve(aLastPass);
} // TVCalendarTypeConfig::localResolve


#ifdef CONFIGURABLE_TYPE_SUPPORT


// config element parsing
bool TVCalendarTypeConfig::localStartElement(const char *aElementName, const char **aAttributes, sInt32 aLine)
{
  // checking the elements
  if (strucmp(aElementName,"version")==0)
    expectEnum(sizeof(fVCalendarVersion),&fVCalendarVersion,vCalendarVersionNames,numVCalendarVersions);
  else
    return TMIMEDirTypeConfig::localStartElement(aElementName,aAttributes,aLine);
  // ok
  return true;
} // TVCalendarTypeConfig::localStartElement


#endif


/*
 * Implementation of TVCalendarItemType
 */

/* public TVCalendarItemType members */


// private helper
TVCalendarVersion TVCalendarItemType::getVCalenderVersionByMode(sInt32 aMode)
{
	if (aMode!=PROFILEMODE_DEFAULT) {
  	for (int v=vcalendar_vers_1_0; v<numVCalendarVersions-1; v++) {
    	if (VCalendarVersionInfo[v].profilemode==aMode)
      	return (TVCalendarVersion)v;
    }
  }
  // not found or default mode
  return fVCalendarVersion; // return the configured version
} // TVCalendarItemType::getVCalenderVersionByMode


// - get type name / vers
cAppCharP TVCalendarItemType::getTypeName(sInt32 aMode)
{
  TVCalendarVersion v = getVCalenderVersionByMode(aMode);
  if (v!=vcalendar_vers_none)
  	return VCalendarVersionInfo[v].typetext;
  else
  	return inherited::getTypeName(aMode);
} // TVCalendarItemType::getTypeName


cAppCharP TVCalendarItemType::getTypeVers(sInt32 aMode)
{
  TVCalendarVersion v = getVCalenderVersionByMode(aMode);
  if (v!=vcalendar_vers_none)
  	return VCalendarVersionInfo[v].versiontext;
  else
  	return inherited::getTypeVers(aMode);
} // TVCalendarItemType::getTypeVers


// relaxed type comparison, taking into account common errors in real-world implementations
bool TVCalendarItemType::supportsType(const char *aName, const char *aVers, bool aVersMustMatch)
{
	bool match = inherited::supportsType(aName,aVers,aVersMustMatch);
  if (!match) {
  	// no exact match, but also check for unambiguos misstyped variants
    if (aVers && strstr(aName,"calendar")!=NULL) {
    	// if "calendar" is in type name, version alone is sufficient to identify the vCalendar version,
      // even if the type string is wrong, like mixing "x-vcalendar" and "calendar"
      match = strucmp(getTypeVers(),aVers)==0;
      if (match) {
        PDEBUGPRINTFX(DBG_ERROR,(
          "Warning: fuzzy type match: probably misspelt %s version %s detected as correct type %s version %s",
          aName,aVers,
          getTypeName(),getTypeVers()
        ));
      }
    }
  }
  // return result now
	return match;
} // TVCalendarItemType::supportsType


// try to extract a version string from actual item data, NULL if none
bool TVCalendarItemType::versionFromData(SmlItemPtr_t aItemP, string &aString)
{
  // try to extract version
  return parseForProperty(aItemP,"VERSION",aString);
}


#ifdef APP_CAN_EXPIRE

// try to extract a version string from actual item data, NULL if none
sInt32 TVCalendarItemType::expiryFromData(SmlItemPtr_t aItemP, lineardate_t &aDat)
{
	string rev;
  aDat=0; // default to no date
  // try to extract version
  if (!parseForProperty(aItemP,"LAST-MODIFIED",rev)) return 0; // no date, is ok
  lineartime_t t;
  timecontext_t tctx;
  if (ISO8601StrToTimestamp(rev.c_str(),t,tctx)==0) return 0; // bad format, is ok;
  aDat=t/linearDateToTimeFactor; // mod date
  #ifdef EXPIRES_AFTER_DATE
  sInt16 y,mo,d;
  lineardate2date(aDat,&y,&mo,&d);
  // check if this is after expiry date
  long v=SCRAMBLED_EXPIRY_VALUE;
  v =
		(y-1720)*12*42+
		(mo-1)*42+
		(d+7);
	v=v-SCRAMBLED_EXPIRY_VALUE;	
  return (v>0 ? v : 0);
  #else
  return 0; // not expired
  #endif
} // TVCalendarItemType::expiryFromData

#endif // APP_CAN_EXPIRE


#ifdef OBJECT_FILTERING

// get field index of given filter expression identifier.
sInt16 TVCalendarItemType::getFilterIdentifierFieldIndex(const char *aIdentifier, uInt16 aIndex)
{
  // check if explicit field level identifier
  if (strucmp(aIdentifier,"F.",2)==0) {
    // explicit field identifier, skip property lookup
    return TMultiFieldItemType::getFilterIdentifierFieldIndex(aIdentifier+2,aIndex);
  }
  else {
    // translate SyncML-defined abstracts
    if (strucmp(aIdentifier,"START")==0)
      return inherited::getFilterIdentifierFieldIndex("DTSTART",0);
    else if (strucmp(aIdentifier,"END")==0)
      return inherited::getFilterIdentifierFieldIndex("DTEND",0);
  }
  // simply search for matching property names
  return inherited::getFilterIdentifierFieldIndex(aIdentifier,aIndex);
} // TVCalendarItemType::getFilterIdentifierFieldIndex

#endif


// helper to create same-typed instance via base class
TSyncItemType *TVCalendarItemType::newCopyForSameType(
  TSyncSession *aSessionP,     // the session
  TSyncDataStore *aDatastoreP  // the datastore
)
{
  // create new itemtype of appropriate derived class type that can handle
  // this type
  MP_RETURN_NEW(TVCalendarItemType,DBG_OBJINST,"TVCalendarItemType",TVCalendarItemType(
    aSessionP,
    fTypeConfigP,
    getTypeName(),
    getTypeVers(),
    aDatastoreP,
    fFieldDefinitionsP
  ));
} // TVCalendarItemType::newCopyForSameType



/* %%% moved to mimedirprofile.cpp


// special vCal field translations
// - the string returned by this function will be scanned as a
//   value list if combinesep is set, and every single value will be
//   enum-translated if enums defined.
// - returns false if no or empty value is the result
bool TVCalendarItemType::fieldToMIMEString(
  TMultiFieldItem &aItem,           // the item where data goes to
  sInt16 aFid,                       // the field ID (can be NULL for special conversion modes)
  sInt16 aArrIndex,                  // the repeat offset to handle array fields
  const TConversionDef *aConvDefP,  // the conversion definition record
  string &aString                   // output string
)
{
  // helpers
  TTimestampField *tsFldP;
  TIntegerField *ifP;
  TStringField *sfP;
  string s;
  // field block values
  char freq; // frequency
  char freqmod; // frequency modifier
  sInt16 interval; // interval
  fieldinteger_t firstmask; // day mask counted from the first day of the period
  fieldinteger_t lastmask; // day mask counted from the last day of the period
  lineartime_t until; // last day
  timecontext_t untilcontext;

  switch (aConvDefP->convmode) {
    case CONVMODE_RRULE:
      // get values from field block
      if (aFid<0) return false; // no field, no string
      // - freq/freqmod
      if (!(sfP = ITEMFIELD_DYNAMIC_CAST_PTR(TStringField,fty_string,aItem.getArrayField(aFid,aArrIndex,true)))) return false;
      aFid++; // do NOT INCREMENT in macro, as it would get incremented twice
      sfP->getAsString(s);
      freq='0'; // none
      freqmod=' '; // no modifier
      if (s.size()>0) freq=s[0];
      if (s.size()>1) freqmod=s[1];
      // - interval
      if (!(ifP = ITEMFIELD_DYNAMIC_CAST_PTR(TIntegerField,fty_integer,aItem.getArrayField(aFid,aArrIndex,true)))) return false;
      aFid++; // do NOT INCREMENT in macro, as it would get incremented twice
      interval=(sInt16)ifP->getAsInteger();
      // - firstmask
      if (!(ifP = ITEMFIELD_DYNAMIC_CAST_PTR(TIntegerField,fty_integer,aItem.getArrayField(aFid,aArrIndex,true)))) return false;
      aFid++; // do NOT INCREMENT in macro, as it would get incremented twice
      firstmask=ifP->getAsInteger();
      // - lastmask
      if (!(ifP = ITEMFIELD_DYNAMIC_CAST_PTR(TIntegerField,fty_integer,aItem.getArrayField(aFid,aArrIndex,true)))) return false;
      aFid++; // do NOT INCREMENT in macro, as it would get incremented twice
      lastmask=ifP->getAsInteger();
      // - until
      if (!(tsFldP = ITEMFIELD_DYNAMIC_CAST_PTR(TTimestampField,fty_timestamp,aItem.getArrayField(aFid,aArrIndex,true)))) return false;
      aFid++; // do NOT INCREMENT in macro, as it would get incremented twice
      // Until
      // - UTC preferred as output format if basically possible and not actively disabled
      untilcontext=
        fSessionP->fRemoteCanHandleUTC && fSessionP->canHandleUTC() ?
        TCTX_UTC :
        fItemTimeContext;
      // - get in preferred zone (or floating)
      until=tsFldP->getTimestampAs(untilcontext,&untilcontext);
      // Now do the conversion
      if (fMimeDirMode==mimo_old) {
        // vCalendar 1.0 type RRULE
        return internalToRRULE1(
          aString,
          freq,
          freqmod,
          interval,
          firstmask,
          lastmask,
          until,
          untilcontext,
          GETDBGLOGGER
        );
      }
      else {
        // iCalendar 2.0 type RRULE
        return internalToRRULE2(
          aString,
          freq,
          freqmod,
          interval,
          firstmask,
          lastmask,
          until,
          untilcontext,
          GETDBGLOGGER
        );
      }
      break; // just in case
    default:
      // unknown mode, let ancestor handle this
      return TMimeDirItemType::fieldToMIMEString(aItem,aFid,aArrIndex,aConvDefP,aString);
  }
  return false; // just in case
} // TVCalendarItemType::fieldToMIMEString


// special vCal field translations
// - the string passed to this function is already a translated value
//   list if combinesep is set, and every single value is already
//   enum-translated if enums are defined.
// - returns false if field(s) could not be assigned because aText has
//   a bad syntax.
// - returns true if field(s) assigned something useful or no field is
//   available to assign anything to.
bool TVCalendarItemType::MIMEStringToField(
  const char *aText,                // the value text to assign or add to the field
  const TConversionDef *aConvDefP,  // the conversion definition record
  TMultiFieldItem &aItem,           // the item where data goes to
  sInt16 aFid,                       // the field ID (can be NULL for special conversion modes)
  sInt16 aArrIndex                   // the repeat offset to handle array fields
)
{
  string s;
  lineartime_t dtstart;
  timecontext_t startcontext, untilcontext;
  char freq;
  char freqmod;
  sInt16 interval;
  fieldinteger_t firstmask;
  fieldinteger_t lastmask;
  lineartime_t until;
  bool dostore;

  // get pointer to leaf field
  switch (aConvDefP->convmode) {
    case CONVMODE_RRULE:
      // helpers
      TTimestampField *tfP;
      TIntegerField *ifP;
      TStringField *sfP;
      if (aFid<0) return true; // no field block, assignment "ok" (=nop)
      // read DTSTART (last=6th field in block) as reference for converting count to end time point
      dtstart=0; // start date/time, as reference
      if (!(tfP = ITEMFIELD_DYNAMIC_CAST_PTR(TTimestampField,fty_timestamp,aItem.getArrayField(aFid+5,aArrIndex)))) return false;
      // TZ and TZID should be applied to dates by now, so dtstart should be in right zone
      dtstart = tfP->getTimestampAs(TCTX_UNKNOWN,&startcontext);
      if (TCTX_IS_UTC(startcontext)) {
        // UTC is probably not the correct zone to resolve weekdays -> convert to item zone
        dtstart = tfP->getTimestampAs(fItemTimeContext,&startcontext);
      }
      // init field block values
      freq='0'; // frequency
      freqmod=' '; // frequency modifier
      interval=0; // unspecified interval
      firstmask=0; // day mask counted from the first day of the period
      lastmask=0; // day mask counted from the last day of the period
      until=0; // last day
      // do the conversion here
      dostore=false;
      if (fMimeDirMode==mimo_old) {
        // vCalendar 1.0 type RRULE
        dostore=RRULE1toInternal(
          aText, // RRULE string to be parsed
          dtstart, // reference date for parsing RRULE
          startcontext,
          freq,
          freqmod,
          interval,
          firstmask,
          lastmask,
          until,
          untilcontext,
          GETDBGLOGGER
        );
      }
      else {
        // iCalendar 2.0 type RRULE
        dostore=RRULE2toInternal(
          aText, // RRULE string to be parsed
          dtstart, // reference date for parsing RRULE
          startcontext,
          freq,
          freqmod,
          interval,
          firstmask,
          lastmask,
          until,
          untilcontext,
          GETDBGLOGGER
        );
      }
      if (dostore) {
        // store values into field block
        // - freq/freqmod
        if (!(sfP = ITEMFIELD_DYNAMIC_CAST_PTR(TStringField,fty_string,aItem.getArrayField(aFid,aArrIndex)))) return false;
        aFid++; // do NOT INCREMENT in macro, as it would get incremented twice
        sfP->assignEmpty();
        if (freq!='0') {
          sfP->appendChar(freq);
          sfP->appendChar(freqmod);
        }
        // - interval
        if (!(ifP = ITEMFIELD_DYNAMIC_CAST_PTR(TIntegerField,fty_integer,aItem.getArrayField(aFid,aArrIndex)))) return false;
        aFid++; // do NOT INCREMENT in macro, as it would get incremented twice
        ifP->setAsInteger(interval);
        // - firstmask
        if (!(ifP = ITEMFIELD_DYNAMIC_CAST_PTR(TIntegerField,fty_integer,aItem.getArrayField(aFid,aArrIndex)))) return false;
        aFid++; // do NOT INCREMENT in macro, as it would get incremented twice
        ifP->setAsInteger(firstmask);
        // - lastmask
        if (!(ifP = ITEMFIELD_DYNAMIC_CAST_PTR(TIntegerField,fty_integer,aItem.getArrayField(aFid,aArrIndex)))) return false;
        aFid++; // do NOT INCREMENT in macro, as it would get incremented twice
        ifP->setAsInteger(lastmask);
        // - until
        if (!(tfP = ITEMFIELD_DYNAMIC_CAST_PTR(TTimestampField,fty_timestamp,aItem.getArrayField(aFid,aArrIndex)))) return false;
        aFid++; // do NOT INCREMENT in macro, as it would get incremented twice
        tfP->setTimestampAndContext(until,untilcontext);
        // - dtstart is not stored, but only read above for reference
        // done
        return true;
      }
      else {
        return false;
      }
      break; // just in case
    default:
      // unknown mode, let ancestor handle this
      return TMimeDirItemType::MIMEStringToField(aText,aConvDefP,aItem,aFid,aArrIndex);
  }
  return false; // just in case
} // TVCalendarItemType::MIMEStringToField

*/

} // namespace sysync

/* end of TVCalendarItemType implementation */

// eof
