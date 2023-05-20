import pandas as pd
import matplotlib.pyplot as plt

random_insert = pd.read_csv("test_random_insert.csv")\
                    .pivot(index="Sample Size", columns="Tree", values="Elapsed Time (ms)")
random_erase = pd.read_csv("test_random_erase.csv")\
                    .pivot(index="Sample Size", columns="Tree", values="Elapsed Time (ms)")
sorted_insert = pd.read_csv("test_sorted_insert.csv")\
                    .pivot(index="Sample Size", columns="Tree", values="Elapsed Time (ms)")
sorted_erase = pd.read_csv("test_sorted_erase.csv")\
                    .pivot(index="Sample Size", columns="Tree", values="Elapsed Time (ms)")


figure, axes = plt.subplots(nrows=2, ncols=2, figsize=(20, 20))
insert, erase = axes
figure.subplots_adjust(hspace=0.5)
random_insert.plot(
        ax=insert[0],
        ylabel="Elapsed Time (ms)",
        title="Random insertion performance",
        grid=True)
random_erase.plot(
        ax=erase[0],
        ylabel="Elapsed Time (ms)",
        title="Random erase performance",
        grid=True)

figure, axes = plt.subplots(nrows=2, ncols=2, figsize=(20, 20))
insert, erase = axes
figure.subplots_adjust(hspace=0.5)
sorted_insert.plot(
        ax=insert[0],
        ylabel="Elapsed Time (ms)",
        title="Sorted insertion performance",
        grid=True)
sorted_erase.plot(
        ax=erase[0],
        ylabel="Elapsed Time (ms)",
        title="Sorted erase performance",
        grid=True)

sorted_insert = sorted_insert[[col for col in sorted_insert.columns if col != "BinaryTree"]]
sorted_erase = sorted_erase[[col for col in sorted_erase.columns if col != "BinaryTree"]]
figure, axes = plt.subplots(nrows=2, ncols=2, figsize=(20, 20))
insert, erase = axes
figure.subplots_adjust(hspace=0.5)
sorted_insert.plot(
        ax=insert[0],
        ylabel="Elapsed Time (ms)",
        title="Sorted insertion performance",
        grid=True)
sorted_erase.plot(
        ax=erase[0],
        ylabel="Elapsed Time (ms)",
        title="Sorted erase performance",
        grid=True)

plt.show()