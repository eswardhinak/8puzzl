#ifndef GAMETILEPIXMAPITEM_H
#define GAMETILEPIXMAPITEM_H

#include <iostream>
#include <QGraphicsPixMapItem>
#include <QGraphicsSceneMouseEvent>

class BoardState;

class GameTilePixMapItem : public QGraphicsPixmapItem
{
public:
    GameTilePixMapItem(const QPixmap &pixmap, int initialIndex, BoardState * boardState);
    int getInitialIndex();
    int getCurrentIndex();

protected:
    // Event handlers for mouse and hover events
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;    // Handle mouse press events
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;  // Handle mouse release events
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;     // Handle mouse move events
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;    // Handle hover enter events
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;    // Handle hover leave events
private:
    int initialIndex;
    int currentIndex;
    BoardState * boardState;
};

#endif // GAMETILEPIXMAPITEM_H
