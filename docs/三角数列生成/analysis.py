import numpy as np
import matplotlib.pyplot as plt

phase_A_list = []
phase_B_list = []
phase_C_list = []

with open('log.txt', 'r') as f:
    lines = f.readlines()
    for line in lines:
        phase_A = int(line.split('A: ')[1].split(',')[0])
        phase_B = int(line.split('B: ')[1].split(',')[0])
        phase_C = int(line.split('C: ')[1].split(',')[0])
        phase_A_list.append(phase_A)
        phase_B_list.append(phase_B)
        phase_C_list.append(phase_C)

t = np.linspace(0, len(lines) - 1, len(lines))
plt.plot(t, phase_A_list, label='Phase A')
plt.plot(t, phase_B_list, label='Phase B')
plt.plot(t, phase_C_list, label='Phase C')
plt.xlabel('Time (ms)')
plt.ylabel('PWM Compare Value')
plt.title('SVPWM Compare Values Over Time')
plt.legend()

plt.show()