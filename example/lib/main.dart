import 'dart:async';

import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:windows_ime_manager/windows_ime_manager.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatefulWidget {
  const MyApp({super.key});

  @override
  State<MyApp> createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  final _windowsImeManagerPlugin = WindowsImeManager();

  @override
  void initState() {
    super.initState();
    setLanguageIme('Japanese', 'japaneseHiraganaIme');
  }

  Future<void> setLanguageIme(String language, String type) async {
    try {
      await _windowsImeManagerPlugin.setLanguageIme(language, type);
    } on PlatformException {
      debugPrint('Failed to set language IME.');
    }
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
          title: const Text('Windows IME Manager Example'),
        ),
        body: Center(
          child: Container(
            constraints: const BoxConstraints(maxWidth: 500),
            child: Column(
              mainAxisAlignment: MainAxisAlignment.center,
              children: <Widget>[
                Focus(
                  onFocusChange: (hasFocus) {
                    if (hasFocus) {
                      setLanguageIme(
                          'Japanese', 'japaneseHalfWidthKatakanaIme');
                    }
                  },
                  child: const TextField(
                    decoration: InputDecoration(
                      labelText: 'Japanese Half-Width Katakana',
                      border: OutlineInputBorder(),
                    ),
                  ),
                ),
                const SizedBox(height: 20),
                Focus(
                  onFocusChange: (hasFocus) {
                    if (hasFocus) {
                      setLanguageIme(
                          'Japanese', 'japaneseFullWidthKatakanaIme');
                    }
                  },
                  child: const TextField(
                    decoration: InputDecoration(
                      labelText: 'Japanese Full-Width Katakana',
                      border: OutlineInputBorder(),
                    ),
                  ),
                ),
                const SizedBox(height: 20),
                Focus(
                  onFocusChange: (hasFocus) {
                    if (hasFocus) {
                      setLanguageIme('Japanese', 'japaneseHiraganaIme');
                    }
                  },
                  child: const TextField(
                    decoration: InputDecoration(
                      labelText: 'Japanese Hiragana IME',
                      border: OutlineInputBorder(),
                    ),
                  ),
                ),
                const SizedBox(height: 40),
                ElevatedButton(
                  onPressed: () {},
                  child: const Text('Submit'),
                ),
              ],
            ),
          ),
        ),
      ),
    );
  }
}
