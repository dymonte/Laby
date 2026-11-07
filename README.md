# Maze - Problem Solving

## About the project

This project aims at solving the maze problem. It generates a maze of size (width x height) and then solves it using a pathfinding algorithm ([DFS](https://en.wikipedia.org/wiki/Depth-first_search)).
The path is unique and because of that it is the shortest.

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
The following command will compile the project :
```bash
make maze
```

### Running
The following command will run the project :
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

### 3D visualization
You can also run a 3D representation of the maze using the following command :
```bash
make 3D; ./3D
```

### Cleaning
The following command will clean the project :
```bash
make clean
```

### Test the project
The following command will test the project with different sizes.
```bash
make test
```

### Generate documentation
The following command will generate the [Doxygen](https://www.doxygen.nl/) doc :
```bash
make doc
```





## Team members (3.2)
- Barbutov Filip
- Berthelot Sacha
- Imhoff Guillaume
- Kihoulou Bakela Timothé
- Le Duc Bao
- Rizkallah Rouba
- Monteneri Dylan