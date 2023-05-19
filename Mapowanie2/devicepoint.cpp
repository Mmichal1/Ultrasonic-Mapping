#include "devicepoint.h"

DevicePoint::DevicePoint(const QPixmap& pixmap, std::array<int, 3> pose)
    : pixmap(pixmap), pose(pose) {}

std::array<int, 3> DevicePoint::getPose() { return pose; }

const QPixmap& DevicePoint::getPixmap() { return pixmap; }

void DevicePoint::setPixmap(const QPixmap& newPixmap) {
    DevicePoint::pixmap = newPixmap;
}

void DevicePoint::setPose(std::array<int, 3> newPose) {
    DevicePoint::pose = newPose;
}