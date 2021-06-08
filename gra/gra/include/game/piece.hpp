#ifndef GAME_PIECE_HPP
#define GAME_PIECE_HPP

#include "game/figure_interface.hpp"

class Piece : public FigureInterface{
public:
    Piece() = delete;
    Piece(int _y, int _x, color _col) {pos.x=_x;  pos.y=_y; col=_col;}
    Piece(position _pos, color _col) {pos=_pos; col=_col;}
    std::vector<std::vector<position>> generateMoves(std::vector<std::vector<std::shared_ptr<FigureInterface>>>  board) override;
    bool isMother() override {return false;}


};
#endif //GAME_PIECE_HPP
