#include "poselabel.h"

PoseLabel::PoseLabel(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
    setLayout(layout);
}

void PoseLabel::setLabelText(const QString& text) {
    label->setText(text);
}
