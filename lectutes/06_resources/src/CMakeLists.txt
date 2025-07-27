cmake_minimum_required(VERSION 3.19)
project(i18n_demo LANGUAGES CXX)

find_package(Qt6 6.5 COMPONENTS Core Widgets LinguistTools REQUIRED)

qt_standard_project_setup()
set(CMAKE_AUTORCC ON)
# Джерела застосунку
qt_add_executable(i18n_demo
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    resources.qrc # Your resource file
)

# Set translation files
# These are the .ts files that lupdate will generate/update
set(TS_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/translations/app_uk.ts
    ${CMAKE_CURRENT_SOURCE_DIR}/translations/app_en.ts
)

# Configure translations
# This will run lupdate to create/update .ts files and lrelease to compile them into .qm files.
# The .qm files will be placed in the build directory and then embedded via the resource system.
qt_add_translations(
    TARGETS i18n_demo
    TS_FILES ${TS_FILES}
    RESOURCE_PREFIX "/" # Important: This prefix determines how .qm files are accessed in code
)

target_link_libraries(i18n_demo PRIVATE Qt::Core Qt::Widgets)

include(GNUInstallDirs)

install(TARGETS i18n_demo
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_generate_deploy_app_script(
    TARGET i18n_demo
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
