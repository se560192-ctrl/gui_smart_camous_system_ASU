cmake_minimum_required(VERSION 3.19)
project(solar_energy LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(solar_energy
    WIN32 MACOSX_BUNDLE
    main.cpp
    my_project.cpp
    my_project.h
    my_project.ui
    admin.cpp admin.h alert.cpp alert.h building.cpp building.h
    filehandling.cpp filehandling.h
    reading.cpp reading.h report.cpp report.h
    "smart campus.cpp"
    build/Desktop_Qt_6_11_0_MinGW_64_bit-Debug/campusData.txt
)

target_link_libraries(solar_energy
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS solar_energy
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET solar_energy
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
