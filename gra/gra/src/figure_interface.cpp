#include "game/figure_interface.hpp"

void FigureInterface::gen_capture(position _pos,std::vector<position> &path, std::vector<std::vector<position>> & result, std::vector<std::vector<std::shared_ptr<FigureInterface>>> & board)
{
    bool pushed =false;
    int size = path.size();

    bool loop_warning=false;
    int k = 0;
    for(; k<size;k++)
    {
        if(path[k].x==_pos.x && path[k].y==_pos.y)
        {
            loop_warning = true;
            break;
        }
    }


    /// top left
    if( !(size > 0 && path[size-1].x ==_pos.x-2 && path[size-1].y ==_pos.y-2) )
        if (_pos.x-2 >=0 && _pos.y-2>=0 )
            if (board[_pos.y - 1][_pos.x - 1] != nullptr && board[_pos.y - 1][_pos.x - 1]->get_col() == !col &&
                (board[_pos.y-2][_pos.x-2] == nullptr || board[_pos.y-2][_pos.x-2]->get_position() ==  pos))
            {
                if(!(loop_warning && _pos.x-2==path[k+1].x && _pos.y-2==path[k+1].y))
                {
                    if (!pushed)
                    {
                        pushed = true;
                        path.push_back(_pos);
                        if (path.size() > 1)
                            result.push_back(path);
                    }

                    gen_capture(position{_pos.x - 2, _pos.y - 2}, path, result, board);
                }
            }
    /// top right
    if( !(size > 0 && path[size-1].x ==_pos.x+2 && path[size-1].y ==_pos.y-2) )
        if (_pos.x+2 <8 && _pos.y-2>=0  )
            if (board[_pos.y - 1][_pos.x + 1] != nullptr && board[_pos.y - 1][_pos.x + 1]->get_col() ==!col &&
                 (board[_pos.y-2][_pos.x+2] == nullptr || board[_pos.y-2][_pos.x+2]->get_position() == pos))
            {
                if(!(loop_warning && _pos.x+2==path[k+1].x && _pos.y-2==path[k+1].y))
                {
                    if (!pushed)
                    {
                        pushed = true;
                        path.push_back(_pos);
                        if (path.size() > 1)
                            result.push_back(path);
                    }
                    else
                        path.resize(size + 1);

                    gen_capture(position{_pos.x + 2, _pos.y - 2}, path, result, board);
                }
            }

    /// bot left
    if( !(size > 0 && path[size-1].x ==_pos.x-2 && path[size-1].y ==_pos.y+2) )
        if (_pos.x-2 >=0 && _pos.y+2<8 )
            if (board[_pos.y + 1][_pos.x - 1] != nullptr && board[_pos.y + 1][_pos.x - 1]->get_col() == !col &&
                (board[_pos.y+2][_pos.x-2] == nullptr || board[_pos.y+2][_pos.x-2]->get_position() == pos))
            {
                if(!(loop_warning && _pos.x-2==path[k+1].x && _pos.y+2==path[k+1].y))
                {
                    if (!pushed)
                    {
                        pushed = true;
                        path.push_back(_pos);
                        if (path.size() > 1)
                            result.push_back(path);
                    }
                    else
                        path.resize(size + 1);

                    gen_capture(position{_pos.x - 2, _pos.y + 2}, path, result, board);
                }
            }

    /// bot right
    if( !(size > 0 &&  path[size-1].x ==_pos.x+2 && path[size-1].y ==_pos.y+2 ) )
        if (_pos.x+2 <8 && _pos.y+2<8 )
            if (board[_pos.y + 1][_pos.x + 1] != nullptr && board[_pos.y + 1][_pos.x + 1]->get_col() == !col &&
                (board[_pos.y+2][_pos.x+2] == nullptr || board[_pos.y+2][_pos.x+2]->get_position() == pos))
            {
                if(!(loop_warning && _pos.x+2==path[k+1].x && _pos.y+2==path[k+1].y))
                {
                    if (!pushed)
                    {
                        pushed = true;
                        path.push_back(_pos);
                        if (path.size() > 1)
                            result.push_back(path);
                    }
                    else
                        path.resize(size + 1);

                    gen_capture(position{_pos.x + 2, _pos.y + 2}, path, result, board);
                }
            }

    if(!pushed)
    {
        path.push_back(_pos);
        if(path.size()>1)
            result.push_back(path);
    }
}