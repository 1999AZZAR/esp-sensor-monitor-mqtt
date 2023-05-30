import matplotlib.pyplot as plt
import numpy as np

def fuzzy_logic(calibrated_temp, fire, ppm):
    # Fuzzy logic calculation for temperature
    cold = np.maximum(0.0, 1.0 - (calibrated_temp - 0.0) / (40.0 - 0.0))
    warm = np.maximum(0.0, np.minimum((calibrated_temp - 0.0) / (35.0 - 0.0), (55.0 - calibrated_temp) / (55.0 - 35.0)))
    hot = np.maximum(0.0, np.minimum((calibrated_temp - 50.0) / (70.0 - 50.0), 1.0))

    # Fuzzy logic calculation for fire
    none = np.maximum(0.0, 1.0 - (fire - 0.0) / (40.0 - 0.0))
    small = np.maximum(0.0, np.minimum((fire - 0.0) / (35.0 - 0.0), (55.0 - fire) / (55.0 - 35.0)))
    large = np.maximum(0.0, np.minimum((fire - 50.0) / (70.0 - 50.0), 1.0))

    # Fuzzy logic calculation for gas (smoke)
    no_gas = np.maximum(0.0, 1.0 - (ppm - 0.0) / (100.0 - 0.0))
    light_gas = np.maximum(0.0, np.minimum((ppm - 0.0) / (50.0 - 0.0), (200.0 - ppm)) / (200.0 - 50.0))
    heavy_gas = np.maximum(0.0, np.minimum((ppm - 100.0) / (150.0 - 100.0), 1.0))

    # Fuzzy logic rules for output
    safe = np.minimum(np.maximum(cold, none), np.maximum(light_gas, no_gas))
    warning = np.minimum(np.maximum(warm, hot), np.maximum(small, light_gas))
    danger = np.minimum(np.maximum(cold, np.maximum(warm, hot)), np.maximum(large, np.maximum(light_gas, heavy_gas)))

    # Calculate the sum of safe, warning, and danger
    total = safe + warning + danger

    # Adjust the values to ensure the sum is equal to 1
    if total > 0 or total < 1:
        safe /= total
        warning /= total
        danger /= total

    return safe, warning, danger


# Example usage:
calibrated_temp = float(input("Enter the calibrated temperature: "))
fire = float(input("Enter the fire level: "))
ppm = float(input("Enter the gas (smoke) concentration (ppm): "))

safe_output, warning_output, danger_output = fuzzy_logic(calibrated_temp, fire, ppm)

print("Safe: ", safe_output)
print("Warning: ", warning_output)
print("Danger: ", danger_output)

# Plotting the membership functions for temperature, fire, and gas (smoke) concentration
x = np.linspace(0, 100, 100)

# Temperature membership functions
temperature_cold = np.maximum(0.0, 1.0 - (x - 0.0) / (40.0 - 0.0))
temperature_warm = np.maximum(0.0, np.minimum((x - 0.0) / (35.0 - 0.0), (55.0 - x) / (55.0 - 35.0)))
temperature_hot = np.maximum(0.0, np.minimum((x - 50.0) / (70.0 - 50.0), 1.0))

# Fire membership functions
fire_none = np.maximum(0.0, 1.0 - (x - 0.0) / (40.0 - 0.0))
fire_small = np.maximum(0.0, np.minimum((x - 0.0) / (35.0 - 0.0), (55.0 - x) / (55.0 - 35.0)))
fire_large = np.maximum(0.0, np.minimum((x - 50.0) / (70.0 - 50.0), 1.0))

# Gas (smoke) membership functions
gas_no_gas = np.maximum(0.0, 1.0 - (x - 0.0) / (100.0 - 0.0))
gas_light_gas = np.maximum(0.0, np.minimum((x - 0.0) / (50.0 - 0.0), (200.0 - x)) / (200.0 - 50.0))
gas_heavy_gas = np.maximum(0.0, np.minimum((x - 100.0) / (150.0 - 100.0), 1.0))

# Plotting the membership functions for temperature, fire, and gas (smoke) concentration
plt.figure(figsize=(12, 6))
plt.plot(x, temperature_cold, label='Temperature - Cold')
plt.plot(x, temperature_warm, label='Temperature - Warm')
plt.plot(x, temperature_hot, label='Temperature - Hot')
plt.plot(x, fire_none, label='Fire - None')
plt.plot(x, fire_small, label='Fire - Small')
plt.plot(x, fire_large, label='Fire - Large')
plt.plot(x, gas_no_gas, label='Gas - No Gas')
plt.plot(x, gas_light_gas, label='Gas - Light Gas')
plt.plot(x, gas_heavy_gas, label='Gas - Heavy Gas')
plt.xlabel('Input Range')
plt.ylabel('Membership Degree')
plt.title('Membership Functions')
plt.legend()
plt.show()

# Plotting the output membership functions
output_labels = ['Safe', 'Warning', 'Danger']
output_values = [safe_output, warning_output, danger_output]

plt.figure(figsize=(8, 4))
plt.bar(output_labels, output_values)
plt.xlabel('Output')
plt.ylabel('Membership Degree')
plt.title('Fuzzy Logic Output')
plt.show()
