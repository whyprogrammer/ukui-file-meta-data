find_package(QT NAMES Qt6 Qt5 COMPONENTS Test REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} ${REQUIRED_QT_VERSION} CONFIG REQUIRED Test)


remove_definitions(-DQT_NO_CAST_FROM_ASCII)

configure_file(indexerextractortestsconfig.h.in
               ${CMAKE_CURRENT_BINARY_DIR}/indexerextractortestsconfig.h @ONLY)
include_directories(../src)

add_executable(ffmpegExtractorTest
    ffmpeg-extractortest.cpp
    ../src/extractors/ffmpeg-extractor.cpp)
target_include_directories(ffmpegExtractorTest SYSTEM PRIVATE ${AVCODEC_INCLUDE_DIRS} ${AVFORMAT_INCLUDE_DIRS} ${AVUTIL_INCLUDE_DIRS})
target_link_libraries(ffmpegExtractorTest PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Test
    UkuiFileMetaData
    ${AVCODEC_LIBRARIES}
    ${AVFORMAT_LIBRARIES}
    ${AVUTIL_LIBRARIES}
    )

add_test(ffmpegExtractorTest ${CMAKE_BINARY_DIR}/autotests/ffmpegExtractorTest)






