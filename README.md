# pipex

_This project has been created as part of the 42 curriculum by dachin_

## Description

A simple 2D game where the player must collect all items and reach the exit.

## Instructions
``` bash
# Compile the project
make

# Compile with bonus (if applicable)
make bonus

# Clean object files
make clean

# Full clean (remove executable)
make fclean

# Recompile everything
make re

# Running the program
./pipex
```

## Program Flow
```
main()
  ├─> parse_map()
  │     ├─> read_map_file()
  │     └─> validate_map()
  │           ├─> validate_map_characters()
  │           ├─> validate_element_counts()
  │           │     └─> count_map_elements()
  │           ├─> validate_map_shape()
  │           ├─> validate_wall()
  │           └─> validate_path()
  │                 ├─> find_map_size()
  │                 ├─> find_player_start()
  │                 ├─> create_visited_matrix()
  │                 ├─> flood_fill_reachable()
  │                 └─> free_visited_matrix()
  │
  │─> mlx_init()
  │─> load_and_resize()
  ├─> render_map()
  ├─> mlx_key_hook
  ├─> mlx_loop_hook
  │     └─> animation_hook()
  ├─> mlx_loop()
  └─> mlx_terminate()
```

## Resources & Credits
