//==========================================================
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//----------------------------------------------------------
// (c) 2021 Media Design School
//==========================================================
//   File Name  : 
//----------------------------------------------------------
//  Description :
//----------------------------------------------------------
//    Author    : 
//----------------------------------------------------------
//    E-mail    : 
//==========================================================

#ifndef EBFCE19A_AF61_4BFE_992B_7CBA03948A5B
#define EBFCE19A_AF61_4BFE_992B_7CBA03948A5B
#include <memory>
#include <list>
#include <algorithm>
#include "EasySFML.h"
#include "CResourceHolder.h"

class IUIElement
{
    friend class UIManager;
    friend struct UIElementComparator;
public:
    void SetZIndex(int _zIndex){m_Zindex = _zIndex;};
    int GetZIndex(){return m_Zindex;};
private:
    virtual void DrawUI(sf::RenderWindow* _window) = 0;
    //UIManager* m_manager;
    int m_Zindex;
protected:
    IUIElement();
    virtual ~IUIElement();
};
struct UIElementComparator
{
    bool operator ()(const IUIElement* lhs, IUIElement* rhs)
    {
        return lhs->m_Zindex < rhs->m_Zindex;
    }
};
class UIManager 
{
    friend class IUIElement;
public:
    static UIManager* GetUIManager() { if(m_instance == nullptr) m_instance = new UIManager(); return m_instance; };
    static void Draw()
    {
        m_elements.sort(UIElementComparator());
        std::for_each(m_elements.begin(), m_elements.end(), [&](IUIElement* element){element->DrawUI(CResourceHolder::GetWindow());});
    };
private:
    static std::list<IUIElement*> m_elements;
    static UIManager* m_instance;
    static void AddElement(IUIElement* _element);
    static void RemoveElement(IUIElement* _element);
    UIManager();
};
#endif /* EBFCE19A_AF61_4BFE_992B_7CBA03948A5B */
