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
timeutil.cpp
timeutil.h
UI_util.cpp
UI_util.h
EOF`"

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
blobs.cpp
blobs.h
enginesessiondispatch.cpp
syncserver.cpp
EOF`"

sed -e "s;@LIBSYNTHESIS_SOURCES@;`find ${ENGINE_SOURCES} syncapps/clientEngine_custom \( -name '*.cpp' -o -name '*.[ch]' \) \! \( ${SDK_FILES} -o ${SERVER_FILES} -o -name clientprovisioning_inc.cpp -o -name \*_tables_inc.cpp -o -name syncsessiondispatch.cpp \) -printf '%p '`;" \
    -e "s;@LIBSYNTHESISSERVER_SOURCES@;`find ${ENGINE_SOURCES} sysync_SDK/DB_Interfaces/text_db syncapps/serverEngine_custom \( -name '*.cpp' -o -name '*.[ch]' \) \! \( ${SDK_FILES} -o ${CLIENT_FILES} -o -name clientprovisioning_inc.cpp -o -name \*_tables_inc.cpp -o -name syncsessiondispatch.cpp \) -printf '%p '`;" \
    -e "s;@LIBSYNTHESISSDK_SOURCES_BOTH@;`find sysync_SDK/Sources \( -name '*.cpp' -o -name '*.c' \) -printf '%p '`;" \
    -e "s;@LIBSYNTHESISSDK_SOURCES_SDK_ONLY@;`find sysync_SDK/Sources \( -name '*.cpp' -o -name '*.c' \) -a \( ${SDK_FILES} \) -printf '%p '`;" \
    -e "s;@LIBSMLTK_SOURCES@;`find syncml_tk \( -name '*.cpp' -o -name '*.[ch]' \) \! \( -wholename syncml_tk/src/sml/\*/palm/\* -o -wholename syncml_tk/src/sml/\*/win/\* \) -printf '%p '`;" \
    -e "s;@LIBSYNTHESISSDK_HEADERS@;`find sysync_SDK/Sources \( -name '*.h' \) -printf 'synthesis/%f '`;" \
    Makefile.am.in >Makefile.am
