#pragma once
#include <QWidget>
#include <QImage>
#include <vector>
#include <opencv2/opencv.hpp>

class MultiImageClass : public QWidget
{
    Q_OBJECT

public:
    MultiImageClass(QWidget *parent = nullptr);
    void setImages(const std::vector<cv::Mat>& images);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    std::vector<QImage> m_images;
    QImage matToQImage(const cv::Mat& mat);
};
