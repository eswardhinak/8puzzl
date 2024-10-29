#ifndef BOARDSTATE_H
#define BOARDSTATE_H
#include <QPixmap>
#include <unordered_set>
#include <utility>
#include "gametilepixmapitem.h"


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
    bool swap(int index, bool checkSolution);
    int getSelected();
    void setSelected();
    void shuffle();
    void setHiddenTile(QPixmap);
private:
    std::vector<GameTilePixMapItem*> solution;
    std::vector<GameTilePixMapItem*> current;
    int selected;
    int whiteSpaceIndex = 8;
    bool solutionReached();
    int getShuffleIndex();
    std::vector<std::pair<int, int>> * coords;
    QPixmap hiddenTile;
    void placeHiddenTileIfGameOver();
};

#endif // BOARDSTATE_H
