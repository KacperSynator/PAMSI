#include "game/piece.hpp"

std::vector<std::vector<position>> Piece::generateMoves(std::vector<std::vector<std::shared_ptr<FigureInterface>>>   board)
{
    std::vector<std::vector<position>> paths;
    std::vector<position> path;


    if(col==black) // top of the board (black forward moves)
    {
        if (pos.x + 1 < 8 && pos.y + 1 < 8)
            if (board[pos.y + 1][pos.x + 1] == nullptr)
            {
                path.push_back(position{pos.x, pos.y});
                path.push_back(position{pos.x + 1, pos.y + 1});
                paths.push_back(path);
                path.clear();
            }

        if (pos.x - 1 >= 0 && pos.y + 1 < 8)
            if (board[pos.y + 1][pos.x - 1] == nullptr)
            {
                path.push_back(position{pos.x, pos.y});
                path.push_back(position{pos.x - 1, pos.y + 1});
                paths.push_back(path);
                path.clear();
            }
    }



    if(col==white) //bottom of the board (white forward moves)
    {
        if (pos.x + 1 < 8 && pos.y - 1 >= 0 )
            if (board[pos.y - 1][pos.x + 1] == nullptr)
            {
                path.push_back(position{pos.x, pos.y});
                path.push_back(position{pos.x + 1, pos.y - 1});
                paths.push_back(path);
                path.clear();
            }

        if (pos.x - 1 >= 0 && pos.y - 1 >= 0 )
            if (board[pos.y - 1][pos.x - 1] == nullptr)
            {
                path.push_back(position{pos.x, pos.y});
                path.push_back(position{pos.x - 1, pos.y - 1});
                paths.push_back(path);
                path.clear();
            }
    }

    gen_capture(pos,path ,paths,board);

    return paths;
}
