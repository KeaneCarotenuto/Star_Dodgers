// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//----------------------------------------------------------
// (c) 2021 Media Design School
//==========================================================
//   File Name  : CResourceHolder.cpp
//----------------------------------------------------------
//  Description : holds all of the recourses that are needed in multiple loctaions
//----------------------------------------------------------
//    Author    : 
//----------------------------------------------------------
//    E-mail    : 
//==========================================================

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
std::map<std::string, sf::SoundBuffer *> CResourceHolder::m_soundBufferMap;

/// <summary>
/// Initialises all of the recources needed in the project
/// </summary>
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
	CreateTexture("PlayerSprite0.png");
	CreateTexture("PlayerSprite1.png");
	CreateTexture("PlayerSprite2.png");
	CreateTexture("PlayerSprite3.png");
	CreateTexture("BackButton.png");
	CreateTexture("X-Ready.png");
	CreateTexture("Move_Direction.png");
	CreateTexture("UIBarFrame.png");
	CreateTexture("UIBarRed.png");
	CreateTexture("UIBarBlue.png");
	CreateTexture("UIframeimg_2P.png");
	CreateTexture("UIframeimg_4P.png");
	CreateTexture("LeftCurveIcon.png");
	CreateTexture("RightCurveIcon.png");
	CreateTexture("NormalThrowIcon.png");
	CreateTexture("FastBallIcon.png");
	CreateSoundBuffer("bullethit_cannon.wav");
	CreateSoundBuffer("Throw.wav");
	CreateSoundBuffer("Dash.wav");
	CreateSoundBuffer("Explosion.wav");
	CreateSoundBuffer("Catch.wav");
	CreateSoundBuffer("GoldenStarPickup.wav");
	CreateSoundBuffer("Powerup.wav");
	CreateSoundBuffer("MenuSelect.wav");
	CreateSoundBuffer("MenuCancel.wav");
	CreateSoundBuffer("MenuMove.wav");
	CreateFont("comic.ttf");

	CreateShader("starry.glsl", sf::Shader::Fragment);
	CreateShader("screenshake.glsl", sf::Shader::Fragment);
}

/// <summary>
/// Gets the render window that is stored in the m_window pointer
/// </summary>
/// <returns>returns the m_window pointer</returns>
sf::RenderWindow *CResourceHolder::GetWindow()
{
	return (m_window);
}

/// <summary>
/// Gets the size of the window
/// </summary>
/// <returns>returns a vector2u with window size</returns>
sf::Vector2u CResourceHolder::GetWindowSize()
{
	return(m_window->getSize());
}

/// <summary>
/// Creates a image with the given name then adds it to the map of created images
/// </summary>
/// <param name="_name">the name/path of the image in the images folder</param>
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

/// <summary>
/// get the image from the map with the given name
/// </summary>
/// <param name="_name">The name used at creation of the image</param>
/// <returns>the image at the map location or a nullptr</returns>
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

/// <summary>
/// creates a texture with the name given and adding it to the texture map
/// </summary>
/// <param name="_name">location/ name of the image with respect to the image folder</param>
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

/// <summary>
/// gets the texture at the map location 
/// </summary>
/// <param name="_name"></param>
/// <returns></returns>
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

/// <summary>
/// creates a font with the given name and stores it on the map 
/// </summary>
/// <param name="_name">the image path/name in respect to the fonts folder</param>
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

/// <summary>
/// gets the font at the map location of name
/// </summary>
/// <param name="_name">the map lookup for the font </param>
/// <returns>the font at the map location or a nullptr</returns>
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
/// <summary>
/// Creates a Shader from the provided file.
/// <para>Author: Nerys</para>
/// </summary>
/// <param name="_name">Filename</param>
/// <param name="_type">Fragment, Geometry, or Vertex</param>
/// <returns></returns>
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

/// <summary>
/// Creates a Shader from the provided file.
/// <para>Author: Nerys</para>
/// </summary>
/// <param name="_name">Filename</param>
/// <param name="_type">Fragment, Geometry, or Vertex</param>
/// <returns></returns>
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

/// <summary>
/// Retrieves a shader by name.
/// <para>Author: Nerys</para>
/// </summary>
/// <param name="_name"></param>
/// <returns></returns>
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

/// <summary>
/// Creates a sound buffer from the provided file.
/// <para> Only WAV, OGG, anf FLAC supported</para>
/// <para>Author: Nerys</para>
/// </summary>
/// <param name="_name"></param>
/// <returns></returns>
void CResourceHolder::CreateSoundBuffer(std::string _name) {
	std::string path = "Resources/Audio/";

	// check that this shader is not already in map
	std::map<std::string, sf::SoundBuffer *>::iterator iter = m_soundBufferMap.find(_name);
	if (iter != m_soundBufferMap.end())
	{
		std::cout << "Shader: " << _name << " has already been created. " << std::endl;
	}
	else
	{
		sf::SoundBuffer *newSoundBuffer = new sf::SoundBuffer();
		newSoundBuffer->loadFromFile(path + _name);
		m_soundBufferMap.insert(std::pair<std::string, sf::SoundBuffer *>(_name, newSoundBuffer));
	}
}

/// <summary>
/// Retrieves a sound buffer by name.
/// <para> Only WAV, OGG, anf FLAC supported</para>
/// <para>Author: Nerys</para>
/// </summary>
/// <param name="_name"></param>
/// <returns></returns>
sf::SoundBuffer* CResourceHolder::GetSoundBuffer(std::string _name) {
	// make sure sound buffer is in map
	std::map<std::string, sf::SoundBuffer *>::iterator iter = m_soundBufferMap.find(_name);
	if (iter != m_soundBufferMap.end())
	{
		return (iter->second);
	}
	else
	{
		std::cout << "Sound buffer: " << _name << " has not been created yet." << std::endl;
		return (nullptr);
	}
}