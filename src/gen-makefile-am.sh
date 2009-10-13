#! /bin/sh
#
# Turns Makefile.am.in into a Makefile.am which can be processed by
# automake. This is necessary because automake cannot build a list
# of source files dynamically.

# directories which contain sources for the sync engine
ENGINE_SOURCES="sysync DB_interfaces sysync_SDK/Sources Transport_interfaces/engine platform_adapters"

# files needed exclusively for libsynthesissdk.a
SDK_FILES="-false `sed -e 's/^/-o -name /' <<EOF
enginemodulebridge.cpp
enginemodulebridge.h
stringutil.cpp
stringutil.h
target_options.h
san.cpp
san.h
timeutil.cpp
timeutil.h
UI_util.cpp
UI_util.h
EOF`"

# The distinction between client and server files is not
# important and even likely to be wrong/incomplete. Right now,
# all of these files are compiled into libsynthesis and only
# kept out of libsynthesisdk.

# files needed exclusively for the client engine
CLIENT_FILES="-false `sed -e 's/^/-o -name /' <<EOF
binfile.cpp
binfileimplds.cpp
binfileimplclient.cpp
binfilebase.cpp
engineclientbase.cpp
syncclient.cpp
syncclientbase.cpp
EOF`"

# files needed exclusively for the server engine
SERVER_FILES="-false `sed -e 's/^/-o -name /' <<EOF
admindata.cpp
admindata.h
dbitem.cpp
dbitem.h
blobs.cpp
blobs.h
enginesessiondispatch.cpp
syncserver.cpp
EOF`"

# files not needed anywhere at the moment
EXTRA_FILES="-false `sed -e 's/^/-o -name /' <<EOF
clientprovisioning_inc.cpp
\*_tables_inc.cpp
syncsessiondispatch.cpp
platform_thread.cpp
enginestubs.c
EOF`"

sed -e "s;@LIBSYNTHESIS_SOURCES@;`find ${ENGINE_SOURCES} syncapps/clientEngine_custom syncapps/serverEngine_custom sysync_SDK/DB_Interfaces/text_db \( -name '*.cpp' -o -name '*.[ch]' \) \! \( ${SDK_FILES} -o ${EXTRA_FILES} \) -printf '%p '`;" \
    -e "s;@LIBSYNTHESISSDK_SOURCES_BOTH@;`find sysync_SDK/Sources \( -name '*.cpp' -o -name '*.c' \) -a \! \( ${SERVER_FILES} -o ${CLIENT_FILES} -o ${EXTRA_FILES} \) -printf '%p '`;" \
    -e "s;@LIBSYNTHESISSDK_SOURCES_SDK_ONLY@;`find sysync_SDK/Sources \( -name '*.cpp' -o -name '*.c' \) -a \( ${SDK_FILES} \) -a \! \( ${SERVER_FILES} -o ${CLIENT_FILES} -o ${EXTRA_FILES} \) -printf '%p '`;" \
    -e "s;@LIBSMLTK_SOURCES@;`find syncml_tk \( -name '*.cpp' -o -name '*.[ch]' \) \! \( -wholename syncml_tk/src/sml/\*/palm/\* -o -wholename syncml_tk/src/sml/\*/win/\* \) -printf '%p '`;" \
    -e "s;@LIBSYNTHESISSDK_HEADERS@;`find sysync_SDK/Sources \( -name '*.h' \) -printf 'synthesis/%f '`;" \
    Makefile.am.in >Makefile.am
