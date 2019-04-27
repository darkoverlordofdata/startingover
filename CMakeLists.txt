cmake_minimum_required ( VERSION 3.1 )
###################################################################################
#
#   Build startingover
#
###################################################################################
project ( startingover VERSION 0.0.1 )

#
set ( VERSION 0.0.1 )
set ( RELEASE_NAME startingover )

#
# enable features
#
include ( CMakeToolsHelpers OPTIONAL )

#
#   libraries - sources & packages
#
if (EXISTS ${CMAKE_SOURCE_DIR}/data AND NOT DEFINED ZEROG )
    add_subdirectory (data)
    list ( APPEND RESOURCES ${resources_gresource_xml_C_FILE} )
endif ()

#
#   application source
#

list ( APPEND C_SOURCES src/startingover.c )
#
#   application includes
#
set ( INCLUDES "${INCLUDES};./include" )


#
#   compiler options
#
# Libs: 
set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lm" )


set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -w -std=c99 -O3" )

# definitions 

include_directories(AFTER ${INCLUDES})

#
#   compile ccode & link executable
#
add_executable ( ${PROJECT_NAME} ${C_SOURCES} ${RESOURCES} )

target_link_libraries ( ${PROJECT_NAME} m  )
install (TARGETS ${PROJECT_NAME} RUNTIME DESTINATION . )

include (CPack)

# (generated from template: c. Do not modify. )
