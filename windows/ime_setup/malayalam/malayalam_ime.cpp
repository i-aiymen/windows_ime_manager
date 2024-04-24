#include "malayalam_ime.h"

bool setupMalayalamIme()
{
    HKL malayalamIME = LoadKeyboardLayout(TEXT("0000044C"), KLF_ACTIVATE);
    if (malayalamIME == NULL)
    {
        std::cout << "Failed to load Malayalam IME" << std::endl;
        return false;
    }

    if (!ActivateKeyboardLayout(malayalamIME, 0))
    {
        std::cout << "Failed to activate Malayalam IME" << std::endl;
        return false;
    }

    HWND hwnd = GetForegroundWindow();
    HIMC himc = ImmGetContext(hwnd);

    DWORD conversionMode = 0, sentenceMode = 0;
    ImmGetConversionStatus(himc, &conversionMode, &sentenceMode);

    sentenceMode = IME_SMODE_NONE;

    ImmSetConversionStatus(himc, conversionMode, sentenceMode);
    ImmSetOpenStatus(himc, true);
    ImmReleaseContext(hwnd, himc);
    return true;
}
