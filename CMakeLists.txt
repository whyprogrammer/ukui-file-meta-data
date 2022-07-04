cmake_minimum_required(VERSION 3.5)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(VERSION "1.0.0")
project(UkuiFileMetaData VERSION ${VERSION})

include(FeatureSummary)
include(GNUInstallDirs)
feature_summary(WHAT REQUIRED_PACKAGES_NOT_FOUND FATAL_ON_MISSING_REQUIRED_PACKAGES)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(CheckStructHasMember)

# Dependencies
set(REQUIRED_QT_VERSION 5.15.2)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

find_package(FFmpeg 57.48 COMPONENTS AVCODEC)
find_package(FFmpeg 57.40 COMPONENTS AVFORMAT)
find_package(FFmpeg 55.27 COMPONENTS AVUTIL)
set_package_properties(FFmpeg PROPERTIES DESCRIPTION "Video Tag reader"
                       URL "https://ffmpeg.org/" TYPE OPTIONAL
                       PURPOSE "Support for video metadata")
set(CMAKECONFIG_INSTALL_DIR "/usr/include/Ukui-File-Meta-Data")
include(CMakePackageConfigHelpers)
configure_package_config_file(
                     "${CMAKE_CURRENT_SOURCE_DIR}/UkuiFileMetaDataConfig.cmake.in"
                     "${CMAKE_CURRENT_BINARY_DIR}/UkuiFileMetaDataConfig.cmake"
                     INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
                   )
enable_testing()
add_subdirectory(src)
#if (BUILD_TESTING)
add_subdirectory(autotests)
add_subdirectory(tests)
#endif()

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)

