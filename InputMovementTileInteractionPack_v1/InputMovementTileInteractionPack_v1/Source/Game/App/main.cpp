#include <windows.h>
#include <string>
#include <chrono>
#include "Game/Input/InputSystem.h"
#include "Game/Player/PlayerController.h"
#include "Game/World/TileMap.h"

using namespace Game;

namespace
{
    LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
            case WM_DESTROY:
                PostQuitMessage(0);
                return 0;
            default:
                return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }

    FTileMap CreateTestMap()
    {
        FTileMap map(8, 8);

        for (int y = 0; y < map.GetHeight(); ++y)
        {
            for (int x = 0; x < map.GetWidth(); ++x)
            {
                map.SetTile({ x, y }, { ETileType::Grass, false, true });
            }
        }

        map.SetTile({ 1, 1 }, { ETileType::Tree, true, true });
        map.SetTile({ 3, 2 }, { ETileType::Rock, true, true });
        map.SetTile({ 4, 4 }, { ETileType::Water, true, true });
        map.SetTile({ 2, 3 }, { ETileType::Dirt, false, true });
        map.SetTile({ 6, 1 }, { ETileType::Tree, true, true });
        map.SetTile({ 0, 0 }, { ETileType::Rock, true, true });
        return map;
    }
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow)
{
    const wchar_t CLASS_NAME[] = L"InputMovementTileInteractionPackWindowClass";

    WNDCLASS wc {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

    if (!RegisterClass(&wc))
    {
        return 1;
    }

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Input + Movement + Tile Interaction Pack v1",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        1280,
        240,
        nullptr,
        nullptr,
        hInstance,
        nullptr);

    if (hwnd == nullptr)
    {
        return 1;
    }

    ShowWindow(hwnd, nCmdShow);

    FTileMap map = CreateTestMap();
    FInputSystem input;
    FPlayerController player(map);

    using clock = std::chrono::high_resolution_clock;
    auto lastTime = clock::now();

    bool running = true;
    while (running)
    {
        MSG msg {};
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                running = false;
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        const auto now = clock::now();
        const std::chrono::duration<float> delta = now - lastTime;
        lastTime = now;

        input.Update();
        if (input.Get(EInputAction::Pause).bPressed)
        {
            running = false;
        }

        player.Update(delta.count(), input);
        const std::wstring title = L"Input + Movement + Tile Interaction Pack v1 | " + player.BuildDebugStatus(map);
        SetWindowTextW(hwnd, title.c_str());

        Sleep(16);
    }

    return 0;
}
