#include "CUIImage.h"

CUIImage::CUIImage(int _Zindex, sf::Vector2f _position, sf::Vector2f _scale, float _rotation, sf::Texture* _tex) {
    SetZIndex(_Zindex);
    
    m_Sprite.setTexture(*_tex);
    m_Sprite.setPosition(_position);
    m_Sprite.setScale(_scale);
    m_Sprite.setRotation(_rotation);
}

void CUIImage::DrawUI(sf::RenderWindow* _window) {
    _window->draw(m_Sprite);
}