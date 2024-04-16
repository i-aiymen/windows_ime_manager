#include "english_ime.h"

bool setupEnglishIme()
{
    HKL englishIME = LoadKeyboardLayout(TEXT("00000409"), KLF_ACTIVATE);
    if (englishIME == NULL)
    {
        std::cout << "Failed to load English IME" << std::endl;
        return false;
    }

    if (!ActivateKeyboardLayout(englishIME, 0))
    {
        std::cout << "Failed to activate English IME" << std::endl;
        return false;
    }

    HWND hwnd = GetForegroundWindow();
    HIMC himc = ImmGetContext(hwnd);

    DWORD conversionMode = 0, sentenceMode = 0;
    ImmGetConversionStatus(himc, &conversionMode, &sentenceMode);

    conversionMode = IME_CMODE_ALPHANUMERIC;
    sentenceMode = IME_SMODE_NONE;

    ImmSetConversionStatus(himc, conversionMode, sentenceMode);
    ImmSetOpenStatus(himc, true);
    ImmReleaseContext(hwnd, himc);
    return true;
}
