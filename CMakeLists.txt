cmake_minimum_required(VERSION 3.10)

set(TARGET qr-bench)

project(${TARGET} LANGUAGES C CXX)

#find_package(OpenVINO REQUIRED)
find_package(OpenCV REQUIRED core imgproc imgcodecs objdetect highgui wechat_qrcode)
find_program(MAKE_EXECUTABLE NAMES make REQUIRED)

if(${CMAKE_BUILD_TYPE}=="Debug")
  set(QUIRC_FLAGS "CFLAGS=-fPIC -g QUIRC_FLOAT_TYPE=float")
endif()

# If the package has been found, several variables will
# be set, you can find the full list with descriptions
# in the OpenCVConfig.cmake file.
# Print some message showing some of them
message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

include(ExternalProject)

ExternalProject_Add(
    quirc
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/quirc
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${MAKE_EXECUTABLE} clean all -C <SOURCE_DIR> ${QUIRC_FLAGS}
    INSTALL_COMMAND "")

#ExternalProject_Get_Property(quirc SOURCE_DIR)
#message("+++++" ${SOURCE_DIR})
#BINARY_DIR ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}
