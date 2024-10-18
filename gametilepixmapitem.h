#ifndef GAMETILEPIXMAPITEM_H
#define GAMETILEPIXMAPITEM_H

#include <iostream>
#include <QGraphicsPixMapItem>
#include <QGraphicsSceneMouseEvent>

class GameTilePixMapItem : public QGraphicsPixmapItem
{
public:
    GameTilePixMapItem(const QPixmap &pixmap, int initialIndex);
protected:
    // Event handlers for mouse and hover events
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;    // Handle mouse press events
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;  // Handle mouse release events
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;     // Handle mouse move events
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;    // Handle hover enter events
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;    // Handle hover leave events
    int getInitialIndex();
    int getCurrentIndex();
private:
    int initialIndex;
    int currentIndex;
};

#endif // GAMETILEPIXMAPITEM_H
