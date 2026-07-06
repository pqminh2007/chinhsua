#include "mainwindow.h"
#include <QApplication>
#include <QButtonGroup>
#include <QMessageBox>
#include <QHeaderView>
#include <QDateTime>
#include <QList>
#include <cmath>

// ============================================================================
// IconKit — Đã cập nhật màu sắc mặc định của Icon sang màu Xanh Dương Sáng
// và Xám Đậm để hòa hợp 100% với giao diện SaaS tối giản mới.
// ============================================================================
QIcon IconKit::icon(const QString &type, const QColor &color, int size) {
    QPixmap pm(size, size);
    pm.fill(Qt::transparent);

    pm.setDevicePixelRatio(qApp->devicePixelRatio());

    QPainter p(&pm);
    p.setRenderHint(QPainter::Antialiasing);

    QPen pen(color);
    pen.setWidthF(size * 0.085);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    p.setPen(pen);
    p.setBrush(Qt::NoBrush);

    const qreal s = size;
    const qreal m = s * 0.16;

    if (type == "dashboard") {
        qreal g = s * 0.10;
        qreal cell = (s - 2*m - g) / 2.0;
        p.drawRoundedRect(QRectF(m, m, cell, cell), 3, 3);
        p.drawRoundedRect(QRectF(m+cell+g, m, cell, cell), 3, 3);
        p.drawRoundedRect(QRectF(m, m+cell+g, cell, cell), 3, 3);
        p.drawRoundedRect(QRectF(m+cell+g, m+cell+g, cell, cell), 3, 3);
    } else if (type == "bed") {
        p.drawLine(QPointF(m, s*0.42), QPointF(m, s-m));
        p.drawLine(QPointF(s-m, s*0.42), QPointF(s-m, s-m));
        p.drawRoundedRect(QRectF(m, s*0.42, s-2*m, s*0.22), 2, 2);
        p.drawLine(QPointF(m, s*0.64), QPointF(s-m, s*0.64));
        p.drawRoundedRect(QRectF(m*1.1, s*0.22, s*0.28, s*0.20), 2, 2);
    } else if (type == "calendar") {
        p.drawRoundedRect(QRectF(m, s*0.22, s-2*m, s-m-s*0.22), 3, 3);
        p.drawLine(QPointF(m, s*0.40), QPointF(s-m, s*0.40));
        p.drawLine(QPointF(s*0.32, m*0.6), QPointF(s*0.32, s*0.30));
        p.drawLine(QPointF(s*0.68, m*0.6), QPointF(s*0.68, s*0.30));
    } else if (type == "users") {
        p.drawEllipse(QPointF(s*0.38, s*0.36), s*0.14, s*0.14);
        QPainterPath body;
        body.moveTo(s*0.16, s*0.82);
        body.cubicTo(s*0.16, s*0.60, s*0.60, s*0.60, s*0.60, s*0.82);
        p.drawPath(body);
        p.drawEllipse(QPointF(s*0.68, s*0.32), s*0.11, s*0.11);
        QPainterPath body2;
        body2.moveTo(s*0.52, s*0.82);
        body2.cubicTo(s*0.52, s*0.66, s*0.86, s*0.66, s*0.86, s*0.82);
        p.drawPath(body2);
    } else if (type == "invoice") {
        p.drawRoundedRect(QRectF(m, m*0.8, s-2*m, s-m*1.6), 3, 3);
        for (int i = 0; i < 3; ++i) {
            qreal y = s*0.36 + i*s*0.16;
            p.drawLine(QPointF(m*1.6, y), QPointF(s-m*1.6, y));
        }
    } else if (type == "staff" || type == "account") {
        p.drawEllipse(QPointF(s/2.0, s*0.36), s*0.16, s*0.16);
        QPainterPath body;
        body.moveTo(s*0.20, s*0.85);
        body.cubicTo(s*0.20, s*0.58, s*0.80, s*0.58, s*0.80, s*0.85);
        p.drawPath(body);
    } else if (type == "wallet") {
        p.drawRoundedRect(QRectF(m, s*0.28, s-2*m, s*0.52), 3, 3);
        p.drawLine(QPointF(m, s*0.28), QPointF(m + (s-2*m)*0.7, s*0.28));
        QPainterPath flap;
        flap.moveTo(m, s*0.28);
        flap.lineTo(s*0.30, m);
        flap.lineTo(s-m, m*1.1);
        p.drawPath(flap);
        p.setBrush(color);
        p.drawEllipse(QPointF(s-m*1.8, s*0.54), s*0.045, s*0.045);
        p.setBrush(Qt::NoBrush);
    } else if (type == "chart-up") {
        QPainterPath path;
        path.moveTo(m, s*0.72);
        path.lineTo(s*0.38, s*0.46);
        path.lineTo(s*0.58, s*0.60);
        path.lineTo(s-m, s*0.26);
        p.drawPath(path);
        p.drawLine(QPointF(s-m*1.7, s*0.26), QPointF(s-m, s*0.26));
        p.drawLine(QPointF(s-m, s*0.26), QPointF(s-m, s*0.44));
    } else if (type == "chart-bar") {
        p.drawLine(QPointF(s*0.24, s*0.70), QPointF(s*0.24, s*0.86));
        p.drawLine(QPointF(s*0.50, s*0.50), QPointF(s*0.50, s*0.86));
        p.drawLine(QPointF(s*0.76, s*0.30), QPointF(s*0.76, s*0.86));
    } else if (type == "star") {
        QPainterPath star;
        const int n = 5;
        qreal cx = s/2.0, cy = s/2.0, rOut = s*0.42, rIn = s*0.18;
        for (int i = 0; i < n*2; ++i) {
            qreal ang = -M_PI/2 + i * M_PI / n;
            qreal r = (i % 2 == 0) ? rOut : rIn;
            QPointF pt(cx + r*cos(ang), cy + r*sin(ang));
            if (i == 0) star.moveTo(pt); else star.lineTo(pt);
        }
        star.closeSubpath();
        p.drawPath(star);
    } else if (type == "percent") {
        p.drawLine(QPointF(s*0.24, s*0.76), QPointF(s*0.76, s*0.24));
        p.drawEllipse(QPointF(s*0.30, s*0.30), s*0.11, s*0.11);
        p.drawEllipse(QPointF(s*0.70, s*0.70), s*0.11, s*0.11);
    } else if (type == "search") {
        p.drawEllipse(QPointF(s*0.42, s*0.42), s*0.26, s*0.26);
        p.drawLine(QPointF(s*0.62, s*0.62), QPointF(s*0.84, s*0.84));
    } else if (type == "plus") {
        p.drawLine(QPointF(s/2.0, m), QPointF(s/2.0, s-m));
        p.drawLine(QPointF(m, s/2.0), QPointF(s-m, s/2.0));
    } else if (type == "logout") {
        p.drawRoundedRect(QRectF(m, m, s*0.36, s-2*m), 2, 2);
        p.drawLine(QPointF(s*0.42, s/2.0), QPointF(s-m, s/2.0));
        p.drawLine(QPointF(s-m*1.6, s*0.32), QPointF(s-m, s/2.0));
        p.drawLine(QPointF(s-m*1.6, s*0.68), QPointF(s-m, s/2.0));
    } else if (type == "door-in") {
        p.drawLine(QPointF(m, s/2.0), QPointF(s*0.62, s/2.0));
        p.drawLine(QPointF(s*0.40, s*0.30), QPointF(s*0.62, s/2.0));
        p.drawLine(QPointF(s*0.40, s*0.70), QPointF(s*0.62, s/2.0));
        p.drawRoundedRect(QRectF(s*0.66, m, s*0.20, s-2*m), 2, 2);
    } else if (type == "door-out") {
        p.drawLine(QPointF(s*0.38, s/2.0), QPointF(s-m, s/2.0));
        p.drawLine(QPointF(s*0.60, s*0.30), QPointF(s*0.38, s/2.0));
        p.drawLine(QPointF(s*0.60, s*0.70), QPointF(s*0.38, s/2.0));
        p.drawRoundedRect(QRectF(m*0.9, m, s*0.20, s-2*m), 2, 2);
    } else if (type == "key") {
        p.drawEllipse(QPointF(s*0.32, s*0.32), s*0.16, s*0.16);
        p.drawLine(QPointF(s*0.44, s*0.44), QPointF(s*0.82, s*0.82));
        p.drawLine(QPointF(s*0.70, s*0.68), QPointF(s*0.82, s*0.68));
        p.drawLine(QPointF(s*0.76, s*0.74), QPointF(s*0.88, s*0.74));
    } else if (type == "check-circle") {
        p.drawEllipse(QRectF(m*0.8, m*0.8, s-1.6*m, s-1.6*m));
        p.drawLine(QPointF(s*0.32, s*0.52), QPointF(s*0.44, s*0.66));
        p.drawLine(QPointF(s*0.44, s*0.66), QPointF(s*0.70, s*0.34));
    } else if (type == "settings") {
        p.drawEllipse(QPointF(s/2.0, s/2.0), s*0.16, s*0.16);
        for (int i = 0; i < 6; ++i) {
            qreal ang = i * M_PI / 3.0;
            QPointF a(s/2.0 + cos(ang)*s*0.26, s/2.0 + sin(ang)*s*0.26);
            QPointF b(s/2.0 + cos(ang)*s*0.40, s/2.0 + sin(ang)*s*0.40);
            p.drawLine(a, b);
        }
    } else if (type == "avatar") {
        p.setBrush(QColor(color.red(), color.green(), color.blue(), 30));
        p.drawEllipse(QRectF(m*0.6, m*0.6, s-1.2*m, s-1.2*m));
        p.setBrush(color);
        p.drawEllipse(QPointF(s/2.0, s*0.40), s*0.13, s*0.13);
        QPainterPath body;
        body.moveTo(s*0.28, s*0.80);
        body.cubicTo(s*0.28, s*0.60, s*0.72, s*0.60, s*0.72, s*0.80);
        p.setBrush(color);
        p.drawPath(body);
    }
    p.end();
    return QIcon(pm);
}

// ============================================================================
// 1. LOGIN WINDOW
// ============================================================================
LoginWindow::LoginWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Sign In - Grand Hotel Enterprise");
    resize(400, 500);
    setStyleSheet("background-color: #111827;");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(40, 40, 40, 40);
    layout->setSpacing(20);

    QLabel *logoImg = new QLabel(this);
    QPixmap pixLogo(":/hotel2.png");
    if (!pixLogo.isNull()) {
        logoImg->setPixmap(pixLogo.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        logoImg->setPixmap(IconKit::icon("bed", QColor("#2563EB"), 64).pixmap(64, 64));
    }
    logoImg->setAlignment(Qt::AlignCenter);

    QLabel *logoText = new QLabel("GRAND HOTEL\nENTERPRISE", this);
    logoText->setStyleSheet("color: white; font-size: 20px; font-weight: bold; font-family: 'Inter';");
    logoText->setAlignment(Qt::AlignCenter);

    QLineEdit *user = new QLineEdit(this);
    user->setPlaceholderText("Username / Email");
    user->setStyleSheet("padding: 12px; border-radius: 6px; background: #1F2937; color: white; border: 1px solid #374151; font-family: 'Inter';");

    QLineEdit *pass = new QLineEdit(this);
    pass->setPlaceholderText("Password");
    pass->setEchoMode(QLineEdit::Password);
    pass->setStyleSheet("padding: 12px; border-radius: 6px; background: #1F2937; color: white; border: 1px solid #374151; font-family: 'Inter';");

    QPushButton *btnLogin = new QPushButton("Access Dashboard", this);
    btnLogin->setStyleSheet("background: #2563EB; color: white; padding: 12px; border-radius: 6px; font-weight: bold; font-family: 'Inter'; font-size: 14px;");
    btnLogin->setCursor(Qt::PointingHandCursor);

    layout->addStretch();
    layout->addWidget(logoImg);
    layout->addWidget(logoText);
    layout->addSpacing(10);
    layout->addWidget(user);
    layout->addWidget(pass);
    layout->addWidget(btnLogin);
    layout->addStretch();

    connect(btnLogin, &QPushButton::clicked, this, &LoginWindow::loginSuccess);
}

// ============================================================================
// 2. ENTERPRISE STAT CARD — Đã tinh chỉnh đổ bóng mờ siêu nhẹ chuẩn SaaS
// ============================================================================
EnterpriseStatCard::EnterpriseStatCard(const QString &iconType, const QString &title, const QString &value,
                                       const QString &trend, bool isPositive, const QString &colorHex, QWidget *parent)
    : QFrame(parent)
{
    setObjectName("StatCard");

    m_shadow = new QGraphicsDropShadowEffect(this);
    m_shadow->setBlurRadius(8);
    m_shadow->setXOffset(0);
    m_shadow->setYOffset(2);
    m_shadow->setColor(QColor(0, 0, 0, 10)); // Đổ bóng mờ cực nhẹ tách biệt nền
    setGraphicsEffect(m_shadow);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(20, 18, 20, 18);
    layout->setSpacing(12);

    QHBoxLayout *topHBox = new QHBoxLayout();
    topHBox->setSpacing(10);
    QLabel *lblIcon = new QLabel();
    lblIcon->setFixedSize(36, 36);
    lblIcon->setAlignment(Qt::AlignCenter);
    lblIcon->setPixmap(IconKit::icon(iconType, QColor(colorHex), 20).pixmap(20, 20));
    lblIcon->setStyleSheet(QString("background: %1; border-radius: 9px;").arg(QColor(colorHex).lighter(185).name()));

    QLabel *lblTitle = new QLabel(title);
    lblTitle->setWordWrap(true);
    lblTitle->setStyleSheet("color: #4B5563; font-size: 12.5px; font-weight: 600; font-family: 'Inter';");

    topHBox->addWidget(lblIcon);
    topHBox->addWidget(lblTitle, 1);

    QLabel *lblValue = new QLabel(value);
    lblValue->setStyleSheet("font-size: 25px; font-weight: 700; color: #1F2937; font-family: 'Inter';");

    QHBoxLayout *trendHBox = new QHBoxLayout();
    trendHBox->setSpacing(4);
    QLabel *lblTrendIcon = new QLabel();
    lblTrendIcon->setPixmap(IconKit::icon(isPositive ? "chart-up" : "chart-bar",
                                          QColor(isPositive ? "#16A34A" : "#DC2626"), 13).pixmap(13, 13));
    QLabel *lblTrend = new QLabel(trend);
    lblTrend->setStyleSheet(QString("font-size: 12px; font-weight: 700; font-family: 'Inter'; color: %1;")
                                .arg(isPositive ? "#16A34A" : "#DC2626"));
    QLabel *lblSub = new QLabel("so với tháng trước");
    lblSub->setStyleSheet("color: #9CA3AF; font-size: 11.5px; font-family: 'Inter';");
    trendHBox->addWidget(lblTrendIcon);
    trendHBox->addWidget(lblTrend);
    trendHBox->addWidget(lblSub);
    trendHBox->addStretch();

    layout->addLayout(topHBox);
    layout->addWidget(lblValue);
    layout->addLayout(trendHBox);
}

void EnterpriseStatCard::enterEvent(QEnterEvent *event) {
    Q_UNUSED(event);
    if (m_shadow) {
        m_shadow->setBlurRadius(14);
        m_shadow->setYOffset(4);
        m_shadow->setColor(QColor(37, 99, 235, 20));
    }
}

void EnterpriseStatCard::leaveEvent(QEvent *event) {
    Q_UNUSED(event);
    if (m_shadow) {
        m_shadow->setBlurRadius(8);
        m_shadow->setYOffset(2);
        m_shadow->setColor(QColor(0, 0, 0, 10));
    }
}

// ============================================================================
// 3. MAIN WINDOW IMPLEMENTATION
// ============================================================================
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupWindow();
    setupLayouts();
    createSidebar();
    createHeader();
    createDashboardPage();
    applyStyle();
}

MainWindow::~MainWindow() {}

void MainWindow::setupWindow() {
    resize(1600, 900);
    setMinimumSize(1280, 720);
    setWindowTitle("Grand Hotel Management System");
}

void MainWindow::setupLayouts() {
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    rightContentLayout = new QVBoxLayout();
    rightContentLayout->setContentsMargins(0, 0, 0, 0);
    rightContentLayout->setSpacing(0);
}

void MainWindow::createSidebar() {
    sidebarFrame = new QFrame();
    sidebarFrame->setObjectName("Sidebar");
    sidebarFrame->setFixedWidth(260);

    QVBoxLayout *sLayout = new QVBoxLayout(sidebarFrame);
    sLayout->setContentsMargins(16, 24, 16, 16);
    sLayout->setSpacing(4);

    QHBoxLayout *logoLayout = new QHBoxLayout();
    logoLayout->setSpacing(10);
    QLabel *lblLogoIcon = new QLabel();
    QPixmap pixLogo(":/hotel2.png");
    if (!pixLogo.isNull()) {
        lblLogoIcon->setPixmap(pixLogo.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        lblLogoIcon->setPixmap(IconKit::icon("bed", QColor("#FFFFFF"), 26).pixmap(26, 26));
    }

    QVBoxLayout *logoTextLayout = new QVBoxLayout();
    logoTextLayout->setSpacing(0);
    QLabel *lblLogoTitle = new QLabel("GRAND HOTEL");
    lblLogoTitle->setStyleSheet("color: #FFFFFF; font-size: 14.5px; font-weight: 800; font-family: 'Inter'; letter-spacing: 0.5px;");
    QLabel *lblVersion = new QLabel("v2.5.0 Premium");
    lblVersion->setStyleSheet("color: #E0E7FF; font-size: 10.5px; font-weight: 500; font-family: 'Inter';");
    logoTextLayout->addWidget(lblLogoTitle);
    logoTextLayout->addWidget(lblVersion);
    logoLayout->addWidget(lblLogoIcon);
    logoLayout->addLayout(logoTextLayout);
    logoLayout->addStretch();
    sLayout->addLayout(logoLayout);
    sLayout->addSpacing(28);

    struct MenuItem { QString icon; QString label; };
    QList<MenuItem> menus = {
        {"dashboard", "Dashboard"},
        {"bed", "Quản lý phòng"},
        {"calendar", "Đặt phòng"},
        {"users", "Khách hàng"},
        {"invoice", "Hóa đơn"},
        {"staff", "Nhân viên"},
        {"wallet", "Doanh thu"},
        {"account", "Tài khoản"},
        {"settings", "Cài đặt"}
    };
    QButtonGroup *sidebarBtnGroup = new QButtonGroup(this);
    sidebarBtnGroup->setExclusive(true);

    for (int i = 0; i < menus.size(); ++i) {
        QPushButton *btn = new QPushButton("  " + menus[i].label);
        btn->setObjectName("SidebarButton");
        btn->setCheckable(true);
        btn->setCursor(Qt::PointingHandCursor);
        btn->setIcon(IconKit::icon(menus[i].icon, QColor("#F3F4F6"), 18));
        btn->setIconSize(QSize(18, 18));
        sidebarBtnGroup->addButton(btn);
        sLayout->addWidget(btn);
        if (i == 0) btn->setChecked(true);
    }

    sLayout->addStretch();

    QFrame *line = new QFrame();
    line->setStyleSheet("background-color: rgba(255,255,255,0.2); max-height: 1px;");
    sLayout->addWidget(line);
    sLayout->addSpacing(8);

    QPushButton *btnLogout = new QPushButton();
    btnLogout->setObjectName("BtnLogout");
    btnLogout->setIcon(IconKit::icon("logout", QColor("#FEE2E2"), 18));
    btnLogout->setIconSize(QSize(18, 18));
    btnLogout->setToolTip("Đăng xuất hệ thống");
    btnLogout->setCursor(Qt::PointingHandCursor);
    btnLogout->setFixedSize(36, 36);
    sLayout->addWidget(btnLogout, 0, Qt::AlignLeft);

    mainLayout->addWidget(sidebarFrame);

    connect(btnLogout, &QPushButton::clicked, this, [=]() {
        QMessageBox::StandardButton resBtn = QMessageBox::question(
            this, "Xác nhận", "Bạn có chắc chắn muốn đăng xuất khỏi phiên làm việc?",
            QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        if (resBtn == QMessageBox::Yes) {
            emit logoutRequested();
        }
    });
}

void MainWindow::createHeader() {
    headerFrame = new QFrame();
    headerFrame->setObjectName("Header");
    headerFrame->setFixedHeight(70);
    addPremiumShadow(headerFrame, 6, 1, 4);

    QHBoxLayout *hLayout = new QHBoxLayout(headerFrame);
    hLayout->setContentsMargins(28, 0, 28, 0);
    hLayout->setSpacing(16);

    QVBoxLayout *titleBox = new QVBoxLayout();
    titleBox->setSpacing(1);
    QLabel *lblTitle = new QLabel("Dashboard");
    lblTitle->setStyleSheet("color: #1F2937; font-weight: 700; font-size: 16px; font-family: 'Inter';");
    QLabel *lblDate = new QLabel(QDateTime::currentDateTime().toString("dddd, dd MMMM yyyy"));
    lblDate->setStyleSheet("color: #6B7280; font-weight: 500; font-size: 12px; font-family: 'Inter';");
    titleBox->addWidget(lblTitle);
    titleBox->addWidget(lblDate);
    hLayout->addLayout(titleBox);
    hLayout->addSpacing(24);

    QLineEdit *searchBar = new QLineEdit();
    searchBar->setObjectName("SearchBar");
    searchBar->addAction(IconKit::icon("search", QColor("#6B7280"), 16), QLineEdit::LeadingPosition);
    searchBar->setPlaceholderText("Tìm phòng, hóa đơn, đặt phòng...");
    searchBar->setFixedWidth(360);
    hLayout->addWidget(searchBar);

    hLayout->addStretch();

    QPushButton *btnNewBooking = new QPushButton(" Đặt phòng mới");
    btnNewBooking->setObjectName("BtnPrimary");
    btnNewBooking->setIcon(IconKit::icon("plus", QColor("#FFFFFF"), 15));
    btnNewBooking->setIconSize(QSize(15, 15));
    btnNewBooking->setCursor(Qt::PointingHandCursor);
    hLayout->addWidget(btnNewBooking);
    hLayout->addSpacing(6);

    QFrame *userBlock = new QFrame();
    QHBoxLayout *userLayout = new QHBoxLayout(userBlock);
    userLayout->setContentsMargins(0, 0, 0, 0);
    userLayout->setSpacing(10);

    QVBoxLayout *nameRoleBox = new QVBoxLayout();
    nameRoleBox->setSpacing(2);
    lblHeaderUserName = new QLabel("Alex Mercer");
    lblHeaderUserName->setAlignment(Qt::AlignRight);
    lblHeaderUserName->setStyleSheet("color: #1F2937; font-weight: 700; font-size: 12.5px; font-family: 'Inter';");
    lblHeaderUserRole = new QLabel("Quản lý");
    lblHeaderUserRole->setAlignment(Qt::AlignRight);
    lblHeaderUserRole->setObjectName("RoleBadge");
    nameRoleBox->addWidget(lblHeaderUserName);
    nameRoleBox->addWidget(lblHeaderUserRole, 0, Qt::AlignRight);

    QLabel *lblAvatar = new QLabel();
    lblAvatar->setFixedSize(38, 38);
    lblAvatar->setPixmap(IconKit::icon("avatar", QColor("#2563EB"), 38).pixmap(38, 38));

    userLayout->addLayout(nameRoleBox);
    userLayout->addWidget(lblAvatar);
    hLayout->addWidget(userBlock);

    rightContentLayout->addWidget(headerFrame);

    setUserProfile(lblHeaderUserName->text(), lblHeaderUserRole->text());
}

QString MainWindow::roleAccentColor(const QString &role) const {
    if (role.contains("Quản trị", Qt::CaseInsensitive) || role.contains("Admin", Qt::CaseInsensitive))
        return "#6366F1";
    if (role.contains("Quản lý", Qt::CaseInsensitive) || role.contains("Manager", Qt::CaseInsensitive))
        return "#2563EB";
    if (role.contains("Lễ tân", Qt::CaseInsensitive) || role.contains("Receptionist", Qt::CaseInsensitive))
        return "#0D9488";
    return "#4B5563";
}

void MainWindow::setUserProfile(const QString &name, const QString &role) {
    lblHeaderUserName->setText(name);
    lblHeaderUserRole->setText(role);
    QString accent = roleAccentColor(role);
    lblHeaderUserRole->setStyleSheet(QString(
                                         "background: %1; color: %2; font-size: 10.5px; font-weight: 700;"
                                         "font-family: 'Inter'; padding: 2px 9px; border-radius: 8px;"
                                         ).arg(QColor(accent).lighter(190).name(), accent));
}

void MainWindow::createDashboardPage() {
    dashboardPageWidget = new QWidget();
    dashboardPageLayout = new QVBoxLayout(dashboardPageWidget);
    dashboardPageLayout->setContentsMargins(0, 0, 0, 0);
    dashboardPageLayout->setSpacing(0);

    dashboardScrollArea = new QScrollArea();
    dashboardScrollArea->setWidgetResizable(true);
    dashboardScrollArea->setFrameShape(QFrame::NoFrame);
    dashboardScrollArea->setObjectName("DashboardScrollArea");

    dashboardScrollContent = new QWidget();
    dashboardScrollContent->setObjectName("dashboardScrollContent"); // Đặt tên đối tượng để định dạng QSS

    dashboardScrollLayout = new QVBoxLayout(dashboardScrollContent);
    dashboardScrollLayout->setContentsMargins(28, 24, 28, 28);
    dashboardScrollLayout->setSpacing(28);

    dashboardScrollArea->setWidget(dashboardScrollContent);
    dashboardPageLayout->addWidget(dashboardScrollArea);

    createStatisticsCards();
    createRoomGrid();
    createRecentBookingTable();

    pageStackedWidget = new QStackedWidget();
    pageStackedWidget->addWidget(dashboardPageWidget);

    centerWorkspaceLayout = new QHBoxLayout();
    centerWorkspaceLayout->setContentsMargins(0, 0, 0, 0);
    centerWorkspaceLayout->setSpacing(0);
    centerWorkspaceLayout->addWidget(pageStackedWidget, 1);

    rightContentLayout->addLayout(centerWorkspaceLayout);
    mainLayout->addLayout(rightContentLayout, 1);
}

void MainWindow::createStatisticsCards() {
    QGridLayout *grid = new QGridLayout();
    grid->setSpacing(18);

    grid->addWidget(new EnterpriseStatCard("dashboard", "Tổng số phòng", "140", "2.5%", true, "#2563EB", this), 0, 0);
    grid->addWidget(new EnterpriseStatCard("key", "Phòng đang sử dụng", "92", "8.1%", true, "#D97706", this), 0, 1);
    grid->addWidget(new EnterpriseStatCard("check-circle", "Phòng trống sẵn sàng", "48", "1.2%", false, "#16A34A", this), 0, 2);
    grid->addWidget(new EnterpriseStatCard("door-in", "Check-in hôm nay", "18", "14%", true, "#4F46E5", this), 0, 3);

    grid->addWidget(new EnterpriseStatCard("door-out", "Check-out hôm nay", "12", "4.3%", true, "#DB2777", this), 1, 0);
    grid->addWidget(new EnterpriseStatCard("users", "Khách lưu trú hiện tại", "195", "11.5%", true, "#CA8A04", this), 1, 1);
    grid->addWidget(new EnterpriseStatCard("wallet", "Doanh thu ngày", "42.8M", "18.2%", true, "#0D9488", this), 1, 2);
    grid->addWidget(new EnterpriseStatCard("chart-up", "Doanh thu tháng", "1.25B", "6.4%", true, "#4338CA", this), 1, 3);

    grid->addWidget(new EnterpriseStatCard("chart-bar", "Doanh thu năm", "14.2B", "12.3%", true, "#1E40AF", this), 2, 0);
    grid->addWidget(new EnterpriseStatCard("star", "Đánh giá trung bình", "4.8/5", "0.2%", true, "#CA8A04", this), 2, 1);
    grid->addWidget(new EnterpriseStatCard("percent", "Tỷ lệ lấp đầy phòng", "78.4%", "5.1%", true, "#0369A1", this), 2, 2);

    QWidget *spacer = new QWidget();
    spacer->setStyleSheet("background: transparent;");
    grid->addWidget(spacer, 2, 3);

    dashboardScrollLayout->addLayout(grid);
}

void MainWindow::createRoomGrid() {
    QLabel *lblSec = new QLabel("Giám sát trạng thái phòng");
    lblSec->setStyleSheet("font-size: 15px; font-weight: 700; color: #1F2937; font-family: 'Inter';");
    dashboardScrollLayout->addWidget(lblSec);

    QGridLayout *grid = new QGridLayout();
    grid->setSpacing(18);

    grid->addWidget(createRoomCard("P.101", "Standard King", "650,000", "2 Người lớn", "Trống", "#16A34A"), 0, 0);
    grid->addWidget(createRoomCard("P.102", "Standard Twin", "650,000", "2 Người lớn", "Đang ở", "#DC2626"), 0, 1);
    grid->addWidget(createRoomCard("P.103", "Deluxe Suite", "1,200,000", "3 Người lớn", "Đã đặt", "#D97706"), 0, 2);
    grid->addWidget(createRoomCard("P.201", "Executive Ocean", "2,500,000", "4 Người lớn", "Dọn phòng", "#CA8A04"), 0, 3);

    dashboardScrollLayout->addLayout(grid);
}

QFrame* MainWindow::createRoomCard(const QString &roomNum, const QString &type, const QString &price,
                                   const QString &capacity, const QString &status, const QString &color) {
    QFrame *card = new QFrame();
    card->setObjectName("RoomCard");
    addPremiumShadow(card, 8, 2, 8);

    QVBoxLayout *layout = new QVBoxLayout(card);
    layout->setContentsMargins(16, 16, 16, 16);
    layout->setSpacing(10);

    QHBoxLayout *h1 = new QHBoxLayout();
    QLabel *lblNum = new QLabel(roomNum);
    lblNum->setStyleSheet("font-size: 16px; font-weight: 700; color: #1F2937; font-family: 'Inter';");
    QLabel *lblStatus = new QLabel(status);
    lblStatus->setStyleSheet(QString("background: %115; color: %1; font-weight: 700; font-size: 11px; padding: 4px 11px; border-radius: 10px;").arg(color));
    h1->addWidget(lblNum);
    h1->addStretch();
    h1->addWidget(lblStatus);

    QLabel *lblType = new QLabel(type + "  ·  " + capacity);
    lblType->setStyleSheet("color: #4B5563; font-size: 12.5px; font-weight: 500; font-family: 'Inter';");

    QFrame *divider = new QFrame();
    divider->setStyleSheet("background-color: #E5E7EB; max-height: 1px;");

    QLabel *lblPrice = new QLabel(price + " VND / đêm");
    lblPrice->setStyleSheet("color: #2563EB; font-size: 14px; font-weight: 700; font-family: 'Inter';");

    layout->addLayout(h1);
    layout->addWidget(lblType);
    layout->addWidget(divider);
    layout->addWidget(lblPrice);

    return card;
}

void MainWindow::createRecentBookingTable() {
    QLabel *lblSec = new QLabel("Lịch sử đặt phòng gần đây");
    lblSec->setStyleSheet("font-size: 15px; font-weight: 700; color: #1F2937; font-family: 'Inter';");
    dashboardScrollLayout->addWidget(lblSec);

    recentBookingTable = new QTableWidget(5, 6);
    recentBookingTable->setObjectName("RecentBookingTable");
    recentBookingTable->setHorizontalHeaderLabels({"Khách hàng", "Số phòng", "Check-In", "Check-Out", "Tổng hóa đơn", "Trạng thái"});

    recentBookingTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    recentBookingTable->verticalHeader()->setVisible(false);
    recentBookingTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    recentBookingTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    recentBookingTable->setAlternatingRowColors(true);
    recentBookingTable->setShowGrid(false);
    recentBookingTable->setFixedHeight(260);

    recentBookingTable->viewport()->setStyleSheet("background-color: transparent; border-radius: 12px;");

    addPremiumShadow(recentBookingTable, 8, 2, 8);

    QString data[5][6] = {
        {"Trần Sĩ Hoàng", "P.103", "06/07/2026", "09/07/2026", "3,600,000", "Đã xác nhận"},
        {"Emma Watson", "P.201", "05/07/2026", "12/07/2026", "17,500,000", "Đang ở"},
        {"Lê Minh Quân", "P.101", "06/07/2026", "07/07/2026", "650,000", "Chờ thanh toán"},
        {"Nguyễn Bích Hà", "P.102", "04/07/2026", "06/07/2026", "1,300,000", "Đã trả phòng"},
        {"Johnathan Nguyen", "P.305", "08/07/2026", "15/07/2026", "45,000,000", "Đã đặt"}
    };

    for (int i = 0; i < 5; ++i) {
        recentBookingTable->setRowHeight(i, 46);
        for (int j = 0; j < 6; ++j) {
            recentBookingTable->setItem(i, j, new QTableWidgetItem(data[i][j]));
        }
    }

    dashboardScrollLayout->addWidget(recentBookingTable);
}

void MainWindow::addPremiumShadow(QWidget *widget, int blur, int offset, int alpha) {
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(blur);
    shadow->setXOffset(0);
    shadow->setYOffset(offset);
    shadow->setColor(QColor(0, 0, 0, alpha));
    widget->setGraphicsEffect(shadow);
}

// ============================================================================
// HỆ THỐNG MÀU SẮC QSS: Thiết kế lại toàn bộ bảng màu theo chuẩn Modern SaaS
// ============================================================================
void MainWindow::applyStyle() {
    QString qss = R"(
        /* Nền chính, vùng cuộn và toàn bộ nội dung đã được sửa thành màu Trắng Tinh Khiết */
        QMainWindow, #DashboardScrollArea, #dashboardScrollContent {
            background-color: #FFFFFF;
        }

        /* THANH MENU BÊN TRÁI: Sử dụng màu Xanh Dương Sáng hiện đại */
        #Sidebar {
            background-color: #2563EB;
        }

        /* Các mục menu chưa được chọn: Nền trong suốt, chữ màu Trắng Ngà dễ đọc */
        #SidebarButton {
            color: #F3F4F6; text-align: left; padding: 11px 12px; border: none; border-radius: 6px;
            font-size: 13px; font-weight: 600; font-family: 'Inter'; margin-bottom: 2px;
            background-color: transparent;
        }
        #SidebarButton:hover {
            background-color: rgba(255, 255, 255, 0.15);
            color: #FFFFFF;
        }

        /* MỤC MENU ĐANG ĐƯỢC CHỌN: Xanh dương nổi bật rực rỡ, chữ trắng, bo góc nhẹ */
        #SidebarButton:checked {
            background-color: #1D4ED8;
            color: #FFFFFF;
        }

        /* Nút đăng xuất góc dưới Sidebar */
        #BtnLogout { background: transparent; border: none; border-radius: 6px; }
        #BtnLogout:hover { background: rgba(255, 255, 255, 0.2); }

        /* THANH HEADER: Đồng bộ màu trắng tinh, có viền mỏng phân tách phía dưới */
        #Header {
            background-color: #FFFFFF;
            border-bottom: 1px solid #E5E7EB;
        }

        /* THANH TÌM KIẾM: Nền xám rất nhạt, viền màu xám trung tính */
        #SearchBar {
            background-color: #F8FAFC;
            border: 1px solid #D1D5DB;
            border-radius: 8px;
            padding: 9px 12px; font-size: 12.5px; font-family: 'Inter'; color: #1F2937;
        }
        #SearchBar:focus {
            background-color: #FFFFFF;
            border: 1px solid #2563EB;
        }

        /* NÚT BẤM CHỦ ĐẠO: Màu xanh dương hiện đại, chữ trắng */
        #BtnPrimary {
            background: #2563EB; color: white; border: none; border-radius: 8px;
            padding: 9px 18px; font-weight: 700; font-family: 'Inter'; font-size: 12.5px;
        }
        #BtnPrimary:hover { background: #1D4ED8; }

        /* THẺ THỐNG KÊ (CARDS): Giữ nền trắng, viền mỏng xám và đổ bóng nhẹ */
        #StatCard {
            background-color: #FFFFFF;
            border-radius: 12px;
            border: 1px solid #E5E7EB;
        }

        /* KHUNG PHÒNG (ROOM CARDS): Giữ nền trắng, viền mỏng xám tương đương */
        #RoomCard {
            background-color: #FFFFFF;
            border-radius: 12px;
            border: 1px solid #E5E7EB;
        }

        /* KHUNG THÔNG TIN BẢNG DỮ LIỆU: Viền mỏng xám nhạt */
        #RecentBookingTable {
            background-color: #FFFFFF;
            border: 1px solid #E5E7EB;
            border-radius: 12px;
            font-family: 'Inter';
            font-size: 12.5px;
        }
        QTableWidget::item {
            border-bottom: 1px solid #E5E7EB;
            padding-left: 12px;
            color: #1F2937;
        }
        QTableWidget::item:selected {
            background-color: #EFF6FF;
            color: #2563EB;
        }
        QHeaderView::section {
            background-color: #F8FAFC;
            color: #4B5563;
            font-weight: 700; border: none;
            border-bottom: 1px solid #E5E7EB;
            padding: 10px;
        }
    )";
    setStyleSheet(qss);
}