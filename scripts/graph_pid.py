import pandas as pd
import matplotlib.pyplot as plt

headers = ["Power", "P", "I", "D"]
file = pd.read_csv("log.csv", delimiter=",", names=headers)

y = []
index = 0
for line in file.Power:
    y.append(index)
    index += 1


plt.plot(y, file["Power"], "y", file["P"], "r", file["I"], "g", file["D"], "b")
plt.xlabel("Power = yellow, P = red, I = green, D = blue")

plt.show()
