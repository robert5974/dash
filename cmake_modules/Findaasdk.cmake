find_path(AASDK_INCLUDE_DIR
    aasdk/Version.hpp
    PATHS ${CMAKE_SOURCE_DIR}/aasdk/include
    NO_DEFAULT_PATH
)

find_path(AASDK_PROTO_INCLUDE_DIR
    aasdk_proto/AbsoluteInputEventData.pb.h
    PATHS ${CMAKE_SOURCE_DIR}/aasdk/build
    NO_DEFAULT_PATH
)

find_library(AASDK_LIBRARY NAMES aasdk
    PATHS ${CMAKE_SOURCE_DIR}/aasdk/lib
    NO_DEFAULT_PATH
)
find_library(AASDK_PROTO_LIBRARY NAMES aasdk_proto
    PATHS ${CMAKE_SOURCE_DIR}/aasdk/lib
    NO_DEFAULT_PATH
)

if (AASDK_INCLUDE_DIR AND AASDK_PROTO_INCLUDE_DIR AND AASDK_LIBRARY AND AASDK_PROTO_LIBRARY)
    set(AASDK_FOUND TRUE)
endif()

if (AASDK_FOUND)
    if (NOT aasdk_FIND_QUIETLY)
        message(STATUS "Found aasdk: ${AASDK_LIBRARY}")
        message(STATUS "Found aasdk_proto: ${AASDK_PROTO_LIBRARY}")
    endif()

    add_library(aasdk INTERFACE)
    target_include_directories(aasdk INTERFACE ${AASDK_INCLUDE_DIR} ${AASDK_PROTO_INCLUDE_DIR})
    target_link_libraries(aasdk INTERFACE ${AASDK_LIBRARY} ${AASDK_PROTO_LIBRARY})
else()
    if (aasdk_FIND_REQUIRED)
        message(FATAL_ERROR "Could not find aasdk")
    endif()
endif()

mark_as_advanced(AASDK_INCLUDE_DIR AASDK_PROTO_INCLUDE_DIR AASDK_LIBRARY AASDK_PROTO_LIBRARY)
