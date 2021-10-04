#include "CUIBar.h"
#include"CMath.h"

CUIBar::CUIBar(int _Zindex, float& _valueToTrack, sf::Vector2f _position, sf::Vector2f _scale, float _rotation, sf::Texture* _barTex, sf::Texture* _bgTex) : m_value(_valueToTrack) 
{
    SetZIndex(_Zindex);
    m_barSprite.setTexture(*_barTex);
    m_bgSprite.setTexture(*_bgTex);
    m_bgSprite.setPosition(_position);
    m_bgSprite.setScale(_scale);
    m_bgSprite.setRotation(_rotation);
    m_barSprite.setPosition(_position);
    m_barSprite.setScale(_scale);
    m_barSprite.setRotation(_rotation);
    

}

void CUIBar::DrawUI(sf::RenderWindow* _window) {
   
    m_value = cmath::Clamp(m_value, 0.0f, 1.0f);
    m_barSprite.setScale(sf::Vector2f(m_bgSprite.getScale().x * m_value, m_bgSprite.getScale().y));
    
    _window->draw(m_barSprite);
    _window->draw(m_bgSprite);
}