import 'windows_ime_manager_platform_interface.dart';

enum LanguageIme {
  japaneseHiraganaIme,
  japaneseFullWidthKatakanaIme,
  japaneseHalfWidthKatakanaIme,
  japaneseHalfWidthAlphanumericIme,
  englishIme,
}

class WindowsImeManager {
  Future<String?> setLanguageIme(LanguageIme languageIme) {
    return WindowsImeManagerPlatform.instance.setLanguageIme(languageIme);
  }
}
