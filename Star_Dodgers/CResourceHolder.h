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
	static void CreateImage(std::string _name);
	static sf::Image* GetImage(std::string _name);
	static void CreateFont(std::string _name);
	static sf::Font* GetFont(std::string _name);

	// sound assets too maybe

private:
	static std::map<std::string, sf::Image*> m_imageMap;
	static std::map<std::string, sf::Font*> m_fontMap;
};

#endif  // __CRESOURCE_HOLDER_H__
