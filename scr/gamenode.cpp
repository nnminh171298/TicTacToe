#include "gamenode.h"

GameNode::GameNode(Board::BoardStatus status, QObject *parent)
    : QObject (parent), _status{status}
{

}

bool GameNode::isEndNode() const
{
    return _status == Board::Tie || _status == Board::Win || _status == Board::Lose;
}

Board::BoardStatus GameNode::status() const
{
    return _status;
}

void GameNode::addChild(GameNode *node_ptr, int leading_move)
{
    _children.insert(leading_move, node_ptr);
}

QMap<int, GameNode *> GameNode::children() const
{
    return _children;
}
