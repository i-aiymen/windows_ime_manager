#include "arabic_ime.h"

bool setupArabicIme()
{
    HKL arabicIME = LoadKeyboardLayout(TEXT("00000401"), KLF_ACTIVATE);
    if (arabicIME == NULL)
    {
        std::cout << "Failed to load Arabic IME" << std::endl;
        return false;
    }

    if (!ActivateKeyboardLayout(arabicIME, 0))
    {
        std::cout << "Failed to activate Arabic IME" << std::endl;
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
