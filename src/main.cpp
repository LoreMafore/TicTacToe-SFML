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
                if(rect.getGlobalBounds().contains(static_cast<v2f>(mos_pos)))
                {
                    printf("gay");
                }
                return 0;
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
bool players_move(x_or_y player, std::vector<std::reference_wrapper<sf::Sprite>> x_sprites, std::vector<std::reference_wrapper<sf::Sprite>> y_sprites,
                 int (&array)[9], bool players_turn, std::vector<button_Maker> buttons, const v2i mouse_pos, sf::RenderWindow& window, int counter)
{

        auto& chosen_piece = (player == x_or_y::X)? x_sprites : y_sprites;
        int  chosen_array_piece = (player == x_or_y::X) ? 1 : 2;
        for (int i = 0; i < buttons.size(); i++)
            if (buttons[i].mouse_On_Button(mouse_pos) && even&&sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                printf("Help");
                if (array[i] == 0) {
                    array[i] = chosen_array_piece;
                    chosen_piece[counter].get().setPosition(
                            v2f(buttons[i].rect.getPosition().x / 2, buttons[i].rect.getPosition().y / 2));
                    counter++;
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
    sf::Sprite x_piece_sprite (x_texture);
    sf::Sprite x_piece_sprite1(x_texture);
    sf::Sprite x_piece_sprite2(x_texture);
    sf::Sprite x_piece_sprite3(x_texture);
    sf::Sprite x_piece_sprite4(x_texture);
    sf::Sprite o_piece_sprite(o_texture);
    sf::Sprite o_piece_sprite1(o_texture);
    sf::Sprite o_piece_sprite2(o_texture);
    sf::Sprite o_piece_sprite3(o_texture);
    sf::Sprite o_piece_sprite4(o_texture);



    sprite_maker background_sprite("C:/Users/momer/Umary/CSC204/MidTerm/assets/background.png", v2f(1,1),v2f(0,0));
    x_piece_sprite.setScale(v2f(.1, .1));
    x_piece_sprite1.setScale(v2f(.1,.1));
    x_piece_sprite2.setScale(v2f(.1,.1));
    x_piece_sprite3.setScale(v2f(.1,.1));
    x_piece_sprite4.setScale(v2f(.1,.1));
    o_piece_sprite.setScale(v2f(.1, .1));
    o_piece_sprite1.setScale(v2f(.1,.1));
    o_piece_sprite2.setScale(v2f(.1,.1));
    o_piece_sprite3.setScale(v2f(.1,.1));
    o_piece_sprite4.setScale(v2f(.1,.1));

    x_piece_sprite.setPosition(v2f(1000,1000));
    x_piece_sprite1.setPosition(v2f(1000,1000));
    x_piece_sprite2.setPosition(v2f(1000,1000));
    x_piece_sprite3.setPosition(v2f(1000,1000));
    x_piece_sprite4.setPosition(v2f(1000,1000));

    o_piece_sprite.setPosition(v2f(1000,1000));
    o_piece_sprite1.setPosition(v2f(1000,1000));
    o_piece_sprite2.setPosition(v2f(1000,1000));
    o_piece_sprite3.setPosition(v2f(1000,1000));
    o_piece_sprite4.setPosition(v2f(1000,1000));

    v2i mouse_pos = sf::Mouse::getPosition(window);
    button_Maker top_left(v2f(100, 100),  7.5);
    button_Maker top_middle(v2f(100, 100), 7.5);
    button_Maker top_right(v2f(100, 100),  7.5);

    top_left.rect.setPosition(v2f(310,160));
    //top_left.circ_pos(top_left.rect,top_left.circ);
    top_left.circ.setOrigin(v2f(top_left.circ.getRadius(),top_left.circ.getRadius()));
    top_left.circ.setPosition(v2f(top_left.rect.getPosition().x + top_left.rect.getSize().x/2, top_left.rect.getPosition().y + top_left.rect.getSize().y/2));
    top_left.set_button_style(sf::Color(192,192,192), 1, sf::Color::Black);

    top_middle.rect.setPosition(v2f(415,160));
    top_middle.circ.setOrigin(v2f(top_middle.circ.getRadius(),top_middle.circ.getRadius()));
    top_middle.circ.setPosition(v2f(top_middle.rect.getPosition().x + top_middle.rect.getSize().x/2, top_middle.rect.getPosition().y + top_middle.rect.getSize().y/2));
    top_middle.set_button_style(sf::Color(192,192,192), 1, sf::Color::White);

    top_right.rect.setPosition(v2f(520,160));
    top_right.circ.setOrigin(v2f(top_right.circ.getRadius(),top_right.circ.getRadius()));
    top_right.circ.setPosition(v2f(top_right.rect.getPosition().x + top_right.rect.getSize().x/2, top_right.rect.getPosition().y + top_right.rect.getSize().y/2));
    top_right.set_button_style(sf::Color(192,192,192), 1, sf::Color::Black);

    bool picked_character = false;
    bool players_turn = true;
    int counter =0;

    std::vector<button_Maker> button_list;
    button_list.push_back(top_left);
    button_list.push_back(top_middle);
    button_list.push_back(top_right);

    std::vector<sf::RectangleShape> button_list_rect;
    button_list_rect.push_back(top_left.rect);
    button_list_rect.push_back(top_middle.rect);
    button_list_rect.push_back(top_right.rect);
    std::vector<std::reference_wrapper<sf::Sprite>> x_list;
    x_list.emplace_back(x_piece_sprite);
    x_list.emplace_back(x_piece_sprite1);
    x_list.emplace_back(x_piece_sprite2);
    x_list.emplace_back(x_piece_sprite3);
    x_list.emplace_back(x_piece_sprite4);

    std::vector<std::reference_wrapper<sf::Sprite>> o_list;
    o_list.emplace_back(o_piece_sprite);
    o_list.emplace_back(o_piece_sprite1);
    o_list.emplace_back(o_piece_sprite2);
    o_list.emplace_back(o_piece_sprite3);
    o_list.emplace_back(o_piece_sprite4);

    int board[9] {0};

    while (window.isOpen())
    {
        if (picked_character == false)
        {
            window.clear();
            window.draw(background_sprite.sprite);
            for(int i = 0; i < x_list.size(); i++)
            {
                window.draw(x_list[i]);
                window.draw(o_list[i]);
            }

            top_left.bM_draw(window);
            top_middle.bM_draw(window);
            top_right.bM_draw(window);
            window.draw(x_piece_sprite);
            window.display();
        }

        else
        {
            window.clear();
            //window.draw(background_sprite.sprite);
            window.draw(x_piece_sprite);
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

//            if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
//            {
//                for(int position = 0; position < button_list_rect.size(); position++)
//                {
//                    if(button_list_rect[position].getGlobalBounds().contains(static_cast<v2f>(mouse_pos)) )
//                    {
//                        if(board[position] == 0)
//                        {
//                            board[position] = 1;
//                            x_piece_sprite.setPosition(v2f(static_cast<float>(mouse_pos.x),static_cast<float>(mouse_pos.y)));
//                            window.draw(x_piece_sprite);
//                        }
//                    }
//                }
//
//            }
        }

            mouse_pos = sf::Mouse::getPosition(window);


            top_left.mouse_on_button_circ_change(mouse_pos, sf::Color::White, 2.5, sf::Color::White,
                                                 sf::Color::Transparent, 2.5, sf::Color::White);
            top_left.bM_draw(window);

            top_middle.mouse_on_button_circ_change(mouse_pos, sf::Color::White, 2.5, sf::Color::White,
                                                   sf::Color::Transparent, 2.5, sf::Color::White);
            top_middle.bM_draw(window);

            top_right.mouse_on_button_circ_change(mouse_pos, sf::Color::White, 2.5, sf::Color::White,
                                                  sf::Color::Transparent, 2.5, sf::Color::White);

//            window.clear();
//            for(auto i: button_list)
//            {
//                i.bM_draw(window);
//            }
            //window.display();
            //inside the player function we need to have the  mouse_pos update
            players_move(x_or_y::X, x_list, o_list, board, players_turn, button_list, mouse_pos,window, counter);
    }
}
