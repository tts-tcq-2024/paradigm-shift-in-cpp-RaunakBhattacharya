#include "Checker.h"
#include <assert.h>
#include <iostream>

Battery::Battery() {
    parameterErrorMessages = {
        {BatteryParameter::TEMPERATURE, "Temperature out of range!\n"},
        {BatteryParameter::SOC, "State of Charge out of range!\n"},
        {BatteryParameter::CHARGE_RATE, "Charge Rate out of range!\n"}
    };

    parameterWarningMessages = {
        {BatteryParameter::TEMPERATURE, "Warning: Temperature approaching limit!\n"},
        {BatteryParameter::SOC, "Warning: State of Charge approaching limit!\n"},
        {BatteryParameter::CHARGE_RATE, "Warning: Charge Rate approaching limit!\n"}
    };

    parameterErrorMessagesGerman = {
        {BatteryParameter::TEMPERATURE, "Temperatur außerhalb des Bereichs!\n"},
        {BatteryParameter::SOC, "Ladezustand außerhalb des Bereichs!\n"},
        {BatteryParameter::CHARGE_RATE, "Ladegeschwindigkeit außerhalb des Bereichs!\n"}
    };

    parameterWarningMessagesGerman = {
        {BatteryParameter::TEMPERATURE, "Warnung: Temperatur nähert sich dem Limit!\n"},
        {BatteryParameter::SOC, "Warnung: Ladezustand nähert sich dem Limit!\n"},
        {BatteryParameter::CHARGE_RATE, "Warnung: Ladegeschwindigkeit nähert sich dem Limit!\n"}
    };

    language = "English";
}

void Battery::printErrorMessage(BatteryParameter parameter) {
    if (language == "German") {
        std::cout << parameterErrorMessagesGerman[parameter];
    } else {
        std::cout << parameterErrorMessages[parameter];
    }
}

bool Battery::isWithinLimits(float value, BatteryLimits limits, BatteryParameter parameter) {
    bool isOutOfRange = value < limits.min || value > limits.max;
    if (isOutOfRange) {
        printErrorMessage(parameter);
    }
    return !isOutOfRange;
}

void Battery::printWarningMessage(BatteryParameter parameter) {
    if (language == "German") {
        std::cout << parameterWarningMessagesGerman[parameter];
    } else {
        std::cout << parameterWarningMessages[parameter];
    }
}

bool Battery::isWithinWarningLimits(float value, BatteryWarningLimits limits, BatteryParameter parameter) {
    bool isOutOfRange = value < limits.min || value > limits.max;
    if (isOutOfRange) {
        printWarningMessage(parameter);
    }
    return !isOutOfRange;
}

bool Battery::batteryIsOk(float temperature, float soc, float chargeRate) {
    const BatteryLimits temperatureLimits{0, 45};
    const BatteryLimits socLimits{20, 80};
    const BatteryLimits chargeRateLimits{0, 0.8};

    const BatteryWarningLimits temperatureWarningLimits{20+4, 80-4};
    const BatteryWarningLimits socWarningLimits{20+4, 80-4};
    const BatteryWarningLimits chargeRateWarningLimits{0+0.04, 0.8-0.04};

    bool isTemperatureOk = checkParameter(temperature, temperatureLimits, temperatureWarningLimits, BatteryParameter::TEMPERATURE);
    bool isSocOk = checkParameter(soc, socLimits, socWarningLimits, BatteryParameter::SOC);
    bool isChargeRateOk = checkParameter(chargeRate, chargeRateLimits, chargeRateWarningLimits, BatteryParameter::CHARGE_RATE);

    return isTemperatureOk && isSocOk && isChargeRateOk;
}

bool Battery::checkParameter(float value, BatteryLimits limits, BatteryWarningLimits warningLimits, BatteryParameter parameter) {
    return isWithinLimits(value, limits, parameter) && isWithinWarningLimits(value, warningLimits, parameter);
}

void Battery::testBatteryIsOk() {
    assert(batteryIsOk(25, 70, 0.7) == true);
    assert(batteryIsOk(50, 85, 0) == false);
    assert(batteryIsOk(-1, 70, 0.7) == false);
    assert(batteryIsOk(25, 19, 0.7) == false);
    assert(batteryIsOk(25, 70, 0.9) == false);
    //assert(batteryIsOk(25, 75, 0.7) == false); // Warning for SOC
    //assert(batteryIsOk(25, 70, 0.76) == false); // Warning for Charge Rate
    //assert(batteryIsOk(24, 70, 0.7) == false); // Warning for Temperature
}

int main() {
    Battery battery;
    battery.testBatteryIsOk();
    return 0;
}
