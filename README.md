# windows_ime_manager

[![pub package](https://img.shields.io/pub/v/windows_ime_manager.svg)](https://pub.dev/packages/windows_ime_manager)
[![style: lint](https://img.shields.io/badge/style-lint-4BC0F5.svg)](https://pub.dev/packages/lint)

The `windows_ime_manager` package enables easy management of Input Method Editors (IME) for Windows applications developed with Flutter. It supports Japanese and English languages, allowing for straightforward IME setup and switching. This package is designed to enhance multilingual input in desktop applications, providing a reliable and simple solution for developers looking to incorporate diverse language support.

Feel free to connect me at: [<img align="center" height="30" src="https://img.shields.io/badge/linkedin-blue.svg?&style=for-the-badge&logo=linkedin&logoColor=white" />][LinkedIn]

## Features Supported

| Features               | Windows |
|------------------------|---------|
| Setup IME          | :heavy_check_mark: |


## Platform Support

| Windows |
|---------|
| ✔       |

## Languages Supported

| Languages |
|-----------|
| Japanese  |
| English   |
| Arabic    |
| Malayalam   |
| Hindi     |

## Types of IME Supported

| IME Types |
|-----------|
| English |
| Arabic  |
| Malayalam |
| Hindi  |
| Hiragana |
| Half-Width Katakana |
| Full-Width Katakana |
| Half-Width Alphanumeric|



## Usage

Import the package with:
```
import 'package:windows_ime_manager/windows_ime_manager.dart';
```

Create an instance of the `WindowsImeManager` class:
```
final _windowsImeManagerPlugin = WindowsImeManager();
```

Create a function to set the IME using the enums:
```
Future<void> setLanguageIme(LanguageIme languageIme) async {
  try {
    await _windowsImeManagerPlugin.setLanguageIme(languageIme);
  } on PlatformException {
    debugPrint('Failed to set language IME.');
  }
}
```

Call the function with the desired LanguageIme enums:
```
setLanguageIme(LanguageIme.japaneseHalfWidthKatakanaIme);
setLanguageIme(LanguageIme.englishIme);
```

See the example app for detailed implementation information.




[linkedin]: https://www.linkedin.com/in/aiymenlatheef/

