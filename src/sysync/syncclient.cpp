/*
 *  File:         syncclient.cpp
 *
 *  Author:			  Lukas Zeller (luz@synthesis.ch)
 *
 *  stub for using TSyncAgent in old projects that used TSyncServer or TSyncClient
 *
 *  Copyright (c) 2001-2009 by Synthesis AG (www.synthesis.ch)
 *
 *  2009-09-30 : luz : Created
 *
 */

#include "prefix_file.h"

#if defined(SYSYNC_SERVER) || !defined(SYSYNC_CLIENT)
	#error "syncclient.cpp can only be included in a client-only build"
#else
	#include "syncagent.cpp"
#endif

// eof

