#pragma once

#ifndef __CRESOURCE_HOLDER_H__
#define __CRESOURCE_HOLDER_H__

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics/Font.hpp>
#include <map>

class CResourceHolder
{
public:
	CResourceHolder(void);
	~CResourceHolder(void);

	static void Initialise();

	static sf::RenderWindow* GetWindow();
	static sf::Vector2u GetWindowSize();

	static void CreateImage(std::string _name);
	static sf::Image* GetImage(std::string _name);
	static void CreateTexture(std::string _name);
	static sf::Texture* GetTexture(std::string _name);
	static void CreateFont(std::string _name);
	static sf::Font* GetFont(std::string _name);
	static void CreateShader(std::string _name, std::string _vertexName, std::string _fragmentName);
	static void CreateShader(std::string _name, sf::Shader::Type _type);
	static sf::Shader* GetShader(std::string _name);
	static void CreateSoundBuffer(std::string _name);
	static sf::SoundBuffer* GetSoundBuffer(std::string _name);

	// sound assets too maybe

private:
	static sf::RenderWindow* m_window;
	static std::map<std::string, sf::Image*> m_imageMap;
	static std::map<std::string, sf::Texture*> m_textureMap;
	static std::map<std::string, sf::Font*> m_fontMap;
	static std::map<std::string, sf::Shader*> m_shaderMap;
	static std::map<std::string, sf::SoundBuffer*> m_soundBufferMap;
	
};

#endif  // __CRESOURCE_HOLDER_H__
