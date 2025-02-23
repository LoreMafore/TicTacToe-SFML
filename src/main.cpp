#include <SFML/Graphics.hpp>
#include "dialect.h"
#include "classes.h"
#include "algorithm"
#include "random"
#include <windows.h>



int win_condition(int (&array)[9], x_or_y player, results& outcome, float& player_score, float& bot_score) {

    int filled = 0;
    //keeps track of what piece the player and bot are
    int bot_array_piece = (player == x_or_y::X) ? 2 : 1;
    int player_array_piece = (player == x_or_y::X) ? 1 : 2;

    //winning positions
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
    //checks for win
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
            outcome = LOSE;
            return 1;
        }
        if (player_count == 3) {
            outcome = WIN;
            return 1;
        }
    }

    for (int i = 0; i < 9; i++) {
        if (array[i] != 0) {
            filled++;
        }
    }

    if (filled == 9) {
        outcome = DRAW;
        return 1;
    }


    return 0;

}



int bot_move(int (&array)[9], x_or_y player,const std::vector<sf::Sprite*>& x_sprites, const std::vector<sf::Sprite*>& o_sprites,
             std::vector<button_Maker> buttons, int& counter, bool& players_turn){
    //allows random number
    std::srand(std::time(nullptr));
    int random_number = 0;
    //assigns a piece to the bot
    auto &bot_piece = (player == x_or_y::X) ?o_sprites : x_sprites;
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
//checks if player or bot can win
        if (count == 2 && empty_array != -1 || player_count == 2 && empty_array != -1) {
            int pos = win_pos[empty_array_pos.x][empty_array_pos.y];
            array[win_pos[empty_array_pos.x][empty_array_pos.y]] = bot_array_piece;
            bot_piece[counter]->setPosition(v2f(buttons.at(pos).rect.getPosition().x, buttons.at(pos).rect.getPosition().y ));
            counter += 1;
            players_turn = true;
            return 1;
        }

    }
    //place in center
        if (array[4] == 0)
        {
            array[4] = bot_array_piece;
            bot_piece[counter]->setPosition(v2f(buttons.at(4).rect.getPosition().x, buttons.at(4).rect.getPosition().y));
            counter += 1;
            players_turn = true;
            return 1;
        }

    // place at a random corner
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

    // place at a random edge
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


bool players_move(x_or_y player, std::vector<sf::Sprite*> x_sprites, std::vector<sf::Sprite*> 
o_sprites,
                  int (&array)[9], bool& players_turn, std::vector<button_Maker> buttons, const v2i mouse_pos,
                  int& counter, sf::RenderWindow& window, bool& picked_char){

    auto &chosen_piece = (player == x_or_y::X) ? x_sprites : o_sprites;
    int chosen_array_piece = (player == x_or_y::X) ? 1 : 2;
    for (int i = 0; i < buttons.size(); i++) {

        //player input
        if (buttons[i].mouse_On_Button(mouse_pos) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && picked_char == true) {
            
            if (array[i] == 0)
            {

                printf("\narray[%d]: %d", i, array[i]);
                array[i] = chosen_array_piece;
                chosen_piece[counter]->setPosition(v2f(buttons.at(i).rect.getPosition().x, buttons.at(i).rect.getPosition().y));

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
    //draws the grid
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

int words(sf::Text& txt, int size, const std::string& string ,sf::Color fill, int thick,sf::Color outer, v2f pos)
{
    //makes text easily
    txt.setCharacterSize(size);
    txt.setString(string);
    txt.setFillColor(fill);
    txt.setOutlineThickness(thick);
    txt.setOutlineColor(outer);
    txt.setPosition(v2f(pos));

    return 1;
}

void scene_starting_player(sf::RenderWindow& window, button_Maker& yes, button_Maker& no, x_or_y& player,
                           std::vector<sf::Text>& text_list, const sprite_maker& background_sprite,
                          bool& picked_character, bool& draw_once, bool& players_turn, v2i& mouse_pos)
{
    // starting scene after rules
    mouse_pos = sf::Mouse::getPosition(window);
    if (draw_once == true)
    {
        //sets positions for buttons and well as initializes text
        yes.rect.setPosition(v2f(200,340));
        no.rect.setPosition(v2f(520,340));
        yes.circ.setPosition(v2f(1000, 1000));
        yes.rect.setSize(v2f(200,100));
        no.circ.setPosition(v2f(1000,1000));
        no.rect.setSize(v2f(200,100));

        words(text_list[0],50, "Yes",sf::Color(255,255,255),2,sf::Color(96,96,96),
              v2f(yes.rect.getPosition().x + yes.rect.getSize().x/2 -65, yes.rect.getPosition().y + yes.rect.getSize().y/2 -30));

        words(text_list[1],50,"No",sf::Color(255,255,255),2,sf::Color(96,96,96),
              v2f(no.rect.getPosition().x + no.rect.getSize().x/2 -40, no.rect.getPosition().y + no.rect.getSize().y/2 -30));

        words(text_list[3],25,"Would you like to go first?",sf::Color(255,255,255),2,sf::Color(96,96,96),v2f(210,250));


        draw_once = false;
    }

    window.clear();
    //draws everything needed
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

    //determines pieces and moves buttons off screen

    if(yes.mouse_On_Button(mouse_pos) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && picked_character == false)
    {
        player = X;
        picked_character = true;
        players_turn = true;
        yes.rect.setPosition(v2f(1000,1000));
        no.rect.setPosition(v2f(1000,1000));
        draw_once = true;
    }

    if(no.mouse_On_Button(mouse_pos) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && picked_character == false)
    {
        player = O;
        picked_character = true;
        players_turn = false;
        yes.rect.setPosition(v2f(1000,1000));
        no.rect.setPosition(v2f(1000,1000));
        draw_once = true;
    }

    window.display();
}

void reset_game(int (&array)[9], x_or_y& player, results& outcomes,
                std::vector<sf::Sprite*>& x_sprites, std::vector<sf::Sprite*>&o_sprites,
                bool& player_turn, bool& picked_char, bool& draw_once,
                int& bot_counter, int& player_counter)
{
    //resets game so that it can be played multiple times
    for(int i = 0; i < 9; i++)
    {
        array[i] = 0;
    }

    for(auto &i : x_sprites)
    {
        i->setPosition(v2f(1000,1000));
    }
    for(auto &i : o_sprites)
    {
        i->setPosition(v2f(1000,1000));
    }
    player = SetUp;
    outcomes = IDK;
    player_turn = false;
    picked_char = false;
    draw_once = true;
    player_counter = 0;
    bot_counter = 0;
}

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({940u, 580u}), "CMake SFML Project");
    window.setFramerateLimit(144);

    //initializes textures, text, sprites, font, and rect
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

    back_ground_texture.loadFromFile("C:/Users/momer/Umary/CSC204/MidTerm/assets/background.png");
    x_texture.loadFromFile("C:/Users/momer/Umary/CSC204/MidTerm/assets/X1.png");
    o_texture.loadFromFile("C:/Users/momer/Umary/CSC204/MidTerm/assets/O4.png");
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
    sf::RectangleShape board_rect;
    board_rect.setSize(v2f(315, 315));
    board_rect.setPosition(v2f(310,160));
    board_rect.setFillColor(sf::Color(96,96,96));

    //vectors of sprites to be used later
    std::vector<sf::Sprite*> x_list {x_piece_sprite, x_piece_sprite1,x_piece_sprite2,x_piece_sprite3,x_piece_sprite4};
    std::vector<sf::Sprite*> o_list {o_piece_sprite, o_piece_sprite1, o_piece_sprite2, o_piece_sprite3, o_piece_sprite4};
    //sets all the positions of the sprites
    for(auto &i : x_list)
    {
        i->setPosition(v2f(1000,1000));
    }
    for(auto &i : o_list)
    {
        i->setPosition(v2f(1000,1000));
    }

    //initializes mouse
    v2i mouse_pos = sf::Mouse::getPosition(window);
    //initializes the grid and buttons
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

    //vector of button_Maker to be used later
    std::vector<button_Maker> button_list {top_left, top_middle, top_right,
                                           mid_l,    mid_m,      mid_r,
                                           bottom_l, bottom_m,   bottom_r};


    //stylize yes and no buttons
    yes.set_button_style(sf::Color(192,192,192), 3, sf::Color(160,160,160));
    no.set_button_style(sf::Color(192,192,192), 3, sf::Color(160,160,160));

    //vector of text to be used later
    std::vector<sf::Text> text_starting_player{yes_text, no_text, title_text, question_text};
    std::vector<sf::Text> text_game_over{yes_text, no_text,title_text,question_text,score_text,description_1_text};

    //initializes variables
    bool game_start = false;
    bool picked_character = false;
    bool players_turn = true;
    bool draw_once = true;
    bool rules = false;
    int counter =0;
    int bot_counter =0;
    int posX = 310;
    int posY = 160;
    float player_score = 0;
    float bot_score = 0;
    int board[9] {0};
    std::string game_over_str;

    std::ostringstream stream;
    stream << std::fixed << std::setprecision(1);
    stream << "BOT: " << bot_score << "\n\nPlayer: " << player_score;
    std::string score_text_paste = stream.str();

    //initializes ENUM
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
            //escape closes window
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            {
                window.close();
            }


        }

        //starting screen
        if(game_start == false && rules == false)
        {

            mouse_pos = sf::Mouse::getPosition(window);
            if (draw_once == true)
            {
                yes.rect.setPosition(v2f(200,340));
                yes.circ.setPosition(v2f(1000, 1000));
                yes.rect.setSize(v2f(200,100));
                no.rect.setPosition(v2f(520,340));
                no.circ.setPosition(v2f(1000,1000));
                no.rect.setSize(v2f(200,100));

                words(yes_text,45, "Start",sf::Color(255,255,255),2,sf::Color(96,96,96),
                      v2f(yes.rect.getPosition().x + yes.rect.getSize().x/2 -90, yes.rect.getPosition().y + yes.rect.getSize().y/2 -30));

                words(no_text,45,"Quit",sf::Color(255,255,255),2,sf::Color(96,96,96),
                      v2f(no.rect.getPosition().x + no.rect.getSize().x/2 -75, no.rect.getPosition().y + no.rect.getSize().y/2 -30));

                draw_once = false;
            }

            window.clear();
            window.draw(background_sprite.sprite);
            yes.mouse_on_button_rect_change(mouse_pos, sf::Color(160,160,160), 3, sf::Color(192,192,192),
                                            sf::Color(192,192,192), 3, sf::Color(160,160,160));
            no.mouse_on_button_rect_change(mouse_pos, sf::Color(160,160,160), 3, sf::Color(192,192,192),
                                           sf::Color(192,192,192), 3, sf::Color(160,160,160));
            yes.bM_draw(window);
            no.bM_draw(window);
            window.draw(title_text);
            window.draw(yes_text);
            window.draw(no_text);
            window.display();

            if(yes.mouse_On_Button(mouse_pos) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && game_start == false)
            {
                yes.rect.setPosition(v2f(1000,1000));
                no.rect.setPosition(v2f(1000,1000));
                draw_once = true;
                rules = true;
                //so that the mouse doesnt activate a button that will be loaded in
                Sleep(100);
            }

            if(no.mouse_On_Button(mouse_pos) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && game_start == false)
            {

                window.close();
                exit(0);
            }

        }

        //rules screen
        if(rules == true)
        {
            mouse_pos = sf::Mouse::getPosition(window);
            if (draw_once == true)
            {
                no.rect.setPosition(v2f(370,480));
                no.circ.setPosition(v2f(1000,1000));
                no.rect.setSize(v2f(200,75));

                words(description_1_text,15, "Tic Tack Toe is played against two players(you and a bot)\n\nOne player uses the X symbol, and the other uses the O symbol.\n\nPlayers alternate turns.",
                      sf::Color(255,255,255),2,sf::Color(96,96,96),
                      v2f(75,150));

                words(description_2_text,15,"You can interact with the game by clicking on the grid cells.\n\nWhen it is their turn, a player clicks on an empty cell in the \n\n3x3 grid to place their symbol",
                      sf::Color(255,255,255),2,sf::Color(96,96,96),
                      v2f(75,275));

                words(description_3_text,15,"The game ends when a player wins, the grid is full (tie), or \n\nthe Escape key is pressed to quit.",
                      sf::Color(255,255,255),2,sf::Color(96,96,96),
                      v2f(75,400));

                words(no_text,50,"OK!",sf::Color(255,255,255),2,sf::Color(96,96,96),
                      v2f(no.rect.getPosition().x + no.rect.getSize().x/2 -55, no.rect.getPosition().y + no.rect.getSize().y/2 -30));
                draw_once = false;
            }

            window.clear();
            window.draw(background_sprite.sprite);
            yes.mouse_on_button_rect_change(mouse_pos, sf::Color(160,160,160), 3, sf::Color(192,192,192),
                                            sf::Color(192,192,192), 3, sf::Color(160,160,160));
            no.mouse_on_button_rect_change(mouse_pos, sf::Color(160,160,160), 3, sf::Color(192,192,192),
                                           sf::Color(192,192,192), 3, sf::Color(160,160,160));
            yes.bM_draw(window);
            no.bM_draw(window);
            window.draw(title_text);
            window.draw(no_text);
            window.draw(description_1_text);
            window.draw(description_2_text);
            window.draw(description_3_text);
            window.display();



            if(no.mouse_On_Button(mouse_pos) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && rules == true)
            {
                no.rect.setPosition(v2f(1000,1000));
                draw_once = true;
                rules = false;
                game_start = true;
                Sleep(100);
            }
        }


        if (game_start == true) {
            //choosing character screen
            if (picked_character == false) {

                scene_starting_player(window, yes, no, player, text_starting_player, background_sprite,
                                      picked_character, draw_once, players_turn, mouse_pos);

            }

            //game screen
            if (picked_character == true && outcomes == IDK) {
                if (draw_once == true) {
                    Sleep(100);
                    draw_square(posX, posY, button_list);
                    draw_once = false;
                    words(score_text, 25, "SCORE", sf::Color(255, 255, 255), 2, sf::Color(96, 96, 96), v2f(85, 225));
                    words(description_1_text, 15, score_text_paste, sf::Color(255, 255, 255), 2, sf::Color(96, 96, 96),
                          v2f(55, 275));
                }

                mouse_pos = sf::Mouse::getPosition(window);
                window.clear();

                window.draw(background_sprite.sprite);
                window.draw(board_rect);
                for (auto &button: button_list) {
                    button.bM_draw(window);
                }

                for (auto &sprite: x_list) {
                    window.draw(*sprite);
                }

                for (auto &sprite: o_list) {
                    window.draw(*sprite);
                }

                window.draw(title_text);
                window.draw(score_text);
                window.draw(description_1_text);


                window.display();
                if (players_turn == true) {

                    for (auto &buttons: button_list) {
                        buttons.mouse_on_button_circ_change(mouse_pos, sf::Color::White, 2.5, sf::Color::White,
                                                            sf::Color::Transparent, 2.5, sf::Color::White);
                    }

                    players_move(player, x_list, o_list, board, players_turn, button_list, mouse_pos, counter, window,
                                 picked_character);
                } else {
                    bot_move(board, player, x_list, o_list, button_list, bot_counter, players_turn);
                }

                win_condition(board, player, outcomes, player_score, bot_score);

                if (outcomes != IDK) {
                    draw_once = true;
                }

            }
            //game over screen
            if (outcomes == WIN || outcomes == LOSE || outcomes == DRAW) {
                mouse_pos = sf::Mouse::getPosition(window);
                if (draw_once == true) {

                    yes.rect.setPosition(v2f(675, 260));
                    yes.rect.setSize(v2f(100, 50));
                    no.rect.setPosition(v2f(800, 260));
                    no.rect.setSize(v2f(100, 50));

                    if (outcomes == WIN) {
                        player_score++;
                        game_over_str = "You Won! :)";

                    } else if (outcomes == LOSE) {
                        bot_score++;
                        game_over_str = "You Lost :(";
                    } else if (outcomes == DRAW) {
                        player_score += 0.5;
                        bot_score += 0.5;
                        game_over_str = "It's a Draw! :|";
                    }
                    stream.str(""); // Clear the previous contents
                    stream.clear();
                    stream << "BOT: " << bot_score << "\n\nPlayer: " << player_score;
                    score_text_paste = stream.str();

                    words(question_text, 25, game_over_str, sf::Color(255, 255, 255), 2, sf::Color(96, 96, 96),
                          v2f(650, 125));
                    words(question_text, 12, "Would you like to play again?", sf::Color(255, 255, 255), 2,
                          sf::Color(96, 96, 96), v2f(650, 225));

                    words(yes_text, 25, "Yes", sf::Color(255, 255, 255), 2, sf::Color(96, 96, 96),
                          v2f(yes.rect.getPosition().x + yes.rect.getSize().x / 2 - 35,
                              yes.rect.getPosition().y + yes.rect.getSize().y / 2 - 15));

                    words(no_text, 25, "No", sf::Color(255, 255, 255), 2, sf::Color(96, 96, 96),
                          v2f(no.rect.getPosition().x + no.rect.getSize().x / 2 - 20,
                              no.rect.getPosition().y + no.rect.getSize().y / 2 - 15));

                    words(score_text, 25, "SCORE", sf::Color(255, 255, 255), 2, sf::Color(96, 96, 96), v2f(85, 225));
                    words(description_1_text, 15, score_text_paste, sf::Color(255, 255, 255), 2, sf::Color(96, 96, 96),
                          v2f(55, 275));


                    draw_once = false;
                }

                window.clear();
                window.draw(background_sprite.sprite);
                window.draw(board_rect);

                for (auto &button: button_list) {
                    button.bM_draw(window);
                }

                for (auto &sprite: x_list) {
                    window.draw(*sprite);
                }

                for (auto &sprite: o_list) {
                    window.draw(*sprite);
                }

                yes.bM_draw(window);
                no.bM_draw(window);

                yes.mouse_on_button_rect_change(mouse_pos, sf::Color(160, 160, 160), 3, sf::Color(192, 192, 192),
                                                sf::Color(192, 192, 192), 3, sf::Color(160, 160, 160));
                no.mouse_on_button_rect_change(mouse_pos, sf::Color(160, 160, 160), 3, sf::Color(192, 192, 192),
                                               sf::Color(192, 192, 192), 3, sf::Color(160, 160, 160));


                window.draw(yes_text);
                window.draw(no_text);
                window.draw(title_text);
                window.draw(question_text);
                window.draw(score_text);
                window.draw(description_1_text);

                if (yes.mouse_On_Button(mouse_pos) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) &&
                    picked_character == true) {
                    //reset game
                    reset_game(board, player, outcomes, x_list, o_list, players_turn, picked_character, draw_once,
                               bot_counter, counter);
                }

                if (no.mouse_On_Button(mouse_pos) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) &&
                    picked_character == true) {
                    window.close();
                    exit(0);
                }

                window.display();
            }
        }

    }
}
