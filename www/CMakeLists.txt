set (npm "npm")

if (WIN32)
	set (npm "npm.cmd")
endif()

set (npm_args "install")

# Copy files from www to correct output folders as a post build step
set(app_target_1 $<TARGET_FILE_DIR:api-mock>/www/app)
set(app_target_2 ${CMAKE_CURRENT_BINARY_DIR}/app)
set(app "${CMAKE_SOURCE_DIR}/www/app")

message ("-- Downloading AngularJS, Bootstrap and dependencies")
execute_process(COMMAND ${npm} ${npm_args}
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# Custom build target to deploy dashboard

add_custom_target(deploy)

add_custom_command(
    TARGET deploy POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${app} ${app_target_1})
    
add_custom_command(
    TARGET deploy POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${app} ${app_target_2})

