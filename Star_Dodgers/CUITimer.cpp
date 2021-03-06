#include "CUITimer.h"

/// <summary>
/// Constructor
/// <para>Author: Nerys</para>
/// </summary>
/// <returns></returns>
CUITimer::CUITimer(int _Zindex, sf::Vector2f _position, sf::Vector2f _scale, float _rotation) {
    SetZIndex(_Zindex);
    m_text.setPosition(_position);
    m_text.setRotation(_rotation);
    m_text.setScale(_scale);
    m_text.setFont(*CResourceHolder::GetFont("chintzys.ttf"));
    
    m_timeElapsed = 0.0f;
    m_clock.restart();
}

/// <summary>
/// Draws the UI to the screen
/// <para>Author: Nerys</para>
/// </summary>
/// <returns></returns>
void CUITimer::DrawUI(sf::RenderWindow* _window) {
    m_timeElapsed += m_clock.restart().asSeconds();
    m_text.setString(std::to_string((int)m_timeElapsed / 60) + ":" + std::to_string((int)m_timeElapsed % 60));
    _window->draw(m_text);

}