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
    if (delayCheck(forwardGaSwitchLastTrigger, SWTICH_DEBOUNCE) &&
        openknx.gpio.digitalRead(LCP_FRONT_GA_SWT_PIN) == LCP_FRONT_SWT_PIN_ACTIVE_ON)
    {
        forwardGaSwitchLastTrigger = delayTimerInit();
        forwardGa = !forwardGa;
        openknx.gpio.digitalWrite(LCP_FRONT_GA_LED_PIN, forwardGa ? LCP_FRONT_LED_PIN_ACTIVE_ON : !LCP_FRONT_LED_PIN_ACTIVE_ON);
    }

    if (delayCheck(forwardPaSwitchLastTrigger, SWTICH_DEBOUNCE) &&
        openknx.gpio.digitalRead(LCP_FRONT_PA_SWT_PIN) == LCP_FRONT_SWT_PIN_ACTIVE_ON)
    {
        forwardPaSwitchLastTrigger = delayTimerInit();
        forwardPa = !forwardPa;
        openknx.gpio.digitalWrite(LCP_FRONT_PA_LED_PIN, forwardPa ? LCP_FRONT_LED_PIN_ACTIVE_ON : !LCP_FRONT_LED_PIN_ACTIVE_ON);
    }

    if (!delayCheck(debugOutTimer, 1000))
        return;

    ledStateActive = !ledStateActive;
    openknx.gpio.digitalWrite(LCP_FRONT_MASTER_ACTIVE_LED_PIN, ledStateActive ? LCP_FRONT_LED_PIN_ACTIVE_ON : !LCP_FRONT_LED_PIN_ACTIVE_ON);
    openknx.gpio.digitalWrite(LCP_FRONT_MASTER_FAULT_LED_PIN, ledStateActive ? LCP_FRONT_LED_PIN_ACTIVE_ON : !LCP_FRONT_LED_PIN_ACTIVE_ON);
    openknx.gpio.digitalWrite(LCP_FRONT_SLAVE_ACTIVE_LED_PIN, ledStateActive ? LCP_FRONT_LED_PIN_ACTIVE_ON : !LCP_FRONT_LED_PIN_ACTIVE_ON);
    openknx.gpio.digitalWrite(LCP_FRONT_SLAVE_FAULT_LED_PIN, ledStateActive ? LCP_FRONT_LED_PIN_ACTIVE_ON : !LCP_FRONT_LED_PIN_ACTIVE_ON);

    debugOutTimer = delayTimerInit();
}

LineCouplerModule openknxLineCouplerModule;