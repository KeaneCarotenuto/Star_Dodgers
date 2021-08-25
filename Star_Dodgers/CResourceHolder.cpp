#include <iostream>
#include "CResourceHolder.h"

CResourceHolder::CResourceHolder(void) {}
CResourceHolder::~CResourceHolder(void) {}

// static variables
sf::RenderWindow *CResourceHolder::m_window = nullptr;
std::map<std::string, sf::Image *> CResourceHolder::m_imageMap;
std::map<std::string, sf::Texture*> CResourceHolder::m_textureMap;
std::map<std::string, sf::Font *> CResourceHolder::m_fontMap;

// create resources that will be used later in the project
void CResourceHolder::Initialise()
{
	m_window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Star Dodgers - By ClosedGL", sf::Style::Default);

	CreateImage("icon.png");
	CreateImage("P1.png");
	CreateImage("P2.png");
	CreateImage("P3.png");
	CreateImage("P4.png");
	CreateImage("BackButton.png");
	CreateImage("X-Ready.png");

	CreateFont("comic.ttf");
	
}

sf::RenderWindow *CResourceHolder::GetWindow()
{
	return (m_window);
}

sf::Vector2u CResourceHolder::GetWindowSize()
{
	return(m_window->getSize());
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

void CResourceHolder::CreateTexture(std::string _name)
{
	std::string path = "Resources/Images/";

	// check that this image is not already in map
	std::map<std::string, sf::Texture*>::iterator iter = m_textureMap.find(_name);
	if (iter != m_textureMap.end())
	{
		std::cout << "Texture: " << _name << " has already been created. " << std::endl;
	}
	else
	{
		sf::Texture* newTexture = new sf::Texture();
		newTexture->loadFromFile(path + _name);
		m_textureMap.insert(std::pair<std::string, sf::Texture*>(_name, newTexture));
	}
}

sf::Texture* CResourceHolder::GetTexture(std::string _name)
{
	// make sure texture is in map
	std::map<std::string, sf::Texture*>::iterator iter = m_textureMap.find(_name);
	if (iter != m_textureMap.end())
	{
		return (iter->second);
	}
	else
	{
		std::cout << "Texture: " << _name << " has not been created yet." << std::endl;
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
