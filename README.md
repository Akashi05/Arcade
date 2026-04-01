# 🎮 Arcade

A modular arcade game platform written in C++ that uses **dynamic library loading** to switch between graphical backends and games at runtime — no recompilation needed.

> Epitech project — B-OOP-400

---

## 📁 Project Structure

```
Arcade/
├── arcade              # Main executable (generated after build)
├── lib/                # Shared libraries (generated after build)
│   ├── arcade_sfml.so
│   ├── arcade_sdl2.so
│   ├── arcade_ncurses.so
│   ├── arcade_snake.so
│   └── arcade_nibbler.so
├── include/            # Interfaces and headers
│   ├── IDisplay.hpp    # Graphics API interface
│   ├── Games.hpp       # Game API interface (IGames / AGames)
│   ├── Core.hpp
│   ├── Error.hpp
│   └── ...
└── src/
    ├── Core/           # Core engine (main loop, dynamic loading)
    ├── Games/          # Game modules: Snake, Nibbler
    └── Graphicals/     # Display modules: SFML, SDL2, NCurses
```

---

## 🧱 Architecture

The project is split into three independent layers, all communicating through stable interfaces:

| Layer | Interface | Implementations |
|-------|-----------|-----------------|
| **Core** | — | `arcade` binary |
| **Graphics** | `IDisplay` | SFML · SDL2 · NCurses |
| **Games** | `IGames` / `AGames` | Snake · Nibbler |

Each graphical library and each game is compiled as a separate `.so` shared library. The core loads them at runtime via `dlopen`/`dlsym`, allowing you to switch library or game without restarting.

---

## 🔧 Dependencies

| Library | Used by |
|---------|---------|
| [SFML](https://www.sfml-dev.org/) | `arcade_sfml.so` |
| [SDL2](https://www.libsdl.org/) | `arcade_sdl2.so` |
| [ncurses](https://invisible-island.net/ncurses/) | `arcade_ncurses.so` |

Install on Debian/Ubuntu:
```bash
sudo apt install libsfml-dev libsdl2-dev libncurses-dev
```

---

## 🚀 Build

```bash
make        # Build everything (core + all games + all graphical libs)
make core   # Build only the core executable
make games  # Build only the game libraries
make graphicals  # Build only the graphical libraries
make clean  # Remove build artifacts
make fclean # Remove everything including binaries and .so files
make re     # Full rebuild
```

---

## ▶️ Usage

```bash
./arcade ./lib/arcade_ncurses.so   # Start with NCurses
./arcade ./lib/arcade_sfml.so      # Start with SFML
./arcade ./lib/arcade_sdl2.so      # Start with SDL2
```

The launcher displays a menu where you can select a game. You can switch between graphical libraries and games from within the menu at runtime.

---

## 🎮 Available Games

| Game | Library |
|------|---------|
| **Snake** | `lib/arcade_snake.so` |
| **Nibbler** | `lib/arcade_nibbler.so` |

---

## 🔌 Cross-Group Compatibility

This project follows shared interfaces for cross-group compatibility:

- **`IDisplay.hpp`** — Graphics API. Any graphical library must implement:
  - `init()`, `close()`, `isOpen()`
  - `display_menu()`, `display_game_over()`, `display_score(int)`
  - `display_state(const std::vector<std::vector<int>> &map)`
  - `handleEvents(std::string &direction)`
  - `getActualGame()`, `getActualLibrary()`, `setActualGame()`, `setActualLibrary()`

- **`Games.hpp`** — Game API. Any game must implement:
  - `init()`, `update(std::string key)`
  - `getState()` → `std::vector<std::vector<int>>`
  - `getPlayerScore()`, `getPlayerLive()`, `is_gameEnd()`

To use our libraries with another group's core (or vice versa):
1. Copy the `lib/*.so` files into their `lib/` directory.
2. Our games and graphical modules will work with any core that respects the same interfaces.

---

## 👥 Authors

- **Ramziath Zakari** — ramziathzakari@epitech.eu
- Collaboration leader: brouhane.gomina@epitech.eu
