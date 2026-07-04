#include "logindialog.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>
#include <QPainterPath>
#include <QListView>

QIcon LoginDialog::createVectorIcon(const QString& type, const QColor& color) {
    QPixmap pixmap(32, 32);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(color, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.setBrush(Qt::NoBrush);

    if (type == "user") {
        painter.drawEllipse(11, 5, 10, 10);
        QPainterPath path;
        path.moveTo(5, 27);
        path.arcTo(5, 17, 22, 20, 180, -180);
        painter.drawPath(path);
    }
    else if (type == "lock") {
        painter.drawRoundedRect(7, 13, 18, 14, 2, 2);
        painter.drawArc(10, 5, 12, 16, 0, 180 * 16);
    }
    else if (type == "eye") {
        QPainterPath path;
        path.moveTo(3, 16);
        path.quadTo(16, 5, 29, 16);
        path.quadTo(16, 27, 3, 16);
        painter.drawPath(path);
        painter.setBrush(color);
        painter.drawEllipse(13, 13, 6, 6);
    }
    else if (type == "eye-off") {
        QPainterPath path;
        path.moveTo(3, 16);
        path.quadTo(16, 5, 29, 16);
        path.quadTo(16, 27, 3, 16);
        painter.drawPath(path);
        painter.setBrush(color);
        painter.drawEllipse(13, 13, 6, 6);
        painter.setBrush(Qt::NoBrush);
        painter.drawLine(6, 6, 26, 26);
    }
    else if (type == "feature-dot") {
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor("#38BDF8"));
        painter.drawEllipse(12, 12, 8, 8);
    }
    else if (type == "info") {
        painter.drawEllipse(5, 5, 22, 22);
        painter.setFont(QFont("Segoe UI", 11, QFont::Bold));
        painter.drawText(QRect(5, 5, 22, 22), Qt::AlignCenter, "i");
    }

    painter.end();
    return QIcon(pixmap);
}

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent), isPasswordHidden(true)
{
    this->setWindowTitle("Grand Hotel PMS");
    this->resize(1100, 720);
    this->setMinimumSize(1050, 680);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // ==================== PANEL BÊN TRÁI (35%) ====================
    QWidget *leftPanel = new QWidget(this);
    leftPanel->setObjectName("leftPanel");

    QVBoxLayout *leftLayout = new QVBoxLayout(leftPanel);
    leftLayout->setContentsMargins(45, 60, 45, 60);
    leftLayout->setSpacing(0);

    leftLayout->addStretch(2);

    QWidget *logoContainer = new QWidget(leftPanel);
    logoContainer->setObjectName("logoContainer");
    logoContainer->setFixedSize(110, 110);

    QVBoxLayout *logoLayout = new QVBoxLayout(logoContainer);
    logoLayout->setContentsMargins(0, 0, 0, 0);
    logoLayout->setAlignment(Qt::AlignCenter);

    QLabel *logoLabel = new QLabel(logoContainer);
    QPixmap hotelPixmap(":/hotel2.png");
    if(!hotelPixmap.isNull()) {
        logoLabel->setPixmap(hotelPixmap.scaled(75, 75, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        logoLabel->setText("🏨");
        logoLabel->setStyleSheet("font-size: 50px;");
    }
    logoLabel->setAlignment(Qt::AlignCenter);
    logoLayout->addWidget(logoLabel);
    leftLayout->addWidget(logoContainer, 0, Qt::AlignHCenter);
    leftLayout->addSpacing(25);

    QLabel *hotelName = new QLabel("Grand Hotel", leftPanel);
    hotelName->setObjectName("hotelName");
    hotelName->setAlignment(Qt::AlignCenter);
    leftLayout->addWidget(hotelName);
    leftLayout->addSpacing(6);

    QLabel *hotelSub = new QLabel("MANAGEMENT SYSTEM", leftPanel);
    hotelSub->setObjectName("hotelSub");
    hotelSub->setAlignment(Qt::AlignCenter);
    leftLayout->addWidget(hotelSub);

    leftLayout->addStretch(1);

    QVBoxLayout *featuresLayout = new QVBoxLayout();
    featuresLayout->setSpacing(20);
    featuresLayout->setAlignment(Qt::AlignLeft);

    QStringList features = {"Bảo mật hệ thống", "Quản lý phòng", "Quản lý đặt phòng", "Phân quyền nhân viên"};
    for (const QString& text : features) {
        QHBoxLayout *row = new QHBoxLayout();
        row->setSpacing(14);

        QLabel *iconLabel = new QLabel(leftPanel);
        iconLabel->setPixmap(createVectorIcon("feature-dot").pixmap(20, 20));

        QLabel *txtLabel = new QLabel(text, leftPanel);
        txtLabel->setObjectName("leftPureText");

        row->addWidget(iconLabel);
        row->addWidget(txtLabel);
        row->addStretch();
        featuresLayout->addLayout(row);
    }

    QWidget *featuresContainer = new QWidget(leftPanel);
    featuresContainer->setLayout(featuresLayout);
    leftLayout->addWidget(featuresContainer, 0, Qt::AlignHCenter);

    leftLayout->addStretch(2);

    // ==================== PANEL BÊN PHẢI (65%) ====================
    QWidget *rightPanel = new QWidget(this);
    rightPanel->setObjectName("rightPanel");

    QHBoxLayout *rightCenterWrapper = new QHBoxLayout(rightPanel);
    rightCenterWrapper->setContentsMargins(0, 0, 0, 0);

    // Khóa cứng chiều rộng Form để chuẩn tỉ lệ Enterprise không bị co giãn
    QWidget *formContainer = new QWidget(rightPanel);
    formContainer->setFixedWidth(450);

    QVBoxLayout *rightLayout = new QVBoxLayout(formContainer);
    rightLayout->setContentsMargins(0, 20, 0, 20);
    rightLayout->setSpacing(18); // Giữ khoảng cách cố định chống chồng chữ

    // Tiêu đề & Slogan
    QLabel *titleLabel = new QLabel("Đăng nhập", formContainer);
    titleLabel->setObjectName("titleLabel");

    QLabel *descLabel = new QLabel("Chào mừng quay trở lại!\nĐăng nhập để tiếp tục sử dụng hệ thống.", formContainer);
    descLabel->setObjectName("descLabel");

    rightLayout->addWidget(titleLabel);
    rightLayout->addWidget(descLabel);
    rightLayout->addSpacing(10);

    // Khối nhập Email / Username
    QVBoxLayout *emailBox = new QVBoxLayout();
    emailBox->setSpacing(8);
    QLabel *lblEmail = new QLabel("Email hoặc tên đăng nhập", formContainer);
    lblEmail->setObjectName("fieldLabel");
    emailEdit = new QLineEdit(formContainer);
    emailEdit->setFixedHeight(50);
    emailEdit->setPlaceholderText("Nhập email hoặc tên tài khoản...");
    emailEdit->addAction(createVectorIcon("user", QColor("#94A3B8")), QLineEdit::LeadingPosition);
    emailBox->addWidget(lblEmail);
    emailBox->addWidget(emailEdit);
    rightLayout->addLayout(emailBox);

    // Khối nhập Mật khẩu
    QVBoxLayout *passBox = new QVBoxLayout();
    passBox->setSpacing(8);
    QLabel *lblPass = new QLabel("Mật khẩu", formContainer);
    lblPass->setObjectName("fieldLabel");
    passwordEdit = new QLineEdit(formContainer);
    passwordEdit->setFixedHeight(50);
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setPlaceholderText("Nhập mật khẩu doanh nghiệp...");
    passwordEdit->addAction(createVectorIcon("lock", QColor("#94A3B8")), QLineEdit::LeadingPosition);
    eyeAction = passwordEdit->addAction(createVectorIcon("eye", QColor("#94A3B8")), QLineEdit::TrailingPosition);
    connect(eyeAction, &QAction::triggered, this, &LoginDialog::togglePasswordVisibility);
    passBox->addWidget(lblPass);
    passBox->addWidget(passwordEdit);
    rightLayout->addLayout(passBox);

    // Khối chọn Vai trò
    QVBoxLayout *roleBox = new QVBoxLayout();
    roleBox->setSpacing(8);
    QLabel *lblRole = new QLabel("Vai trò truy cập", formContainer);
    lblRole->setObjectName("fieldLabel");
    roleComboBox = new QComboBox(formContainer);
    roleComboBox->setView(new QListView(roleComboBox));
    roleComboBox->addItems({"Quản lý", "Nhân viên"});
    roleComboBox->setFixedHeight(50);
    roleComboBox->setCurrentIndex(1); // Mặc định chọn Nhân viên
    roleBox->addWidget(lblRole);
    roleBox->addWidget(roleComboBox);
    rightLayout->addLayout(roleBox);

    // Tiện ích (Remember me & Forgot pass)
    QHBoxLayout *utilBox = new QHBoxLayout();
    rememberMeCheck = new QCheckBox("Ghi nhớ đăng nhập", formContainer);
    rememberMeCheck->setObjectName("rememberMeCheck");
    rememberMeCheck->setCursor(Qt::PointingHandCursor);
    QPushButton *forgotBtn = new QPushButton("Quên mật khẩu?", formContainer);
    forgotBtn->setObjectName("forgotBtn");
    forgotBtn->setCursor(Qt::PointingHandCursor);
    utilBox->addWidget(rememberMeCheck);
    utilBox->addStretch();
    utilBox->addWidget(forgotBtn);
    rightLayout->addLayout(utilBox);

    // Nhãn báo lỗi
    errorLabel = new QLabel("", formContainer);
    errorLabel->setObjectName("errorLabel");
    errorLabel->setFixedHeight(20);
    rightLayout->addWidget(errorLabel);

    // Nút Đăng nhập chính
    loginButton = new QPushButton("Đăng nhập", formContainer);
    loginButton->setObjectName("loginButton");
    loginButton->setFixedHeight(50);
    loginButton->setCursor(Qt::PointingHandCursor);
    rightLayout->addWidget(loginButton);
    connect(loginButton, &QPushButton::clicked, this, &LoginDialog::handleLogin);

    // Thanh chia cách
    QLabel *divLabel = new QLabel("──────────────── Hoặc tiếp tục với Google ────────────────", formContainer);
    divLabel->setObjectName("dividerLabel");
    divLabel->setAlignment(Qt::AlignCenter);
    rightLayout->addWidget(divLabel);

    // Nút Google SSO độc quyền
    QPushButton *gBtn = new QPushButton(" Continue with Google", formContainer);
    gBtn->setObjectName("socialGoogleBtn");
    gBtn->setFixedHeight(48);
    gBtn->setCursor(Qt::PointingHandCursor);
    QIcon googleIcon(":/google1.png");
    if(!googleIcon.isNull()) {
        gBtn->setIcon(googleIcon);
        gBtn->setIconSize(QSize(20, 20));
    }
    rightLayout->addWidget(gBtn);

    // Card Demo Account (Cập nhật danh sách tài khoản thực tế mới)
    QWidget *infoCard = new QWidget(formContainer);
    infoCard->setObjectName("infoCard");
    QHBoxLayout *infoCardLayout = new QHBoxLayout(infoCard);
    infoCardLayout->setContentsMargins(16, 14, 16, 14);
    infoCardLayout->setSpacing(14);
    QLabel *infoIconLabel = new QLabel(infoCard);
    infoIconLabel->setPixmap(createVectorIcon("info", QColor("#64748B")).pixmap(18, 18));
    infoIconLabel->setAlignment(Qt::AlignTop | Qt::AlignHCenter);

    QLabel *infoText = new QLabel("<b>Demo Accounts</b><br>"
                                  "• <b>Manager:</b> quangminh / 111<br>"
                                  "• <b>Employee:</b> mytu, giahung, tuyetoanh, minhquan / 222", infoCard);
    infoText->setObjectName("infoText");
    infoCardLayout->addWidget(infoIconLabel);
    infoCardLayout->addWidget(infoText, 1);
    rightLayout->addWidget(infoCard);

    // Căn giữa toàn bộ Form theo chiều dọc
    rightCenterWrapper->addStretch(1);
    rightCenterWrapper->addWidget(formContainer);
    rightCenterWrapper->addStretch(1);

    mainLayout->addWidget(leftPanel, 35);
    mainLayout->addWidget(rightPanel, 65);

    // ==================== BỘ STYLE SHEET CỐ ĐỊNH LAYOUT ====================
    this->setStyleSheet(R"(
        QDialog { background-color: #FFFFFF; }

        QWidget#leftPanel {
            background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #0F172A, stop:1 #1E3A8A);
        }
        QWidget#logoContainer {
            background-color: rgba(255, 255, 255, 0.05);
            border: 1px solid rgba(255, 255, 255, 0.12);
            border-radius: 55px;
        }
        QLabel#hotelName {
            color: #FFFFFF;
            font-size: 36px;
            font-weight: bold;
            font-family: 'Segoe UI', Arial;
        }
        QLabel#hotelSub {
            color: #38BDF8;
            font-size: 11px;
            font-weight: bold;
            letter-spacing: 3.5px;
        }
        QLabel#leftPureText {
            color: #E2E8F0;
            font-size: 15px;
            font-weight: 500;
        }
        QWidget#rightPanel { background-color: #FFFFFF; }
        QLabel#titleLabel {
            color: #1E293B;
            font-size: 36px;
            font-weight: bold;
        }
        QLabel#descLabel {
            color: #64748B;
            font-size: 15px;
        }
        QLabel#fieldLabel {
            color: #1E293B;
            font-size: 14px;
            font-weight: 600;
        }
        QLineEdit {
            background-color: #FFFFFF;
            border: 1px solid #E2E8F0;
            border-radius: 10px;
            padding-left: 42px;
            padding-right: 42px;
            color: #1E293B;
            font-size: 15px;
        }
        QLineEdit:focus { border: 2px solid #2563EB; }

        QComboBox {
            background-color: #FFFFFF;
            border: 1px solid #E2E8F0;
            border-radius: 10px;
            padding-left: 16px;
            color: #1E293B;
            font-size: 15px;
        }
        QComboBox:focus { border: 2px solid #2563EB; }
        QComboBox::drop-down { border: none; width: 36px; }
        QComboBox QAbstractItemView {
            background-color: #FFFFFF;
            border: 1px solid #E2E8F0;
            border-radius: 10px;
            color: #1E293B;
            outline: 0px;
        }
        QComboBox QAbstractItemView::item { height: 44px; padding-left: 16px; }
        QComboBox QAbstractItemView::item:hover { background-color: #EFF6FF; color: #2563EB; }

        QCheckBox#rememberMeCheck { color: #64748B; font-size: 14px; }
        QPushButton#forgotBtn {
            background-color: transparent;
            color: #2563EB;
            border: none;
            font-size: 14px;
            font-weight: 600;
        }
        QPushButton#loginButton {
            background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #2563EB, stop:1 #1D4ED8);
            color: #FFFFFF;
            border-radius: 10px;
            font-size: 16px;
            font-weight: 600;
        }
        QPushButton#loginButton:hover {
            background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #3B82F6, stop:1 #2563EB);
        }
        QLabel#dividerLabel { color: #94A3B8; font-size: 13px; }
        QPushButton#socialGoogleBtn {
            background-color: #FFFFFF;
            border: 1px solid #E2E8F0;
            border-radius: 10px;
            color: #1E293B;
            font-size: 15px;
            font-weight: 500;
        }
        QPushButton#socialGoogleBtn:hover { background-color: #F8FAFC; }
        QWidget#infoCard { background-color: #F8FAFC; border: 1px solid #E2E8F0; border-radius: 10px; }
        QLabel#infoText { color: #64748B; font-size: 13px; }
        QLabel#errorLabel { color: #EF4444; font-size: 13px; font-weight: 500; }
    )");
}

void LoginDialog::togglePasswordVisibility() {
    if (isPasswordHidden) {
        passwordEdit->setEchoMode(QLineEdit::Normal);
        eyeAction->setIcon(createVectorIcon("eye-off", QColor("#94A3B8")));
    } else {
        passwordEdit->setEchoMode(QLineEdit::Password);
        eyeAction->setIcon(createVectorIcon("eye", QColor("#94A3B8")));
    }
    isPasswordHidden = !isPasswordHidden;
}

// ==================== CẬP NHẬT CƠ SỞ DỮ LIỆU VÀ BIỆN PHÁP XÁC THỰC MỚI ====================
void LoginDialog::handleLogin() {
    QString user = emailEdit->text().trimmed(); // Loại bỏ khoảng trắng thừa ở hai đầu chuỗi
    QString pass = passwordEdit->text();
    int roleIndex = roleComboBox->currentIndex(); // 0: Quản lý, 1: Nhân viên

    // Định nghĩa cấu trúc tài khoản bảo mật
    struct AccountMock {
        QString username;
        QString password;
        int allowedRoleIndex; // Khớp chuẩn với chỉ mục trong Combobox (0: Quản lý, 1: Nhân viên)
    };

    // Khởi tạo Mock Database phân quyền hệ thống nghiêm ngặt
    QVector<AccountMock> userDatabase = {
        {"quangminh", "111", 0}, // CHỈ DUY NHẤT tài khoản này là Quản lý
        {"mytu",      "222", 1}, // Nhân viên
        {"giahung",   "222", 1}, // Nhân viên
        {"tuyetoanh", "222", 1}, // Nhân viên
        {"minhquan",  "222", 1}  // Nhân viên
    };

    bool isAuthenticated = false;

    // Kiểm tra đồng thời 3 điều kiện (Tên, Mật khẩu, Vai trò)
    for (const auto& acc : userDatabase) {
        if (acc.username.compare(user, Qt::CaseInsensitive) == 0 &&
            acc.password == pass &&
            acc.allowedRoleIndex == roleIndex) {

            isAuthenticated = true;
            break;
        }
    }

    // Điều hướng UI dựa trên kết quả xác thực
    if (isAuthenticated) {
        errorLabel->setText(""); // Xóa thông báo lỗi
        this->accept();          // Cho phép mở MainWindow thành công
    } else {
        // Trả về chính xác thông báo lỗi theo yêu cầu hệ thống doanh nghiệp
        errorLabel->setText("Thông tin xác thực tài khoản doanh nghiệp không chính xác!");
    }
}

int LoginDialog::getSelectedRoleIndex() const { return roleComboBox->currentIndex(); }
QString LoginDialog::getUsername() const { return emailEdit->text(); }
LoginDialog::~LoginDialog() {}