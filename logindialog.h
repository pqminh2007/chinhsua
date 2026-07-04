#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QLabel>
#include <QPushButton>
#include <QAction>

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

    int getSelectedRoleIndex() const;
    QString getUsername() const;

private slots:
    void handleLogin();
    void togglePasswordVisibility();

private:
    QIcon createVectorIcon(const QString& type, const QColor& color = QColor());

    QLineEdit *emailEdit;
    QLineEdit *passwordEdit;
    QComboBox *roleComboBox;
    QCheckBox *rememberMeCheck;
    QLabel *errorLabel;
    QPushButton *loginButton;
    QAction *eyeAction;
    bool isPasswordHidden;
};

#endif // LOGINDIALOG_H