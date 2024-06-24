#include <assert.h>
#include <iostream>
#include <string>
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

bool isWithinLimits(float value, BatteryLimits limits, BatteryParameter parameter) {
    if (value < limits.min || value > limits.max) {
        switch (parameter) {
            case BatteryParameter::TEMPERATURE:
                cout << "Temperature out of range!\n";
                break;
            case BatteryParameter::SOC:
                cout << "State of Charge out of range!\n";
                break;
            case BatteryParameter::CHARGE_RATE:
                cout << "Charge Rate out of range!\n";
                break;
        }
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
