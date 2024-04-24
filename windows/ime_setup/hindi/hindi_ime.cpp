#include "hindi_ime.h"

bool setupHindiIme()
{
    HKL hindiIME = LoadKeyboardLayout(TEXT("00000439"), KLF_ACTIVATE);
    if (hindiIME == NULL)
    {
        std::cout << "Failed to load Hindi IME" << std::endl;
        return false;
    }

    if (!ActivateKeyboardLayout(hindiIME, 0))
    {
        std::cout << "Failed to activate Hindi IME" << std::endl;
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
