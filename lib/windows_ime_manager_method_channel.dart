import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';

import 'windows_ime_manager.dart';
import 'windows_ime_manager_platform_interface.dart';

/// An implementation of [WindowsImeManagerPlatform] that uses method channels.
class MethodChannelWindowsImeManager extends WindowsImeManagerPlatform {
  /// The method channel used to interact with the native platform.
  @visibleForTesting
  final methodChannel = const MethodChannel('windows_ime_manager');

  Map languageImeToMethod = {
    LanguageIme.japaneseHiraganaIme: 'japaneseHiraganaIme',
    LanguageIme.japaneseFullWidthKatakanaIme: 'japaneseFullWidthKatakanaIme',
    LanguageIme.japaneseHalfWidthKatakanaIme: 'japaneseHalfWidthKatakanaIme',
    LanguageIme.japaneseHalfWidthAlphanumericIme:
        'japaneseHalfWidthAlphanumericIme',
    LanguageIme.englishIme: 'englishIme',
    LanguageIme.arabicIme: 'arabicIme',
    LanguageIme.malayalamIme: 'malayalamIme',
    LanguageIme.hindiIme: 'hindiIme',
    LanguageIme.spanishIme: 'spanishIme',
    LanguageIme.frenchIme: 'frenchIme',
  };

  @override
  Future<String?> setLanguageIme(LanguageIme languageIme) async {
    final version = await methodChannel
        .invokeMethod<String>(languageImeToMethod[languageIme]);
    return version;
  }
}
