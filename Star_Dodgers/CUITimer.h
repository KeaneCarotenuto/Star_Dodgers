#ifndef E668591A_FDBB_4F78_8196_6BFCC5CEC589
#define E668591A_FDBB_4F78_8196_6BFCC5CEC589
#include "IUIElement.h"
#include <iomanip>

class CUITimer : public IUIElement
{
public:
    CUITimer(int _Zindex, sf::Vector2f _position, sf::Vector2f _scale, float _rotation);
private:
    void DrawUI(sf::RenderWindow* _window);
    sf::Clock m_clock;
    sf::Text m_text;
    float m_timeElapsed;
};

#endif /* E668591A_FDBB_4F78_8196_6BFCC5CEC589 */
