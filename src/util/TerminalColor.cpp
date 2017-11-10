#include "TerminalColor.hpp"
#include <iostream>

static const int BACKGROUND_RED = 41;
static const int BACKGROUND_GREEN = 42;
static const int BACKGROUND_BLACK = 40;

TerminalColor& TerminalColor::GetInstance()
{
    static TerminalColor terminalColor;
    return terminalColor;
}

TerminalColor::TerminalColor()
{
    m_backgroundColor = BACKGROUND_BLACK;
}

void TerminalColor::SetBackgroundWhite()
{
    return TerminalColor::GetInstance().SetBackgroundWhitePrivate();
}

void TerminalColor::SetBackgroundWhitePrivate()
{
    m_backgroundColor = BACKGROUND_GREEN;
}

void TerminalColor::SetBackgroundBlack()
{
    return TerminalColor::GetInstance().SetBackgroundBlackPrivate();
}

void TerminalColor::SetBackgroundBlackPrivate()
{
    m_backgroundColor = BACKGROUND_RED;
}

std::string TerminalColor::Red()
{
    return TerminalColor::GetInstance().RedPrivate();
}

std::string TerminalColor::RedPrivate()
{
    return ("\x1b[31;" + std::to_string(m_backgroundColor) + "m");
}

std::string TerminalColor::Green()
{
    return TerminalColor::GetInstance().GreenPrivate();
}

std::string TerminalColor::GreenPrivate()
{
    return ("\x1b[32;" + std::to_string(m_backgroundColor) + "m");
}

std::string TerminalColor::Brown()
{
    return TerminalColor::GetInstance().BrownPrivate();
}

std::string TerminalColor::BrownPrivate()
{
    return ("\x1b[33;" + std::to_string(m_backgroundColor) + "m");
}

std::string TerminalColor::DarkBlue()
{
    return TerminalColor::GetInstance().DarkBluePrivate();
}

std::string TerminalColor::DarkBluePrivate()
{
    return ("\x1b[34;" + std::to_string(m_backgroundColor) + "m");
}

std::string TerminalColor::Blue()
{
    return TerminalColor::GetInstance().BluePrivate();
}

std::string TerminalColor::BluePrivate()
{
    return ("\x1b[36;" + std::to_string(m_backgroundColor) + "m");
}

std::string TerminalColor::Grey()
{
    return TerminalColor::GetInstance().GreyPrivate();
}

std::string TerminalColor::GreyPrivate()
{
    return ("\x1b[37;" + std::to_string(m_backgroundColor) + "m");
}

std::string TerminalColor::Reset()
{
    return TerminalColor::GetInstance().ResetPrivate();
}

std::string TerminalColor::ResetPrivate()
{
    m_backgroundColor = BACKGROUND_BLACK;
    return ("\x1b[0m");
}
