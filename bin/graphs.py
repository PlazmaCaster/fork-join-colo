import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import sys

# Useful functions
def avg(arr) :
    total=sum(arr)
    return total / len(arr)

def image_stats(img_data):
    stats=img_data.iloc[len(img_data) - 1]  # stats will always be on last row
    return stats.iloc[0], stats.iloc[1], stats.iloc[2]

def cache_results(img_data):
    img_data.drop(1, inplace=True)
    offsets = img_data["Offset"]
    cache_data=img_data.drop(["Offset"], axis=1)

    return offsets, cache_data

img_data=pd.read_csv(sys.argv[1])

img, cache_sz, runs=image_stats(img_data=img_data)
offsets, cache_data = cache_results(img_data=img_data)


# print(offsets)
# print(cache_data)
# print(img, cache_sz, runs)


# offsets=cache_data["Offset"]
# runs=cache_data.drop(["Offset"], axis=1)
# max_miss=runs.max(axis=1)


# max_df=pd.concat([offsets, max_miss], axis=1)
# max_df.rename(columns={0: "WC Data Miss"}, inplace=True)

fig, ax = plt.subplots()
df = cache_data.T
print(df)
# df.columns=['380']
# df.boxplot()
# max_df[["WC Data Miss"]].boxplot(ax=ax)

# plt.xticks([1], [''])
plt.suptitle("Object09 - Matmul")
ax.set_xlabel('Offset')
ax.set_ylabel('Data Misses')
ax.set_ylim([2250, 2260])
# minimum=min(max_miss)
# maximum=max(max_miss)
# q1=np.quantile(max_miss, 0.25)
# median=np.quantile(max_miss, 0.5)
# q3=np.quantile(max_miss, 0.75)

# ax.text(1.1, minimum, f"Min: {minimum:.2f}", verticalalignment='center')
# ax.text(1.1, q1, f"Q1: {q1:.2f}", ha='left')
# ax.text(1.1, median, f"Median: {median:.2f}", horizontalalignment='left', verticalalignment='center')
# ax.text(.9, q3, f"Q3: {q3:.2f}", horizontalalignment='right', verticalalignment='center')
# ax.text(1.1, maximum, f"Max: {maximum:.2f}", verticalalignment='center')
# # ax.text(1.1, q1, f"Q1: {q1:.2f}", verticalalignment='center')

# plt.xlabel("object09 - matmul")
# print(max_miss.std())
# print((maximum - avg(max_miss)) / max_miss.std())
plt.show()
# # print(max_df)
