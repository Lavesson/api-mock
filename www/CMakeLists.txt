set (npm "npm")
set (npm_args "install")

execute_process(COMMAND ${npm} ${npm_args}
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
                
file(GLOB_RECURSE app ${CMAKE_SOURCE_DIR}/app)