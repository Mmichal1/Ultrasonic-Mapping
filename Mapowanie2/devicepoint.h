#ifndef DEVICEPOINT_H
#define DEVICEPOINT_H

#include <array>

#include <QWidget>
#include <QLabel>
#include <QPixmap>

class DevicePoint
{
public:
    DevicePoint(const QPixmap& pixmap, std::array<int, 3> pose);

    std::array<int, 3> getPose();
    const QPixmap& getPixmap();
    void setPixmap(const QPixmap& newPixmap);
    void setPose(std::array<int, 3> newPose);

private:
    QPixmap pixmap;
    std::array<int, 3> pose;
};

#endif // DEVICEPOINT_H
