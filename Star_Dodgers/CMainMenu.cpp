#include "CGameSettings.h"
#include "CResourceHolder.h"
#include "CMainMenu.h"

CMainMenu::CMainMenu()
{
	// bind master controller to input settings
	m_selectedItem = &m_input.m_selectedItem;
	m_canBindController = (CGameSettings::GetMasterController() == nullptr) ? false : true;

	// get font and set colours
	sf::Font* font = CResourceHolder::GetFont("comic.ttf");
	m_highlight = sf::Color::Cyan;
	m_neutral = sf::Color::White;

	// create buttons and set positions
	m_playButton = new sf::Text("Play", *font);
	m_playButton->setPosition(50, 50);
	m_playButton->setFillColor(m_neutral);

	m_controlsButton = new sf::Text("Controls", *font);
	m_controlsButton->setPosition(950, 50);
	m_controlsButton->setFillColor(m_neutral);

	m_settingsButton = new sf::Text("Settings", *font);
	m_settingsButton->setPosition(50, 650);
	m_settingsButton->setFillColor(m_neutral);

	m_quitButton = new sf::Text("Quit", *font);
	m_quitButton->setPosition(950, 650);
	m_quitButton->setFillColor(m_neutral);

	CWindowUtilities::Draw(m_playButton);
	CWindowUtilities::Draw(m_controlsButton);
	CWindowUtilities::Draw(m_settingsButton);
	CWindowUtilities::Draw(m_quitButton);
}

CMainMenu::~CMainMenu()
{

}


void CMainMenu::Update(float _fDeltaTime)
{
	if (m_canBindController)
	{
		CGameSettings::GetMasterController()->Bind((IGamepadInput)m_input, "MainMenu");
		m_canBindController = false;
	}

	switch (*m_selectedItem)
	{
	case 0: // play button
	{
		m_playButton->setFillColor(m_highlight);
		m_controlsButton->setFillColor(m_neutral);
		m_settingsButton->setFillColor(m_neutral);
		m_quitButton->setFillColor(m_neutral);
		break;
	}
	case 1: // controls button
	{
		m_playButton->setFillColor(m_neutral);
		m_controlsButton->setFillColor(m_highlight);
		m_settingsButton->setFillColor(m_neutral);
		m_quitButton->setFillColor(m_neutral);
		break;
	}
	case 2: // settings button
	{
		m_playButton->setFillColor(m_neutral);
		m_controlsButton->setFillColor(m_neutral);
		m_settingsButton->setFillColor(m_highlight);
		m_quitButton->setFillColor(m_neutral);
		break;
	}
	case 3: // quit button
	{
		m_playButton->setFillColor(m_neutral);
		m_controlsButton->setFillColor(m_neutral);
		m_settingsButton->setFillColor(m_neutral);
		m_quitButton->setFillColor(m_highlight);
		break;
	}
	}
}

void CMainMenu::FixedUpdate()
{

}

void CMainMenu::LateUpdate(float _fDeltaTime)
{

}