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

# Tổng hợp tất cả các file nguồn trong dự án (Đã xóa bỏ hoàn toàn dấu ../)
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    resources.qrc

    # Quản lý Tài khoản & Đăng nhập
    Account.h
    Account.cpp
    logindialog.h
    logindialog.cpp
    UserManager.h
    UserManager.cpp

    # Khách hàng & Nhân viên
    person.h
    person.cpp
    customer.h
    customer.cpp
    employee.h
    employee.cpp

    # Quản lý Phòng (Room)
    room.h
    room.cpp
    Room.h                # Lưu ý: Giữ lại nếu hệ thống phân biệt hoa/thường hệ điều hành
    RoomFactory.h
    RoomFactory.cpp
    standardroom.h
    standardroom.cpp
    deluxeroom.h
    deluxeroom.cpp
    suiteroom.h
    suiteroom.cpp

    # Quản lý Đặt phòng (Booking)
    Booking.h
    Booking.cpp
    BookingManager.h
    BookingManager.cpp

    # Quản lý Dịch vụ (Service)
    Service.h
    Service.cpp
    ServiceUsage.h
    ServiceUsage.cpp

    # Cơ sở dữ liệu & Tiện ích khác
    DatabaseManager.h
    DatabaseManager.cpp
    Classify.h
    Classify.cpp
    Data.h
    date.h
    date.cpp
    Invoice.h
    Invoice.cpp
    Statistic.h
    Statistic.cpp
    class_giu_de_xem_tong.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(untitled3
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
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