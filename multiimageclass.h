#pragma once
#include <QImage>
#include <QGraphicsScene>
#include <vector>
#include <QGraphicsPixmapItem>
#include "gametilepixmapitem.h"
#include <QGraphicsView>
#include <QRectF>
#include <opencv2/opencv.hpp>

class MultiImageClass
{

public:
    MultiImageClass(int height, int width);
    QGraphicsView * startGame(const std::vector<cv::Mat>& images);
    QGraphicsScene * scene;
    ~MultiImageClass();
    void move();

private:
    std::vector<GameTilePixMapItem*> solution;
    QImage matToQImage(const cv::Mat& mat);

};
