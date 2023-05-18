#ifndef MAP_H
#define MAP_H

#include <math.h>
#include <vector>
#include <iterator>
#include <array>
#include "obstaclepoint.h"
#include "devicepoint.h"
#include "poselabel.h"

#include <QWidget>
#include <QLabel>
#include <QDebug>
#include <QPixmap>
#include <QPainter>
#include <QCoreApplication>
#include <QStringList>
#include <QTransform>

class Map : public QWidget
{
    Q_OBJECT
public:
    explicit Map(QWidget *parent = nullptr);
    std::array<int, 3> getDevicePose();

private:
    QPixmap *dev_pos_pixmap;
    QPixmap *point_pixmap;
    QPixmap *dev_pos_prev_pixmap;
    QPixmap *point_prev_pixmap;
    DevicePoint *curr_dev_pose;
    std::vector<DevicePoint> prev_dev_pose;
    std::vector<ObstaclePoint> curr_points;
    std::vector<ObstaclePoint> prev_points;
//    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
    void drawGrid(QPainter& painter, int mapWidth, int mapHeight);
    void drawArrow(QPainter& painter, int arrowX, int arrowY);
    void drawPoints(QPainter& painter);
    std::array<int, 2> transormCoordinates(std::array<int, 2> goalPosition, int pixmapWidth, int pixmapHeight);

public slots:
    void onResetButtonClicked();
    void handleSentString(const QString& text);

signals:

};

#endif // MAP_H
