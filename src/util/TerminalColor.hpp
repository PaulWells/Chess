#pragma once
#include <string>
#include <memory>

class TerminalColor
{
public:
    static void SetBackgroundWhite();
    static void SetBackgroundBlack();

    static std::string Red();
    static std::string Green();
    static std::string Brown();
    static std::string DarkBlue();
    static std::string Blue();
    static std::string Grey();
    static std::string Reset();

private:
    static TerminalColor& GetInstance();
    void SetBackgroundWhitePrivate();
    void SetBackgroundBlackPrivate();

    std::string RedPrivate();
    std::string GreenPrivate();
    std::string BrownPrivate();
    std::string DarkBluePrivate();
    std::string BluePrivate();
    std::string GreyPrivate();
    std::string ResetPrivate();
    TerminalColor();
    int m_backgroundColor;
};
