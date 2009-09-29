/**
 *  @File     stdlogicagent.h
 *
 *  @Author   Lukas Zeller (luz@synthesis.ch)
 *
 *  @brief TStdLogicAgent
 *    Agent (=server or client session) for standard database logic implementations, see @ref TStdLogicDS
 *
 *    Copyright (c) 2001-2009 by Synthesis AG (www.synthesis.ch)
 *
 *  @Date 2005-09-23 : luz : created from custdbagent
 */
/*
 */

#ifndef STDLOGICAGENT_H
#define STDLOGICAGENT_H

// includes
#include "sysync.h"
#ifdef SYSYNC_CLIENT
#include "syncclient.h"
#endif
#ifdef SYSYNC_SERVER
#include "syncserver.h"
#endif
#include "localengineds.h"


using namespace sysync;

namespace sysync {


class TStdLogicAgent:
  #ifdef SYSYNC_CLIENT
  public TSyncClient
  #endif
  #ifdef SYSYNC_SERVER
  public TSyncServer
  #endif
{
  #ifdef SYSYNC_CLIENT
  typedef TSyncClient inherited;
  #endif
  #ifdef SYSYNC_SERVER
  typedef TSyncServer inherited;
  #endif
public:
  #ifdef SYSYNC_CLIENT
  TStdLogicAgent(TSyncClientBase *aClientBaseP, const char *aSessionID);
  #endif
  #ifdef SYSYNC_SERVER
  TStdLogicAgent(TSyncAppBase *aAppBaseP, TSyncSessionHandle *aSessionHandleP, const char *aSessionID);
  #endif
  virtual ~TStdLogicAgent();
  virtual void TerminateSession(void); // Terminate session, like destructor, but without actually destructing object itself
  virtual void ResetSession(void); // Resets session (but unlike TerminateSession, session might be re-used)
  void InternalResetSession(void); // static implementation for calling through virtual destructor and virtual ResetSession();
  // user authentication
  #ifdef SYSYNC_SERVER
  // - server should implement it, so we make it abstract here again (altough there is
  //   an implementation for simpleauth in session.
  virtual bool SessionLogin(const char *aUserName, const char *aAuthString, TAuthSecretTypes aAuthStringType, const char *aDeviceID) = 0;
  #endif // SYSYNC_SERVER
}; // TStdLogicAgent


}	// namespace sysync


#endif	// STDLOGICAGENT_H

// eof
