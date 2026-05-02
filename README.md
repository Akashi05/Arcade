# 🕹️ Arcade

A modular C++ arcade platform where graphical libraries and games are loaded dynamically as shared libraries (`.so`). Switch display backends and games at runtime without recompiling.

---

## 📦 Project Structure

```
.
├── src/
│   ├── Core/         # Main loop & dynamic loader
│   ├── Games/        # Snake, Nibbler
│   └── Graphicals/   # SFML, SDL2, Ncurses backends
├── include/          # Shared interfaces (IDisplay, IGame…)
├── lib/              # Compiled shared libraries (generated)
└── Makefile
```

---

## 🔧 Build

Requirements: `g++`, `libsfml-dev`, `libsdl2-dev`, `libncurses-dev`

```bash
make        # builds core + all games + all graphical libs
make clean  # removes build artifacts
make fclean # full clean (binaries + .so)
make re     # fclean + all
```

Outputs:
- `arcade` — main executable
- `lib/arcade_snake.so` / `lib/arcade_nibbler.so` — games
- `lib/arcade_sfml.so` / `lib/arcade_sdl2.so` / `lib/arcade_ncurses.so` — display backends

---

## 🚀 Usage

```bash
./arcade lib/arcade_sfml.so
```

Pass any graphical library as the first argument. Games and display backends can be switched at runtime via keyboard shortcuts.

---

## 🎮 Games

| Game    | Description                       |
|---------|-----------------------------------|
| Snake   | Classic snake — eat, grow, avoid walls |
| Nibbler | Enhanced snake with levels & obstacles |

## 🖥️ Display Backends

| Library  | Notes                  |
|----------|------------------------|
| SFML     | Hardware-accelerated 2D |
| SDL2     | Cross-platform 2D      |
| Ncurses  | Terminal-based         |

---

## 🔗 Cross-Group Compatibility

Shared interfaces for inter-group library compatibility:

- `include/IDisplay.hpp` — Graphics API
- `include/IGame.hpp` — Game API (via `include/Games.hpp`)

To use our libraries with another group's core:
1. Copy `lib/*.so` into their `lib/` directory
2. Our games and display libs follow the shared interface contract

**Collaboration group leader:** aurel.pliya@epitech.eu

---

## 👥 Authors

| Name | Email |
|------|-------|
| Bérenger Sessou | berenger.sessou@epitech.eu |
| Ramziath Zakari | ramziathzakari@epitech.eu |
| Aurel Pliya | aurel.pliya@epitech.eu |

---

*Epitech – B-OOP-400 – Arcade project*
