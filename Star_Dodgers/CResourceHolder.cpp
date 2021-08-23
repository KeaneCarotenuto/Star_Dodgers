#include <iostream>
#include "CResourceHolder.h"

CResourceHolder::CResourceHolder(void) {}
CResourceHolder::~CResourceHolder(void) {}

// create resources that will be used later in the project
void CResourceHolder::Initialise()
{
	CreateImage("icon.png");
	CreateFont("comic.ttf");
}

void CResourceHolder::CreateImage(std::string _name)
{
	std::string path = "Resources/Images/";

	// check that this image is not already in map
	std::map<std::string, sf::Image *>::iterator iter = m_imageMap.find(_name);
	if (iter != m_imageMap.end())
	{
		std::cout << "Image: " << _name << " has already been created. " << std::endl;
	}
	else
	{
		sf::Image *newImage = new sf::Image();
		newImage->loadFromFile(path + _name);
		m_imageMap.insert(std::pair<std::string, sf::Image *>(_name, newImage));
	}
}

sf::Image *CResourceHolder::GetImage(std::string _name)
{
	// make sure image is in map
	std::map<std::string, sf::Image *>::iterator iter = m_imageMap.find(_name);
	if (iter != m_imageMap.end())
	{
		return (iter->second);
	}
	else
	{
		std::cout << "Image: " << _name << " has not been created yet." << std::endl;
		return (nullptr);
	}
}

void CResourceHolder::CreateFont(std::string _name)
{
	std::string path = "Resources/Fonts/";

	// check that this font is not already in map
	std::map<std::string, sf::Font *>::iterator iter = m_fontMap.find(_name);
	if (iter != m_fontMap.end())
	{
		std::cout << "Font: " << _name << " has already been created. " << std::endl;
	}
	else
	{
		sf::Font *newFont = new sf::Font();
		newFont->loadFromFile(path + _name);
		m_fontMap.insert(std::pair<std::string, sf::Font *>(_name, newFont));
	}
}

sf::Font *CResourceHolder::GetFont(std::string _name)
{
	// make sure font is in map
	std::map<std::string, sf::Font *>::iterator iter = m_fontMap.find(_name);
	if (iter != m_fontMap.end())
	{
		return (iter->second);
	}
	else
	{
		std::cout << "Font: " << _name << " has not been created yet." << std::endl;
		return (nullptr);
	}
}

std::map<std::string, sf::Image *> CResourceHolder::m_imageMap;
std::map<std::string, sf::Font *> CResourceHolder::m_fontMap;
