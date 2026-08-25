import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np

# 1. Me Read Data
df = pd.read_csv('/Users/swojas.changde/Documents/Depth_Data.csv')

# 2. Me Convert Any String To Number
df['Point'] = pd.to_numeric(df['Point'], errors='coerce')
df['Depth (m)'] = pd.to_numeric(df['Depth (m)'], errors='coerce')

# 3. Me Creating Arrays to store that Shi
time = df['Point'].to_numpy()
depth = df['Depth (m)'].to_numpy()

n = len(time)
MEDIAN_WINDOW = 5

""" 4. Me Calculate Median (See Ik you dont use for loop but i only knew
 basic operators 2 weeks ago so this is still a pretty good soln for
 me (dont get mad at the for loop pls) (NO AI FOR LOGICS))"""
depth_median = []
for i in range(n):
    start = max(0, i - 2)
    end = min(n, i + 2)
    subset = df.iloc[start:end, 1]
    depth_median.append(subset.median())
depth_median = np.array(depth_median)

# 5. Me Set up the plotting
fig, ax = plt.subplots(figsize=(10, 6))
ax.set_xlim(np.nanmin(time), np.nanmax(time))
ax.set_ylim(np.nanmin(depth), np.nanmax(depth))
ax.invert_yaxis()
ax.set_xlabel("Time (s)")
ax.set_ylabel("Depth (m)")
ax.set_title("Seafloor Depth: Raw vs. Filtered")

raw_line, = ax.plot([], [], label="Raw depth", color="blue",
                     linewidth=1, marker="o", markersize=3)
median_line, = ax.plot([], [], label=f"Median filtered plot)",
                        color="red", linewidth=1.5)
ax.legend()
plt.tight_layout()

""" 6. Me Update Function For Each Frame (Ts req a lot of yt tuts so pls
show some love)"""
def update(frame):
    raw_line.set_data(time[:frame + 1], depth[:frame + 1])
    median_line.set_data(time[:frame + 1], depth_median[:frame + 1])
    return raw_line, median_line


ani = animation.FuncAnimation(
    fig, update, frames=n, interval=100, blit=True, repeat=False
)

plt.show()

#Sidenote: Love you guys