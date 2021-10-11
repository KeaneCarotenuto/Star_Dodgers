#include <iostream>
#include "CResourceHolder.h"

CResourceHolder::CResourceHolder(void) {}
CResourceHolder::~CResourceHolder(void) {}

// static variables
sf::RenderWindow *CResourceHolder::m_window = nullptr;
std::map<std::string, sf::Image *> CResourceHolder::m_imageMap;
std::map<std::string, sf::Texture*> CResourceHolder::m_textureMap;
std::map<std::string, sf::Font *> CResourceHolder::m_fontMap;
std::map<std::string, sf::Shader *> CResourceHolder::m_shaderMap;

// create resources that will be used later in the project
void CResourceHolder::Initialise()
{
	float titlebarHeight = 25;
	float taskbarBeight = 40;
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

	m_window = new sf::RenderWindow(sf::VideoMode(1920, 1080 - titlebarHeight - taskbarBeight, desktop.bitsPerPixel), "Star Dodgers - By ClosedGL", sf::Style::Default);
	m_window->setFramerateLimit(60);
	m_window->setPosition({ 0, 0 });
	m_window->requestFocus();


	CreateImage("icon_pixel.PNG");
	CreateTexture("Ball.png");
	CreateTexture("Ball_Red.png");
	CreateTexture("Ball_Blue.png");
	CreateTexture("Ball_Yellow.png");
	CreateTexture("Ball_Yellow_Red.png");
	CreateTexture("Ball_Yellow_Blue.png");
	CreateTexture("Ball_Rainbow.png");
	CreateTexture("Ball_Rainbow_Blue.png");
	CreateTexture("Ball_Rainbow_Red.png");
	CreateTexture("P1.png");
	CreateTexture("P2.png");
	CreateTexture("P3.png");
	CreateTexture("P4.png");
	CreateTexture("BackButton.png");
	CreateTexture("X-Ready.png");
	CreateTexture("Move_Direction.png");
	CreateTexture("UIBarFrame.png");
	CreateTexture("UIBarRed.png");
	CreateTexture("UIBarBlue.png");
	CreateTexture("UIframeimg.png");

	CreateFont("comic.ttf");

	CreateShader("starry.glsl", sf::Shader::Fragment);

	
	
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
void CResourceHolder::CreateShader(std::string _name, std::string _vertexName, std::string _fragmentName) {
	std::string path = "Resources/Shaders/";

	// check that this shader is not already in map
	std::map<std::string, sf::Shader *>::iterator iter = m_shaderMap.find(_name);
	if (iter != m_shaderMap.end())
	{
		std::cout << "Shader: " << _name << " has already been created. " << std::endl;
	}
	else
	{
		sf::Shader *newShader = new sf::Shader();
		newShader->loadFromFile(path + _vertexName, path + _fragmentName);
		m_shaderMap.insert(std::pair<std::string, sf::Shader *>(_name, newShader));
	}
}

void CResourceHolder::CreateShader(std::string _name, sf::Shader::Type _type) {
	std::string path = "Resources/Shaders/";

	// check that this shader is not already in map
	std::map<std::string, sf::Shader *>::iterator iter = m_shaderMap.find(_name);
	if (iter != m_shaderMap.end())
	{
		std::cout << "Shader: " << _name << " has already been created. " << std::endl;
	}
	else
	{
		sf::Shader *newShader = new sf::Shader();
		newShader->loadFromFile(path + _name, _type);
		m_shaderMap.insert(std::pair<std::string, sf::Shader *>(_name, newShader));
	}
}

sf::Shader* CResourceHolder::GetShader(std::string _name) {
	// make sure shader is in map
	std::map<std::string, sf::Shader *>::iterator iter = m_shaderMap.find(_name);
	if (iter != m_shaderMap.end())
	{
		return (iter->second);
	}
	else
	{
		std::cout << "Shader: " << _name << " has not been created yet." << std::endl;
		return (nullptr);
	}
}