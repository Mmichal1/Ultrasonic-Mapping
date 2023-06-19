#include "../inc/posetextedit.h"

PoseTextEdit::PoseTextEdit(QWidget *parent) : QTextEdit{parent} {}

void PoseTextEdit::keyPressEvent(QKeyEvent *event) {

    if (event->key() == Qt::Key_Backspace || event->key() == Qt::Key_Delete) {
        QTextEdit::keyPressEvent(event);
        return;
    }

    QString text = toPlainText();
    if (text.length() >= 4 && event->key() != Qt::Key_Backspace) {
        event->ignore();
        return;
    }

    static QRegularExpression regex("[0-9 \-]");
    if (!regex.match(event->text()).hasMatch()) {
        event->ignore();
        return;
    }

    QTextEdit::keyPressEvent(event);
}
