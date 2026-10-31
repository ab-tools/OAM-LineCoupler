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

    openknx.gpio.pinMode(FRONT_GA_SWT_PIN, INPUT);
    openknx.gpio.pinMode(FRONT_PA_SWT_PIN, INPUT);
    openknx.gpio.pinMode(FRONT_GA_LED_PIN, OUTPUT, true, !FRONT_LED_PIN_ACTIVE_ON);
    openknx.gpio.pinMode(FRONT_PA_LED_PIN, OUTPUT, true, !FRONT_LED_PIN_ACTIVE_ON);
    openknx.gpio.pinMode(FRONT_MASTER_ACTIVE_LED_PIN, OUTPUT, true, !FRONT_LED_PIN_ACTIVE_ON);
    openknx.gpio.pinMode(FRONT_MASTER_FAULT_LED_PIN, OUTPUT, true, !FRONT_LED_PIN_ACTIVE_ON);
    openknx.gpio.pinMode(FRONT_SLAVE_ACTIVE_LED_PIN, OUTPUT, true, !FRONT_LED_PIN_ACTIVE_ON);
    openknx.gpio.pinMode(FRONT_SLAVE_FAULT_LED_PIN, OUTPUT, true, !FRONT_LED_PIN_ACTIVE_ON);

    logInfoP("Line coupler module ready.");
    logIndentDown();
}

void LineCouplerModule::loop(bool configured)
{
    if (delayCheck(forwardGaSwitchLastTrigger, SWTICH_DEBOUNCE) &&
        openknx.gpio.digitalRead(FRONT_GA_SWT_PIN) == FRONT_SWT_PIN_ACTIVE_ON)
    {
        forwardGaSwitchLastTrigger = delayTimerInit();
        forwardGa = !forwardGa;
        openknx.gpio.digitalWrite(FRONT_GA_LED_PIN, forwardGa ? FRONT_LED_PIN_ACTIVE_ON : !FRONT_LED_PIN_ACTIVE_ON);
    }

    if (delayCheck(forwardPaSwitchLastTrigger, SWTICH_DEBOUNCE) &&
        openknx.gpio.digitalRead(FRONT_PA_SWT_PIN) == FRONT_SWT_PIN_ACTIVE_ON)
    {
        forwardPaSwitchLastTrigger = delayTimerInit();
        forwardPa = !forwardPa;
        openknx.gpio.digitalWrite(FRONT_PA_LED_PIN, forwardPa ? FRONT_LED_PIN_ACTIVE_ON : !FRONT_LED_PIN_ACTIVE_ON);
    }

    if (!delayCheck(debugOutTimer, 1000))
        return;

    ledStateActive = !ledStateActive;
    openknx.gpio.digitalWrite(FRONT_MASTER_ACTIVE_LED_PIN, ledStateActive ? FRONT_LED_PIN_ACTIVE_ON : !FRONT_LED_PIN_ACTIVE_ON);
    openknx.gpio.digitalWrite(FRONT_MASTER_FAULT_LED_PIN, ledStateActive ? FRONT_LED_PIN_ACTIVE_ON : !FRONT_LED_PIN_ACTIVE_ON);
    openknx.gpio.digitalWrite(FRONT_SLAVE_ACTIVE_LED_PIN, ledStateActive ? FRONT_LED_PIN_ACTIVE_ON : !FRONT_LED_PIN_ACTIVE_ON);
    openknx.gpio.digitalWrite(FRONT_SLAVE_FAULT_LED_PIN, ledStateActive ? FRONT_LED_PIN_ACTIVE_ON : !FRONT_LED_PIN_ACTIVE_ON);

    debugOutTimer = delayTimerInit();
}

LineCouplerModule openknxLineCouplerModule;