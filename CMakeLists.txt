cmake_minimum_required(VERSION 3.10)

set(TARGET qr-bench)

project(${TARGET})

find_package(OpenVINO REQUIRED)
find_package(OpenCV REQUIRED core imgproc imgcodecs objdetect highgui wechat_qrcode)

# If the package has been found, several variables will
# be set, you can find the full list with descriptions
# in the OpenCVConfig.cmake file.
# Print some message showing some of them
message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

ExternalProject_Add(
    quirc
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/quirc
    BINARY_DIR ${CMAKE_BINARY_DIR}/${CMAKE_SYSTEM_PROCESSOR}/${CMAKE_BUILD_TYPE})
