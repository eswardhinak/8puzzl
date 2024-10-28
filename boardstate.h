#ifndef BOARDSTATE_H
#define BOARDSTATE_H
#include "gametilepixmapitem.h"

class BoardState
{
public:
    BoardState(std::vector<GameTilePixMapItem*> solution, std::vector<GameTilePixMapItem*> current);
    BoardState();
    void setSolution(std::vector<GameTilePixMapItem*> solution);
    void setCurrent(std::vector<GameTilePixMapItem*> current);
    bool swap(int index);
    int getSelected();
    void setSelected();
private:
    std::vector<GameTilePixMapItem*> solution;
    std::vector<GameTilePixMapItem*> current;
    int selected;
    int whiteSpaceIndex = 8;
};

#endif // BOARDSTATE_H
