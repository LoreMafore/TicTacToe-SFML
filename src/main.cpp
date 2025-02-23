#include <SFML/Graphics.hpp>
#include "dialect.h"
#include "classes.h"
#include "algorithm"
#include "random"
#include <windows.h>



///TODO Start working on win cons
int win_condition(int (&array)[9], x_or_y player, results& outcome, float& player_score, float& bot_score) {
    int filled = 0;
    int bot_array_piece = (player == x_or_y::X) ? 2 : 1;
    int player_array_piece = (player == x_or_y::X) ? 1 : 2;

    int win_pos[8][3]
            {
                    {0, 1, 2},
                    {3, 4, 5},
                    {6, 7, 8},
                    {0, 3, 6},
                    {1, 4, 7},
                    {2, 5, 8},
                    {0, 4, 8},
                    {2, 4, 6}
            };

    for (int i = 0; i < 8; i++) {
        int bot_count = 0;
        int player_count = 0;

        for (int j = 0; j < 3; j++) {
            if (array[win_pos[i][j]] == bot_array_piece) {
                bot_count++;
            }
            if (array[win_pos[i][j]] == player_array_piece) {
                player_count++;
            }
        }

        if (bot_count == 3) {
            bot_count ++;
            outcome = LOSE;
            return 1;
        }
        if (player_count == 3) {
            player_count ++;
            outcome = WIN;
            return 1;
        }
    }

    // Count filled positions separately to avoid overcounting
    for (int i = 0; i < 9; i++) {
        if (array[i] != 0) {
            filled++;
        }
    }

    if (filled == 9) {
        outcome = DRAW;
        player_score += 0.5;
        bot_score += 0.5;
        return 1;
    }


    return 0;

}



int bot_move(int (&array)[9], x_or_y player,const std::vector<sf::Sprite*>& x_sprites, const std::vector<sf::Sprite*>& y_sprites,
             std::vector<button_Maker> buttons, int& counter, bool& players_turn) {
    std::srand(std::time(nullptr));
    int random_number = 0;
    auto &bot_piece = (player == x_or_y::X) ? y_sprites : x_sprites;
    int bot_array_piece = (player == x_or_y::X) ? 2 : 1;
    int player_array_piece = (player == x_or_y::X) ? 1 : 2;

    int win_pos[8][3]
            {
                    {0, 1, 2},
                    {3, 4, 5},
                    {6, 7, 8},
                    {0, 3, 6},
                    {1, 4, 7},
                    {2, 5, 8},
                    {0, 4, 8},
                    {2, 4, 6}
            };


    for (int i = 0; i < 8; i++) {
        int count = 0;
        int player_count = 0;
        int empty_array = -1;
        v2i empty_array_pos = v2i(0, 0);

        for (int j = 0; j < 3; j++) {
            if (array[win_pos[i][j]] == bot_array_piece) {
                count++;
            } else if (array[win_pos[i][j]] == player_array_piece) {
                player_count++;
            } else if (array[win_pos[i][j]] == 0) {
                empty_array = j;
                empty_array_pos = v2i(i, j);
            }
        }

        if (count == 2 && empty_array != -1 || player_count == 2 && empty_array != -1) {
            int pos = win_pos[empty_array_pos.x][empty_array_pos.y];
            array[win_pos[empty_array_pos.x][empty_array_pos.y]] = bot_array_piece;
            bot_piece[counter]->setPosition(v2f(buttons.at(pos).rect.getPosition().x, buttons.at(pos).rect.getPosition().y ));
            counter += 1;
            players_turn = true;
            return 1;
        }

    }

        if (array[4] == 0)
        {
            array[4] = bot_array_piece;
            bot_piece[counter]->setPosition(v2f(buttons.at(4).rect.getPosition().x, buttons.at(4).rect.getPosition().y));
            counter += 1;
            players_turn = true;
            return 1;
        }

    std::vector<int> corners = {0, 2, 6, 8};
    std::shuffle(corners.begin(), corners.end(), std::mt19937(std::random_device()()));

    for (int pos : corners) {
        if (array[pos] == 0) {
            array[pos] = bot_array_piece;
            bot_piece[counter]->setPosition(v2f(buttons[pos].rect.getPosition().x, buttons[pos].rect.getPosition().y));
            counter++;
            players_turn = true;
            return 1;
        }
    }

    // **Take a Random Edge**
    std::vector<int> edges = {1, 3, 5, 7};
    std::shuffle(edges.begin(), edges.end(), std::mt19937(std::random_device()()));

    for (int pos : edges) {
        if (array[pos] == 0) {
            array[pos] = bot_array_piece;
            bot_piece[counter]->setPosition(v2f(buttons[pos].rect.getPosition().x, buttons[pos].rect.getPosition().y));
            counter++;
            players_turn = true;
            return 1;
        }
    }

    return 0;
}


bool players_move(x_or_y player, std::vector<sf::Sprite*> x_sprites, std::vector<sf::Sprite*> y_sprites,
                  int (&array)[9], bool& players_turn, std::vector<button_Maker> buttons, const v2i mouse_pos,
                  int& counter, sf::RenderWindow& window, bool& picked_char){

    auto &chosen_piece = (player == x_or_y::X) ? x_sprites : y_sprites;
    int chosen_array_piece = (player == x_or_y::X) ? 1 : 2;
    for (int i = 0; i < buttons.size(); i++) {

        //printf("\n\n%d\n\n", array[i]);

        if (buttons[i].mouse_On_Button(mouse_pos) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && picked_char == true) {
            


            if (array[i] == 0)
            {

                printf("\narray[%d]: %d", i, array[i]);
                //printf("\nbuttons_rect[%d]: %f , %F", i, button_rects[i].getPosition().x, button_rects[i].getPosition().y);
                array[i] = chosen_array_piece;
                //chosen_piece[counter]->setPosition(v2f(buttons.at(i).circ.getPosition().x-15, buttons.at(i).circ.getPosition().y-15));
                chosen_piece[counter]->setPosition(v2f(buttons.at(i).rect.getPosition().x, buttons.at(i).rect.getPosition().y));
                //chosen_piece[counter]->setPosition(v2f(buttons.at(i).circ.getPosition().x, button_rects.at(i).getPosition().y));

                counter += 1;
                players_turn = false;
                return true;
            }

        }

    }
    return false;
}

int draw_square(int posX, int posY, std::vector<button_Maker>& button_list)
{
    for(int button = 0; button < button_list.size(); button++)
    {
        button_list[button].rect.setPosition(v2f(posX, posY));
        if((button + 1)%3 ==0)
        {
            posX = 310;
            posY += 105;
        }

        else
        {
            posX += 105;
        }
        button_list[button].circ.setOrigin(v2f(button_list[button].circ.getRadius(), button_list[button].circ.getRadius()));
        button_list[button].circ.setPosition(v2f(button_list[button].rect.getPosition().x + button_list[button].rect.getSize().x/2, button_list[button].rect.getPosition().y + button_list[button].rect.getSize().y/2));
        button_list[button].set_button_style(sf::Color(192,192,192), 1, sf::Color::Black);

    }
    return 1;
}

void scene_starting_player(sf::RenderWindow& window, button_Maker& yes, button_Maker& no, x_or_y& player,
                          const std::vector<sf::Text>& text_list, const sprite_maker& background_sprite,
                          bool& picked_character, bool& draw_once, bool& players_turn, v2i& mouse_pos)
{
    mouse_pos = sf::Mouse::getPosition(window);
    if (draw_once == true)
    {
        yes.rect.setPosition(v2f(200,340));
        no.rect.setPosition(v2f(520,340));
        draw_once = false;
    }

    window.clear();
    window.draw(background_sprite.sprite);
    yes.bM_draw(window);
    no.bM_draw(window);

    yes.mouse_on_button_rect_change(mouse_pos, sf::Color(160,160,160), 3, sf::Color(192,192,192),
                                    sf::Color(192,192,192), 3, sf::Color(160,160,160));
    no.mouse_on_button_rect_change(mouse_pos, sf::Color(160,160,160), 3, sf::Color(192,192,192),
                                   sf::Color(192,192,192), 3, sf::Color(160,160,160));

    for(auto& i : text_list)
    {
        window.draw(i);
    }

    if(yes.mouse_On_Button(mouse_pos) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && picked_character == false)
    {
        player = X;
        picked_character = true;
        yes.rect.setPosition(v2f(1000,1000));
        no.rect.setPosition(v2f(1000,1000));
        draw_once = true;
    }

    if(no.mouse_On_Button(mouse_pos) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && picked_character == false)
    {
        player = Y;
        picked_character = true;
        players_turn = false;
        yes.rect.setPosition(v2f(1000,1000));
        no.rect.setPosition(v2f(1000,1000));
        draw_once = true;
    }

    window.display();
}

void scene_gameOver()
{

}


int words(sf::Text& txt, int size, const std::string& string ,sf::Color fill, int thick,sf::Color outer, v2f pos)
{
    txt.setCharacterSize(size);
    txt.setString(string);
    txt.setFillColor(fill);
    txt.setOutlineThickness(thick);
    txt.setOutlineColor(outer);
    txt.setPosition(v2f(pos));

    return 1;
}

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({940u, 580u}), "CMake SFML Project");
    window.setFramerateLimit(144);

    sf::Texture x_texture;
    sf::Texture o_texture;
    sf::Texture back_ground_texture;

    const sf::Font font("C:/Users/momer/Umary/CSC204/MidTerm/assets/fonts/PixelOperator8.ttf");
    sf::Text yes_text(font);
    sf::Text no_text(font);
    sf::Text question_text(font);
    sf::Text title_text(font);
    sf::Text description_1_text(font);
    sf::Text description_2_text(font);
    sf::Text description_3_text(font);
    sf::Text score_text(font);

    words(title_text,50,"Tic Tac Toe",sf::Color(255,255,255),2,sf::Color(96,96,96), v2f(245,50));
    words(question_text,25,"Would you like to do first?",sf::Color(255,255,255),2,sf::Color(96,96,96),v2f(210,250));

    back_ground_texture.loadFromFile("C:/Users/momer/Umary/CSC204/MidTerm/assets/background.png");
    x_texture.loadFromFile("C:/Users/momer/Umary/CSC204/MidTerm/assets/X1.png");
    o_texture.loadFromFile("C:/Users/momer/Umary/CSC204/MidTerm/assets/O1.png");
    sf::Sprite* x_piece_sprite = new sf::Sprite(x_texture);
    sf::Sprite* x_piece_sprite1 = new sf::Sprite(x_texture);
    sf::Sprite* x_piece_sprite2 = new sf::Sprite(x_texture);
    sf::Sprite* x_piece_sprite3 = new sf::Sprite(x_texture);
    sf::Sprite* x_piece_sprite4 = new sf::Sprite(x_texture);
    sf::Sprite* o_piece_sprite = new sf::Sprite(o_texture);
    sf::Sprite* o_piece_sprite1 = new sf::Sprite(o_texture);
    sf::Sprite* o_piece_sprite2 = new sf::Sprite(o_texture);
    sf::Sprite* o_piece_sprite3 = new sf::Sprite(o_texture);
    sf::Sprite* o_piece_sprite4 = new sf::Sprite(o_texture);


    sprite_maker background_sprite("C:/Users/momer/Umary/CSC204/MidTerm/assets/background.png", v2f(1,1),v2f(0,0));

    std::vector<sf::Sprite*> x_list {x_piece_sprite, x_piece_sprite1,x_piece_sprite2,x_piece_sprite3,x_piece_sprite4};
    std::vector<sf::Sprite*> o_list {o_piece_sprite, o_piece_sprite1, o_piece_sprite2, o_piece_sprite3, o_piece_sprite4};
    for(auto &i : x_list)
    {
        //i->setScale(v2f(.1,.1));
        i->setPosition(v2f(1000,1000));
    }
    for(auto &i : o_list)
    {
        //i->setScale(v2f(.5,.5));
        i->setPosition(v2f(1000,1000));
    }


    v2i mouse_pos = sf::Mouse::getPosition(window);
    button_Maker top_left(v2f(100, 100),  7.5);
    button_Maker top_middle(v2f(100, 100), 7.5);
    button_Maker top_right(v2f(100, 100),  7.5);
    button_Maker mid_l(v2f(100,100), 7.5);
    button_Maker mid_m(v2f(100,100), 7.5);
    button_Maker mid_r(v2f(100,100), 7.5);
    button_Maker bottom_l(v2f(100,100), 7.5);
    button_Maker bottom_m(v2f(100,100), 7.5);
    button_Maker bottom_r(v2f(100,100), 7.5);

    button_Maker yes(v2f(200, 100), 7.5);
    button_Maker no(v2f(200, 100), 7.5);

    std::vector<button_Maker> button_list {top_left, top_middle, top_right,
                                           mid_l,    mid_m,      mid_r,
                                           bottom_l, bottom_m,   bottom_r};



    yes.circ.setPosition(v2f(1000, 1000));
    yes.rect.setPosition(v2f(200, 340));
    yes.set_button_style(sf::Color(192,192,192), 3, sf::Color(160,160,160));
    no.circ.setPosition(v2f(1000,1000));
    no.rect.setPosition(v2f(520, 340));
    no.set_button_style(sf::Color(192,192,192), 3, sf::Color(160,160,160));

    words(yes_text,50, "Yes",sf::Color(255,255,255),2,sf::Color(96,96,96),
          v2f(yes.rect.getPosition().x + yes.rect.getSize().x/2 -65, yes.rect.getPosition().y + yes.rect.getSize().y/2 -30));

    words(no_text,50,"No",sf::Color(255,255,255),2,sf::Color(96,96,96),
          v2f(no.rect.getPosition().x + no.rect.getSize().x/2 -40, no.rect.getPosition().y + no.rect.getSize().y/2 -30));

    std::vector<sf::Text> text_starting_player{yes_text, no_text, title_text, question_text};

    bool picked_character = false;
    bool players_turn = true;
    bool draw_once = true;
    int counter =0;
    int bot_counter =0;
    int posX = 310;
    int posY = 160;
    float player_score = 0;
    float bot_score = 0;

    std::ostringstream stream;
    stream << std::fixed << std::setprecision(1);
    stream << "BOT: " << bot_score << "\n\nPlayer: " << player_score;
    std::string score_text_paste = stream.str();

    int board[9] {0};

    results outcomes = IDK;
    x_or_y player = X;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            {
                window.close();
            }


        }
        if (picked_character == false)
        {

            scene_starting_player(window,yes,no,player,text_starting_player,background_sprite,picked_character,draw_once,players_turn,mouse_pos);

        }

        if (picked_character == true && outcomes == IDK)
        {
            if (draw_once == true)
            {
                Sleep(100);
                draw_square(posX,posY, button_list);
                draw_once = false;
            }

            mouse_pos = sf::Mouse::getPosition(window);
            window.clear();
            window.draw(background_sprite.sprite);
            words(score_text,25, "SCORE",sf::Color(255,255,255),2,sf::Color(96,96,96),v2f(85,225));
            words(description_1_text,15, score_text_paste,sf::Color(255,255,255),2,sf::Color(96,96,96),v2f(55,275));
            for(auto& button : button_list)
            {
                button.bM_draw(window);
            }

            for(auto& sprite: x_list )
            {
                window.draw(*sprite);
            }

            for(auto& sprite: o_list )
            {
                window.draw(*sprite);
            }

            window.draw(title_text);
            window.draw(score_text);
            window.draw(description_1_text);


            window.display();
            if(players_turn == true)
            {

                for (auto& buttons : button_list)
                {
                    buttons.mouse_on_button_circ_change(mouse_pos, sf::Color::White, 2.5, sf::Color::White,
                                                        sf::Color::Transparent, 2.5, sf::Color::White);
                }

                players_move(player, x_list, o_list, board, players_turn, button_list, mouse_pos, counter, window, picked_character);
            }

            else
            {
                bot_move(board,player,x_list,o_list,button_list, bot_counter,players_turn);
            }

            win_condition(board, player, outcomes, player_score, bot_score);

            if(outcomes != IDK)
            {
//                int x = 1000;
//                int y = 1000;
//                draw_square(x,y,button_list);
                draw_once = true;
            }

        }

        if (outcomes == WIN || outcomes == LOSE || outcomes == DRAW)
        {
            if (draw_once == true)
            {
                stream << std::fixed << std::setprecision(1);
                stream << "BOT: " << bot_score << "\n\nPlayer: " << player_score;
                std::string score_text_paste = stream.str();
                draw_once = false;
            }

            mouse_pos = sf::Mouse::getPosition(window);
            yes.rect.setPosition(v2f(675, 260));
            no.rect.setPosition(v2f(800, 260));
            yes.rect.setSize(v2f(100,50));
            no.rect.setSize(v2f(100,50));

            words(question_text,12,"Would you like to play again?",sf::Color(255,255,255),2,sf::Color(96,96,96),v2f(650,225));

            words(yes_text,25, "Yes",sf::Color(255,255,255),2,sf::Color(96,96,96),
                  v2f(yes.rect.getPosition().x + yes.rect.getSize().x/2 -65, yes.rect.getPosition().y + yes.rect.getSize().y/2 -30));

            words(no_text,25,"No",sf::Color(255,255,255),2,sf::Color(96,96,96),
                  v2f(no.rect.getPosition().x + no.rect.getSize().x/2 -40, no.rect.getPosition().y + no.rect.getSize().y/2 -30));

            words(score_text,25, "SCORE",sf::Color(255,255,255),2,sf::Color(96,96,96),v2f(85,225));
            words(description_1_text,15, score_text_paste,sf::Color(255,255,255),2,sf::Color(96,96,96),v2f(55,275));

            window.clear();
            window.draw(background_sprite.sprite);

            for(auto& button : button_list)
            {
                button.bM_draw(window);
            }

            for(auto& sprite: x_list )
            {
                window.draw(*sprite);
            }

            for(auto& sprite: o_list )
            {
                window.draw(*sprite);
            }

            yes.bM_draw(window);
            no.bM_draw(window);

            yes.mouse_on_button_rect_change(mouse_pos, sf::Color(160,160,160), 3, sf::Color(192,192,192),
                                            sf::Color(192,192,192), 3, sf::Color(160,160,160));
            no.mouse_on_button_rect_change(mouse_pos, sf::Color(160,160,160), 3, sf::Color(192,192,192),
                                           sf::Color(192,192,192), 3, sf::Color(160,160,160));

            window.draw(yes_text);
            window.draw(no_text);
            window.draw(title_text);
            window.draw(question_text);
            window.draw(score_text);
            window.draw(description_1_text);
            if(yes.mouse_On_Button(mouse_pos) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && picked_character == true)
            {

                

            }

            if(no.mouse_On_Button(mouse_pos) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && picked_character == true)
            {
                

                window.close();
                exit(0);
            }

            window.display();
        }

    }
}
