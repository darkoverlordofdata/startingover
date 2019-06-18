cmake_minimum_required ( VERSION 3.1 )
###################################################################################
#
#   Library: glm
#
###################################################################################
project ( glm VERSION 0.0.1 )

# Includes: 
list ( APPEND INCLUDE .lib/glm/include )

# C Sources: 
list ( APPEND CSOURCE .lib/glm/src/glm.c )

# Vala Sources: 

# Vapis: 
list ( APPEND VAPI .lib/glm/src/glm.vapi )

# Vapidir: 

## Export to the parent scope:
set ( GLM true PARENT_SCOPE )
set ( INCLUDES "${INCLUDES};${INCLUDE}" PARENT_SCOPE )
set ( C_SOURCES "${C_SOURCES};${CSOURCE}" PARENT_SCOPE )

set ( CUSTOM_VAPIS "${CUSTOM_VAPIS};${VAPI}" PARENT_SCOPE )




# (generated from template: package. Do not modify. )
