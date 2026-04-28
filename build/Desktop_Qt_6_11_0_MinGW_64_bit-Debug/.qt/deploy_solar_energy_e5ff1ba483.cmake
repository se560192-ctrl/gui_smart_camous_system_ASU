include("S:/sp project/solar_energy/build/Desktop_Qt_6_11_0_MinGW_64_bit-Debug/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/solar_energy-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE "S:/sp project/solar_energy/build/Desktop_Qt_6_11_0_MinGW_64_bit-Debug/solar_energy.exe"
    GENERATE_QT_CONF
)
