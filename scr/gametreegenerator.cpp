#include "gamenode.h"
#include "gametreegenerator.h"

using namespace std;

GameTreeGenerator::GameTreeGenerator(QObject *parent) : QObject(parent)
{
    _root = new GameNode(Board::Unknown, this);
    _node_map.insert(boardToString(_board), _root);
}

GameNode *GameTreeGenerator::getNode(const Board &board) const
{
    return _node_map.value(boardToString(board), nullptr);
}

void GameTreeGenerator::generate()
{
    recursiveGenerate(_root, Board::Computer);
}

QString GameTreeGenerator::boardToString(const Board &board) const
{
    QStringList str_list;
    generate_n(back_inserter(str_list), Board::CELL_COUNT, [i=0, &board]() mutable
    {
        return QString("%1").arg(board.at(i++));
    });
    return str_list.join("");
}

void GameTreeGenerator::recursiveGenerate(GameNode *parent, Board::CellStatus current_player)
{
    for(int i=0; i<Board::CELL_COUNT; i++)
    {
        if(_board.at(i) != Board::CellStatus::None)
            continue;

        _board.setCell(i, current_player);
        QString board_str = boardToString(_board);
        auto existing_node = _node_map.value(board_str, nullptr);   // consider rotation and flip here to reduce
        if(existing_node == nullptr)
        {
            GameNode *child = new GameNode(_board.status(), parent);
            parent->addChild(child, i);
            _node_map.insert(board_str, child);
            if(!child->isEndNode())
                recursiveGenerate(child, current_player == Board::CellStatus::Computer ? Board::CellStatus::Player : Board::CellStatus::Computer);
        }
        else
            parent->addChild(existing_node, i);
        _board.setCell(i, Board::CellStatus::None);
    }
}
