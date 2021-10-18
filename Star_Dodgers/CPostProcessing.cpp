#include "CPostProcessing.h"

CPostProcessing * CPostProcessing::m_singleton = nullptr;

/// <summary>
/// Gets a Singleton Instance of the PostProcessing class.
/// <para>Author: Nerys</para>
/// </summary>
/// <returns></returns>
CPostProcessing * CPostProcessing::GetInstance() {
    if(m_singleton == nullptr) m_singleton = new CPostProcessing();
    return m_singleton;
}

/// <summary>
/// Adds a Screen shake effect to the post processing for the specified duration.
/// <para>Author: Nerys</para>
/// </summary>
/// <param name="_amplitude"></param>
/// <param name="_frequency"></param>
/// <param name="_duration"></param>
/// <returns></returns>
void CPostProcessing::AddScreenShake(sf::Vector2f _amplitude, sf::Vector2f _frequency, float _duration) {
    
    m_currScreenShakeEffect.m_amplitude = sf::Vector2f(std::max(m_currScreenShakeEffect.m_amplitude.x, _amplitude.x), std::max(m_currScreenShakeEffect.m_amplitude.y, _amplitude.y));
    m_currScreenShakeEffect.m_frequency = sf::Vector2f(std::max(m_currScreenShakeEffect.m_frequency.x, _frequency.x), std::max(m_currScreenShakeEffect.m_frequency.y, _frequency.y));
    m_currScreenShakeEffect.m_duration = std::max(m_currScreenShakeEffect.m_duration, _duration);
}

void CPostProcessing::AddChromaAberration(float _magnitude, float _duration) {
    m_chromaAberrationMagnitude = std::max(m_chromaAberrationMagnitude, _magnitude);
    m_chromaAberrationDuration = std::max(m_chromaAberrationDuration, _duration);
}

/// <summary>
/// Updates the Post Processing class, this needs to be called every frame before rendering.
/// <para>Author: Nerys</para>
/// </summary>
/// <returns></returns>
void CPostProcessing::Update() {
    float deltaTime = m_clock.restart().asSeconds();
    if ((m_currScreenShakeEffect.m_duration -= deltaTime) <= 0.0f)
    {
        m_currScreenShakeEffect.m_duration = 0.0f;
        m_currScreenShakeEffect.m_amplitude = sf::Vector2f{0.0f,0.0f};
        m_currScreenShakeEffect.m_frequency = sf::Vector2f{0.0f,0.0f};
    }
    else
    {
        m_currScreenShakeEffect.m_amplitude -= (deltaTime * (m_currScreenShakeEffect.m_amplitude / m_currScreenShakeEffect.m_duration));
    }
    
    if ((m_chromaAberrationDuration -= deltaTime) > 0.0f)
    {
        m_chromaAberrationMagnitude -= (deltaTime * (m_chromaAberrationMagnitude / m_chromaAberrationDuration));
        if (m_chromaAberrationMagnitude < 0.0f) m_chromaAberrationMagnitude = 0.0f;
    }
    
    
    
}

/// <summary>
/// Gets the screen shake effect.
/// <para>Author: Nerys</para>
/// </summary>
/// <returns></returns>
CPostProcessing::ScreenShakeEffect CPostProcessing::GetTotalScreenShake() {
    return m_currScreenShakeEffect;
}

/// <summary>
/// Applies enabled post-processing effects to the provided texture
/// <para>Author: Nerys</para>
/// </summary>
/// <param name="_tex"></param>
/// <param name="_window"></param>
/// <returns></returns>
void CPostProcessing::ApplyPostProcessing(const sf::Texture& _tex, sf::RenderWindow& _window) {
    CPostProcessing::ScreenShakeEffect shake = GetTotalScreenShake();
    CResourceHolder::GetShader("screenshake.glsl")->setUniform("iImageTexture", sf::Shader::CurrentTexture);
	CResourceHolder::GetShader("screenshake.glsl")->setUniform("iResolution", (sf::Vector2f)CResourceHolder::GetWindowSize());
	CResourceHolder::GetShader("screenshake.glsl")->setUniform("iTime", cmath::g_clock->getElapsedTime().asSeconds());
	CResourceHolder::GetShader("screenshake.glsl")->setUniform("ShakeAmplitude", shake.m_amplitude);
	CResourceHolder::GetShader("screenshake.glsl")->setUniform("ShakeFrequency", shake.m_frequency);
    CResourceHolder::GetShader("screenshake.glsl")->setUniform("ChromaticAberration", m_chromaAberrationMagnitude);
    _window.draw(sf::Sprite(_tex), CResourceHolder::GetShader("screenshake.glsl"));
    
}