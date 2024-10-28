#pragma once
#include <QImage>
#include <QPixmap>
#include <QGraphicsScene>
#include <vector>
#include <QGraphicsPixmapItem>
#include "gametilepixmapitem.h"
#include <QGraphicsView>
#include <QRectF>
#include <opencv2/opencv.hpp>

const int SQUARE_LEN = 300;
const int PADDING = 10;


class MultiImageClass
{

public:
    MultiImageClass(int height, int width);
    QGraphicsView * startGame(const std::vector<cv::Mat>& images);
    QGraphicsScene * scene;
    ~MultiImageClass();
    void swap(int idx, int idx_new);

private:
    std::vector<GameTilePixMapItem*> solution;
    QImage matToQImage(const cv::Mat& mat);
    QPixmap createEmptyItem(int, int);

};
