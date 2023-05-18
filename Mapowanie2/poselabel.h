#ifndef POSELABEL_H
#define POSELABEL_H

#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>

class PoseLabel : public QWidget
{
    Q_OBJECT
public:
    explicit PoseLabel(QWidget *parent = nullptr);
    void setLabelText(const QString& text);
private:
    QLabel *label;
public slots:
};

#endif // POSELABEL_H
