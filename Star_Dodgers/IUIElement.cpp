#include "IUIElement.h"

IUIElement::IUIElement() 
{
    UIManager::AddElement(this);
}

IUIElement::~IUIElement() 
{
    UIManager::RemoveElement(this);
}

std::list<IUIElement*> UIManager::m_elements;

void UIManager::AddElement(IUIElement* _element) { UIManager::m_elements.push_back(_element); }

void UIManager::RemoveElement(IUIElement* _element) { UIManager::m_elements.remove(_element); }