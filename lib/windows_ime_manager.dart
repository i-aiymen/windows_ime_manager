import 'windows_ime_manager_platform_interface.dart';

class WindowsImeManager {
  Future<String?> setJapaneseIme() {
    return WindowsImeManagerPlatform.instance.setJapaneseIme();
  }
}
