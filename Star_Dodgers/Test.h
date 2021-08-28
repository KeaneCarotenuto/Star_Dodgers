#ifndef TEST_H
#define TEST_H
#include "IGamepadInput.h"
#include <iostream>

class InputTest : public IGamepadInput
{
public:
        InputTest(){};

private:
    void OnButtonInput(GamepadButtonEvent _event);
};
#endif