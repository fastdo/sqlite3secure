cmake_minimum_required(VERSION 2.8...3.28)
project(sqlite3secure)

file(
    GLOB SQLITE3SECURE_HEADERS
    RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "include/*.*"
)
file(
    GLOB SQLITE3SECURE_INTERNAL_HEADERS
    RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "src/*.h"
)
file(
    GLOB SQLITE3SECURE_INTERNAL_SRCS
    RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "src/*.c"
)
file(
    GLOB SQLITE3SECURE_INTERNAL_MISCS
    RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "src/*.*"
)

list(APPEND SQLITE3SECURE_SRCS "src/sqlite3secure.c" "src/sqlite3.def" "src/sqlite3.rc")
list(REMOVE_ITEM SQLITE3SECURE_INTERNAL_MISCS ${SQLITE3SECURE_INTERNAL_HEADERS} ${SQLITE3SECURE_INTERNAL_SRCS})
list(REMOVE_ITEM SQLITE3SECURE_INTERNAL_SRCS ${SQLITE3SECURE_SRCS})

add_library(sqlite3secure SHARED ${SQLITE3SECURE_SRCS} ${SQLITE3SECURE_INTERNAL_HEADERS})
target_include_directories(sqlite3secure PUBLIC include)
target_compile_definitions(
    sqlite3secure
    PRIVATE
    THREADSAFE=1
    SQLITE_THREADSAFE=1
    SQLITE_DQS=0
    SQLITE_MAX_ATTACHED=10
    SQLITE_SOUNDEX
    SQLITE_ENABLE_COLUMN_METADATA
    SQLITE_HAS_CODEC
    SQLITE_SECURE_DELETE
    SQLITE_ENABLE_FTS3
    SQLITE_ENABLE_FTS3_PARENTHESIS
    SQLITE_ENABLE_FTS4
    SQLITE_ENABLE_FTS5
    SQLITE_ENABLE_JSON1
    SQLITE_ENABLE_RTREE
    SQLITE_ENABLE_GEOPOLY
    SQLITE_CORE
    SQLITE_ENABLE_EXTFUNC
    SQLITE_ENABLE_CSV
    SQLITE_ENABLE_SHA3
    SQLITE_ENABLE_CARRAY
    SQLITE_ENABLE_FILEIO
    SQLITE_ENABLE_SERIES
    SQLITE_ENABLE_UUID
    SQLITE_TEMP_STORE=2
    SQLITE_USE_URI
    SQLITE_USER_AUTHENTICATION
)
# # Sources
# aux_source_directory(src WINUX_SRCS)
# aux_source_directory(../eienexpr/src EIENEXPR_SRCS)

# add_library(winux SHARED ${WINUX_SRCS} ${EIENEXPR_SRCS} ${WINUX_HEADERS} ${WINUX_INTERNAL_HEADERS} ${EIENEXPR_HEADERS})
# target_include_directories(winux PUBLIC include PRIVATE ../eienexpr/include)
# target_compile_definitions(winux PUBLIC WINUX_DLL_USE PRIVATE WINUX_DLL_EXPORTS)

# add_library(winux_a STATIC ${WINUX_SRCS} ${WINUX_HEADERS} ${WINUX_INTERNAL_HEADERS} ${EIENEXPR_HEADERS})
# target_include_directories(winux_a PUBLIC include PRIVATE ../eienexpr/include)

# # Public headers
# set_target_properties(winux winux_a PROPERTIES PUBLIC_HEADER "${WINUX_HEADERS}")


# # Install
# install(
#     TARGETS winux winux_a
#     ARCHIVE DESTINATION lib
#     LIBRARY DESTINATION lib
#     RUNTIME DESTINATION bin
#     PUBLIC_HEADER DESTINATION include
# )
