#include "windows_ime_manager_plugin.h"

// This must be included before many other Windows headers.
#include <windows.h>

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>
#include <memory>
#include <sstream>

// IME setup files for different languages
#include "ime_setup/japanese/japanese_ime.h"
#include "ime_setup/english/english_ime.h"
#include "ime_setup/arabic/arabic_ime.h"
#include "ime_setup/malayalam/malayalam_ime.h"
#include "ime_setup/hindi/hindi_ime.h"
#include "ime_setup/ime_setup.h"

// IME files
#pragma comment(lib, "imm32.lib")
#pragma comment(lib, "user32.lib")

namespace windows_ime_manager
{

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

    if (!imeSetup(method_call.method_name(), ""))
    {
      result->Error("IME Setup Failure", "Failed to setup language IME");
      return;
    }
    result->Success();

    if (method_call.method_name() == "japaneseHiraganaIme" || method_call.method_name() == "japaneseFullWidthKatakanaIme" || method_call.method_name() == "japaneseHalfWidthKatakanaIme" || method_call.method_name() == "japaneseHalfWidthAlphanumericIme")
    {
      if (!setupJapaneseIme(method_call.method_name()))
      {
        result->Error("IME Setup Failure", "Failed to setup Japanese IME");
        return;
      }
      result->Success();
    }
    else if (method_call.method_name() == "englishIme")
    {
      if (!setupEnglishIme())
      {
        result->Error("IME Setup Failure", "Failed to setup English IME");
        return;
      }
      result->Success();
    }
    else if (method_call.method_name() == "arabicIme")
    {
      if (!setupArabicIme())
      {
        result->Error("IME Setup Failure", "Failed to setup Arabic IME");
        return;
      }
      result->Success();
    }
    else if (method_call.method_name() == "malayalamIme")
    {
      if (!setupMalayalamIme())
      {
        result->Error("IME Setup Failure", "Failed to setup Malayalam IME");
        return;
      }
      result->Success();
    }
    else if (method_call.method_name() == "hindiIme")
    {
      if (!setupHindiIme())
      {
        result->Error("IME Setup Failure", "Failed to setup Hindi IME");
        return;
      }
      result->Success();
    }
    else
    {
      result->Error("Invalid Arguments", "Invalid language name");
      result->NotImplemented();
    }
  }

} // namespace windows_ime_manager
