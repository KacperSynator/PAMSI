#ifndef GAME_DRAUGHTS_HPP
#define GAME_DRAUGHTS_HPP

#include "game/piece.hpp"
#include "game/mother.hpp"

#include <vector>
#include <memory>



class Draughts{
public:

    class AI{
    public:
        enum difficulty{easy=1, normal=3, hard=5};

        std::vector<position> findMove(Draughts & draughts);
        void set_difficulty(difficulty dif) {max_depth=dif;}
        difficulty get_difficulty();

    private:
        int max_depth=normal;
        int evaluate(Draughts & draughts);
        int minimax(int depth,bool isPlayerTurn,Draughts & draughts, int & alpha, int & beta);
    };

    Draughts();
    void makeNewBoard ();
    std::vector<std::vector<std::shared_ptr<FigureInterface>>> get_board() {return board;}
    std::vector<std::vector<position>> generateMoves(std::shared_ptr<FigureInterface> figure);
    std::vector<std::vector<std::vector<position>>> generateAllMoves();
    int getWhiteCount() {return white_count;}
    int getBlackCount() {return black_count;}
    int getWhiteMotherCount() {return white_mother_count;}
    int getBlackMotherCount() {return black_mother_count;}
    AI & getAI() {return ai;}
    bool isAIon() {return ai_on;}
    void toggleAI() {ai_on = !ai_on;}
    void startGame(bool white_first=true);
    bool gameOver();
    void nextTurn() {white_turn = !white_turn;}
    void move(std::vector<position> & path);
    bool aiMove();
    bool isWhiteTurn() {return white_turn;}
    void transform2queen(std::shared_ptr<FigureInterface> piece);

private:
    bool ai_on=true;
    AI ai;

    std::vector<std::vector<std::shared_ptr<FigureInterface>>> board;
    int white_count=12;
    int white_mother_count=0;
    int black_count=12;
    int black_mother_count=0;
    bool white_turn=true;

};

#endif //GAME_DRAUGHTS_HPP
