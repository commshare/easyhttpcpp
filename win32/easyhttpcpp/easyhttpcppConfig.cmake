if (CMAKE_VERSION VERSION_LESS 3.0)
    message(FATAL_ERROR "easyhttpcpp requires at least CMake version 3.0")
endif ()

set(_easyhttpcpp_FIND_PARTS_REQUIRED)
if (easyhttpcpp_FIND_REQUIRED)
    set(_easyhttpcpp_FIND_PARTS_REQUIRED REQUIRED)
endif ()
set(_easyhttpcpp_FIND_PARTS_QUIET)
if (easyhttpcpp_FIND_QUIETLY)
    set(_easyhttpcpp_FIND_PARTS_QUIET QUIET)
endif ()

get_filename_component(_easyhttpcpp_install_prefix "${CMAKE_CURRENT_LIST_DIR}" ABSOLUTE)

set(_easyhttpcpp_NOTFOUND_MESSAGE)

set(_easyhttpcpp_CMAKE_PREFIX_PATH_old ${CMAKE_PREFIX_PATH})
set(CMAKE_PREFIX_PATH ${_easyhttpcpp_install_prefix})

set(module easyhttp)
find_package(easyhttpcpp${module}
             ${_easyhttpcpp_FIND_PARTS_QUIET}
             ${_easyhttpcpp_FIND_PARTS_REQUIRED}
             PATHS "${_easyhttpcpp_install_prefix}" NO_DEFAULT_PATH
             )
if (NOT easyhttpcpp${module}_FOUND)
    if (easyhttpcpp_FIND_REQUIRED_${module})
        set(_easyhttpcpp_NOTFOUND_MESSAGE
            "${_easyhttpcpp_NOTFOUND_MESSAGE}Failed to find easyhttpcpp component \"${module}\" config file at \"${_easyhttpcpp_install_prefix}/easyhttpcpp${module}/easyhttpcpp${module}Config.cmake\"\n")
    elseif (NOT easyhttpcpp_FIND_QUIETLY)
        message(WARNING "Failed to find easyhttpcpp component \"${module}\" config file at \"${_easyhttpcpp_install_prefix}/easyhttpcpp${module}/easyhttpcpp${module}Config.cmake\"")
    endif ()
endif ()

# For backward compatibility set the LIBRARIES variable
list(APPEND easyhttpcpp_LIBRARIES "easyhttpcpp::${module}")

# For backward compatibility set the INCLUDE_DIR(s) variables
list(APPEND easyhttpcpp_INCLUDE_DIR "C:/Program Files (x86)/easyhttpcpp/include")
list(APPEND easyhttpcpp_INCLUDE_DIRS "C:/Program Files (x86)/easyhttpcpp/include")

# Restore the original CMAKE_PREFIX_PATH value
set(CMAKE_PREFIX_PATH ${_easyhttpcpp_CMAKE_PREFIX_PATH_old})

if (_easyhttpcpp_NOTFOUND_MESSAGE)
    set(easyhttpcpp_NOT_FOUND_MESSAGE "${_easyhttpcpp_NOTFOUND_MESSAGE}")
    set(easyhttpcpp_FOUND False)
endif ()
