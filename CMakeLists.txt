cmake_minimum_required(VERSION 3.10)

project(qr-bench LANGUAGES C CXX)

option(WITH_ZXING "build with zxing-cpp" OFF)

find_package(OpenCV REQUIRED core imgproc imgcodecs objdetect highgui wechat_qrcode)

# If the package has been found, several variables will
# be set, print some message showing some of them
message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

# configure quirc library build with cmake
set(LIBQUIRC_NAME libquirc)
set(LIBQUIRC_VERSION "1.2")
set(LIBQUIRC_HDRS
    ${CMAKE_SOURCE_DIR}/quirc/lib/quirc.h
    ${CMAKE_SOURCE_DIR}/quirc/lib/quirc_internal.h)
set(LIBQUIRC_SRCS
    ${CMAKE_SOURCE_DIR}/quirc/lib/decode.c
    ${CMAKE_SOURCE_DIR}/quirc/lib/identify.c
    ${CMAKE_SOURCE_DIR}/quirc/lib/quirc.c
    ${CMAKE_SOURCE_DIR}/quirc/lib/version_db.c)

add_library(${LIBQUIRC_NAME} SHARED ${LIBQUIRC_HDRS} ${LIBQUIRC_SRCS})
set_target_properties(${LIBQUIRC_NAME} PROPERTIES VERSION ${LIBQUIRC_VERSION})
target_compile_definitions(${LIBQUIRC_NAME} PRIVATE QUIRC_FLOAT_TYPE=float)
target_compile_definitions(${LIBQUIRC_NAME} PRIVATE QUIRC_USE_TGMATH)
target_include_directories(${LIBQUIRC_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/quirc/lib)
target_link_libraries(${LIBQUIRC_NAME} m)

add_subdirectory(thirdparty/gflags)

set(APP_HDRS
    ${CMAKE_SOURCE_DIR}/src/qrcode-base.h
    ${CMAKE_SOURCE_DIR}/src/qrcode-quirc.h)
set(APP_SRCS
    ${CMAKE_SOURCE_DIR}/src/qrcode-bench.cpp
    ${CMAKE_SOURCE_DIR}/src/qrcode-quirc.cpp)

add_executable(${PROJECT_NAME} ${APP_HDRS} ${APP_SRCS})
target_include_directories(${PROJECT_NAME} PUBLIC ${OpenCV_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PUBLIC ${LIBQUIRC_NAME})
target_link_libraries(${PROJECT_NAME} PUBLIC gflags::gflags)
target_link_libraries(${PROJECT_NAME} PUBLIC ${OpenCV_LIBS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBQUIRC_NAME})
