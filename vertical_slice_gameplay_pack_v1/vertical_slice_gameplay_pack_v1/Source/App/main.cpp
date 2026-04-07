#include "Gameplay/VerticalSliceGame.h"
#include <iostream>

int main()
{
    VerticalSliceGame game;
    if (!game.Initialize())
    {
        std::cerr << "Failed to initialize vertical slice.\n";
        return 1;
    }

    game.Update(1.0f / 60.0f);
    game.Render();
    game.AdvanceToNextDay();
    game.Render();
    return 0;
}
