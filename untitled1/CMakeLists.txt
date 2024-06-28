cmake_minimum_required(VERSION 3.5)

project(untitled1 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network Quick)

set(PROJECT_SOURCES
        main.cpp
        maindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(untitled1
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        add.cpp add.h add.ui change_avatar.cpp change_avatar.h change_back.cpp change_back.h change_name.cpp change_name.h chat_window.cpp chat_window.h chat_window.ui DoubleClickLineEdit.h dynamic.cpp dynamic.h dynamic.ui frienditem.cpp frienditem.h frienditem.ui friends.cpp friends.h friends.ui groupitem.cpp groupitem.h groupitem.ui groups.cpp groups.h groups.ui main.cpp maindow.cpp mainwindow.h mainwindow.ui messageitem.cpp messageitem.h messageitem.ui my_tcpsocket.cpp my_tcpsocket.h pendingmessage.cpp pendingmessage.h pendingmessage.ui pendingmessageitem.cpp pendingmessageitem.h pendingmessageitem.ui person_dynamic.cpp person_dynamic.h person_dynamic.ui person_message.cpp person_message.h person_message.ui post_item.cpp post_item.h post_item.ui release_post.cpp release_post.h release_post.ui todoitem.cpp todoitem.h todoitem.ui widget.cpp widget.h widget.ui
        picture.qrc
        picture/avatar/1.jpg picture/avatar/2.jpg picture/avatar/3.jpg picture/avatar/4.jpg picture/avatar/5.jpg picture/avatar/6.jpg picture/avatar/7.jpg picture/avatar/8.jpg picture/avatar/9.jpg picture/avatar/10.jpg picture/avatar/11.jpg picture/avatar/12.jpg picture/avatar/13.jpg picture/avatar/14.jpg picture/avatar/15.jpg picture/avatar/16.jpg
        picture/background/1.jpg picture/background/2.jpg picture/background/3.jpg picture/background/4.jpg picture/background/5.jpg picture/background/6.jpg picture/background/7.jpg picture/background/8.jpg picture/background/9.jpg picture/background/10.jpg picture/background/11.jpg picture/background/12.jpg picture/background/13.jpg picture/background/14.jpg picture/background/15.jpg picture/background/16.jpg


    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET untitled1 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(untitled1 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(untitled1
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(untitled1 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network Qt6::Quick)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.untitled1)
endif()
set_target_properties(untitled1 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS untitled1
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(untitled1)
endif()
