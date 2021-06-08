#include "game/draughts.hpp"

#include <iostream>
#include <random>

static int count;
Draughts::Draughts()
{
    board.resize(8);
    for(int i=0; i<8;i++)
        board[i].resize(8);


    for(int i=0;i<=2;i+=2)
        for(int j=1;j<8;j+=2)
            board[i][j]= std::make_shared<Piece>(i, j, black);

    for(int j=0;j<8;j+=2)
        board[1][j]=std::make_shared<Piece>(1, j, black);


    for(int i=5;i<=7;i+=2)
        for(int j=0;j<8;j+=2)
            board[i][j] = std::make_shared<Piece>(i, j, white);

    for(int j=1;j<8;j+=2)
        board[6][j] = std::make_shared<Piece>(6, j, white);



}
void Draughts::makeNewBoard ()
{
    for(auto & row : board)
        for(auto & pos : row)
            if(pos != nullptr)
            {
                if (pos->isMother()) pos = std::make_shared<Mother>(pos->get_position(), pos->get_col());
                else pos = std::make_shared<Piece>(pos->get_position(), pos->get_col());
            }

}

std::vector<std::vector<position>> Draughts::generateMoves(std::shared_ptr<FigureInterface> figure)
{
    return figure->generateMoves(board);
}

std::vector<std::vector<std::vector<position>>> Draughts::generateAllMoves()
{
    std::vector<std::vector<std::vector<position>>> allMoves;
    color _col;

    if(white_turn) _col=white;
    else _col=black;

    for(int i=0;i<board.size(); i++)
        for(int j=0;j<board[i].size(); j++)
            if(board[i][j]!= nullptr && board[i][j]->get_col()==_col)
                allMoves.push_back(generateMoves(board[i][j]));

    return allMoves;
}

void Draughts::startGame(bool _white_first)
{
    if(!_white_first)
        white_turn=false;

}
bool Draughts::gameOver()
{
    /// no more moves
    std::vector<std::vector<std::vector<position>>> all_moves = generateAllMoves();
    for(auto paths : all_moves)
    {
        if(paths.size() != 0)
            return false;
    }
    return true;
}
void Draughts::move(std::vector<position> & path)
{
    if(path.size()<2) return;
    int last_index=path.size()-1;

    board[path[0].y][path[0].x]->move(path[last_index]);
    std::swap(board[path[0].y][path[0].x],board[path[last_index].y][path[last_index].x]);

    for(int i=0;i<path.size()-1;i++)
    {
         if(abs(path[i+1].x-path[i].x) == 2 ) // move vector x, 2 -> capture
         {
             int x= (path[i+1].x+path[i].x)/2;
             int y= (path[i+1].y+path[i].y)/2;

             if(board[y][x] == nullptr ) continue; // queen normal move
             if(board[y][x]->get_col()==black) black_count--;
             else white_count--;

             if(board[y][x]->isMother() && board[y][x]->get_col()==black) black_mother_count--;
             else if(board[y][x]->isMother() && board[y][x]->get_col()==white) white_mother_count--;

             board[y][x]= nullptr;
         }

    }
    int size = path.size();
    if( !board[path[size-1].y][path[size-1].x]->isMother())
        if(board[path[size-1].y][path[size-1].x]->get_col() == white)
        {
            if (path[size - 1].y == 0)
            {
                white_mother_count++;
                transform2queen(board[path[size - 1].y][path[size - 1].x]);
            }
        }
        else
        {
            if(path[size-1].y == 7)
            {
                black_mother_count++;
                transform2queen(board[path[size - 1].y][path[size - 1].x]);
            }
        }
        nextTurn();
}
bool Draughts::aiMove()
{
    if(ai_on && !white_turn)
    {
        std::vector<position> path = ai.findMove(*this);

        move(path);
        return true;
    }
    return false;
}

void Draughts::transform2queen(std::shared_ptr<FigureInterface> piece)
{
    board[piece->get_position().y][piece->get_position().x]= std::make_shared<Mother>(piece->get_position(),piece->get_col());
}

Draughts::AI::difficulty Draughts::AI::get_difficulty()
{
    switch(max_depth)
    {
        case easy:
            return easy;

        case normal:
            return normal;

        case hard:
            return hard;
    }
}

std::vector<position>  Draughts::AI::findMove(Draughts & draughts) {
    std::vector<position> result_path;
    std::vector<std::vector<std::vector<position>>> all_paths = draughts.generateAllMoves();

    int maxEval = std::numeric_limits<int>::min();
    int alpha = std::numeric_limits<int>::min();
    int beta = std::numeric_limits<int>::max();
    for (auto paths : all_paths)
        for (auto it = paths.end() - 1; it != paths.begin() - 1; --it) // best moves are usually at the end
        {
            Draughts tmp_draughts = draughts;
            tmp_draughts.makeNewBoard();
            tmp_draughts.move(*it);
            int eval = minimax(max_depth - 1, true, tmp_draughts, alpha, beta);
            maxEval = std::max(maxEval, eval);
            if (maxEval == eval) result_path = *it;
            alpha = std::max(alpha, eval);
            //count++;
            if (beta <= alpha)
                break;
        }
    //std::cout << count << "\n";
    //count = 0;

    if (result_path.size() < 2)
    {
        int i;
        for (i = 0; !all_paths[i].empty(); i++);
        result_path = all_paths[i][0];
    }

    return result_path;
}

int Draughts::AI::evaluate(Draughts & draughts)
{
    draughts.nextTurn();
    if(draughts.gameOver()) return std::numeric_limits<int>::min();
    draughts.nextTurn();

    int evaluation;

    if(draughts.isWhiteTurn())
    {
        evaluation = 5*draughts.getBlackCount() + 15 * draughts.getBlackMotherCount() -
                     7*draughts.getWhiteCount() - 15 * draughts.getWhiteMotherCount();
    }
    else
    {
        evaluation = 5*draughts.getWhiteCount() + 15 * draughts.getWhiteMotherCount() -
                    7*draughts.getBlackCount() - 15 * draughts.getBlackMotherCount();
    }

    evaluation += rand() % 7 - 3;

    return evaluation;
}

int Draughts::AI::minimax(int depth,bool isPlayerTurn,Draughts & draughts , int & alpha, int & beta)
{
    if(depth==0 || draughts.gameOver()) return evaluate(draughts);

    std::vector<std::vector<std::vector<position>>> all_paths= draughts.generateAllMoves();

    int eval;

    if(isPlayerTurn)
    {
        int minEval=std::numeric_limits<int>::max();
        for(auto paths : all_paths)
            for(auto it = paths.end()-1; it!=paths.begin()-1;--it) // best moves are usually at the end
            {
                Draughts tmp_draughts = draughts;
                tmp_draughts.makeNewBoard();
                tmp_draughts.move(*it);
                eval = minimax(depth-1, false, tmp_draughts, alpha ,beta);
                minEval= std::min(minEval, eval);
                beta = std::min(beta, eval);
                //count++;
                if(beta <= alpha)
                    break;
            }
        return  eval;
    }
    else
    {
        int maxEval=std::numeric_limits<int>::min();
        for(auto paths : all_paths)
            for(auto it = paths.end()-1; it!=paths.begin()-1;--it) // best moves are usually at the end
            {
                Draughts tmp_draughts = draughts;
                tmp_draughts.makeNewBoard();
                tmp_draughts.move(*it);
                eval = minimax( depth-1, true, tmp_draughts, alpha ,beta);
                maxEval= std::max(maxEval, eval);
                alpha = std::max(alpha, eval);
                //count++;
                if(beta <= alpha)
                    break;
            }
        return  eval;
    }

}