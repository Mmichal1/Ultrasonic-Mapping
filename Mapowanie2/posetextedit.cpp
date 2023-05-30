#include "posetextedit.h"

PoseTextEdit::PoseTextEdit(QWidget *parent) : QTextEdit{parent} {}

void PoseTextEdit::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Backspace || event->key() == Qt::Key_Delete) {
        QTextEdit::keyPressEvent(event);
        return;
    }

    QString text = toPlainText();
    if (text.length() >= 3 && event->key() != Qt::Key_Backspace) {
        // Ignore the key press if the maximum length is reached
        event->ignore();
        return;
    }

    static QRegularExpression regex("[0-9]");
    if (!regex.match(event->text()).hasMatch()) {
        // Ignore the key press if the input is not a numeric character
        event->ignore();
        return;
    }

    QTextEdit::keyPressEvent(event);
}
