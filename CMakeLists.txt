cmake_minimum_required(VERSION 3.17)
project(nginx)

set(CMAKE_CXX_STANDARD 14)

add_executable(nginx main.cpp _include/ngx_func.h _include/ngx_signal.h signal/ngx_signal.cpp app/ngx_c_conf.cpp _include/ngx_c_conf.h _include/ngx_global.h app/ngx_string.cpp app/ngx_setproctitle.cpp app/ngx_log.cpp app/ngx_printf.cpp)