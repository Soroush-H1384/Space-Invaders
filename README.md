# Space Invaders – C++ Console Edition

A classic **Space Invaders** game written in **C++**, fully running inside the **console** with **ANSI color support** for a more vibrant experience.  
This version includes customizable spaceships and bullets, multi-level enemies, a boss enemy at the top of the screen, a save/load system, and a persistent leaderboard.

---

## 🎮 Features

### 🚀 Player Features
- **Customizable Spaceship**
- **Different Bullet Styles**
- **Save & Continue** – load your previous progress from `LoadGame.txt`
- **Colored Console Gameplay** using ANSI escape codes

### 👾 Enemy Features
- **Multiple Levels** with increasingly fast and difficult enemies  
- **Boss Enemy at the Top Line** – a special high-HP enemy that moves differently  
- **Enemy Ships** with different patterns

### 🏆 Leaderboard
- Permanently stores high scores  
- Automatically updates when a new record is achieved  
- Stored inside `LeaderBoard.txt`

---

## 📁 Project Structure

Project includes one C++ source file and one text file for saves:

```
/project
  |-- Game.cpp   # Main C++ game logic
  |-- LoadGame.txt            # Save data 
  |-- Leaderboard.txt #save leaderboard storage
```

---

## 🛠 Requirements
- C++11 or newer  
- Console with ANSI color support (Windows 10+, Linux, macOS)  
- g++, clang++, or MSVC compiler  

---

## ▶️ How to Compile & Run

### Compile:
```bash
g++ -std=c++11 -o space_invaders SpaceInvaders.cpp
```

### Run:
Linux/macOS:
```bash
./space_invaders
```

Windows:
```cmd
space_invaders.exe
```

---

## 📝 Gameplay
- Move your spaceship using **arrow keys**
- Shoot with **Space**
- Dodge enemy bullets and destroy incoming enemies
- Defeat the **Boss Enemy** on the top row
- Colors indicate:
  - Player = Blue 
  - Bullets = Red  
  - Enemies = Green  
  - Boss Enemy = Magenta (or another color)  
- Progress and high scores are saved in `data.txt`

---

## 💾 Save System
The game saves:
- Current level  
- Score  
- Spaceship type  
- Bullet type  
- Boss HP  
- Leaderboard records  

All data is stored and loaded from **LoadGame.txt**
**LeaderBoard**.

---

## 📊 Leaderboard
- Stores player names + high scores  
- Automatically sorted  
- Persistent across game sessions  

---

## 📌 Future Improvements (TODO)
- Add sound effects  
- Add more enemy attack patterns  
- Better boss AI behavior  
- Add user-selectable difficulty  
- Improve color themes  

---

## 👨‍💻 Created By
**Soroush Heydarpour (@Soroush-H1384)**

---

## 📜 License
Open-source.  
Feel free to contribute, fork, or modify!
