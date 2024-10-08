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
    QGraphicsView *  setImages(const std::vector<cv::Mat>& images);
    QGraphicsScene * scene;
    ~MultiImageClass();

private:
    std::vector<QImage> m_images;
    QImage matToQImage(const cv::Mat& mat);
};
