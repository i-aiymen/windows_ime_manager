#include "include/windows_ime_manager/windows_ime_manager_plugin_c_api.h"

#include <flutter/plugin_registrar_windows.h>

#include "windows_ime_manager_plugin.h"

void WindowsImeManagerPluginCApiRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  windows_ime_manager::WindowsImeManagerPlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}
