#include "game/mother.hpp"


std::vector<std::vector<position>> Mother::generateMoves(std::vector<std::vector<std::shared_ptr<FigureInterface>>>  board)
{
    std::vector<std::vector<position>> paths;
    std::vector<position> path;

    /// bot right
    for (int i = pos.y, j = pos.x; i < 7 && j < 7; i++, j++)
        {
            if (board[i + 1][j + 1] == nullptr)
            {
                path.push_back(position{pos.x, pos.y});
                path.push_back(position{j + 1, i + 1});
                paths.push_back(path);
                path.clear();
            }
            else if( board[i + 1][j + 1]->get_col() != col && i+2<8 && j+2<8 && board[i+2][j+2] == nullptr)
            {
                if(pos.x != j || pos.y != i)
                    path.push_back(position{pos.x, pos.y});
                path.push_back(position{j,i});
                gen_capture(position{j+2,i+2},path,paths,board);
                path.clear();
                break;
            }
            else break;
        }

    /// bot left
    for (int i = pos.y, j = pos.x; i < 7 && j > 0; i++ ,j--)
        {
            if (board[i + 1][j - 1] == nullptr)
            {
                path.push_back(position{pos.x, pos.y});
                path.push_back(position{j - 1, i + 1});
                paths.push_back(path);
                path.clear();
            }
            else if( board[i + 1][j - 1]->get_col() != col && i+2<8 && j-2>=0 && board[i+2][j-2] == nullptr)
            {
                if(pos.x != j || pos.y != i)
                    path.push_back(position{pos.x, pos.y});
                path.push_back(position{j,i});
                gen_capture(position{j-2,i+2},path,paths,board);
                path.clear();
                break;
            }
            else break;
        }


    /// top left
    for (int i = pos.y, j = pos.x; i > 0 && j > 0; i--,  j--)
        {
            if (board[i - 1][j - 1] == nullptr)
            {
                path.push_back(position{pos.x, pos.y});
                path.push_back(position{j - 1, i - 1});
                paths.push_back(path);
                path.clear();
            }
            else if( board[i - 1][j - 1]->get_col() != col && i-2>=0 && j-2>=0 && board[i-2][j-2] == nullptr)
            {
                if(pos.x != j || pos.y != i)
                   path.push_back(position{pos.x, pos.y});
                path.push_back(position{j,i});
                gen_capture(position{j-2,i-2},path,paths,board);
                path.clear();
                break;
            }
            else break;
        }

    /// top right
    for (int i = pos.y, j = pos.x; i > 0  &&  j < 7; i--, j++)
        {
            if (board[i - 1][j + 1] == nullptr)
            {
                path.push_back(position{pos.x, pos.y});
                path.push_back(position{j + 1, i - 1});
                paths.push_back(path);
                path.clear();
            }
            else if( board[i - 1][j + 1]->get_col() != col && i-2>=0 && j+2<8 && board[i-2][j+2] == nullptr)
            {
                if(pos.x != j || pos.y != i)
                    path.push_back(position{pos.x, pos.y});
                path.push_back(position{j,i});
                gen_capture(position{j+2,i-2},path,paths,board);
                path.clear();
                break;
            } else break;
        }


    return paths;
}
