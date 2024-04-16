#include "windows_ime_manager_plugin.h"

// This must be included before many other Windows headers.
#include <windows.h>

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>

#include <memory>
#include <sstream>

#pragma comment(lib, "imm32.lib")
#pragma comment(lib, "user32.lib")

namespace windows_ime_manager
{

  // static
  void WindowsImeManagerPlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarWindows *registrar)
  {
    auto channel =
        std::make_unique<flutter::MethodChannel<flutter::EncodableValue>>(
            registrar->messenger(), "windows_ime_manager",
            &flutter::StandardMethodCodec::GetInstance());

    auto plugin = std::make_unique<WindowsImeManagerPlugin>();

    channel->SetMethodCallHandler(
        [plugin_pointer = plugin.get()](const auto &call, auto result)
        {
          plugin_pointer->HandleMethodCall(call, std::move(result));
        });

    registrar->AddPlugin(std::move(plugin));
  }

  WindowsImeManagerPlugin::WindowsImeManagerPlugin() {}

  WindowsImeManagerPlugin::~WindowsImeManagerPlugin() {}

  void WindowsImeManagerPlugin::HandleMethodCall(
      const flutter::MethodCall<flutter::EncodableValue> &method_call,
      std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result)
  {
    if (method_call.method_name() == "japaneseHiraganaIme" ||
        method_call.method_name() == "japaneseFullWidthKatakana" ||
        method_call.method_name() == "japaneseHalfWidthKatakana" ||
        method_call.method_name() == "japaneseHalfWidthAlphanumeric")
    {
      HKL japaneseIME = LoadKeyboardLayout(TEXT("00000411"), KLF_ACTIVATE);

      if (japaneseIME == NULL)
      {
        std::cout << "Failed to load Japanese IME" << std::endl;
        result->Error("IME Load Failure", "Failed to load Japanese IME");
        return;
      }

      if (!ActivateKeyboardLayout(japaneseIME, 0))
      {
        std::cout << "Failed to activate Japanese IME" << std::endl;
        result->Error("IME Activation Failure", "Failed to activate Japanese IME");
        return;
      }

      HWND hwnd = GetForegroundWindow();
      HIMC himc = ImmGetContext(hwnd);

      DWORD conversionMode = 0, sentenceMode = 0;
      ImmGetConversionStatus(himc, &conversionMode, &sentenceMode);

      if (method_call.method_name() == "japaneseHiraganaIme")
      {
        conversionMode = IME_CMODE_NATIVE | IME_CMODE_FULLSHAPE;
      }
      else if (method_call.method_name() == "japaneseFullWidthKatakana")
      {
        conversionMode = IME_CMODE_NATIVE | IME_CMODE_KATAKANA | IME_CMODE_FULLSHAPE;
      }
      else if (method_call.method_name() == "japaneseHalfWidthKatakana")
      {
        conversionMode = IME_CMODE_NATIVE | IME_CMODE_KATAKANA;
      }
      else if (method_call.method_name() == "japaneseHalfWidthAlphanumeric")
      {
        conversionMode = IME_CMODE_ALPHANUMERIC;
      }

      sentenceMode = IME_SMODE_NONE;

      ImmSetConversionStatus(himc, conversionMode, sentenceMode);
      ImmSetOpenStatus(himc, true);
      ImmReleaseContext(hwnd, himc);
      result->Success();
    }
    else
    {
      result->NotImplemented();
    }
  }

} // namespace windows_ime_manager
