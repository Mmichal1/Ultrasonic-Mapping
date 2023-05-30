#ifndef POSETEXTEDIT_H
#define POSETEXTEDIT_H

#include <QWidget>
#include <QTextEdit>
#include <QKeyEvent>
#include <QRegularExpression>

class PoseTextEdit : public QTextEdit {
    Q_OBJECT
public:
    explicit PoseTextEdit(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent* event) override;
};

#endif // POSETEXTEDIT_H
