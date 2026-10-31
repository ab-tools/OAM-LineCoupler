#pragma once
#include "OpenKNX.h"
#include "hardware.h"

#define INIT_RESET_TIMEOUT 1000
#define LED_RESET_TIMEOUT 1000
#define SWTICH_DEBOUNCE 250

class LineCouplerModule : public OpenKNX::Module
{
  public:
    void loop(bool configured) override;
    void setup(bool configured) override;

    const std::string name() override;
    const std::string version() override;

    //void processInputKo(GroupObject &ko) override;
    //bool processCommand(const std::string cmd, bool diagnoseKo);

  private:
    //void runTestMode();

    uint32_t debugOutTimer = 0;
    bool ledStateActive = false;

    bool forwardGa = false;
    uint32_t forwardGaSwitchLastTrigger = 0;
    bool forwardPa = false;
    uint32_t forwardPaSwitchLastTrigger = 0;
};

extern LineCouplerModule openknxLineCouplerModule;