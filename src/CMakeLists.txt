include_directories (${CMAKE_SOURCE_DIR}/3rdParty/mupdf-qt/include)
link_directories    (${CMAKE_SOURCE_DIR}/3rdParty/mupdf-qt/build/lib)
link_directories    (${CMAKE_SOURCE_DIR}/3rdParty/mupdf-qt/mupdf/build/debug)

add_executable (${PROJECT_NAME}
   main.cpp
   Controller.cpp
   PdfViewer.cpp
)

target_link_libraries (${PROJECT_NAME}
   mupdf-qt
   mupdf
   z
   mujs
   freetype
   jbig2dec
   jpeg
   openjpeg
   crypto
)

qt5_use_modules (${PROJECT_NAME} Widgets)

