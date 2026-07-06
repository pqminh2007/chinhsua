#ifndef MAINWINDOW_H

#define MAINWINDOW_H

#include <QMainWindow>

#include <QVBoxLayout>

#include <QHBoxLayout>

#include <QGridLayout>

#include <QWidget>

#include <QFrame>

#include <QLabel>

#include <QPushButton>

#include <QTableWidget>

#include <QScrollArea>

#include <QLineEdit>

#include <QStackedWidget>

#include <QToolButton>

#include <QMenu>

#include <QAction>

#include <QIcon>

#include <QPixmap>

#include <QPainter>

#include <QPainterPath>

#include <QGraphicsDropShadowEffect>

#include <QEnterEvent> // Thêm thư viện này cho Qt 6

// ============================================================================

// IconKit — vẽ icon vector đơn sắc bằng QPainter (không dùng emoji / font ngoài)

// Phong cách outline mảnh, đồng bộ kích thước & màu, gần với Material/Fluent.

// ============================================================================

namespace IconKit {

QIcon icon(const QString &type, const QColor &color, int size = 20);

}

// --- Mock Login Window để phục vụ tính năng Đăng xuất ---

class LoginWindow : public QWidget {

    Q_OBJECT

public:

    explicit LoginWindow(QWidget *parent = nullptr);

signals:

    void loginSuccess();

};

// --- Custom Widget Card Thống kê (đã tinh gọn: bỏ ProgressBar / mini-chart) ---

class EnterpriseStatCard : public QFrame {

    Q_OBJECT

public:

    EnterpriseStatCard(const QString &iconType, const QString &title, const QString &value,

                       const QString &trend, bool isPositive, const QString &colorHex, QWidget *parent = nullptr);

protected:

    // Đồng bộ với Qt 6 (dùng QEnterEvent thay vì QEvent cũ)

    void enterEvent(QEnterEvent *event) override;

    void leaveEvent(QEvent *event) override;

private:

    QGraphicsDropShadowEffect *m_shadow;

};

// --- Main Window ---

class MainWindow : public QMainWindow

{

    Q_OBJECT // BẮT BUỘC phải có để chạy được signals / slots trong Qt

public:

    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    // Gọi hàm này sau khi đăng nhập để cập nhật tên & vai trò (Quản lý / Nhân viên / Quản trị viên...)

    void setUserProfile(const QString &name, const QString &role);

signals:

    void logoutRequested();

private:

    // Core layout containers

    QWidget *centralWidget;

    QHBoxLayout *mainLayout;

    QVBoxLayout *rightContentLayout;

    QHBoxLayout *centerWorkspaceLayout;

    QStackedWidget *pageStackedWidget;

    // Frames

    QFrame *sidebarFrame;

    QFrame *headerFrame;

    // Header user profile (tên + vai trò, hiển thị cạnh avatar)

    QLabel *lblHeaderUserName;

    QLabel *lblHeaderUserRole;

    // Dashboard page

    QWidget *dashboardPageWidget;

    QVBoxLayout *dashboardPageLayout;

    QScrollArea *dashboardScrollArea;

    QWidget *dashboardScrollContent;

    QVBoxLayout *dashboardScrollLayout;

    QTableWidget *recentBookingTable;

    // Khởi tạo

    void setupWindow();

    void setupLayouts();

    void createSidebar();

    void createHeader();

    void createDashboardPage();

    void createStatisticsCards();

    void createRoomGrid();

    void createRecentBookingTable();

    void applyStyle();

    // Helpers

    void addPremiumShadow(QWidget *widget, int blur = 16, int offset = 2, int alpha = 10);

    QFrame* createRoomCard(const QString &roomNum, const QString &type, const QString &price,

                           const QString &capacity, const QString &status, const QString &color);

    QString roleAccentColor(const QString &role) const;

};

#endif // MAINWINDOW_H tôi muốn cái nền màu trắng bên phải là xanh dương nhạt và có viền quanh để làm khung
