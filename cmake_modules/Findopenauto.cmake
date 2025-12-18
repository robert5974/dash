
set(OPENAUTO_SEARCH_DIR "${CMAKE_SOURCE_DIR}/openauto")

find_path(OPENAUTO_INCLUDE_DIR
    openauto/Service/ServiceFactory.hpp
    PATHS ${OPENAUTO_SEARCH_DIR}/include
    NO_DEFAULT_PATH
)

find_library(OPENAUTO_LIBRARY
    NAMES openauto
    PATHS ${OPENAUTO_SEARCH_DIR}/lib
    NO_DEFAULT_PATH
)

if (OPENAUTO_INCLUDE_DIR AND OPENAUTO_LIBRARY)
    set(OPENAUTO_FOUND TRUE)
endif()
  
if (OPENAUTO_FOUND)
    if (NOT openauto_FIND_QUIETLY)
        message(STATUS "Found openauto:")
        message(STATUS " - Includes: ${OPENAUTO_INCLUDE_DIR}")
        message(STATUS " - Library: ${OPENAUTO_LIBRARY}")
    endif()
    add_library(openauto INTERFACE)
    target_include_directories(openauto INTERFACE ${OPENAUTO_INCLUDE_DIR}) 
    target_link_libraries(openauto INTERFACE ${OPENAUTO_LIBRARY})
else()
    if (openauto_FIND_REQUIRED)
               message(FATAL_ERROR "Could not find openauto")
    endif()
endif()

mark_as_advanced(OPENAUTO_INCLUDE_DIRS OPENAUTO_LIBRARIES)
