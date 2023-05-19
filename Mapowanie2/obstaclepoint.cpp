#include "obstaclepoint.h"

ObstaclePoint::ObstaclePoint(const QPixmap& pixmap, std::array<int, 2> position)
    : pixmap(pixmap), position(position) {}

std::array<int, 2> ObstaclePoint::getPos() { return position; }

const QPixmap& ObstaclePoint::getPixmap() { return pixmap; }

void ObstaclePoint::setPixmap(const QPixmap& newPixmap) {
    ObstaclePoint::pixmap = newPixmap;
}

void ObstaclePoint::setPos(std::array<int, 2> newPosition) {
    ObstaclePoint::position = newPosition;
}