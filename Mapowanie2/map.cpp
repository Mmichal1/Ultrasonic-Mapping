#include "map.h"

Map::Map(QWidget* parent) : QWidget{parent} {

    dev_pos_pixmap = new QPixmap(":/device_pos.svg");
    *dev_pos_pixmap = dev_pos_pixmap->scaled(dev_pos_pixmap->width() / 2,
                                             dev_pos_pixmap->height() / 2);

    dev_pos_prev_pixmap = new QPixmap(":/device_pos_prev.svg");
    *dev_pos_prev_pixmap = dev_pos_prev_pixmap->scaled(
        dev_pos_prev_pixmap->width() / 2, dev_pos_prev_pixmap->height() / 2);

    point_pixmap = new QPixmap(":/point.svg");
    point_prev_pixmap = new QPixmap(":/point_prev.svg");

    curr_dev_pose = new DevicePoint(*dev_pos_pixmap, {0, 0, 0});
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
    std::array<int, 2> position = transormCoordinates(
        {curr_dev_pose->getPose()[0], curr_dev_pose->getPose()[1]},
        curr_dev_pose->getPixmap().width(),
        curr_dev_pose->getPixmap().height());

    if (!prev_dev_pose.empty()) {
        for (auto point : prev_dev_pose) {
            std::array<int, 2> position = transormCoordinates(
                {point.getPose()[0], point.getPose()[1]},
                point.getPixmap().width(), point.getPixmap().height());
            painter.drawPixmap(position[0], position[1], point.getPixmap());
        }
    }

    painter.drawPixmap(position[0], position[1], curr_dev_pose->getPixmap());

    if (!prev_points.empty()) {
        for (auto point : prev_points) {
            std::array<int, 2> position = transormCoordinates(
                {point.getPos()[0], point.getPos()[1]},
                point.getPixmap().width(), point.getPixmap().height());
            painter.drawPixmap(position[0], position[1], point.getPixmap());
        }
    }

    if (!curr_points.empty()) {
        for (auto point : curr_points) {
            std::array<int, 2> position = transormCoordinates(
                {point.getPos()[0], point.getPos()[1]},
                point.getPixmap().width(), point.getPixmap().height());
            painter.drawPixmap(position[0], position[1], point.getPixmap());
        }
    }
}

std::array<int, 2> Map::transormCoordinates(std::array<int, 2> goalPosition,
                                            int pixmapWidth, int pixmapHeight) {
    std::array<int, 2> position;
    position[0] = goalPosition[0] - pixmapWidth / 2;
    position[1] = -(goalPosition[1] + (pixmapHeight / 2));
    return position;
}

std::array<int, 3> Map::getDevicePose() { return curr_dev_pose->getPose(); }


void Map::onResetButtonClicked() {
    curr_points.clear();
    prev_points.clear();
    prev_dev_pose.clear();
    curr_dev_pose->setPose({0, 0, 0});
    update();
}

void Map::handleSentString(const QString& text) {
    QStringList list = text.split(" ");
    prev_dev_pose.push_back(*curr_dev_pose);
    prev_dev_pose.back().setPixmap(*dev_pos_prev_pixmap);
    curr_dev_pose->setPose({list[0].toInt(), list[1].toInt(), list[2].toInt()});
    update();

    prev_points.insert(prev_points.end(),
                       std::make_move_iterator(curr_points.begin()),
                       std::make_move_iterator(curr_points.end()));

    curr_points.erase(curr_points.begin(), curr_points.end());

    for (auto& i : prev_points) {
        i.setPixmap(*point_prev_pixmap);
    }
}

void Map::handleSentStringFromSerial(const QString& message) {

    QStringList list = message.split(" ");
//    std::string crc = list.last();
    list.removeLast();
    std::array<int, 2> data;

    for (int i = 0; i < 5; i++) {
        data = {list.at(i).toInt(), list.at(i+1).toInt()};
        i++;
        addPoints(data);
    }
}

void Map::addPoints(std::array<int, 2> data) {
    std::array<int, 3> angles = {-45, 0, 45};
    std::array<int, 2> pos;

    curr_points.clear(); // Only keep the newest sensor data

    double alpha = (angles[data[0]] + curr_dev_pose->getPose()[2]) * M_PI / 180;
    pos[0] = round(sin(alpha) * data[1]) + curr_dev_pose->getPose()[0];
    pos[1] = round(cos(alpha) * data[1]) + curr_dev_pose->getPose()[1];

    curr_points.push_back(ObstaclePoint(*point_pixmap, pos));

    update();
}
