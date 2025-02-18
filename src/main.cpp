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
            //v2f size;
            sf::RectangleShape rect;

            //constructor
            button_Maker(const v2f& button_size) : rect(button_size)
            {
                rect.setFillColor(sf::Color::White);
                rect.setOutlineThickness(1);
                rect.setOutlineColor(sf::Color::Transparent);
            }

            void bM_draw(sf::RenderTarget& target) const
            {
                target.draw(rect);
            }

            void set_button_style(const sf::Color& color, f32 thickness, const sf::Color& outline_color)
            {
                rect.setFillColor(color);
                rect.setOutlineThickness(thickness);
                rect.setOutlineColor(outline_color);
            }

            int mouse_On_Button_rect_change(const v2i mouse_pos, const sf::Color& color, f32 thickness, const sf::Color& outline_color)
            {
                if(rect.getLocalBounds().contains(static_cast<v2f>(mouse_pos)))
                {
                    rect.setFillColor(color);
                    rect.setOutlineThickness(thickness);
                    rect.setOutlineColor(outline_color);
                }
            }

        };

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({920u, 580u}), "CMake SFML Project");
    window.setFramerateLimit(144);

    sf::FloatRect rect(v2f(0,0), v2f(100,100));
    sf::RectangleShape button_1(v2f(rect.size));
    sf::RectangleShape button_2(v2f(rect.size));
    sf::Texture background_texture;
    sf::Texture board_texture;
    sf::Texture x_texture;
    sf::Texture o_texture;
    sf::Texture button_1_text;
    sf::Texture button_2_text;

    background_texture.loadFromFile("C:/Users/momer/Umary/CSC204/MidTerm/assets/background.png");
    board_texture.loadFromFile("C:/Users/momer/Umary/CSC204/MidTerm/assets/board_processed.png");
    x_texture.loadFromFile("C:/Users/momer/Umary/CSC204/MidTerm/assets/head.png");
    o_texture.loadFromFile("C:/Users/momer/Umary/CSC204/MidTerm/assets/bee.png");
    button_1_text.loadFromFile("C:/Users/momer/Umary/CSC204/MidTerm/assets/head.png");
    button_2_text.loadFromFile("C:/Users/momer/Umary/CSC204/MidTerm/assets/head.png");

    sf::Sprite background_sprite(background_texture);
    sf::Sprite board_sprite(board_texture);
    sf::Sprite x_piece_sprite(x_texture);
    sf::Sprite o_piece_sprite(o_texture);
    sf::Sprite button_1_sprite(button_1_text);
    sf::Sprite button_2_sprite(button_2_text);

    x_piece_sprite.setScale(v2f(.1, .1));
    button_1_sprite.setScale(v2f(.1, .1));
    button_2_sprite.setScale(v2f(.1, .1));
    button_1.setFillColor(sf::Color(160,160,160));
    button_2.setFillColor(sf::Color(160,160,160));

    background_sprite.setPosition(v2f(0,0));
    board_sprite.setPosition(v2f(360,190));
    x_piece_sprite.setPosition(v2f(1000,1000));
    button_1.setPosition(v2f(300, 290));
    button_2.setPosition(v2f(585, 290));

    v2i mouse_pos = sf::Mouse::getPosition(window);
    //v2f mouse = v2f(sf::Mouse::getPosition(window));

//    v2f ul = v2f(button_1.getPosition());
//    v2f br = v2f(button_1.getPosition() + v2f(rect.size.x, rect.size.y));

    button_Maker cool(v2f(100, 100));
    cool.rect.setPosition(v2f(100,100));

    cool.set_button_style(sf::Color(192,192,192), 1, sf::Color::Transparent);


    bool picked_character = false;
    int board[9] {0};

    while (window.isOpen())
    {
        if (picked_character == false)
        {
            window.clear();
            window.draw(background_sprite);
            cool.bM_draw(window);
            window.draw(button_1);
            window.draw(button_2);
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
        mouse_pos = sf::Mouse::getPosition(window);
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            if(event->is<sf::Event::MouseMoved>())
            {
                cool.mouse_On_Button_rect_change(mouse_pos,sf::Color(160,160,160), 1, sf::Color::Transparent);
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


        //mouse_pos = v2f(sf::Mouse::getPosition(window));

        //print, mouse pos, ur, bl, button1 pos

//        if(button_1.getGlobalBounds().contains(static_cast<v2f>(mouse_pos)))
//        {
//            printf("Really gay\n\n\n");
//        }

//        if( mouse.x >= ul.x && mouse.x <= br.x && mouse.y >= ul.y && mouse.y <= br.y)
//        {
//            printf("\n\n\n\n\ngay\n\n\n\n");
//        }
//        button(button_1.getPosition(), mouse_pos, button_1);


    }
}
