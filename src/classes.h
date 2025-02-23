#include <SFML/Graphics.hpp>

#ifndef CMAKESFMLPROJECT_CLASSES_H
#define CMAKESFMLPROJECT_CLASSES_H

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

    //function to draw to screen
    void bM_draw(sf::RenderTarget& target) const
    {
        target.draw(rect);
        target.draw(circ);
    }

    //function that stylizes button
    void set_button_style(const sf::Color& color, f32 thickness, const sf::Color& outline_color)
    {
        rect.setFillColor(color);
        rect.setOutlineThickness(thickness);
        rect.setOutlineColor(outline_color);
    }

    //function - button changes color if on button
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

    //function - circ changes color if on button
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

    //returns if mouse is on button
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
    O,
    SetUp
};

enum results
{
    WIN,
    LOSE,
    DRAW,
    IDK
};

#endif //CMAKESFMLPROJECT_CLASSES_H
