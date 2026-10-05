#pragma once

// Combined BLE + WiFi companion (meck_max_ble_wifi test build).
//
// Holds the Bluetooth and the WiFi companion connections and passes every
// call to whichever one is selected. Only one is selected at a time; with
// neither selected it behaves as a switched-off connection. Selecting a
// connection and switching the radios on and off is done in main.cpp
// (meckCompanionUseBLE / meckCompanionUseWiFi / meckCompanionUseNone).

#include <helpers/BaseSerialInterface.h>

class DualCompanionInterface : public BaseSerialInterface {
public:
  enum Mode : uint8_t { MODE_NONE = 0, MODE_BLE = 1, MODE_WIFI = 2 };

private:
  BaseSerialInterface* _ble;
  BaseSerialInterface* _wifi;
  Mode _mode;

  BaseSerialInterface* active() const {
    if (_mode == MODE_BLE) return _ble;
    if (_mode == MODE_WIFI) return _wifi;
    return nullptr;
  }

public:
  DualCompanionInterface(BaseSerialInterface* ble, BaseSerialInterface* wifi)
    : _ble(ble), _wifi(wifi), _mode(MODE_NONE) { }

  Mode getMode() const { return _mode; }
  void setMode(Mode m) { _mode = m; }

  // BaseSerialInterface methods, passed to the selected connection
  void enable() override { if (active()) active()->enable(); }
  void disable() override { if (active()) active()->disable(); }
  bool isEnabled() const override { return active() ? active()->isEnabled() : false; }
  bool isConnected() const override { return active() ? active()->isConnected() : false; }
  bool isWriteBusy() const override { return active() ? active()->isWriteBusy() : false; }
  bool hasPendingData() const override { return active() ? active()->hasPendingData() : false; }
  size_t writeFrame(const uint8_t src[], size_t len) override {
    return active() ? active()->writeFrame(src, len) : 0;
  }
  size_t checkRecvFrame(uint8_t dest[]) override {
    return active() ? active()->checkRecvFrame(dest) : 0;
  }
};
