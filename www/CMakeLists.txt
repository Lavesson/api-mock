# TODO: This will probably not hold on any platform but windows:
set (npm "npm.cmd")
set (npm_args "install")

# Copy files from www to correct output folders as a post build step
set(app_target_1 $<TARGET_FILE_DIR:ApiMock>/www/app)
set(app_target_2 ${CMAKE_CURRENT_BINARY_DIR}/app)
set(app "${CMAKE_SOURCE_DIR}/www/app")

message ("-- Downloading AngularJS, Bootstrap and dependencies")
execute_process(COMMAND ${npm} ${npm_args}
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# Custom build target to deploy dashboard

add_custom_target(Deploy)

add_custom_command(
    TARGET Deploy POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${app} ${app_target_1})
    
add_custom_command(
    TARGET Deploy POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${app} ${app_target_2})

