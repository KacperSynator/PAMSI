#ifndef GUI_HPP_
#define GUI_HPP_

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

#include "game/draughts.hpp"

class Gui
{
  public:
    bool init();
    void execGame();

  private:
    void draw();
    void drawFigure(int x,int y, std::shared_ptr<FigureInterface> figure);
    void handleMouseButtonDown(SDL_MouseButtonEvent event);
    void handleBoardClick(SDL_MouseButtonEvent event);
    void handleSideClick(SDL_MouseButtonEvent event);
    void gameOver();
    void checkMultiplePaths(std::vector<std::vector<position>> & paths);

    Draughts draughts;
    position last_clicked;
    std::shared_ptr<FigureInterface> last_high_ptr;
    int path_index;


    bool gameIsRunning = false;
    bool gameStop = false;
    bool waiting_for_2nd_click=false;
    bool multiple_paths = false;

    SDL_Window* window = nullptr;
    SDL_Surface* surface = nullptr;
    SDL_Surface* piece_w = nullptr;
    SDL_Surface* queen_w = nullptr;
    SDL_Surface* piece_b = nullptr;
    SDL_Surface* queen_b = nullptr;
    SDL_Surface* br_dark_tile = nullptr;
    SDL_Surface* br_light_tile = nullptr;
    SDL_Surface* gr_light_tile = nullptr;
    TTF_Font* font = nullptr;
    TTF_Font* font_small = nullptr;

};

#endif /* GAME_GUI_HPP_ */
