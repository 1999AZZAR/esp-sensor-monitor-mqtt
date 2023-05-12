# Fuzzy Logic Temperature, Fire, and Gas (Smoke) Detection

This code implements a fuzzy logic system to detect temperature, fire, and gas (smoke) levels using analog input signals from sensors and outputting corresponding analog signals to control three output pins: safePin, warningPin, and dangerPin.

## Input Pins
The following input pins are defined in the code:

* tempPin - temperature sensor analog input pin
* firePin - fire sensor analog input pin
* gasPin - gas (smoke) sensor analog input pin

## Output Pins
The following output pins are defined in the code:

* safePin - output analog signal pin for safe condition
* warningPin - output analog signal pin for warning condition
* dangerPin - output analog signal pin for danger condition

## Fuzzy Logic Calculation
The code uses fuzzy logic to calculate temperature, fire, and gas levels based on the input analog signals and define the output analog signals based on the following rules:

### Temperature Fuzzy Logic Calculation
* cold - temperature less than 20°C
* warm - temperature between 20°C and 30°C
* hot - temperature greater than 30°C

### Fire Fuzzy Logic Calculation
* none - fire less than 5 units
* small - fire between 5 units and 10 units
* large - fire greater than 10 units

### Gas Fuzzy Logic Calculation
* noGas - gas (smoke) less than 10 units
* lightGas - gas (smoke) between 10 units and 20 units
* heavyGas - gas (smoke) greater than 20 units

### Output Fuzzy Logic Rules
* safe - temperature cold AND fire none AND gas noGas
* warning - temperature cold OR warm AND fire none OR small AND gas noGas OR light
