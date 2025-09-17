cmake_minimum_required(VERSION 3.16)

project(NoteSync VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)
set(PROJECT_SOURCES
        main.cpp
        UI/MainWindow/MainWindow.cpp
        UI/MainWindow/MainWindow.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(NoteSync
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        Core/Note/Note.h Core/Note/Note.cpp
        Core/NoteManager/NoteManager.h Core/NoteManager/NoteManager.cpp
        Persistance/Database/Database.h Persistance/Database/Database.cpp
        UI/NotesList/NotesList.h UI/NotesList/NotesList.cpp
        UI/Header/Header.h UI/Header/Header.cpp
        UI/CategoriesList/CategoriesList.h UI/CategoriesList/CategoriesList.cpp
        UI/Editor/Editor.h UI/Editor/Editor.cpp
        Persistance/DatabaseWorker/DatabaseWorker.h Persistance/DatabaseWorker/DatabaseWorker.cpp



    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET NoteSync APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(NoteSync SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(NoteSync
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(NoteSync PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt6::Sql)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.NoteSync)
endif()
set_target_properties(NoteSync PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS NoteSync
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(NoteSync)
endif()
