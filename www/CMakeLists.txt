# TODO: This will probably not hold on any platform but windows:
set (npm "npm.cmd")
set (npm_args "install")

message ("-- Downloading and installing dependencies via npm")
execute_process(COMMAND ${npm} ${npm_args}
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE app ${CMAKE_SOURCE_DIR}/app)