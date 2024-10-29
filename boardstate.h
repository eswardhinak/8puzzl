#ifndef BOARDSTATE_H
#define BOARDSTATE_H
#include "gametilepixmapitem.h"
#include <unordered_set>
#include <utility>

class BoardState
{
public:
    BoardState(std::vector<GameTilePixMapItem*> solution, std::vector<GameTilePixMapItem*> current);
    BoardState();
    ~BoardState();
    void setSolution(std::vector<GameTilePixMapItem*> solution);
    void setCurrent(std::vector<GameTilePixMapItem*> current);
    void shuffle(int moves);
    bool swap(int index);
    int getSelected();
    void setSelected();
    void shuffle();
private:
    std::vector<GameTilePixMapItem*> solution;
    std::vector<GameTilePixMapItem*> current;
    int selected;
    int whiteSpaceIndex = 8;
    bool solutionReached();
    int getShuffleIndex();
    std::vector<std::pair<int, int>> * coords;
};

#endif // BOARDSTATE_H
