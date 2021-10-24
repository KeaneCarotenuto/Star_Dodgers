#ifndef CCD47BF2_D822_440F_A5D0_E0076168100A
#define CCD47BF2_D822_440F_A5D0_E0076168100A
#include "IUIElement.h"
#include "EasySFML.h"
#include "CResourceHolder.h"
#include "CMath.h"

class CUIImage : public IUIElement
{
public:
    CUIImage(int _Zindex, sf::Vector2f _position, sf::Vector2f _scale, float _rotation, sf::Texture* _tex);
    sf::Sprite* GetSprite() { return(&m_Sprite); }
private:
    void DrawUI(sf::RenderWindow* _window);
    sf::Sprite m_Sprite;
    

};

#endif /* CCD47BF2_D822_440F_A5D0_E0076168100A */
