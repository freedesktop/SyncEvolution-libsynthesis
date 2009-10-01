/*
 *  File:         SyncAgent.h
 *
 *  Author:			  Lukas Zeller (luz@synthesis.ch)
 *
 *  TSyncAgent:   Provides functionality to run client or server
 *                sessions.
 *                Unifies former TSyncClient and TSyncServer
 *
 *  Copyright (c) 2002-2009 by Synthesis AG (www.synthesis.ch)
 *
 *  2009-09-30 : luz : created from syncclient.h and syncserver.h
 *
 */

#ifndef SYNC_AGENT_H
#define SYNC_AGENT_H

//%%% we still need this at this time
#define NON_FULLY_GRANULAR_ENGINE 1

#ifdef NON_FULLY_GRANULAR_ENGINE
namespace sysync {
  // queued progress events
  typedef std::list<TEngineProgressInfo> TEngineProgressInfoList;
}
#endif


#include "syncsession.h"
#include "localengineds.h"
#include "remotedatastore.h"

#include "engineinterface.h"


using namespace sysync;


namespace sysync {


// Support for SySync Diagnostic Tool
#ifdef SYSYNC_TOOL
int testLogin(int argc, const char *argv[]);
int convertData(int argc, const char *argv[]);
#endif


/// @brief server engine state
typedef enum {
  ses_needdata,     ///< need SyncML request data, waiting for STEPCMD_GOTDATA
  ses_processing,   ///< ready to perform next STEPCMD_STEP to process SyncML messages
  ses_generating,   ///< ready to perform next STEPCMD_STEP to generate SyncML messages
  ses_dataready,    ///< data is ready to be sent, waiting for STEPCMD_SENTDATA  
  ses_done,         ///< session done
  numServerEngineStates
} TServerEngineState;


/// @brief client engine state
typedef enum {
  ces_idle,         ///< client engine is idle and can be initialized with STEPCMD_CLIENTSTART
  ces_generating,   ///< ready to perform next STEPCMD_STEP to generate SyncML messages
  ces_dataready,    ///< data is ready to be sent, waiting for STEPCMD_SENTDATA
	ces_resending,		///< data already sent, but app indicates with STEPCMD_RESENDDATA that it needed to resend the data
  ces_needdata,     ///< need response data, waiting for STEPCMD_GOTDATA
  ces_processing,   ///< ready to perform next STEPCMD_STEP to process SyncML messages
  ces_done,         ///< session done
  numClientEngineStates
} TClientEngineState;




#ifdef PRECONFIGURED_SYNCREQUESTS

// config for databases to sync with
class TSyncReqConfig: public TConfigElement
{
  typedef TConfigElement inherited;
public:
  TSyncReqConfig(TLocalDSConfig *aLocalDSCfg, TConfigElement *aParentElement);
  virtual ~TSyncReqConfig();
  // General sync db settings
  // - local client datastore involved
  TLocalDSConfig *fLocalDSConfig;
  // - local client datatstore path extension (such as "test" in "contact/test")
  string fLocalPathExtension;
  // - remote server DB layer auth
  string fDBUser;
  string fDBPassword;
  // - remote server datastore path
  string fServerDBPath;
  // - sync mode
  TSyncModes fSyncMode;
  // - slowsync
  bool fSlowSync;
  // - DS 1.2 filters
  string fRecordFilterQuery;
  bool fFilterInclusive;
  // public methods
  // - create appropriate localdatastore from config and init client request params
  TLocalEngineDS *initNewLocalDataStore(TSyncSession *aSessionP);
protected:
  // check config elements
  #ifndef HARDCODED_CONFIG
  virtual bool localStartElement(const char *aElementName, const char **aAttributes, sInt32 aLine);
  #endif
  virtual void clear();
  virtual void localResolve(bool aLastPass);
}; // TSyncReqConfig



// Sync DB config list
typedef std::list<TSyncReqConfig *> TSyncReqList;

#endif


// forward
class TSyncAgent;
#ifdef SYSYNC_SERVER
class TSyncSessionHandle;
#endif
#ifdef SYSYNC_CLIENT
class TSyncClientBase;
#endif

// agent (client or server) config
class TAgentConfig: public TSessionConfig
{
  typedef TSessionConfig inherited;
public:
  TAgentConfig(const char *aElementName, TConfigElement *aParentElementP);
  virtual ~TAgentConfig();
  #ifdef SYSYNC_CLIENT
  // Local client config
  // - syncml version
  TSyncMLVersions fAssumedServerVersion; // we use this version for first connect attempt
  // - PUT devinf at every slow sync?? (smartner server needs this)
  bool fPutDevInfAtSlowSync;
  // - default auth params
  TAuthTypes fAssumedServerAuth;
  TFmtTypes fAssumedServerAuthEnc; // start with char encoding
  string fAssumedNonce; // start with no nonce
  // auth retry options (mainly for stupid servers like SCTS)
  bool fNewSessionForAuthRetry; // restart session for auth retries
  bool fNoRespURIForAuthRetry; // send retry to original URI for auth retries
  bool fSmartAuthRetry; // try to be smart and try different auth retry (different from fNewSessionForAuthRetry/fNoRespURIForAuthRetry) if first attempts fail
  #ifndef NO_LOCAL_DBLOGIN
  // - user/pw to access local DB
  string fLocalDBUser;
  string fLocalDBPassword;
  bool fNoLocalDBLogin; // if set, no local DB login is required, fLocalDBUser is used as userkey
  #endif
  // - server URI (used for PRECONFIGURED_SYNCREQUESTS, but also to predefine server URL in config for fixed-server apps)
  string fServerURI;
  #ifdef PRECONFIGURED_SYNCREQUESTS
  // Preconfigured sync request settings
  // - encoding
  SmlEncoding_t fEncoding;
  // - server layer user / pw
  string fServerUser;
  string fServerPassword;
  string fSocksHost;
  string fProxyHost;
  string fProxyUser;
  string fProxyPassword;
  // - transport layer user / pw
  string fTransportUser;
  string fTransportPassword;
  // - DB sync requests array
  TSyncReqList fSyncRequests;
  #endif
  #ifndef HARDCODED_CONFIG
  // - for debug only - used to fake a devID in the config file (useful when testing)
  string fFakeDeviceID;
  #endif
  #endif // SYSYNC_CLIENT
  #ifdef SYSYNC_SERVER
  // General server settings
  // - requested auth type (Auth requested in Chal sent to client)
  TAuthTypes fRequestedAuth;
  // - minimally required auth type (lowest auth type that is allowed)
  TAuthTypes fRequiredAuth;
  // - use automatic nonce generation for MD5 auth (empty nonce if false)
  bool fAutoNonce;
  // - constant nonce string to be used if autononce is off. If empty, no nonce is used
  string fConstantNonce;
  // - constant external URL, if set, it is used to generate RespURI (instead of Target LocURI sent by client)
  string fExternalURL;
  // - max size of GUID sent if client does not specify a MaxGUIDSize in devInf. 0=unlimited
  uInt16 fMaxGUIDSizeSent;
  // - respURI
  bool fUseRespURI;
  bool fRespURIOnlyWhenDifferent;  
  #endif // SYSYNC_SERVER
  // check config elements
  #ifndef HARDCODED_CONFIG
  virtual bool localStartElement(const char *aElementName, const char **aAttributes, sInt32 aLine);
  #endif
  virtual void clear();
  virtual void localResolve(bool aLastPass);
	#ifdef SYSYNC_SERVER
  // create appropriate session (=agent) for this server
  virtual TSyncAgent *CreateServerSession(TSyncSessionHandle *aSessionHandle, const char *aSessionID)=0;
  #endif
  #ifdef SYSYNC_CLIENT
  // create appropriate session (=agent) for this client
  virtual TSyncAgent *CreateClientSession(cAppCharP aSessionID) = 0;
  #endif
}; // TAgentConfig


// default profile ID
#define DEFAULT_PROFILE_ID 0xFFFFFFFF
#define TUNNEL_PROFILE_ID 0xFFFFFFFE

class TSyncAgent: public TSyncSession
{
  typedef TSyncSession inherited;
public:
	#ifdef SYSYNC_CLIENT
  TSyncAgent(
    TSyncClientBase *aSyncClientBaseP,
    cAppCharP aSessionID // a session ID
  );
  #endif
  #ifdef SYSYNC_SERVER
  TSyncAgent(
    TSyncAppBase *aAppBaseP,
    TSyncSessionHandle *aSessionHandleP,
    const char *aSessionID // a session ID
  );  
  #endif
  virtual ~TSyncAgent();
  virtual void TerminateSession(void); // Terminate session, like destructor, but without actually destructing object itself
  virtual void ResetSession(void); // Resets session (but unlike TerminateSession, session might be re-used)
  void InternalResetSession(void); // static implementation for calling through virtual destructor and virtual ResetSession();

  #ifdef ENGINEINTERFACE_SUPPORT
  // Support for EngineModule common interface
  /// @brief Executes next step of the session
  /// @param aStepCmd[in/out] step command (STEPCMD_xxx):
  ///        - tells caller to send or receive data or end the session etc.
  ///        - instructs engine to abort or time out the session etc.
  /// @param aInfoP[in] pointer to a TEngineProgressInfo structure, NULL if no progress info needed
  /// @return LOCERR_OK on success, SyncML or LOCERR_xxx error code on failure
  TSyError SessionStep(uInt16 &aStepCmd, TEngineProgressInfo *aInfoP);
  /// @brief Get new session key to access details of this session
  virtual appPointer newSessionKey(TEngineInterface *aEngineInterfaceP);
  #endif // ENGINEINTERFACE_SUPPORT

	// Server & Client common:
	// - message start and end
  virtual bool MessageStarted(SmlSyncHdrPtr_t aContentP, TStatusCommand &aStatusCommand, bool aBad=false);
  virtual void MessageEnded(bool aIncomingFinal);
  // - handle status received for SyncHdr, returns false if not handled
  virtual bool handleHeaderStatus(TStatusCommand *aStatusCmdP);
  // - start <sync> command group
  virtual bool processSyncStart(
    SmlSyncPtr_t aSyncP,           // the Sync element
    TStatusCommand &aStatusCommand, // pre-set 200 status, can be modified in case of errors
    bool &aQueueForLater // will be set if command must be queued for later (re-)execution
  );


	#ifdef SYSYNC_CLIENT
  #ifdef ENGINEINTERFACE_SUPPORT
  // set profileID to client session before doing first SessionStep
  virtual void SetProfileSelector(uInt32 aProfileSelector) { fProfileSelectorInternal = aProfileSelector; /* default is just passing it on */ };
  #endif // ENGINEINTERFACE_SUPPORT
  // session set-up
  // - initialize the client session, select the profile and link session with SML instance
  //   for the correct encoding
  localstatus InitializeSession(uInt32 aProfileSelector, bool aAutoSyncSession=false);
  // - selects a profile (returns false if profile not found)
  //   Note: This call must create and initialize all datastores that
  //         are to be synced with that profile.
  virtual localstatus SelectProfile(uInt32 aProfileSelector, bool aAutoSyncSession=false);
  // - Prepares connection-related stuff. Will be called after all
  //   session init is done, but before first request is sent
  virtual localstatus PrepareConnect(void) { return LOCERR_OK; };
  // called when incoming SyncHdr fails to execute
  virtual bool syncHdrFailure(bool aTryAgain);
  // retry older protocol, returns false if no older protocol to try
  bool retryOlderProtocol(bool aSameVersionRetry=false, bool aOldMessageInBuffer=false);
  // prepares client session such that it will do a retry to start a session
  // (but keeping already received auth/nonce/syncML-Version state)
  void retryClientSessionStart(bool aOldMessageInBuffer);
  // - check if session is just starting (no response yet)
  bool isStarting(void) { return fIncomingMsgID==0; };
  // Session and DB management
  // - perform login to local DB to allow accessing datastores later
  localstatus LocalLogin(void);
  // - let session process message in the SML instance buffer
  localstatus processAnswer(void);
  // - let session produce (or finish producing) next message into
  //   SML instance buffer
  //   returns aDone if no answer needs to be sent (=end of session)
  //   returns <>0 SyncML error status on error (no SyncML answer could be generated)
  localstatus NextMessage(bool &aDone);
  // URI to send outgoing message to
  virtual cAppCharP getSendURI(void) { return fRespondURI.c_str(); }; // use respondURI
  // login
  cAppCharP getServerUser(void) { return fServerUser.c_str(); };
  cAppCharP getServerPassword(void) { return fServerPassword.c_str(); };
  void setServerPassword(cAppCharP aPassword, sInt32 aPwSize=-1) { if (aPwSize<0) fServerPassword = aPassword; else fServerPassword.assign(aPassword, aPwSize); };
  // transport layer login
  cAppCharP getTransportUser(void) { return fTransportUser.c_str(); };
  cAppCharP getTransportPassword(void) { return fTransportPassword.c_str(); };
  // proxy/socks hosts
  cAppCharP getSocksHost(void) { return fSocksHost.c_str(); };
  cAppCharP getProxyHost(void) { return fProxyHost.c_str(); };
  cAppCharP getProxyUser(void) { return fProxyUser.c_str(); };
  cAppCharP getProxyPassword(void) { return fProxyPassword.c_str(); };
  // info about needed auth type
  virtual TAuthTypes requestedAuthType(void) { return auth_none; }; // client does not require auth by default
  virtual bool isAuthTypeAllowed(TAuthTypes /* aAuthType */) { return true; }; // client accepts any auth by default
  // special behaviour
  virtual bool devidWithUserHash(void) { return false; }; // do not include user name to make a hash-based pseudo-device ID by default
  // session handling
  // - get client base
  TSyncClientBase *getClientBase(void);
  #endif // SYSYNC_CLIENT

  #ifdef SYSYNC_SERVER
  virtual SmlPcdataPtr_t newResponseURIForRemote(void); // response URI
  // info about needed auth type
  virtual TAuthTypes requestedAuthType(void);
  virtual bool isAuthTypeAllowed(TAuthTypes aAuthType);
  // Request processing
  // - called when incoming SyncHdr fails to execute
  virtual bool syncHdrFailure(bool aTryAgain);
  // - end of request (to make sure even incomplete SyncML messages get cleaned up properly)
  bool EndRequest(bool &aHasData, string &aRespURI, uInt32 aReqBytes); // returns true if session must be deleted
  // - buffer answer in the session's buffer if transport allows it
  Ret_t bufferAnswer(MemPtr_t aAnswer, MemSize_t aAnswerSize);
  // - get buffered answer from the session's buffer if there is any
  void getBufferedAnswer(MemPtr_t &aAnswer, MemSize_t &aAnswerSize);
  // - get byte statistics
  virtual uInt32 getIncomingBytes(void) { return fIncomingBytes; };
  virtual uInt32 getOutgoingBytes(void) { return fOutgoingBytes; };
  // session handling
  // - get session Handle pointer
  TSyncSessionHandle *getSessionHandle(void) { return fSessionHandleP; }
  // returns remaining time for request processing [seconds]
  virtual sInt32 RemainingRequestTime(void);
  // info about server status
  virtual bool serverBusy(void); // return busy status (set by connection limit or app expiry)
  #endif // SYSYNC_SERVER
    
	#ifdef SYSYNC_CLIENT
  // variables
protected:
  // - socks and proxy hosts if any
  string fSocksHost;
  string fProxyHost;
  string fProxyUser;
  string fProxyPassword;
  // - remote SyncML server layer login
  string fServerUser;     // Server layer authentification user name
  string fServerPassword; // Server layer authentification password
  // - remote transport layer login
  string fTransportUser;
  string fTransportPassword;
  // - local DB login
  #ifndef NO_LOCAL_DBLOGIN
  bool fNoLocalDBLogin;
  string fLocalDBUser;
  string fLocalDBPassword;
  #endif
  // Authorisation
  // - get credentials/username to authenticate with remote party, NULL if none
  virtual SmlCredPtr_t newCredentialsForRemote(void); // get credentials to login to remote server
  virtual cAppCharP  getUsernameForRemote(void) { return fServerUser.c_str(); }; // specified user name
  // internal processing events
  // - message start and end
  virtual bool ClientMessageStarted(SmlSyncHdrPtr_t aContentP, TStatusCommand &aStatusCommand, bool aBad=false);
  virtual void ClientMessageEnded(bool aIncomingFinal);
  // device info (uses defaults in this base class, override to customize)
  virtual string getDeviceType(void);
  virtual string getDeviceID(void);
  // if set, SML processing errors will not be reported
  // (in case session wants to re-try something)
  bool fIgnoreMsgErrs;
  // incrementing client session number 0..255
  uInt8 fClientSessionNo;
  #ifdef HARD_CODED_SERVER_URI
  uInt32 fServerURICRC;
  uInt8 fNoCRCPrefixLen;
  #endif
  #ifdef ENGINEINTERFACE_SUPPORT
  // Engine interface
  // - process step
  TSyError ClientSessionStep(uInt16 &aStepCmd, TEngineProgressInfo *aInfoP);
  // - Step that generates SyncML data
  TSyError ClientGeneratingStep(uInt16 &aStepCmd, TEngineProgressInfo *aInfoP);
  // - Step that processes SyncML data
  TSyError ClientProcessingStep(uInt16 &aStepCmd, TEngineProgressInfo *aInfoP);
  // - internal profile selector (can be ID or index) determined with
  //   SetProfileSelector(), to be used with SelectProfile()
  uInt32 fProfileSelectorInternal;
  // - Client engine state
  TClientEngineState fEngineState;
  #endif // ENGINEINTERFACE_SUPPORT
  // - client side consecutive Alert 222, used to detect endless loop
  uInt32 fOutgoingAlertRequests;
  // Loop detecting time frame to avoid wrong detection of "keep-alive" message
  lineartime_t fOutgoingAlertStart;
public:
  // - can be cleared to suppress automatic use of DS 1.2 SINCE/BEFORE filters
  //   (e.g. for date range in func_SetDaysRange())
  bool fServerHasSINCEBEFORE;
  #endif // SYSYNC_CLIENT

  #ifdef SYSYNC_SERVER
public:
  // respuri
  bool fUseRespURI;
protected:
  // access to config
  TAgentConfig *getServerConfig(void);
  // internal processing events
  // - message start and end
  virtual bool ServerMessageStarted(SmlSyncHdrPtr_t aContentP, TStatusCommand &aStatusCommand, bool aBad=false);
  virtual void ServerMessageEnded(bool aIncomingFinal);
  // - request end, called by EndRequest, virtual for descendants
  virtual void RequestEnded(bool &aHasData);
  // - map operation
  virtual bool processMapCommand(
    SmlMapPtr_t aMapCommandP,       // the map command contents
    TStatusCommand &aStatusCommand, // pre-set 200 status, can be modified in case of errors
    bool &aQueueForLater
  );
  // Session level auth
  // - get next nonce string top be sent to remote party for subsequent MD5 auth
  virtual void getNextNonce(const char *aDeviceID, string &aNextNonce);
  // - get nonce string, which is expected to be used by remote party for MD5 auth.
  virtual void getAuthNonce(const char *aDeviceID, string &aAuthNonce);
  // device info (uses defaults for server, override to customize)
  virtual string getDeviceID(void) { return SYSYNC_SERVER_DEVID; }
  virtual string getDeviceType(void) { return SYNCML_SERVER_DEVTYP; }
  #ifdef ENGINEINTERFACE_SUPPORT
  // Engine interface
  // - process step
  TSyError ServerSessionStep(uInt16 &aStepCmd, TEngineProgressInfo *aInfoP);
  // - Step that generates SyncML data
  TSyError ServerGeneratingStep(uInt16 &aStepCmd, TEngineProgressInfo *aInfoP);
  // - Step that processes SyncML data
  TSyError ServerProcessingStep(uInt16 &aStepCmd, TEngineProgressInfo *aInfoP);
  // - Server engine state
  TServerEngineState fEngineState;
  // - request size
  MemSize_t fRequestSize;
  #endif // ENGINEINTERFACE_SUPPORT
  // set if map command received in this session
  bool fMapSeen;
  // standard nonce generation (without persistent device info)
  // %%% note: move this to session when we start supporting client auth checking
  string fLastNonce; // last nonce, will be returned at getAuthNonce()
  // busy status
  bool fServerIsBusy;
  // buffered answer
  MemPtr_t fBufferedAnswer;
  MemSize_t fBufferedAnswerSize;
  // data transfer statistics
  uInt32 fIncomingBytes;
  uInt32 fOutgoingBytes;
  // server session handle
  TSyncSessionHandle *fSessionHandleP; // the session "handle" (wrapper, containing server specific locking etc.)  
  #endif // SYSYNC_SERVER
}; // TSyncAgent


#ifdef ENGINEINTERFACE_SUPPORT

// Support for EngineModule common interface
// =========================================

#ifdef SYSYNC_CLIENT

// client runtime parameters
class TClientParamsKey :
  public TSessionKey
{
  typedef TSessionKey inherited;

public:
  TClientParamsKey(TEngineInterface *aEngineInterfaceP, TSyncAgent *aClientSessionP);
  virtual ~TClientParamsKey() {};
  // open subkey by name (not by path!)
  virtual TSyError OpenSubKeyByName(
    TSettingsKeyImpl *&aSettingsKeyP,
    cAppCharP aName, stringSize aNameSize,
    uInt16 aMode
  );
protected:
  // get table describing the fields in the struct
  virtual const TStructFieldInfo *getFieldsTable(void);
  virtual sInt32 numFields(void);
  // get actual struct base address
  virtual uInt8P getStructAddr(void);
public:
  // the associated client session
  TSyncAgent *fClientSessionP;
}; // TClientParamsKey

#endif // SYSYNC_CLIENT

#ifdef SYSYNC_SERVER


#ifndef ENGINE_LIBRARY

#warning "using ENGINEINTERFACE_SUPPORT in old-style appbase-rooted environment. Should be converted to real engine usage later"

// Define dummy server engine class - no implementation of actual server engine routines,
// defaults from TEngineInterface (returning error codes) will be used.
class TDummyServerEngineInterface :
  public TEngineInterface
{
  typedef TEngineInterface inherited;
public:
  // constructor
  TDummyServerEngineInterface() {};

  // appbase factory
  virtual TSyncAppBase *newSyncAppBase(void);

}; // TDummyServerEngineInterface

#endif // not ENGINE_LIBRARY



// server runtime parameters
class TServerParamsKey :
  public TSessionKey
{
  typedef TSessionKey inherited;

public:
  TServerParamsKey(TEngineInterface *aEngineInterfaceP, TSyncAgent *aServerSessionP);

  virtual ~TServerParamsKey() {};

protected:
  // get table describing the fields in the struct
  virtual const TStructFieldInfo *getFieldsTable(void);
  virtual sInt32 numFields(void);
  // get actual struct base address
  virtual uInt8P getStructAddr(void);
public:
  // the associated server session
  TSyncAgent *fServerSessionP;
}; // TServerParamsKey

#endif // SYSYNC_SERVER

#endif // ENGINEINTERFACE_SUPPORT

}	// namespace sysync

#endif	// SYNC_AGENT_H

// eof