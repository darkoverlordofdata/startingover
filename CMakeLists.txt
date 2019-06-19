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
add_subdirectory ( .lib/glm )
if (EXISTS ${CMAKE_SOURCE_DIR}/data AND NOT DEFINED ZEROG )
    add_subdirectory (data)
    list ( APPEND RESOURCES ${resources_gresource_xml_C_FILE} )
endif ()

#
#   application source
#

list ( APPEND C_SOURCES src/ball_object.cpp )
list ( APPEND C_SOURCES src/game.cpp )
list ( APPEND C_SOURCES src/game_level.cpp )
list ( APPEND C_SOURCES src/game_object.cpp )
list ( APPEND C_SOURCES src/particle_generator.cpp )
list ( APPEND C_SOURCES src/post_processor.cpp )
list ( APPEND C_SOURCES src/program.cpp )
list ( APPEND C_SOURCES src/resource_manager.cpp )
list ( APPEND C_SOURCES src/shader.cpp )
list ( APPEND C_SOURCES src/sprite_renderer.cpp )
list ( APPEND C_SOURCES src/texture.cpp )
#
#   application includes
#
set ( INCLUDES "${INCLUDES};./include" )
set ( INCLUDES "${INCLUDES};/usr/include" )
set ( INCLUDES "${INCLUDES};/usr/include/SOIL" )


#
#   compiler options
#
# Libs: 
set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lm" )
set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lSDL2" )
set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lSDL2_image" )
set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lSDL2_mixer" )
set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lSDL2_ttf" )
set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lSOIL" )
set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lglfw" )
set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lGLEW" )
set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lGLU" )
set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lGL" )


set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -w -std=c99 -O3" )
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w -std=c++17 -O3" )


# definitions 

include_directories(AFTER ${INCLUDES})

#
#   compile ccode & link executable
#
add_executable ( ${PROJECT_NAME} ${C_SOURCES} ${RESOURCES} )
add_custom_command(TARGET ${PROJECT_NAME} 
                   POST_BUILD COMMAND 
                   ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> .. )
target_link_libraries ( ${PROJECT_NAME} m SDL2 SDL2_image SDL2_mixer SDL2_ttf SOIL glfw GLEW GLU GL  )
install (TARGETS ${PROJECT_NAME} RUNTIME DESTINATION . )

include (CPack)

# (generated from template: c. Do not modify. )
