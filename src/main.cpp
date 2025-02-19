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
            bool OG_Color;


            //constructor
            button_Maker( const v2f& button_size, const bool& color, float circle_size) : rect(button_size), OG_Color(color), circ(circle_size)
            {
                rect.setFillColor(sf::Color::White);
                rect.setOutlineThickness(1);
                rect.setOutlineColor(sf::Color::Transparent);

                circ.setFillColor(sf::Color::Black);
                circ.setOutlineThickness(1);
                circ.setOutlineColor(sf::Color::Transparent);
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
                if(rect.getGlobalBounds().contains(static_cast<v2f>(mouse_pos)))
                {

                    circ.setFillColor(color);
                    circ.setOutlineThickness(thickness);
                    circ.setOutlineColor(outline_color);

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

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({920u, 580u}), "CMake SFML Project");
    window.setFramerateLimit(144);

    sf::Texture background_texture;
    sf::Texture board_texture;
    sf::Texture x_texture;
    sf::Texture o_texture;

    background_texture.loadFromFile("C:/Users/momer/Umary/CSC204/MidTerm/assets/background.png");
    board_texture.loadFromFile("C:/Users/momer/Umary/CSC204/MidTerm/assets/board_processed.png");
    x_texture.loadFromFile("C:/Users/momer/Umary/CSC204/MidTerm/assets/head.png");
    o_texture.loadFromFile("C:/Users/momer/Umary/CSC204/MidTerm/assets/bee.png");

    sf::Sprite background_sprite(background_texture);
    sf::Sprite board_sprite(board_texture);
    sf::Sprite x_piece_sprite(x_texture);
    sf::Sprite o_piece_sprite(o_texture);

    x_piece_sprite.setScale(v2f(.1, .1));

    background_sprite.setPosition(v2f(0,0));
    board_sprite.setPosition(v2f(360,190));
    x_piece_sprite.setPosition(v2f(1000,1000));

    v2i mouse_pos = sf::Mouse::getPosition(window);
    button_Maker top_left(v2f(100, 100), true, 7.5);
    button_Maker top_middle(v2f(100, 100), true, 7.5);
    top_left.rect.setPosition(v2f(310,160));
    top_left.circ.setOrigin(v2f(top_left.circ.getRadius(),top_left.circ.getRadius()));
    top_left.circ.setPosition(v2f(top_left.rect.getPosition().x + top_left.rect.getSize().x/2, top_left.rect.getPosition().y + top_left.rect.getSize().y/2));
    top_left.set_button_style(sf::Color(192,192,192), 1, sf::Color::Black);

    top_middle.rect.setPosition(v2f(410,160));
    top_middle.circ.setOrigin(v2f(top_middle.circ.getRadius(),top_middle.circ.getRadius()));
    top_middle.circ.setPosition(v2f(top_middle.rect.getPosition().x + top_middle.rect.getSize().x/2, top_middle.rect.getPosition().y + top_middle.rect.getSize().y/2));
    top_middle.set_button_style(sf::Color(192,192,192), 1, sf::Color::White);
    bool picked_character = false;
    int board[9] {0};

    while (window.isOpen())
    {
        if (picked_character == false)
        {
            window.clear();
            window.draw(background_sprite);
            top_left.bM_draw(window);
            top_middle.bM_draw(window);
            window.display();
        }

        else
        {
            window.clear();
            window.draw(background_sprite);
            window.draw(board_sprite);
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

            if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
//                x_piece_sprite.setPosition(v2f(static_cast<float>(mouse_pos.x),static_cast<float>(mouse_pos.y)));
//                window.draw(x_piece_sprite)


            }
        }


//        if(button_1.getGlobalBounds().contains(static_cast<v2f>(mouse_pos)))
//        {
//            printf("Really gay\n\n\n");
//        }

            //top_left.mouse_On_Button(mouse_pos);
            mouse_pos = sf::Mouse::getPosition(window);
           // top_left.mouse_on_button_rect_change(mouse_pos,sf::Color(160,160,160), 1, sf::Color::Transparent,
            //                                 sf::Color(192,192,192), 1, sf::Color::Transparent);

            top_left.mouse_on_button_circ_change(mouse_pos, sf::Color::White, 2.5, sf::Color::White,
                                                        sf::Color::Transparent, 2.5, sf::Color::White);

            top_middle.mouse_on_button_circ_change(mouse_pos, sf::Color::White, 2.5, sf::Color::White,
                                             sf::Color::Transparent, 2.5, sf::Color::White);
    }
}
