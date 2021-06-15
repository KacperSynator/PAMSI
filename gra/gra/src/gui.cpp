#include "game/gui.hpp"
#include <iostream>

bool Gui::init()
{
    int rendererFlags = SDL_RENDERER_ACCELERATED, windowFlags = 0; //SDL_WINDOW_RESIZABLE
    constexpr auto SCREEN_WIDTH = 1080;
    constexpr auto SCREEN_HEIGHT = 717;

    if(SDL_Init(SDL_INIT_VIDEO) < 0 || TTF_Init() < 0)
    {
        return false;
    }

    window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
                              windowFlags);

    if(!window)
    {
        return false;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    surface = SDL_GetWindowSurface(window);

    piece_w = SDL_LoadBMP("../data/w_pawn_png_128px.bmp");
    queen_w = SDL_LoadBMP("../data/w_queen_png_128px.bmp");
    piece_b = SDL_LoadBMP("../data/b_pawn_png_128px.bmp");
    queen_b = SDL_LoadBMP("../data/b_queen_png_128px.bmp");
    br_dark_tile =SDL_LoadBMP("../data/square_brown_dark_png_128px.bmp");
    br_light_tile =SDL_LoadBMP("../data/square_brown_light_png_128px.bmp");
    gr_light_tile =SDL_LoadBMP("../data/square_gray_light_png_128px.bmp");
    font = TTF_OpenFont("../data/scpreg.ttf", 72);
    font_small = TTF_OpenFont("../data/scpreg.ttf", 36);

    return surface && piece_w && piece_b && queen_w && queen_b && br_light_tile && br_dark_tile && gr_light_tile && font;
}

void Gui::execGame()
{
    gameIsRunning = true;
    draw();
    while(gameIsRunning)
    {
        SDL_Event event;
        bool changed=false;
        while(SDL_PollEvent(&event))
        {
            if (!gameStop || event.type == SDL_QUIT)
            {
                changed = true;
                switch (event.type)
                {
                    case SDL_QUIT:
                    {
                        gameIsRunning = false;
                        break;
                    }
                    case SDL_MOUSEBUTTONDOWN:
                    {
                        handleMouseButtonDown(event.button);
                        if (waiting_for_2nd_click || gameStop) changed = false;
                        break;
                    }
                    default:
                    {
                        changed = false;
                        break;
                    }
                }
            }
            if(changed) draw();
        }
        if(!gameStop && draughts.aiMove())
        {
            draw();
            if (draughts.gameOver())
                gameOver();
        }

    }

    SDL_Quit();
    TTF_Quit();
}
void Gui::handleMouseButtonDown(SDL_MouseButtonEvent event)
{
  if(event.x<720)
      handleBoardClick(event);
  else
      handleSideClick(event);

}
void Gui::handleBoardClick(SDL_MouseButtonEvent event)
{
    int j=event.x/90;
    int i=event.y/90;

    if(!waiting_for_2nd_click)
    {
        if(draughts.get_board()[i][j] != nullptr)
        {
            if( (draughts.isWhiteTurn() && draughts.get_board()[i][j]->get_col() == white)
                || (!draughts.isWhiteTurn() && draughts.get_board()[i][j]->get_col() == black))
            {
                waiting_for_2nd_click= true;
                std::vector<std::vector<position>> paths;
                paths = draughts.generateMoves(draughts.get_board()[i][j]);

                for(auto path : paths)
                {
                    for(auto pos : path)
                    {
                        SDL_Rect imageRect = {pos.x * 90, pos.y * 90, 40, 40};
                        SDL_BlitSurface(gr_light_tile, nullptr, surface, &imageRect);
                    }
                    last_clicked=path[0];
                    last_high_ptr=draughts.get_board()[path[0].y][path[0].x];
                }
                drawFigure(j*90,i*90,draughts.get_board()[i][j]);

                SDL_UpdateWindowSurface(window);
            }
        }
    }
    else if(waiting_for_2nd_click && !multiple_paths)
    {
        if(last_high_ptr != nullptr)
        {
            std::vector<std::vector<position>> paths ,tmp_paths;
            paths = draughts.generateMoves(last_high_ptr);

            for (auto path : paths)
                for (int k=1;k<path.size();k++)
                    if (path[k].y == i && path[k].x == j && path[path.size()-1] == path[k] )
                        tmp_paths.push_back(path);


            if(tmp_paths.size()==1)
            {
                draughts.move(tmp_paths[0]);

                draw();
                if (draughts.gameOver())
                {
                    gameOver();
                    return;
                }
                waiting_for_2nd_click = false;
                return;
            }
            else if(tmp_paths.size()>1)
            {
                multiple_paths = true;
                waiting_for_2nd_click = true;
                draw();
                position last_checked{-1, -1};
                path_index=1;
                for (int k = 0; k < tmp_paths.size(); k++)
                {
                    if (last_checked == tmp_paths[k][path_index])
                    {
                        k = 0;
                        last_checked=tmp_paths[k][path_index];
                        path_index++;
                        continue;
                    }
                    last_checked=tmp_paths[k][path_index];
                }
                for (auto path : tmp_paths)
                {
                    SDL_Rect imageRect = {path[path_index].x * 90, path[path_index].y * 90, 40, 40};
                    SDL_BlitSurface(gr_light_tile, nullptr, surface, &imageRect);
                    last_clicked = path[path.size() - 1];
                }

                SDL_UpdateWindowSurface(window);
                return;
            }
        }
        waiting_for_2nd_click=false;
    }
    else if( waiting_for_2nd_click && multiple_paths)
    {
        std::vector<std::vector<position>> paths ,tmp_paths;
        paths = draughts.generateMoves(last_high_ptr);

        for (auto path : paths)
            for (int k=1;k<path.size();k++)
                if (path[k] == last_clicked && path[k] == path[path.size()-1] )
                    tmp_paths.push_back(path);

        for (auto path : tmp_paths)
        {
            for(auto pos : path)
            {
                if(pos.y == i && pos.x == j && pos == path[path_index])
                {
                    draughts.move(path);
                    draw();
                    if (draughts.gameOver())
                    {
                        gameOver();
                        return;
                    }
                    waiting_for_2nd_click = false;
                    multiple_paths= false;
                    return;
                }
            }
        }
        waiting_for_2nd_click = false;
        multiple_paths= false;
    }
}
void Gui::handleSideClick(SDL_MouseButtonEvent event)
{
    /// ai on/off
    if(event.x > 830 && event.x < 970 && event.y > 200 && event.y < 232)
        draughts.toggleAI();

    /// difficulty easy
    if(event.x > 840 && event.x < 937 && event.y > 260 && event.y < 298)
        draughts.getAI().set_difficulty(Draughts::AI::easy);

    /// difficulty  normal
    if(event.x > 810 && event.x < 959 && event.y > 300 && event.y < 332)
        draughts.getAI().set_difficulty(Draughts::AI::normal);

    /// difficulty hard
    if(event.x > 840 && event.x < 936 && event.y > 340 && event.y < 371)
        draughts.getAI().set_difficulty(Draughts::AI::hard);

    /// alpha beta pruning on/off
    if(event.x > 780  && event.x < 1015 && event.y > 410 && event.y < 482)
        draughts.getAI().toggle_alpha_beta();
}

void Gui::gameOver()
{
    SDL_Color fontColor = {238, 126, 56};
    SDL_Surface* text = TTF_RenderText_Blended(font, "Game Over", fontColor);
    SDL_Rect textRect = {150, 280, text->w, text->h};
    SDL_BlitSurface(text, nullptr, surface, &textRect);
    SDL_FreeSurface(text);

    const char * str;
    if(draughts.isWhiteTurn()) str = "Black Wins";
    else str = "White Wins";
    SDL_Surface* text2 = TTF_RenderText_Blended(font, str, fontColor);
    SDL_Rect textRect2 = {150, 280+text->h, text2->w, text2->h};
    SDL_BlitSurface(text2, nullptr, surface, &textRect2);
    SDL_FreeSurface(text2);

    SDL_UpdateWindowSurface(window);
    gameStop= true;
}

void Gui::draw()
{
    SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, 255, 140, 140));

    /// board
    int x=0,y=0;
    bool dark=false;
    for(int i=0; i<8 ;i++)
    {
        for (int j = 0; j < 8; j++)
        {

            SDL_Rect imageRect = {x, y, 40, 40};

            if(dark) SDL_BlitSurface(br_dark_tile, nullptr, surface, &imageRect);
            else SDL_BlitSurface(br_light_tile, nullptr, surface, &imageRect);

            x += 90;
            dark=!dark;
        }
        dark=!dark;
        y+=90;
        x=0;
    }
    x=0; y=0;
    for(int i=0; i<8 ;i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if(draughts.get_board()[i][j] != nullptr)
            {
                drawFigure(x,y,draughts.get_board()[i][j]);
            }
            x+=90;
        }
        x=0;
        y+=90;
    }

    /// side
    SDL_Color fontColor = {0, 0, 0};
    SDL_Surface* text = TTF_RenderText_Blended(font_small, "Turn:", fontColor);
    SDL_Rect textRect = {780, 40, text->w, text->h};
    SDL_BlitSurface(text, nullptr, surface, &textRect);
    SDL_FreeSurface(text);

    SDL_Rect imageRect = {920, 20, 40, 40};
    if(draughts.isWhiteTurn()) SDL_BlitSurface(piece_w, nullptr, surface, &imageRect);
    else SDL_BlitSurface(piece_b, nullptr, surface, &imageRect);

    if(multiple_paths)
    {
        SDL_Surface* text = TTF_RenderText_Blended(font_small, "Multiple paths!", fontColor);
        SDL_Rect textRect = {740, 120, text->w, text->h};
        SDL_BlitSurface(text, nullptr, surface, &textRect);
        SDL_FreeSurface(text);
    }

    const char * str;
    if(draughts.isAIon()) str="AI: ON";
    else str = "AI: OFF";
    SDL_Surface* ai_on_text = TTF_RenderText_Blended(font_small, str, fontColor);
    SDL_Rect ai_on_textRect = {830, 200};
    SDL_BlitSurface(ai_on_text , nullptr, surface, &ai_on_textRect);
    SDL_FreeSurface(ai_on_text );

    if(draughts.isAIon())
    {
        SDL_Color fontColor_easy = {0, 0, 0};
        SDL_Color fontColor_normal = {0, 0, 0};
        SDL_Color fontColor_hard = {0, 0, 0};
        switch (draughts.getAI().get_difficulty()) {
            case Draughts::AI::easy:
                fontColor_easy = {255, 255, 255};
                break;

            case Draughts::AI::normal:
                fontColor_normal = {255, 255, 255};
                break;

            case Draughts::AI::hard:
                fontColor_hard = {255, 255, 255};
                break;
        }
        SDL_Surface *ai_dif_text = TTF_RenderText_Blended(font_small, "easy", fontColor_easy);
        SDL_Rect ai_dif_textRect = {840, 260};
        SDL_BlitSurface(ai_dif_text, nullptr, surface, &ai_dif_textRect);
        SDL_FreeSurface(ai_dif_text);

        ai_dif_text = TTF_RenderText_Blended(font_small, "normal", fontColor_normal);
        ai_dif_textRect = {810, 300};
        SDL_BlitSurface(ai_dif_text, nullptr, surface, &ai_dif_textRect);
        SDL_FreeSurface(ai_dif_text);

        ai_dif_text = TTF_RenderText_Blended(font_small, "hard", fontColor_hard);
        ai_dif_textRect = {840, 340};
        SDL_BlitSurface(ai_dif_text, nullptr, surface, &ai_dif_textRect);
        SDL_FreeSurface(ai_dif_text);


        str = "Alpha Beta";
        SDL_Surface *alpha_beta_on_text_1 = TTF_RenderText_Blended(font_small, str, fontColor);
        SDL_Rect alpha_beta_on_textRect_1 = {780, 410};
        SDL_BlitSurface(alpha_beta_on_text_1, nullptr, surface, &alpha_beta_on_textRect_1);
        SDL_FreeSurface(alpha_beta_on_text_1);

        if (draughts.getAI().is_alpha_beta_on()) str = "pruning: ON";
        else str = "pruning: OFF";
        SDL_Surface *alpha_beta_on_text_2 = TTF_RenderText_Blended(font_small, str, fontColor);
        SDL_Rect alpha_beta_on_textRect_2 = {770, 450};
        SDL_BlitSurface(alpha_beta_on_text_2, nullptr, surface, &alpha_beta_on_textRect_2);
        SDL_FreeSurface(alpha_beta_on_text_2);

    }

    SDL_Rect wc_Rect = {800, 650, 40, 40};
    SDL_BlitSurface(piece_w, nullptr, surface, &wc_Rect);
    SDL_Rect bc_Rect = {940, 650, 40, 40};
    SDL_BlitSurface(piece_b, nullptr, surface, &bc_Rect);
    if(draughts.isWhiteTurn()) SDL_BlitSurface(piece_w, nullptr, surface, &imageRect);
    else SDL_BlitSurface(piece_b, nullptr, surface, &imageRect);
    if(draughts.isWhiteTurn()) SDL_BlitSurface(piece_w, nullptr, surface, &imageRect);
    else SDL_BlitSurface(piece_b, nullptr, surface, &imageRect);
    SDL_Rect white_count = {800, 600, 40, 40};
    SDL_Rect black_count = {940, 600, 40, 40};
    std::string wc_str= std::to_string(draughts.getWhiteCount());
    std::string wb_str= std::to_string(draughts.getBlackCount());
    SDL_Surface* text_wc = TTF_RenderText_Blended(font_small, wc_str.c_str(), fontColor);
    SDL_Surface* text_bc = TTF_RenderText_Blended(font_small,  wb_str.c_str(), fontColor);
    SDL_BlitSurface(text_wc, nullptr, surface, &white_count);
    SDL_BlitSurface(text_bc, nullptr, surface, &black_count);
    SDL_FreeSurface(text_wc);
    SDL_FreeSurface(text_bc);



    SDL_UpdateWindowSurface(window);
}

void Gui::drawFigure(int x, int y, std::shared_ptr<FigureInterface> figure)
{


    if(!figure->isMother())
    {
        SDL_Rect pieceRect = {x+20, y+10, 40, 40};
        if (figure->get_col() == black)
            SDL_BlitSurface(piece_b, nullptr, surface, &pieceRect);
        else
            SDL_BlitSurface(piece_w, nullptr, surface, &pieceRect);
    }
    else
    {
        SDL_Rect pieceRect = {x+10, y+10, 40, 40};
        if (figure->get_col() == black)
            SDL_BlitSurface(queen_b, nullptr, surface, &pieceRect);
        else
            SDL_BlitSurface(queen_w, nullptr, surface, &pieceRect);
    }
}
