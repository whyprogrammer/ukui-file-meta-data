include_directories(../)
include_directories(${POPPLER_INCLUDE_DIRS})
include_directories(${UCHARDET_INCLUDE_DIRS})

if(AVCODEC_FOUND AND AVFORMAT_FOUND AND AVUTIL_FOUND)
    add_library(ukuifilemetadata_ffmpegextractor MODULE
        ffmpeg-extractor.cpp
    )
    target_include_directories(ukuifilemetadata_ffmpegextractor SYSTEM PRIVATE ${AVCODEC_INCLUDE_DIRS} ${AVFORMAT_INCLUDE_DIRS} ${AVUTIL_INCLUDE_DIRS})
    target_link_libraries(ukuifilemetadata_ffmpegextractor
        UkuiFileMetaData
	${AVCODEC_LIBRARIES}
	${AVFORMAT_LIBRARIES}
	${AVUTIL_LIBRARIES}
    )
    set_target_properties(ukuifilemetadata_ffmpegextractor PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/ukuifilemetadata")
    install(
    TARGETS ukuifilemetadata_ffmpegextractor
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/ukui-file-meta-data/plugins")

endif()

#
#office (binary)
#

add_library(ukuifilemetadata_officeextractor MODULE office-extractor.cpp binary-parser.cpp)
target_link_libraries(ukuifilemetadata_officeextractor
    UkuiFileMetaData)
set_target_properties(ukuifilemetadata_officeextractor PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/ukuifilemetadata")
install(
    TARGETS ukuifilemetadata_officeextractor
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/ukui-file-meta-data/plugins")

#
#office2007
#

add_library(ukuifilemetadata_office2007extractor MODULE office2007-extractor.cpp)
target_link_libraries(ukuifilemetadata_office2007extractor
    UkuiFileMetaData
    libquazip5.so)
set_target_properties(ukuifilemetadata_office2007extractor PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/ukuifilemetadata")
install(
    TARGETS ukuifilemetadata_office2007extractor
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/ukui-file-meta-data/plugins")

#
#text
#

add_library(ukuifilemetadata_textextractor MODULE text-extractor.cpp)
target_link_libraries(ukuifilemetadata_textextractor
    UkuiFileMetaData
    ${UCHARDET_LIBRARIES}
)
set_target_properties(ukuifilemetadata_textextractor PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/ukuifilemetadata")
install(
    TARGETS ukuifilemetadata_textextractor
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/ukui-file-meta-data/plugins")

#
#pdf
#

add_library(ukuifilemetadata_pdfextractor MODULE pdf-extractor.cpp)
target_link_libraries(ukuifilemetadata_pdfextractor
    UkuiFileMetaData
    ${POPPLER_LIBRARIES}
)
set_target_properties(ukuifilemetadata_pdfextractor PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/ukuifilemetadata")
install(
    TARGETS ukuifilemetadata_pdfextractor
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/ukui-file-meta-data/plugins")