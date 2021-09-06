#ifndef EBFCE19A_AF61_4BFE_992B_7CBA03948A5B
#define EBFCE19A_AF61_4BFE_992B_7CBA03948A5B
#include <memory>
#include <list>

class UIManager;
class IUIElement
{
    friend class UIManager;
    friend struct UIElementComparator;
public:

private:
    virtual void DrawUI();
    UIManager* m_manager;
    int m_Zindex;
protected:
    //TODO: Fix this
    /*IUIElement(UIManager* _manager){ m_manager=_manager; m_manager->AddElement(this) };
    ~IUIElement(){ m_manager->RemoveElement() };*/
};
struct UIElementComparator
{
    bool operator ()(const std::shared_ptr<IUIElement> lhs, const std::shared_ptr<IUIElement> rhs)
    {
        return lhs->m_Zindex < rhs->m_Zindex;
    }
};
class UIManager 
{
    friend class IUIElement;
public:
    static UIManager* GetUIManager() { if(m_instance == nullptr) m_instance = new UIManager(); return m_instance; };
    void Draw()
    {
        m_elements.sort(UIElementComparator());
        for(auto element : m_elements) { element->DrawUI(); }
    };
private:
    std::list<std::shared_ptr<IUIElement>> m_elements;
    static UIManager* m_instance;
    void AddElement(std::shared_ptr<IUIElement> _element) { m_elements.push_back(_element); }
    void RemoveElement(std::shared_ptr<IUIElement> _element) { m_elements.remove(_element); }
    UIManager();
};
#endif /* EBFCE19A_AF61_4BFE_992B_7CBA03948A5B */
