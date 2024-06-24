#include <assert.h>
#include <iostream>
#include <string>
#include <map>
using namespace std;

enum class BatteryParameter {
    TEMPERATURE,
    SOC,
    CHARGE_RATE
};

struct BatteryLimits {
    float min;
    float max;
};

const BatteryLimits temperatureLimits{0, 45};
const BatteryLimits socLimits{20, 80};
const BatteryLimits chargeRateLimits{0, 0.8};

map<BatteryParameter, string> parameterErrorMessages = {
    {BatteryParameter::TEMPERATURE, "Temperature out of range!\n"},
    {BatteryParameter::SOC, "State of Charge out of range!\n"},
    {BatteryParameter::CHARGE_RATE, "Charge Rate out of range!\n"}
};

bool isWithinLimits(float value, BatteryLimits limits, BatteryParameter parameter) {
    if (value < limits.min || value > limits.max) {
        cout << parameterErrorMessages[parameter];
        return false;
    }
    return true;
}

bool batteryIsOk(float temperature, float soc, float chargeRate) {
    return isWithinLimits(temperature, temperatureLimits, BatteryParameter::TEMPERATURE) &&
           isWithinLimits(soc, socLimits, BatteryParameter::SOC) &&
           isWithinLimits(chargeRate, chargeRateLimits, BatteryParameter::CHARGE_RATE);
}

void testBatteryIsOk() {
    assert(batteryIsOk(25, 70, 0.7) == true);
    assert(batteryIsOk(50, 85, 0) == false);
    assert(batteryIsOk(-1, 70, 0.7) == false);
    assert(batteryIsOk(25, 19, 0.7) == false);
    assert(batteryIsOk(25, 70, 0.9) == false);
}

int main() {
    testBatteryIsOk();
}
