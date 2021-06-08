#ifndef GAME_MOTHER_HPP
#define GAME_MOTHER_HPP

#include "game/piece.hpp"
#include "game/figure_interface.hpp"

class Mother : public FigureInterface{
public:
   Mother() =delete;
   Mother(int _y, int _x, color _col) {pos.x=_x;  pos.y=_y; col=_col;};
   Mother(position _pos, color _col) {pos=_pos; col=_col;}
   std::vector<std::vector<position>> generateMoves(std::vector<std::vector<std::shared_ptr<FigureInterface>>>  board) override;
    bool isMother() override {return true;}
};


#endif //GAME_MOTHER_HPP
