#include "mainwindow.h"
#include <QApplication>
#include <iostream>

#include "Account.h"
#include "RoomFactory.h"
#include "DatabaseManager.h"
#include "logindialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::cout << "=== HE THONG QUAN LY KHACH SAN GRAND HOTEL ===" << std::endl;

    // 1. Thử nghiệm phân quyền tài khoản
    Account managerAcc("admin", "admin123", Role::Manager);
    if (managerAcc.login("admin", "admin123")) {
        std::cout << "-> Dang nhap thanh cong! User: " << managerAcc.getUsername()
        << " | Quyen: " << managerAcc.getRoleString() << std::endl;
    }

    // 2. Thử nghiệm Factory Pattern tạo phòng tự động
    auto testRoom = RoomFactory::createRoom("Standard", 101);
    if (testRoom) {
        std::cout << "-> Factory tao phong thanh cong! So phong: " << testRoom->getRoomNumber()
        << " | Loai: " << testRoom->getRoomType() << std::endl;
    }

    // 3. Đọc dữ liệu từ file JSON bằng Singleton
    DatabaseManager::getInstance().loadRoomsFromJSON(DatabaseManager::getInstance().getRoomsVectorPlaceholder());

    // KHỞI CHẠY ĐĂNG NHẬP TRƯỚC
    LoginDialog login;

    // Nếu tắt hoặc đăng nhập sai -> thoát ứng dụng trực tiếp
    if (login.exec() != QDialog::Accepted) {
        return 0;
    }

    // ĐĂNG NHẬP THÀNH CÔNG -> Mở MainWindow an toàn không lỗi bộ nhớ
    MainWindow w;
    w.show();

    return a.exec();
}