

# This file was automatically generated by "create_project.py"
# Command: generate_project(type project_name solution_folder project_folder pch_header_name = project_folder pch_src_name = project_folder)
# Example: generate_project(static CoreLibs 1_common core_libs)


# include path: ${CMAKE_SOURCE_DIR}/source/include/0_extern/rex_std_extra
# src path: ${CMAKE_SOURCE_DIR}/source/src/0_extern/rex_std_extra


# Project Name Project
# -------------------------
file(GLOB_RECURSE RexStdExtra_LIBS_INC    ${CMAKE_SOURCE_DIR}/source/include/0_extern/rex_std_extra/*.h)
file(GLOB_RECURSE RexStdExtra_LIBS_SRC    ${CMAKE_SOURCE_DIR}/source/src/0_extern/rex_std_extra/*.cpp)


# Create the project filters
GROUPSOURCES(${CMAKE_SOURCE_DIR}/source/include/0_extern/rex_std_extra include)
GROUPSOURCES(${CMAKE_SOURCE_DIR}/source/src/0_extern/rex_std_extra src)


# Create the project
add_library(RexStdExtra STATIC ${RexStdExtra_LIBS_INC} ${RexStdExtra_LIBS_SRC})


# Set the include directories
target_include_directories(RexStdExtra PUBLIC ${CMAKE_SOURCE_DIR}/source/include/0_extern/rex_std_extra)

# Set the link libraries
target_link_libraries(RexStdExtra PUBLIC RexStd)

# Set project properties
set_target_properties(RexStdExtra PROPERTIES FOLDER                                         0_extern/rex_std)   		# solution folder
set_target_properties(RexStdExtra PROPERTIES DEFINE_SYMBOL                                  "" )                     		# defines
IF(MSVC)
	set_target_properties(RexStdExtra PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY                ${OUTPUT_BINDIR})        		# working directory


	set_target_properties(RexStdExtra PROPERTIES VS_GLOBAL_EnableUnitySupport                 True)                    		# unit builds on visual studio
	set_target_properties(RexStdExtra PROPERTIES VS_GLOBAL_IncludeInUnityFile                 True)
	set_target_properties(RexStdExtra PROPERTIES VS_GLOBAL_OrderInUnityFile                   100)
	set_target_properties(RexStdExtra PROPERTIES VS_GLOBAL_CombineFilesOnlyFromTheSameFolder  false)
	set_target_properties(RexStdExtra PROPERTIES VS_GLOBAL_MinFilesInUnityFile                2)
	set_target_properties(RexStdExtra PROPERTIES VS_GLOBAL_MaxFilesInUnityFile                0)
	set_target_properties(RexStdExtra PROPERTIES VS_GLOBAL_MinUnityFiles                      1)
	set_target_properties(RexStdExtra PROPERTIES VS_GLOBAL_UnityFilesDirectory                .)
ENDIF()


# Compiler options
target_compile_options(RexStdExtra PRIVATE /W4 /WX /MP)


# Set precompiled header
# add_precompiled_header(RexStdExtra "rex_std_extra/rex_std_extra_pch.h" "rex_std_extra/rex_std_extra_pch.cpp")