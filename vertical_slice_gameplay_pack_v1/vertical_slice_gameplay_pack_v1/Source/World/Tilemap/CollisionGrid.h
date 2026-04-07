#pragma once

#include <vector>

class CollisionGrid
{
public:
    void Resize(int width, int height);
    bool IsBlocked(int x, int y) const;
    void SetBlocked(int x, int y, bool blocked);
    int GetWidth() const { return m_width; }
    int GetHeight() const { return m_height; }

private:
    bool InBounds(int x, int y) const;

    int m_width = 0;
    int m_height = 0;
    std::vector<unsigned char> m_cells;
};
