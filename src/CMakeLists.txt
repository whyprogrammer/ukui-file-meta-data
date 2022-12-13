cmake_minimum_required(VERSION 3.14)

project(UkuiFileMetaData LANGUAGES CXX)
include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core LinguistTools REQUIRED)

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

add_library(UkuiFileMetaData SHARED
    ${UkuiFileMetaData_SRCS}
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/pkgconfig/${PROJECT_NAME}.pc.in
    ${CMAKE_CURRENT_BINARY_DIR}/ukui-file-meta-data.pc
    @ONLY
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
        FILES ${CMAKE_CURRENT_BINARY_DIR}/ukui-file-meta-data.pc
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
)

set_target_properties(UkuiFileMetaData PROPERTIES
    VERSION ${VERSION}
    SOVERSION "1"
    OUTPUT_NAME ukuifilemetadata
)
install(
    TARGETS UkuiFileMetaData
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(
    FILES ${HEADERS}
    DESTINATION "include/ukui-file-meta-data"
)