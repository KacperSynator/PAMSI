#ifndef GAME_FIGURE_INTERFACE_HPP
#define GAME_FIGURE_INTERFACE_HPP

#include <vector>
#include <memory>

struct position{
    int x;
    int y;

    bool operator == (const position & other) {return (x==other.x && y==other.y) ? true : false; }
    bool operator != (const position & other) {return !(*this==other);}
};

enum color{white, black};

/// not actually an interface
class FigureInterface{
protected:
    position pos;
    color col;

public:
    void move(position _pos) {pos=_pos;}
    position get_position() {return pos;}
    color get_col() {return col;}
    void gen_capture(position _pos,std::vector<position> &path,std::vector<std::vector<position>> & result, std::vector<std::vector<std::shared_ptr<FigureInterface>>> & board);
    virtual std::vector<std::vector<position>> generateMoves(std::vector<std::vector<std::shared_ptr<FigureInterface>>>  board)=0;
    virtual bool isMother()=0;


};

#endif //GAME_FIGURE_INTERFACE_HPP
