#include "LineCouplerModule.h"

const std::string LineCouplerModule::name()
{
    return "LineCoupler";
}

const std::string LineCouplerModule::version()
{
    return MAIN_Version;
}

void LineCouplerModule::setup(bool configured)
{
    logInfoP("Setup line coupler module");
    logIndentUp();

    openknx.gpio.pinMode(LCP_FRONT_GA_SWT_PIN, INPUT);
    openknx.gpio.pinMode(LCP_FRONT_PA_SWT_PIN, INPUT);
    openknx.gpio.pinMode(LCP_FRONT_GA_LED_PIN, OUTPUT, true, !LCP_FRONT_LED_PIN_ACTIVE_ON);
    openknx.gpio.pinMode(LCP_FRONT_PA_LED_PIN, OUTPUT, true, !LCP_FRONT_LED_PIN_ACTIVE_ON);
    openknx.gpio.pinMode(LCP_FRONT_MASTER_ACTIVE_LED_PIN, OUTPUT, true, !LCP_FRONT_LED_PIN_ACTIVE_ON);
    openknx.gpio.pinMode(LCP_FRONT_MASTER_FAULT_LED_PIN, OUTPUT, true, !LCP_FRONT_LED_PIN_ACTIVE_ON);
    openknx.gpio.pinMode(LCP_FRONT_SLAVE_ACTIVE_LED_PIN, OUTPUT, true, !LCP_FRONT_LED_PIN_ACTIVE_ON);
    openknx.gpio.pinMode(LCP_FRONT_SLAVE_FAULT_LED_PIN, OUTPUT, true, !LCP_FRONT_LED_PIN_ACTIVE_ON);

    logInfoP("Line coupler module ready.");
    logIndentDown();
}

void LineCouplerModule::loop(bool configured)
{
    if (!delayCheck(debugOutTimer, 1000))
        return;

    ledStateActive = !ledStateActive;
    openknx.gpio.digitalWrite(LCP_FRONT_GA_LED_PIN, ledStateActive ? LCP_FRONT_LED_PIN_ACTIVE_ON : !LCP_FRONT_LED_PIN_ACTIVE_ON);
    openknx.gpio.digitalWrite(LCP_FRONT_PA_LED_PIN, ledStateActive ? LCP_FRONT_LED_PIN_ACTIVE_ON : !LCP_FRONT_LED_PIN_ACTIVE_ON);
    openknx.gpio.digitalWrite(LCP_FRONT_MASTER_ACTIVE_LED_PIN, ledStateActive ? LCP_FRONT_LED_PIN_ACTIVE_ON : !LCP_FRONT_LED_PIN_ACTIVE_ON);
    openknx.gpio.digitalWrite(LCP_FRONT_MASTER_FAULT_LED_PIN, ledStateActive ? LCP_FRONT_LED_PIN_ACTIVE_ON : !LCP_FRONT_LED_PIN_ACTIVE_ON);
    openknx.gpio.digitalWrite(LCP_FRONT_SLAVE_ACTIVE_LED_PIN, ledStateActive ? LCP_FRONT_LED_PIN_ACTIVE_ON : !LCP_FRONT_LED_PIN_ACTIVE_ON);
    openknx.gpio.digitalWrite(LCP_FRONT_SLAVE_FAULT_LED_PIN, ledStateActive ? LCP_FRONT_LED_PIN_ACTIVE_ON : !LCP_FRONT_LED_PIN_ACTIVE_ON);

    if (openknx.gpio.digitalRead(LCP_FRONT_GA_SWT_PIN) == LCP_FRONT_SWT_PIN_ACTIVE_ON)
        logDebugP("GA switch pressed");
    if (openknx.gpio.digitalRead(LCP_FRONT_PA_SWT_PIN) == LCP_FRONT_SWT_PIN_ACTIVE_ON)
        logDebugP("PA switch pressed");

    debugOutTimer = delayTimerInit();
}

LineCouplerModule openknxLineCouplerModule;