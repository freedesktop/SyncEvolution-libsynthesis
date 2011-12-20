/* 
 *  File:    platform_DLL.cpp
 *
 *  Author:  Beat Forster (bfo@synthesis.ch)
 *
 *
 *  General interface to access the routines
 *  of a DLL.
 *
 *  Copyright (c) 2004-2011 by Synthesis AG + plan44.ch
 *
 *
 */


#include <dlfcn.h> // the MacOSX DLL functionality
#include "platform_DLL.h"

using namespace std;


bool ConnectDLL( void* &aDLL, const char* aDLLname, ErrReport aReport, void* ref )
/* Connect to <aDLLname>, result is <aDLL> reference */
/* Returns true, if successful */
{
  #define mode RTLD_NOW + RTLD_GLOBAL
  
  const char* DSuff= ".dylib";
  string      lName;
  string      aName= aDLLname;
  
  do {             aName+= DSuff;
    aDLL = dlopen( aName.c_str(), mode ); if (aDLL!=NULL) break;
    //printf("dlopen(%s) failed dlerror()=%s\n",aName.c_str(),dlerror());
  
    lName= "./";   lName+= aName;    // try Linux current path as well
    aDLL = dlopen( lName.c_str(), mode ); if (aDLL!=NULL) break;
    //printf("dlopen(%s) failed dlerror()=%s\n",lName.c_str(),dlerror());
    aDLL = dlopen( aDLLname,      mode ); if (aDLL!=NULL) break;
    //printf("dlopen(%s) failed dlerror()=%s\n",aDLLname,dlerror());
  
    lName= "./";   lName+= aDLLname; // try Linux current path as well
    aDLL = dlopen( lName.c_str(), mode );
    //printf("dlopen(%s) failed dlerror()=%s\n",lName.c_str(),dlerror());
  } while (false);

  bool   ok= aDLL!=NULL;
  if   (!ok && aReport) aReport( ref, aName.c_str() );
  return ok;
} // ConnectDLL



bool DisconnectDLL( void* aDLL )
/* Disconnect <hDLL> */
{
  int     err= dlclose( aDLL );
  return !err;
} // DisonnectDLL



bool DLL_Function( void* aDLL, const char* aFuncName, void* &aFunc )
/* Get <aFunc> of <aFuncName> */
/* Returns true, if available */
{
  aFunc= dlsym( aDLL, aFuncName );
  return aFunc!=NULL;
} // DLL_Function



/* eof */
