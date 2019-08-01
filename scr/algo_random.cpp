#include "algo_random.h"
#include <random>
using namespace std;

int Algo_random::getNextMove(const Board &board)
{
    QVector<int> none_indexes;
    for(int i=0; i<Board::CELL_COUNT; i++)
        if(board.at(i) == Board::CellStatus::None)
            none_indexes.append(i);

    random_device random_device;
    mt19937 generator(random_device());
    shuffle(begin(none_indexes), end(none_indexes), generator);

    return none_indexes.first();
}
