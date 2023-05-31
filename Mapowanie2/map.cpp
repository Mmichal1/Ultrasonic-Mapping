#include "map.h"

Map::Map(QWidget* parent) : QWidget{parent} {

    devPosPixmap = new QPixmap(":/device_pos.svg");
    *devPosPixmap = devPosPixmap->scaled(devPosPixmap->width() / 2,
                                             devPosPixmap->height() / 2);

    devPosPrevPixmap = new QPixmap(":/device_pos_prev.svg");
    *devPosPrevPixmap = devPosPrevPixmap->scaled(
        devPosPrevPixmap->width() / 2, devPosPrevPixmap->height() / 2);

    pointPixmap = new QPixmap(":/point.svg");
    pointPrevPixmap = new QPixmap(":/point_prev.svg");

    currDevPose = new DevicePoint(*devPosPixmap, {0, 0, 0});
}

void Map::paintEvent(QPaintEvent* event) {
    QWidget::paintEvent(event);
    QPainter painter(this);

    drawGrid(painter, width(), height());

    drawPoints(painter);
}

void Map::drawGrid(QPainter& painter, int mapWidth, int mapHeight) {
    // Translate the coordinate system so that point 0 is in the center of the
    // widget
    painter.translate(mapWidth / 2, mapHeight / 2);

    // Set the pen color and width
    painter.setPen(QPen(Qt::black, 2));

    // Draw axis
    painter.drawLine(-mapWidth / 2, 0, mapWidth / 2, 0);
    painter.drawLine(0, -mapHeight / 2, 0, mapHeight / 2);

    // Draw ticks and labels
    int tickDistance = 100;
    for (int x = 0; x < mapWidth / 2;
         x += tickDistance) {
        painter.drawLine(x, -5, x, 5);
        painter.drawText(x - 10, 20, QString::number(x));
    }
    for (int x = 0; x > - mapWidth / 2;
         x -= tickDistance) {
        painter.drawLine(x, -5, x, 5);
        painter.drawText(x - 10, 20, QString::number(x));
    }
    for (int y = 0; y < mapHeight / 2;
         y += tickDistance) {
        painter.drawLine(-5, y, 5, y);
        painter.drawText(10, y + 5, QString::number(-y));
    }
    for (int y = 0; y > - mapHeight / 2;
         y -= tickDistance) {
        painter.drawLine(-5, y, 5, y);
        painter.drawText(10, y + 5, QString::number(-y));
    }

    // Draw labels
    painter.drawText(mapWidth / 2 - 20, -20, "X");
    painter.drawText(-30, -mapHeight / 2 + 20, "Y");

    // Draw grid
    painter.setPen(QPen(Qt::gray, 1, Qt::DotLine));
    for (int x = 0; x < mapWidth / 2;
         x += tickDistance / 5) {
        painter.drawLine(x, -mapHeight / 2, x, mapHeight / 2);
    }
    for (int x = 0; x > - mapWidth / 2;
         x -= tickDistance / 5) {
        painter.drawLine(x, -mapHeight / 2, x, mapHeight / 2);
    }
    for (int y = 0; y < mapHeight / 2;
         y += tickDistance / 5) {
        painter.drawLine(-mapWidth / 2, y, mapWidth / 2, y);
    }
    for (int y = 0; y > - mapHeight / 2;
         y -= tickDistance / 5) {
        painter.drawLine(-mapWidth / 2, y, mapWidth / 2, y);
    }
}

void Map::drawPoints(QPainter& painter) {
    std::array<int, 2> positionDev = transormCoordinates(
        {currDevPose->getPose()[0], currDevPose->getPose()[1]},
        currDevPose->getPixmap().width(),
        currDevPose->getPixmap().height());

    painter.setPen(QPen(Qt::blue, 1, Qt::DashLine));

    drawDetectionArea(painter);

    if (!prevDevPose.empty()) {
        for (auto point : prevDevPose) {
            std::array<int, 2> position = transormCoordinates(
                {point.getPose()[0], point.getPose()[1]},
                point.getPixmap().width(), point.getPixmap().height());
            painter.drawPixmap(position[0], position[1], point.getPixmap());
        }
    }

    painter.drawPixmap(positionDev[0], positionDev[1], currDevPose->getPixmap());

    if (!prevPoints.empty()) {
        for (auto point : prevPoints) {
            std::array<int, 2> position = transormCoordinates(
                {point.getPos()[0], point.getPos()[1]},
                point.getPixmap().width(), point.getPixmap().height());
            painter.drawPixmap(position[0], position[1], point.getPixmap());
        }
    }

    if (!currPoints.empty()) {
        for (auto point : currPoints) {
            std::array<int, 2> position = transormCoordinates(
                {point.getPos()[0], point.getPos()[1]},
                point.getPixmap().width(), point.getPixmap().height());
            painter.drawPixmap(position[0], position[1], point.getPixmap());
        }
    }
}

void Map::drawDetectionArea(QPainter& painter) {

    std::array<int, 2> posLeft;
    std::array<int, 2> posRight;
    int distance = 450;
    double alpha = 0.0;

    alpha = (- 45 + currDevPose->getPose()[2]) * M_PI / 180;
    posLeft[0] = round(sin(alpha) * distance) + currDevPose->getPose()[0];
    posLeft[1] = round(cos(alpha) * distance) + currDevPose->getPose()[1];

    painter.drawLine(currDevPose->getPose()[0], - currDevPose->getPose()[1], posLeft[0] , - posLeft[1] );

    alpha = (45 + currDevPose->getPose()[2]) * M_PI / 180;
    posRight[0] = round(sin(alpha) * distance) + currDevPose->getPose()[0];
    posRight[1] = round(cos(alpha) * distance) + currDevPose->getPose()[1];

    painter.drawLine(currDevPose->getPose()[0], - currDevPose->getPose()[1], posRight[0] , - posRight[1] );

//    int width = 450;  // Width of the arc's bounding rectangle
//    int height = 100; // Height of the arc's bounding rectangle
//    int startAngle = 100 * 16; // Start angle (in 1/16th of a degree)
//    int spanAngle = 120 * 16; // Span angle (in 1/16th of a degree)

//    painter.drawArc(posLeft[0], - posLeft[1], width, height, startAngle, spanAngle);
    painter.drawLine(posLeft[0], - posLeft[1], posRight[0] , - posRight[1] );
}

std::array<int, 2> Map::transormCoordinates(std::array<int, 2> goalPosition,
                                            int pixmapWidth, int pixmapHeight) {
    std::array<int, 2> position;
    position[0] = goalPosition[0] - pixmapWidth / 2;
    position[1] = -(goalPosition[1] + (pixmapHeight / 2));
    return position;
}

std::array<int, 3> Map::getDevicePose() { return currDevPose->getPose(); }


void Map::onResetButtonClicked() {
    currPoints.clear();
    prevPoints.clear();
    prevDevPose.clear();
    currDevPose->setPose({0, 0, 0});
    update();
}

void Map::handleSentString(const QString& text) {
    QStringList list = text.split(" ");
    prevDevPose.push_back(*currDevPose);
    prevDevPose.back().setPixmap(*devPosPrevPixmap);
    currDevPose->setPose({list[0].toInt(), list[1].toInt(), list[2].toInt()});
    update();

    prevPoints.insert(prevPoints.end(),
                       std::make_move_iterator(currPoints.begin()),
                       std::make_move_iterator(currPoints.end()));

    currPoints.erase(currPoints.begin(), currPoints.end());

    for (auto& i : prevPoints) {
        i.setPixmap(*pointPrevPixmap);
    }
}

void Map::handleSentStringFromSerial(const QStringList &list) {

    std::array<int, 2> data;

    currPoints.clear(); // Only keep the newest sensor data

    for (int i = 0; i < 5; i++) {
        data = {list.at(i).toInt(), list.at(i+1).toInt()};
        i++;
        addPoints(data);
    }
}

void Map::addPoints(std::array<int, 2> data) {
    std::array<int, 3> angles = {-45, 0, 45};
    std::array<int, 2> pos;

    double alpha = (angles[data[0]] + currDevPose->getPose()[2]) * M_PI / 180;
    pos[0] = round(sin(alpha) * data[1]) + currDevPose->getPose()[0];
    pos[1] = round(cos(alpha) * data[1]) + currDevPose->getPose()[1];

    currPoints.push_back(ObstaclePoint(*pointPixmap, pos));

    update();
}

