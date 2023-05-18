#ifndef CHANGEPOSEWINDOW_H
#define CHANGEPOSEWINDOW_H

#include <QWidget>
#include <QDialog>
#include <QDebug>
#include <QTextEdit>

namespace Ui {
class ChangePoseWindow;
}

class ChangePoseWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePoseWindow(QWidget *parent = nullptr);
    ~ChangePoseWindow();

public slots:
    void onOkButtonClicked();

signals:
    void textEntered(const QString& text);

private:
    Ui::ChangePoseWindow *ui;
};

#endif // CHANGEPOSEWINDOW_H
