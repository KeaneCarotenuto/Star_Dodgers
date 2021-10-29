#include "CGameManager.h"
#include "CResourceHolder.h"
#include "CLobby.h"
#include"CControlsMenu.h"
#include "CMainMenu.h"

CMainMenu::CMainMenu()
{
	// bind master controller to input settings
	m_selectedItem = 0;
	m_canBindController = (CGameManager::GetInstance()->GetMasterController() == nullptr) ? false : true;

	// get font and set colours
	sf::Font *font = CResourceHolder::GetFont("comic.ttf");
	m_highlight = sf::Color::Cyan;
	m_neutral = sf::Color::White;

	// create buttons and set positions
	m_playButton = new sf::Text("Play", *font);
	m_playButton->setPosition(50, 50);
	m_playButton->setFillColor(m_neutral);

	m_controlsButton = new sf::Text("Controls", *font);
	m_controlsButton->setPosition(50, 250);
	m_controlsButton->setFillColor(m_neutral);


	m_quitButton = new sf::Text("Quit", *font);
	m_quitButton->setPosition(50, 450);
	m_quitButton->setFillColor(m_neutral);

	m_moveSFX.setBuffer(*CResourceHolder::GetSoundBuffer("MenuMove.wav"));
	m_selectSFX.setBuffer(*CResourceHolder::GetSoundBuffer("MenuSelect.wav"));
	m_cancelSFX.setBuffer(*CResourceHolder::GetSoundBuffer("MenuCancel.wav"));

	CWindowUtilities::Draw(m_playButton);
	CWindowUtilities::Draw(m_controlsButton);
	CWindowUtilities::Draw(m_quitButton);
}

CMainMenu::~CMainMenu()
{
	for (unsigned int ele = 0; ele < CWindowUtilities::m_drawList.size(); ele++)
	{
		if (CWindowUtilities::m_drawList[ele] == m_playButton)
		{
			// if play button is found in ToDrawList, create an iterator pointing to the position of the play button then
			// erase the element at the iterator and the 3 elements after it so that all buttons are removed from the list
			std::vector<sf::Drawable*>::iterator iter = CWindowUtilities::m_drawList.begin() + ele;
			CWindowUtilities::m_drawList.erase(iter, iter + 3);
			break;
		}
	}

	delete m_playButton;
	m_playButton = 0;

	delete m_controlsButton; 
	m_controlsButton = 0;

	delete m_quitButton;
	m_quitButton = 0;
}

void CMainMenu::Update(float _fDeltaTime)
{
	if (m_canBindController)
	{
		CGameManager::GetInstance()->GetMasterController()->Bind(dynamic_cast<IGamepadInput *>(this), "MainMenu");
		m_canBindController = false;
	}

	switch (m_selectedItem)
	{
	case 0: // play button
	{
		m_playButton->setFillColor(m_highlight);
		m_controlsButton->setFillColor(m_neutral);
		m_quitButton->setFillColor(m_neutral);
		break;
	}
	case 1: // controls button
	{
		m_playButton->setFillColor(m_neutral);
		m_controlsButton->setFillColor(m_highlight);
		m_quitButton->setFillColor(m_neutral);
		break;
	}
	case 2: // settings button
	{
		m_playButton->setFillColor(m_neutral);
		m_controlsButton->setFillColor(m_neutral);
		m_quitButton->setFillColor(m_highlight);
		break;
	}
	default:
	{
		std::cout << "menu error: m_selectedItem == " << m_selectedItem << " : out of range." << std::endl;
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

void CMainMenu::OnButtonInput(GamepadButtonEvent _event)
{
	switch (_event.button)
	{
	case Button::DPAD_UP:
	{
		if (_event.type == GamepadButtonEvent::EventType::PRESSED)
		{
			// if the selected item is less than 0 after pressed, then change it to the last item in the menu
			if ((m_selectedItem) <= 0)
			{
				m_selectedItem = 2;
			}
			else
			{
				m_selectedItem--;
			}
			m_moveSFX.play();
		}
		break;
	}
	case Button::DPAD_DOWN:
	{
		if (_event.type == GamepadButtonEvent::EventType::PRESSED)
		{
			// if the selected item is less than 0 after pressed, then change it to the last item in the menu
			if ((m_selectedItem) >= 2)
			{
				m_selectedItem = 0;
			}
			else
			{
				m_selectedItem++;
			}
			m_moveSFX.play();
		}
		break;
	}
	case Button::SOUTH:
	{
		if (_event.type == GamepadButtonEvent::EventType::PRESSED)
		{
			switch (m_selectedItem)
			{
			case 0: // play
			{
				CGameManager::GetInstance()->ChangeActiveScene<CLobby>();
				CGameManager::GetInstance()->GetMasterController()->Unbind("MainMenu");
				m_selectSFX.play();
				break;
			}
			case 1: // controls
			{
				CGameManager::GetInstance()->ChangeActiveScene<CControlsMenu>();
				CGameManager::GetInstance()->GetMasterController()->Unbind("MainMenu");
				m_selectSFX.play();
				break;
			}
			case 2: // quit game
			{
				CResourceHolder::GetWindow()->close();
				m_cancelSFX.play();
				break;
			}
			
			}
		}
	}
	}
}
