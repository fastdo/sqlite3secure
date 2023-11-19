cmake_minimum_required(VERSION 2.8...3.28)
project(sqlite3secure)
# Set C99 standard
if(UNIX)
    include(CheckCCompilerFlag)
    CHECK_C_COMPILER_FLAG("-std=c99" COMPILER_SUPPORTS_C99)
    if(COMPILER_SUPPORTS_C99)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
    else()
        message(FATAL_ERROR "The compiler ${CMAKE_C_COMPILER} has no C99 support. Please use a different C compiler.")
    endif()
endif()

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
list(
    APPEND SQLITE3SECURE_DEFINITIONS
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

add_library(sqlite3secure SHARED ${SQLITE3SECURE_SRCS} ${SQLITE3SECURE_INTERNAL_HEADERS})
target_include_directories(sqlite3secure PUBLIC include)
target_compile_definitions(sqlite3secure PRIVATE ${SQLITE3SECURE_DEFINITIONS})

add_library(sqlite3secure_a STATIC ${SQLITE3SECURE_SRCS} ${SQLITE3SECURE_INTERNAL_HEADERS})
target_include_directories(sqlite3secure_a PUBLIC include)
target_compile_definitions(sqlite3secure_a PRIVATE ${SQLITE3SECURE_DEFINITIONS})

set_target_properties(sqlite3secure sqlite3secure_a PROPERTIES PUBLIC_HEADER "${SQLITE3SECURE_HEADERS}")

# Search libraries
find_library(LIBPTHREAD pthread)
if(LIBPTHREAD)
    message(STATUS "pthread: ${LIBPTHREAD}")
    target_link_libraries(sqlite3secure PRIVATE ${LIBPTHREAD})
    target_link_libraries(sqlite3secure_a PRIVATE ${LIBPTHREAD})
endif()

find_library(LIBDL dl)
if(LIBDL)
    message(STATUS "dl: ${LIBDL}")
    target_link_libraries(sqlite3secure PRIVATE ${LIBDL})
    target_link_libraries(sqlite3secure_a PRIVATE ${LIBDL})
endif()

find_library(LIBM m)
if(LIBM)
    message(STATUS "m: ${LIBM}")
    target_link_libraries(sqlite3secure PRIVATE ${LIBM})
    target_link_libraries(sqlite3secure_a PRIVATE ${LIBM})
endif()


add_executable(sqlite3shell "src/shell.c" "src/sqlite3shell.rc")
target_link_libraries(sqlite3shell PRIVATE sqlite3secure)

if(CMAKE_BUILD_TYPE)
    set(DEST_PREFIX "${CMAKE_BUILD_TYPE}")
else()
    set(DEST_PREFIX "$<CONFIG>")
endif()


install(
    TARGETS sqlite3secure sqlite3secure_a sqlite3shell
    ARCHIVE DESTINATION "${DEST_PREFIX}/lib"
    LIBRARY DESTINATION "${DEST_PREFIX}/lib"
    RUNTIME DESTINATION "${DEST_PREFIX}/bin"
    PUBLIC_HEADER DESTINATION include
)

include(CPack)
