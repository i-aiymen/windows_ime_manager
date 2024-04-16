#include "japanese_ime.h"
#include <iostream>

bool SetupJapaneseIme(const std::string &methodName)
{
    HKL japaneseIME = LoadKeyboardLayout(TEXT("00000411"), KLF_ACTIVATE);
    if (japaneseIME == NULL)
    {
        std::cout << "Failed to load Japanese IME" << std::endl;
        return false;
    }

    if (!ActivateKeyboardLayout(japaneseIME, 0))
    {
        std::cout << "Failed to activate Japanese IME" << std::endl;
        return false;
    }

    HWND hwnd = GetForegroundWindow();
    HIMC himc = ImmGetContext(hwnd);

    DWORD conversionMode = 0, sentenceMode = IME_SMODE_NONE;
    if (methodName == "japaneseHiraganaIme")
    {
        conversionMode = IME_CMODE_NATIVE | IME_CMODE_FULLSHAPE;
    }
    else if (methodName == "japaneseFullWidthKatakana")
    {
        conversionMode = IME_CMODE_NATIVE | IME_CMODE_KATAKANA | IME_CMODE_FULLSHAPE;
    }
    else if (methodName == "japaneseHalfWidthKatakana")
    {
        conversionMode = IME_CMODE_NATIVE | IME_CMODE_KATAKANA;
    }
    else if (methodName == "japaneseHalfWidthAlphanumeric")
    {
        conversionMode = IME_CMODE_ALPHANUMERIC;
    }

    ImmSetConversionStatus(himc, conversionMode, sentenceMode);
    ImmSetOpenStatus(himc, true);
    ImmReleaseContext(hwnd, himc);
    return true;
}
