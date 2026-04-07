#include "World/Tilemap/CollisionGrid.h"

void CollisionGrid::Resize(int width, int height)
{
    m_width = width;
    m_height = height;
    m_cells.assign(static_cast<size_t>(width * height), 0);
}

bool CollisionGrid::InBounds(int x, int y) const
{
    return x >= 0 && y >= 0 && x < m_width && y < m_height;
}

bool CollisionGrid::IsBlocked(int x, int y) const
{
    if (!InBounds(x, y))
        return true;
    return m_cells[static_cast<size_t>(y * m_width + x)] != 0;
}

void CollisionGrid::SetBlocked(int x, int y, bool blocked)
{
    if (!InBounds(x, y))
        return;
    m_cells[static_cast<size_t>(y * m_width + x)] = blocked ? 1 : 0;
}
