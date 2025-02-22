#include <SFML/Graphics.hpp>
#include "dialect.h"


int win_condition(std::vector<int> array)
{
    int x_win = false;
    int win_pos[8][3]
            {
                    {array[0],array[1],array[2]},
                    {array[3],array[4],array[5]},
                    {array[6],array[7],array[8]},
                    {array[0],array[3],array[6]},
                    {array[1],array[4],array[7]},
                    {array[2],array[5],array[8]},
                    {array[0],array[4],array[8]},
                    {array[2],array[4],array[6]}
            };
    for(int i = 0; i < 9; i++)
    {
        if (win_pos[i][0] == win_pos[i][1] == win_pos[i][2] == 1)
        {
            return x_win = 1;
        }

        else if (win_pos[i][0] == win_pos[i][1] == win_pos[i][2] == 2)
        {
            return x_win = 2;
        }

        else
        {
            return 0;
        }

    }
}

///TODO Start working on bot_move
int bot_move(std::vector<int> array, int player)
{
    int win_pos[8][3]
            {
                    {array[0],array[1],array[2]},
                    {array[3],array[4],array[5]},
                    {array[6],array[7],array[8]},
                    {array[0],array[3],array[6]},
                    {array[1],array[4],array[7]},
                    {array[2],array[5],array[8]},
                    {array[0],array[4],array[8]},
                    {array[2],array[4],array[6]}
            };

    for(int i = 0; i < 8; i++)
    {

    }

}

class button_Maker
        {
            public:
            sf::RectangleShape rect;
            sf::CircleShape circ;
            bool filled;


            //constructor
            button_Maker( const v2f& button_size,  float circle_size) : rect(button_size), circ(circle_size)
            {
                filled = false;
                rect.setFillColor(sf::Color::White);
                rect.setOutlineThickness(1);
                rect.setOutlineColor(sf::Color::Transparent);

                circ.setFillColor(sf::Color::Black);
                circ.setOutlineThickness(1);
                circ.setOutlineColor(sf::Color::Transparent);
            }

            void circ_pos(const sf::RectangleShape& rectangle, sf::CircleShape circle)
            {
                circle.setOrigin(v2f(circle.getRadius(),circle.getRadius()));
                circle.setPosition(v2f(rectangle.getPosition().x + rectangle.getSize().x/2, rectangle.getPosition().y + rectangle.getSize().y/2));
            }

            void bM_draw(sf::RenderTarget& target) const
            {
                target.draw(rect);
                target.draw(circ);
            }

            void set_button_style(const sf::Color& color, f32 thickness, const sf::Color& outline_color)
            {
                rect.setFillColor(color);
                rect.setOutlineThickness(thickness);
                rect.setOutlineColor(outline_color);
            }

            int mouse_on_button_rect_change(const v2i mouse_pos, const sf::Color& color, f32 thickness, const sf::Color& outline_color,
                                                                 const sf::Color& OG_color, f32 OG_thickness, const sf::Color& OG_outline_color)
            {
                ///this could be optimized
                if(rect.getGlobalBounds().contains(static_cast<v2f>(mouse_pos)))
                {
                    rect.setFillColor(color);
                    rect.setOutlineThickness(thickness);
                    rect.setOutlineColor(outline_color);

                }

                else
                {
                    rect.setFillColor(OG_color);
                    rect.setOutlineThickness(OG_thickness);
                    rect.setOutlineColor(OG_outline_color);
                }
                return 0;
            }
            
            int mouse_on_button_circ_change(const v2i mouse_pos, const sf::Color& color, f32 thickness, const sf::Color& outline_color,
                                            const sf::Color& OG_color, f32 OG_thickness, const sf::Color& OG_outline_color)
            {
                if(rect.getGlobalBounds().contains(static_cast<v2f>(mouse_pos)) && !filled)
                {

                    circ.setFillColor(color);
                    circ.setOutlineThickness(thickness);
                    circ.setOutlineColor(outline_color);

                }

                else if(filled == true)
                {
                    printf("die");
                }

                else
                {
                    circ.setFillColor(OG_color);
                    circ.setOutlineThickness(OG_thickness);
                    circ.setOutlineColor(OG_outline_color);
                }
                return 0; 
            }

            int mouse_On_Button(const v2i mos_pos)
            {
                return rect.getGlobalBounds().contains(static_cast<v2f>(mos_pos));
            }

        };

class sprite_maker
{
    public:
    sf::Texture texture;
    sf::Sprite sprite;

    sprite_maker(const std::string& file_path, const v2f& sprite_scale, const v2f& sprite_pos): texture(file_path),sprite(texture)
    {
        if(!texture.loadFromFile(file_path))
        {
            throw std::runtime_error("Failed to load from: " + file_path);
        }
        sprite.setTexture(texture);
        sprite.setScale(sprite_scale);
        sprite.setPosition(sprite_pos);
    }

};

enum x_or_y
{
    X,
    Y
};

bool players_move(x_or_y player, std::vector<sf::Sprite*> x_sprites, std::vector<sf::Sprite*> y_sprites,
                  int (&array)[9], bool& players_turn, std::vector<button_Maker> buttons, const v2i mouse_pos, std::vector<sf::RectangleShape> button_rects,
                  int& counter, sf::RenderWindow& window) {

    auto &chosen_piece = (player == x_or_y::X) ? x_sprites : y_sprites;
    int chosen_array_piece = (player == x_or_y::X) ? 1 : 2;
    for (int i = 0; i < buttons.size(); i++) {

        //printf("\n\n%d\n\n", array[i]);

        if (buttons[i].mouse_On_Button(mouse_pos) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            //printf("\narray[%d]: %d", i, array[i]);

            if (array[i] == 0)
            {

                printf("\narray[%d]: %d", i, array[i]);
                printf("\nbuttons_rect[%d]: %f , %F", i, button_rects[i].getPosition().x, button_rects[i].getPosition().y);
                array[i] = chosen_array_piece;
                chosen_piece[counter]->setPosition(v2f(buttons.at(i).circ.getPosition().x-15, buttons.at(i).circ.getPosition().y-15));
                //chosen_piece[counter]->setPosition(v2f(buttons.at(i).circ.getPosition().x, button_rects.at(i).getPosition().y));

                counter += 1;
                players_turn = false;
                return true;
            }

        }

    }
    return false;
}

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({920u, 580u}), "CMake SFML Project");
    window.setFramerateLimit(144);

    sf::Texture x_texture;
    sf::Texture o_texture;
    sf::Texture back_ground_texture;
    back_ground_texture.loadFromFile("C:/Users/momer/Umary/CSC204/MidTerm/assets/background.png");
    x_texture.loadFromFile("C:/Users/momer/Umary/CSC204/MidTerm/assets/head.png");
    o_texture.loadFromFile("C:/Users/momer/Umary/CSC204/MidTerm/assets/bee.png");
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

    //these can be in a for loop
    x_piece_sprite->setScale(v2f(.1, .1));
    x_piece_sprite1->setScale(v2f(.1,.1));
    x_piece_sprite2->setScale(v2f(.1,.1));
    x_piece_sprite3->setScale(v2f(.1,.1));
    x_piece_sprite4->setScale(v2f(.1,.1));
    o_piece_sprite->setScale(v2f(.5, .5));
    o_piece_sprite1->setScale(v2f(.5,.5));
    o_piece_sprite2->setScale(v2f(.5,.5));
    o_piece_sprite3->setScale(v2f(.5,.5));
    o_piece_sprite4->setScale(v2f(.5,.5));

    x_piece_sprite->setPosition(v2f(550,500));
    x_piece_sprite1->setPosition(v2f(580,500));
    x_piece_sprite2->setPosition(v2f(520,500));
    x_piece_sprite3->setPosition(v2f(1000,1000));
    x_piece_sprite4->setPosition(v2f(1000,1000));

    o_piece_sprite->setPosition(v2f(1000,1000));
    o_piece_sprite1->setPosition(v2f(1000,1000));
    o_piece_sprite2->setPosition(v2f(1000,1000));
    o_piece_sprite3->setPosition(v2f(1000,1000));
    o_piece_sprite4->setPosition(v2f(1000,1000));

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

    std::vector<button_Maker> button_list;
    button_list.push_back(top_left);
    button_list.push_back(top_middle);
    button_list.push_back(top_right);
    button_list.push_back(mid_l);
    button_list.push_back(mid_m);
    button_list.push_back(mid_r);
    button_list.push_back(bottom_l);
    button_list.push_back(bottom_m);
    button_list.push_back(bottom_r);

    int posX = 310;
    int posY = 160;
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


    bool picked_character = false;
    bool players_turn = true;
    int counter =0;


    std::vector<sf::RectangleShape> button_list_rect;
    button_list_rect.push_back(top_left.rect);
    button_list_rect.push_back(top_middle.rect);
    button_list_rect.push_back(top_right.rect);
    std::vector<sf::Sprite*> x_list;
    x_list.emplace_back(x_piece_sprite);
    x_list.emplace_back(x_piece_sprite1);
    x_list.emplace_back(x_piece_sprite2);
    x_list.emplace_back(x_piece_sprite3);
    x_list.emplace_back(x_piece_sprite4);

    std::vector<sf::Sprite*> o_list;
    o_list.emplace_back(o_piece_sprite);
    o_list.emplace_back(o_piece_sprite1);
    o_list.emplace_back(o_piece_sprite2);
    o_list.emplace_back(o_piece_sprite3);
    o_list.emplace_back(o_piece_sprite4);

    int board[9] {0};

    while (window.isOpen())
    {
       // printf("\n\n\nx: %f, y: %f", button_list_rect[1].get().getPosition().x, button_list_rect[1].get().getPosition().y);

        if (picked_character == false)
        {
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


            window.display();
        }

        else
        {
            window.clear();
            //window.draw(background_sprite.sprite);
           //window.draw(x_piece_sprite);
            window.display();
        }
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

            mouse_pos = sf::Mouse::getPosition(window);

            if(players_turn == true)
            {

                for (auto& buttons : button_list)
                {
                    buttons.mouse_on_button_circ_change(mouse_pos, sf::Color::White, 2.5, sf::Color::White,
                                                        sf::Color::Transparent, 2.5, sf::Color::White);
                }

                players_move(x_or_y::Y, x_list, o_list, board, players_turn, button_list, mouse_pos, button_list_rect, counter, window);
            }

            else
            {
                //enemy_move(players_turn);
                players_turn = true;
            }


    }
}
