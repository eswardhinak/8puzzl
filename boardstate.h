#ifndef BOARDSTATE_H
#define BOARDSTATE_H
#include "gametilepixmapitem.h"

class BoardState
{
public:
    BoardState(std::vector<GameTilePixMapItem*> solution, std::vector<GameTilePixMapItem*> current);
    void setSolution(std::vector<GameTilePixMapItem*> solution);
    void setCurrent(std::vector<GameTilePixMapItem*> current);
private:
    std::vector<GameTilePixMapItem*> solution;
    std::vector<GameTilePixMapItem*> current;
};

#endif // BOARDSTATE_H
