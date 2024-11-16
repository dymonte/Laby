import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

def create_graph(name : str, title : str, y_label : str)->None:
    """
    Create a graph showing the time taken to generate a maze as a function of its size.

    The graph is saved as a PNG image with the given name.

    :param name: the name of the graph to be saved
    :return: None
    """
    data = pd.read_csv(f'stats/result_{name}.csv', sep=';', header=0)

    x = data.iloc[:, 1]
    y = data.iloc[:, 2]


    plt.figure(figsize=(10, 6))
    plt.plot(x, y, 'o')
    plt.xlabel('Number of cells')
    plt.ylabel(y_label)
    plt.title(title)

    slope, intercept = np.polyfit(x, y, 1)

    x_reg = np.array([min(x), max(x)])
    y_reg = slope * x_reg + intercept
    plt.plot(x_reg, y_reg, label='Linear regression', color='red')


    plt.savefig(f'stats/fig_{name}.png')
    
for elem in [['gen', 'Time to create the maze as a function of the number of cells', 'Time to create the maze (ms)'], ['path', 'Time to solve the maze as a function of the number of cells', 'Time to solve the maze (ms)']]:
    create_graph(elem[0], elem[1], elem[2])
