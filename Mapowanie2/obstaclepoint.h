#ifndef OBSTACLEPOINT_H
#define OBSTACLEPOINT_H

#include <array>

#include <QWidget>
#include <QLabel>
#include <QPixmap>

class ObstaclePoint{
public:
    ObstaclePoint(const QPixmap& pixmap, std::array<int, 2> position);

    std::array<int, 2> getPos();
    const QPixmap& getPixmap();
    void setPixmap(const QPixmap& newPixmap);
    void setPos(std::array<int, 2> newPosition);

private:
    QPixmap pixmap;
    std::array<int, 2> position;
};


#endif // OBSTACLEPOINT_H
