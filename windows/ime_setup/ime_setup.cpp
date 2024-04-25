#include "ime_setup.h"

bool imeSetup(const std::string &methodName)
{

    std::map<std::string, std::string> languageNames = {
        {"japaneseHiraganaIme", "Japanese"},
        {"japaneseFullWidthKatakanaIme", "Japanese"},
        {"japaneseHalfWidthKatakanaIme", "Japanese"},
        {"japaneseHalfWidthAlphanumericIme", "Japanese"},
        {"englishIme", "English"},
        {"arabicIme", "Arabic"},
        {"malayalamIme", "Malayalam"},
        {"hindiIme", "Hindi"},
        {"spanishIme", "Spanish"},
        {"frenchIme", "French"},
    };

    std::map<std::string, std::string> languageCodes = {
        {"English", "00000409"},
        {"Japanese", "00000411"},
        {"Malayalam", "0000044C"},
        {"Hindi", "00000439"},
        {"Arabic", "00000401"},
        {"Spanish", "0000040A"},
        {"French", "0000040C"},
    };

    std::string languageName = languageNames[methodName];
    std::string languageCode = languageCodes[languageName];

    std::wstring wstr = std::wstring(languageCode.begin(), languageCode.end());
    LPCWSTR lwstr = wstr.c_str();
    HKL languageIME = LoadKeyboardLayout(lwstr, KLF_ACTIVATE);
    if (languageIME == NULL)
    {
        std::cout << "Failed to load " << languageName << " IME" << std::endl;
        return false;
    }

    if (!ActivateKeyboardLayout(languageIME, 0))
    {
        std::cout << "Failed to activate " << languageName << " IME" << std::endl;
        return false;
    }

    HWND hwnd = GetForegroundWindow();
    HIMC himc = ImmGetContext(hwnd);

    DWORD conversionMode = 0, sentenceMode = IME_SMODE_NONE;
    if (methodName == "japaneseHiraganaIme")
    {
        conversionMode = IME_CMODE_NATIVE | IME_CMODE_FULLSHAPE;
    }
    else if (methodName == "japaneseFullWidthKatakanaIme")
    {
        conversionMode = IME_CMODE_NATIVE | IME_CMODE_KATAKANA | IME_CMODE_FULLSHAPE;
    }
    else if (methodName == "japaneseHalfWidthKatakanaIme")
    {
        conversionMode = IME_CMODE_NATIVE | IME_CMODE_KATAKANA;
    }
    else if (methodName == "japaneseHalfWidthAlphanumericIme")
    {
        conversionMode = IME_CMODE_ALPHANUMERIC;
    }
    else
    {
        ImmGetConversionStatus(himc, &conversionMode, &sentenceMode);
        if (methodName == "englishIme")
        {
            conversionMode = IME_CMODE_ALPHANUMERIC;
        }
    }

    ImmSetConversionStatus(himc, conversionMode, sentenceMode);
    ImmSetOpenStatus(himc, true);
    ImmReleaseContext(hwnd, himc);
    return true;
}
