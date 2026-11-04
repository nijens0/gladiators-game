cmake_minimum_required(VERSION 3.21)
project(gladiators)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        REQUIRED)

add_executable(gladiators main.cpp
        src/entities/ItemType.h
        src/entities/FightType.h
        src/entities/GladiatorZone.h
        src/entities/Item.cpp
        src/entities/Item.h
        src/entities/Gladiator.cpp
        src/entities/Gladiator.h
        src/entities/Fight.cpp
        src/entities/Fight.h
        src/entities/Turn.cpp
        src/entities/Turn.h
        src/inventory/InventoryService.cpp
        src/inventory/InventoryService.h
        src/shop/ShopService.cpp
        src/shop/ShopService.h
        src/character/CharacterService.cpp
        src/character/CharacterService.h
        src/character/StatType.h
        src/arena/ArenaService.cpp
        src/arena/ArenaService.h
        src/entities/ItemName.h
        src/save/SaveService.cpp
        src/save/SaveService.h
)
target_link_libraries(gladiators
        Qt::Core
)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
