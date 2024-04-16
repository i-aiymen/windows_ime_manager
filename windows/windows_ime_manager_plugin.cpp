#include "windows_ime_manager_plugin.h"

// This must be included before many other Windows headers.
#include <windows.h>

// For getPlatformVersion; remove unless needed for your plugin implementation.
#include <VersionHelpers.h>

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
    if (method_call.method_name() == "japaneseImeOn" || method_call.method_name() == "japaneseImeOff")
    {
      HKL japaneseIME = LoadKeyboardLayout(TEXT("00000411"), KLF_ACTIVATE);

      if (japaneseIME == NULL)
      {
        std::cout << "Failed to load Japanese IME" << std::endl;
      }
      else
      {
        if (!ActivateKeyboardLayout(japaneseIME, 0))
        {
          std::cout << "Failed to activate Japanese IME" << std::endl;
        }
      }

      HWND hwnd = GetForegroundWindow();
      HIMC himc = ImmGetContext(hwnd);
      if (method_call.method_name() == "japaneseImeOn")
      {
        ImmSetOpenStatus(himc, true);
      }
      else
      {
        ImmSetOpenStatus(himc, false);
      }
      ImmReleaseContext(hwnd, himc);
      result->Success();
    }
    else
    {
      result->NotImplemented();
    }
  }

} // namespace windows_ime_manager
