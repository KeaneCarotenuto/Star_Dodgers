#ifndef B20AC48F_E59D_4392_89B7_6BD93E543097
#define B20AC48F_E59D_4392_89B7_6BD93E543097
#include "EasySFML.h"
#include "CResourceHolder.h"
#include "CMath.h"
#include <list>
class CPostProcessing
{
public:
    static CPostProcessing * GetInstance();
    void ApplyPostProcessing(const sf::Texture& _tex, sf::RenderWindow& _window);
    void AddScreenShake(sf::Vector2f _amplitude, sf::Vector2f _frequency, float _duration);
    void AddChromaAberration(float _magnitude, float _duration);
    void Update();
protected:
    static CPostProcessing * m_singleton;
private:
    struct ScreenShakeEffect
    {
        sf::Vector2f m_amplitude, m_frequency;
        float m_duration = 0.0f;
    };

    
    ScreenShakeEffect m_currScreenShakeEffect;
    float m_chromaAberrationMagnitude = 0.0f;
    float m_chromaAberrationDuration = 0.0f;
    sf::Clock m_clock;
    ScreenShakeEffect GetTotalScreenShake();
};

#endif /* B20AC48F_E59D_4392_89B7_6BD93E543097 */
