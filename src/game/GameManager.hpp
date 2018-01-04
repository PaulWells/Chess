#pragma once

#include "MoveApplicator.hpp"
#include <memory>

class GameManager
{
public:
    GameManager();
    void StartGame();
private:
    std::unique_ptr<MoveApplicator> m_moveApplicator;
};
