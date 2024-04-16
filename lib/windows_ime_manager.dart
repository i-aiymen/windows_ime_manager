import 'windows_ime_manager_platform_interface.dart';

class WindowsImeManager {
  Future<String?> setLanguageIme(String language, String type) {
    return WindowsImeManagerPlatform.instance.setLanguageIme(language, type);
  }
}
