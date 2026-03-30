import numpy as np
import matplotlib.pyplot as plt

data = {
    "shuntVoltageA": 0,
    "shuntVoltageB": 0,
    "shuntVoltageC": 0,
    "SOA": 0,
    "SOB": 0,
    "SOC": 0,
}

datas = []

with open('log.txt', 'r') as f:
    lines = f.readlines()
    for line in lines:
        if line.startswith('[Feedback]'):
            shuntVoltageA = None
            shuntVoltageB = None
            shuntVoltageC = None
            SOA = None
            SOB = None
            SOC = None
            parts = line.split(' ')
            print(parts)
            try:
                for part in parts:
                    if part.startswith('ShuntVoltageA:'):
                        shuntVoltageA = float(part.split(':')[1][:-1])
                    if part.startswith('ShuntVoltageB:'):
                        shuntVoltageB = float(part.split(':')[1][:-1])
                    if part.startswith('ShuntVoltageC:'):
                        shuntVoltageC = float(part.split(':')[1][:-1])
                    if part.startswith('SOA:'):
                        SOA = float(part.split(':')[1][:-1])
                    if part.startswith('SOB:'):
                        SOB = float(part.split(':')[1][:-1])
                    if part.startswith('SOC:'):
                        SOC = float(part.split(':')[1][:-1])
                if shuntVoltageA is None or shuntVoltageB is None or shuntVoltageC is None or SOA is None or SOB is None or SOC is None:
                    raise ValueError('Missing data in line: ' + line)
                datas.append({
                    "shuntVoltageA": shuntVoltageA,
                    "shuntVoltageB": shuntVoltageB,
                    "shuntVoltageC": shuntVoltageC,
                    "SOA": SOA,
                    "SOB": SOB,
                    "SOC": SOC,
                })

            except ValueError:
                continue


t = np.linspace(0, len(datas) - 1, len(datas))
print("Total data points:", len(datas))
plt.plot(t, [data["shuntVoltageA"] for data in datas], label='Phase A')
plt.plot(t, [data["shuntVoltageB"] for data in datas], label='Phase B')
plt.plot(t, [data["shuntVoltageC"] for data in datas], label='Phase C')
plt.plot(t, [data["SOA"] for data in datas], label='SOA', linestyle='--')
plt.plot(t, [data["SOB"] for data in datas], label='SOB', linestyle='--')
plt.plot(t, [data["SOC"] for data in datas], label='SOC', linestyle='--')
plt.xlabel('Time (ms)')
plt.ylabel('Values')
plt.title('SVPWM Compare Values Over Time')
plt.legend()

plt.show()