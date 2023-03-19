import pandas as pd
import matplotlib.pyplot as plt

headers = ["x", "y"]
file = pd.read_csv("log.csv", delimiter=",", names=headers)


plt.plot(file["x"], file["y"])
plt.xlabel("Position in inches")
plt.show()
