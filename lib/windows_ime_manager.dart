import 'dart:io';

import 'package:flutter/foundation.dart';

import 'windows_ime_manager_platform_interface.dart';

enum LanguageIme {
  japaneseHiraganaIme,
  japaneseFullWidthKatakanaIme,
  japaneseHalfWidthKatakanaIme,
  japaneseHalfWidthAlphanumericIme,
  englishIme,
  arabicIme,
  malayalamIme,
  hindiIme,
  spanishIme,
  frenchIme,
  russianIme,
  chineseIme,
  dutchIme,
  germanIme,
  italianIme,
}

class WindowsImeManager {
  Future<String?> setLanguageIme(LanguageIme languageIme) {
    return !kIsWeb && Platform.isWindows
        ? WindowsImeManagerPlatform.instance.setLanguageIme(languageIme)
        : Future.value(null);
  }
}
