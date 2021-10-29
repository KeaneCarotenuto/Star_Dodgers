#include "IUIElement.h"

/// <summary>
/// Constructor
/// <para>Author: Nerys</para>
/// </summary>
/// <returns></returns>
IUIElement::IUIElement() 
{
    UIManager::AddElement(this);
}

/// <summary>
/// Destructor
/// <para>Author: Nerys</para>
/// </summary>
/// <returns></returns>
IUIElement::~IUIElement() 
{
    UIManager::RemoveElement(this);
}

std::list<IUIElement*> UIManager::m_elements;

/// <summary>
/// Adds an element to the collection of elements.
/// <para>Author: Nerys</para>
/// </summary>
/// <returns></returns>
void UIManager::AddElement(IUIElement* _element) { UIManager::m_elements.push_back(_element); }

/// <summary>
/// Removes an element from the collection of elements.
/// <para>Author: Nerys</para>
/// </summary>
/// <returns></returns>
void UIManager::RemoveElement(IUIElement* _element) { UIManager::m_elements.remove(_element); }