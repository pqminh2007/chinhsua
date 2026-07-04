cmake_minimum_required(VERSION 3.16)

# Đặt tên chính xác theo dự án mới của bạn
project(untitled3 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Danh sách nguồn đã được thêm đầy đủ các file còn thiếu từ thư mục cha
set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        Room.h
        RoomFactory.h
        RoomFactory.cpp
        Account.h
        Account.cpp
        DatabaseManager.h
        DatabaseManager.cpp
        logindialog.h
        logindialog.cpp
        resources.qrc

        # --- CÁC FILE THIẾU ĐƯỢC THÊM VÀO TỪ THƯ MỤC CHA ---
        ../Classify.h
        ../Classify.cpp
        ../Data.h
        ../Invoice.h
        ../Invoice.cpp
        ../Statistic.h
        ../Statistic.cpp
        ../deluxeroom.h
        ../deluxeroom.cpp
        ../room.h
        ../room.cpp
        ../standardroom.h
        ../standardroom.cpp
        ../suiteroom.h
        ../suiteroom.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(untitled3
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        class_giu_de_xem_tong.cpp
        customer.cpp
        customer.h
        date.cpp
        date.h
        employee.h
        employee.cpp
        person.cpp
        person.h
        UserManager.cpp
        UserManager.h
    )
else()
    add_executable(untitled3
        ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(untitled3 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(untitled3)
endif()