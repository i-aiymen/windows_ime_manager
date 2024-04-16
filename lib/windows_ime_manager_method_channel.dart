import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';

import 'windows_ime_manager_platform_interface.dart';

/// An implementation of [WindowsImeManagerPlatform] that uses method channels.
class MethodChannelWindowsImeManager extends WindowsImeManagerPlatform {
  /// The method channel used to interact with the native platform.
  @visibleForTesting
  final methodChannel = const MethodChannel('windows_ime_manager');

  @override
  Future<String?> setLanguageIme(String language, String type) async {
    final version =
        await methodChannel.invokeMethod<String>(type, <String, dynamic>{
      'languageName': language,
      'methodName': type,
    });
    return version;
  }
}
