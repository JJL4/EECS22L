# <center>Software Requirements Specification </center>
<center> EECS 22L - Spring 2025 </center>
<center> Project 1 - Chess Game </center>

---

**Version History**
2025-04-15  v0.0.0  Initial version
2025-04-20  v0.1.0  Added details on game loop and player switching
2025-05-18  v0.4.0  Specified requirement dependencies for Sections 1 and 2

---

**Client:** Adam West High School, Principal Shepherd
**Project:** Project 1 - Chess Game

--- 

## 0. About this Document
This document defines the behavioral and functional requirements for a terminal-based chess game implemented in C. The project is structured into modular components, each responsible for part of the system's operation. This document specifies the interface and behavior of each function in a given module.

```yaml
ID: REQ-FN-FEAT-0000
    Title:    Chess Game
    Parents:  --
    Children: REQ-FN-FEAT-1001,REQ-FN-FEAT-1002,REQ-FN-FEAT-1003,REQ-FN-FEAT-1004
    Description: A terminal-based chess game implemented in C.
```

---

## 1. System Overview
The chess game runs in a terminal using ASCII graphics. It supports two human players taking turns. The game includes board management, move validation, turn control, and basic rule enforcement. The game can detect check and checkmate conditions. The game is played on an 8x8 board with standard chess pieces. Input is provided through standard input (keyboard), and the display is printed to standard output.

```yaml
ID: REQ-FN-FEAT-1001
    Title:    Terminal Chess Gameplay
    Parents:  REQ-FN-FEAT-0000
    Children: REQ-FN-ARCH-2101, REQ-FN-ARCH-2102, REQ-FN-ARCH-2103, REQ-FN-ARCH-2104, REQ-FN-ARCH-2105, REQ-FN-ARCH-2108
    Description: Complete chess game playable in terminal by two human players
```

```yaml
ID: REQ-FN-FEAT-1002
    Title:  Visuals and Input
    Parents:  REQ-FN-FEAT-0000
    Children: REQ-FN-ARCH-2101, REQ-FN-ARCH-2102, REQ-FN-ARCH-2103, REQ-FN-ARCH-2105, REQ-FN-ARCH-2108
    Description: Players must see the board and provide moves
```

```yaml
ID: REQ-FN-FEAT-1003
    Title:    Rule Enforcement
    Parents:  REQ-FN-FEAT-0000
    Children: REQ-FN-ARCH-2101, REQ-FN-ARCH-2102, REQ-FN-ARCH-2106, REQ-FN-ARCH-2107, REQ-FN-ARCH-2108
    Description: The game must validate and enforce chess rules
```

```yaml
ID: REQ-FN-FEAT-1004
    Title:    Game Orchestration
    Parents:  REQ-FN-FEAT-0000
    Children: REQ-FN-ARCH-2101, REQ-FN-ARCH-2102, REQ-FN-ARCH-2104, REQ-FN-ARCH-2106, REQ-FN-ARCH-2107, REQ-FN-ARCH-2108
    Description: The system must manage game flow from start to end
```

---

## 2. Architecture Overview (Proposed)

```
                      ┌────────────┐
                      │  main.c    │
                      └────┬───────┘
                           │
                    ┌──────▼───────┐
                    │  game.c      │
                    └──────┬───────┘
                           │
   ┌────────────┬──────────┼──────────┬──────────────┐
   │            │          │          │              │
┌──▼───┐    ┌────▼────┐ ┌──▼───┐   ┌──▼─────┐   ┌────▼─────┐
│ ui   │    │  check  │ │  io  │   │ player │   │ validator│
└──┬───┘    └────┬────┘ └──┬───┘   └────────┘   └────┬─────┘
   │             │         │                         │
   │             │         │                         │
   ▼             ▼         ▼                         ▼
────────────  ───────────────  ───────────────  ─────────────
   board.c     (Shared Data Layer: 8x8 board state, pieces)
────────────  ───────────────  ───────────────  ─────────────
```

### 2.1. Modules

```yaml
ID: REQ-FN-ARCH-2101
    Title:    Main Module
    Parents:  REQ-FN-FEAT-1001, REQ-FN-FEAT-1002, REQ-FN-FEAT-1003, REQ-FN-FEAT-1004
    Children: REQ-FN-ARCH-2201
    Description: The main module orchestrates the game flow, handling user input and output.
```
