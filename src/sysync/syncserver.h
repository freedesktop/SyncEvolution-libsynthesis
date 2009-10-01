/*
 *  File:         syncserver.h
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

#if defined(SYSYNC_CLIENT) || !defined(SYSYNC_SERVER)
	#error "syncserver.h can only be included in a server-only build"
#else
	#warning "obsolete syncserver.h included - should be replaced by including syncagent.h"
	#include "syncagent.h"
#endif

// eof

