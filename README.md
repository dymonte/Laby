# Maze - Problem Solving

## About the project

This project aims at solving the maze problem. It generates a maze of size (width x height) and then solves it using a pathfinding algorithm.

```bash
+---+---+---+---+---+
| *   * |   |   |   |
+   +   +   +   +   +
| S | * |       |   |
+   +   +---+   +   +
|   | * |           |
+---+   +---+---+   +
|   | * |       |   |
+   +   +   +---+   +
|     *   *   *   E |
+---+---+---+---+---+
```

## How to run the project

### Compiling
The following command will compile the project.
```bash
make maze
```

### Running
The following command will run the project.
```bash
./maze <width> <height> <show_msg> <display> [get_stats]
```

### Get statistics
The following command will create two `CSV` files containing the time taken to generate the maze and to find the path in a maze.
Then, the `generate_fig.py` script can be used to generate the graphs. It will generate two graphs in the `stats` directory.
To do that automatically, you can use the following command.
```bash
make stat
```


### Cleaning
The following command will clean the project.
```bash
make clean
```





## Team members (3.2)
- Barbutov Filip
- Berthelot Sacha
- Imhoff Guillaume
- Kihoulou Bakela Timothé
- Le Duc Bao
- Rizkallah Rouba
- Monteneri Dylan