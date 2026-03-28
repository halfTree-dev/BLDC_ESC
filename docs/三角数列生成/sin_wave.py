import math
arr_length = 1024
resolution = 2000
depth = 0.2

sin_wave_vals = [int((math.sin(2 * math.pi * i / arr_length) * depth +  0.5) * resolution) for i in range(arr_length)]
result = "{" + ", ".join(f"{val}" for val in sin_wave_vals) + "}"
with open("sin_wave_values.txt", "w") as f:
    f.write(result)
    f.close()
