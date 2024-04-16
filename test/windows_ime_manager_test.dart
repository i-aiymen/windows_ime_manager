// import 'package:flutter_test/flutter_test.dart';
// import 'package:windows_ime_manager/windows_ime_manager.dart';
// import 'package:windows_ime_manager/windows_ime_manager_platform_interface.dart';
// import 'package:windows_ime_manager/windows_ime_manager_method_channel.dart';
// import 'package:plugin_platform_interface/plugin_platform_interface.dart';

// class MockWindowsImeManagerPlatform
//     with MockPlatformInterfaceMixin
//     implements WindowsImeManagerPlatform {

//   @override
//   Future<String?> getPlatformVersion() => Future.value('42');
// }

// void main() {
//   final WindowsImeManagerPlatform initialPlatform = WindowsImeManagerPlatform.instance;

//   test('$MethodChannelWindowsImeManager is the default instance', () {
//     expect(initialPlatform, isInstanceOf<MethodChannelWindowsImeManager>());
//   });

//   test('getPlatformVersion', () async {
//     WindowsImeManager windowsImeManagerPlugin = WindowsImeManager();
//     MockWindowsImeManagerPlatform fakePlatform = MockWindowsImeManagerPlatform();
//     WindowsImeManagerPlatform.instance = fakePlatform;

//     expect(await windowsImeManagerPlugin.setJapaneseIme(), '42');
//   });
// }
