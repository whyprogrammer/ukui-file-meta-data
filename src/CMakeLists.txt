cmake_minimum_required(VERSION 3.14)

project(UkuiFileMetaData LANGUAGES CXX)

set(CMAKE_INSTALL_PREFIX)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core LinguistTools REQUIRED)
message("====" ${CMAKE_INSTALL_FULL_LIBDIR})
set(PLUGIN_INSTALL_DIR "${CMAKE_INSTALL_FULL_LIBDIR}/ukui-file-meta-data/plugins")
add_definitions(
    -DPLUGIN_INSTALL_DIR=\"${PLUGIN_INSTALL_DIR}\"
)

#add_compile_definitions(PLUGIN_INSTALL_DIR=${CMAKE_INSTALL_FULL_LIBDIR}/ukui-file-meta-data/plugins)
add_compile_definitions(EXTRACTOR_PLUGIN_IFACE_VERSION="1.0.0")


set(TS_FILES UkuiFileMetaData_zh_CN.ts)

set(HEADERS
    ukui-file-meta-data_global.h
    extractor-manager.h
    extractor-plugin.h
    extraction-result.h
    embedded-image-data.h
    types.h
    properties.h
    extractor.h
    mime-utils.h
    )

set(UkuiFileMetaData_SRCS
    extraction-result.cpp
    embedded-image-data.cpp
    extractor.cpp
    extractor-plugin.cpp
    extractor-manager.cpp
    mime-utils.cpp
    simple-extraction-result.cpp
    property-info.cpp
#    format-strings.cpp
    )

add_library(UkuiFileMetaData
    ${UkuiFileMetaData_SRCS}
)

target_link_libraries(UkuiFileMetaData PUBLIC Qt${QT_VERSION_MAJOR}::Core)

target_compile_definitions(UkuiFileMetaData PRIVATE UKUIFILEMETADATA_LIBRARY)

if(COMMAND qt_create_translation)
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

add_subdirectory(extractors)

install(
    FILES ${HEADERS}
    DESTINATION "include/ukui-file-meta-data" COMPONENT Devel)
