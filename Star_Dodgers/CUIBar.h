#ifndef A16FE15C_B520_46C1_AD73_4B3093E4EAE8
#define A16FE15C_B520_46C1_AD73_4B3093E4EAE8
#include "IUIElement.h"
#include "EasySFML.h"
class CUIBar : public IUIElement
{
public:
    CUIBar(int _Zindex, sf::Vector2f _position, sf::Vector2f _scale, float _rotation, sf::Texture* _barTex, sf::Texture* _bgTex);
    void SetFill(float _max, float _val);
private:
    void DrawUI(sf::RenderWindow* _window);
    float m_value;
    sf::Sprite m_bgSprite;
    sf::Sprite m_barSprite;

};

#endif 
