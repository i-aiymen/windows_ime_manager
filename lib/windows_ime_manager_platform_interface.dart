import 'package:plugin_platform_interface/plugin_platform_interface.dart';

import 'windows_ime_manager_method_channel.dart';

abstract class WindowsImeManagerPlatform extends PlatformInterface {
  /// Constructs a WindowsImeManagerPlatform.
  WindowsImeManagerPlatform() : super(token: _token);

  static final Object _token = Object();

  static WindowsImeManagerPlatform _instance = MethodChannelWindowsImeManager();

  /// The default instance of [WindowsImeManagerPlatform] to use.
  ///
  /// Defaults to [MethodChannelWindowsImeManager].
  static WindowsImeManagerPlatform get instance => _instance;

  /// Platform-specific implementations should set this with their own
  /// platform-specific class that extends [WindowsImeManagerPlatform] when
  /// they register themselves.
  static set instance(WindowsImeManagerPlatform instance) {
    PlatformInterface.verifyToken(instance, _token);
    _instance = instance;
  }

  Future<String?> setLanguageIme(String language, String type) {
    throw UnimplementedError('languageIme() has not been implemented.');
  }
}
