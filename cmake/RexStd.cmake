# Project Name Project
# -------------------------
file(GLOB_RECURSE RexStd_LIBS_INC    ${CMAKE_SOURCE_DIR}/source/RexStd/include/*.h)
file(GLOB_RECURSE RexStd_LIBS_SRC    ${CMAKE_SOURCE_DIR}/source/RexStd/src/*.cpp)


# Create the project filters
GROUPSOURCES(${CMAKE_SOURCE_DIR}/source/RexStd/include include)
GROUPSOURCES(${CMAKE_SOURCE_DIR}/source/RexStd/src src)


# Create the project
add_library(RexStd STATIC ${RexStd_LIBS_INC} ${RexStd_LIBS_SRC})

# Compiler definitions
# add_compile_definitions("REX_ENABLE_LOGGING")
# add_compile_definitions("REX_ENABLE_ASSERTS")

# Set the include directories
target_include_directories(RexStd PUBLIC ${CMAKE_SOURCE_DIR}/source/RexStd/include)

# Set the static libraries you need to link to 
IF(MSVC)
	target_link_libraries(RexStd "Dbghelp.lib")
ENDIF()

# Set project properties
IF(MSVC)
	set_target_properties(RexStd PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY                ${OUTPUT_BINDIR})        		# working directory


	set_target_properties(RexStd PROPERTIES VS_GLOBAL_EnableUnitySupport                 True)                    		# unit builds on visual studio
	set_target_properties(RexStd PROPERTIES VS_GLOBAL_IncludeInUnityFile                 True)
	set_target_properties(RexStd PROPERTIES VS_GLOBAL_OrderInUnityFile                   100)
	set_target_properties(RexStd PROPERTIES VS_GLOBAL_CombineFilesOnlyFromTheSameFolder  false)
	set_target_properties(RexStd PROPERTIES VS_GLOBAL_MinFilesInUnityFile                2)
	set_target_properties(RexStd PROPERTIES VS_GLOBAL_MaxFilesInUnityFile                0)
	set_target_properties(RexStd PROPERTIES VS_GLOBAL_MinUnityFiles                      1)
	set_target_properties(RexStd PROPERTIES VS_GLOBAL_UnityFilesDirectory                .)
ENDIF()


# Compiler options
if (MSVC)
target_compile_options(RexStd PRIVATE /W4 /WX /MP)
endif()

# add the clang tools post build check
add_custom_command(TARGET RexStd POST_BUILD COMMAND "${CMAKE_SOURCE_DIR}/scripts/run_clang_tools.py")