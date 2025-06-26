# Modern C++ Chat App (Raylib GUI)

<p align="center">
  <img src="https://img.shields.io/badge/C%2B%2B-20-blue.svg" alt="C++20">
  <img src="https://img.shields.io/badge/Raylib-4.5-brightgreen.svg" alt="Raylib">
  <img src="https://img.shields.io/badge/Boost%20Asio-planned-orange.svg" alt="Boost Asio Planned">
</p>

---

## ✨ Overview

This is a **modern chat application** written in C++ using [raylib](https://www.raylib.com/) and [raygui](https://github.com/raysan5/raygui) for a beautiful native UI. The app features a clean, minimal, and visually appealing interface, custom fonts, and a modular structure—making it a great starting point for a future networked chat system.

> **Note:**  
> The current version is **offline/local only**. Networking and multi-user/server functionality (via Boost.Asio) is **planned but not implemented yet**.

---

## 🚀 Features

- **Modern C++ (C++20)**
- **Sleek GUI** powered by raylib and raygui
- **Resizable, theme-friendly UI** with custom font (Fira Code)
- **Room-based chats**: select or add rooms, each with its own history
- **Text box with Enter/send support**
- **Persistent chat history** (saved per-room as plain text)
- **Easy to extend** for networking (Boost Asio coming soon!)
- **Simple codebase**—easy to hack and learn from

---

## 🎨 Screenshots

<p align="center">
  <img src="https://raw.githubusercontent.com/raysan5/raygui/master/examples/resources/raygui_logo.png" height="100">
</p>

- **Main Menu:**  
  Select a chat room from a list of available rooms.
- **Chat Room:**  
  Type messages, see them appear instantly, and return to the menu. Each room has its own persistent history.

---

## 🛠️ Usage

### 1. **Requirements**

- C++20-compatible compiler
- [raylib](https://www.raylib.com/) (linked and installed)
- [raygui](https://github.com/raysan5/raygui) (header-only UI lib)
- (Optional) [Fira Code font](https://github.com/tonsky/FiraCode) in `../data/`
- A `../data/rooms.txt` file listing your room names (one per line)
- A `../data/` directory for chat logs (created automatically)


### 2. **Build & Run**

If you haven't already create the database first this only needs to be done once ever 

```bash
./make_db
```

Then simply run both of these are just very simple bash
scripts to make setup and compilation a little easier
Currently no way to actually register a user working on that now so only two 
users and passwords 1 is my first name as user and the last name as the pass
Can either change this in schema.sql or wait till i add it which may be tonight or manana


```bash
./gui
```

- Use the **Main Menu** to enter a room.
- Type your message and press **Enter** or click **Send**.
- Messages are saved per room.
- Click **Back** to return to the menu (saving your chat).

---

## 🌐 Roadmap

- [x] **Beautiful local GUI**
- [x] **Multiple chat rooms**
- [x] **Persistent local chat**
- [ ] **Networking (server/client, Boost.Asio)**
- [ ] **Online multi-user chat**
- [ ] **User authentication**
- [ ] **Rich media/messages**
- [ ] **Settings, themes, and more**

> **Currently:**  
> The app **does not** support networking or online chat. All messages are stored and displayed locally.  
> *The next major milestone is adding asynchronous networking with Boost.Asio for real-time, multi-user chat!*

---

## 📁 Project Structure

```
project-root/
│
├── main.cpp            # The app (this file)
├── ../data/
│    ├── rooms.txt      # List your chat rooms here
│    ├── <room>.txt     # Chat history per room (auto-created)
│    └── FiraCode-Regular.ttf  # Optional: custom font
├── raygui.h            # UI library (header-only)
└── raylib (linked)
```

---

## 🤝 Contributing

Pull requests are welcome! Feel free to open issues for feature requests, questions, or feedback.

---

## 📜 License

MIT (or your preferred license)

---

## 🙋 FAQ

**Q: Is this online?**  
A: Not yet! Currently, it's a local, single-user chat. Online mode is a planned feature.

**Q: What libraries does it use?**  
A: [raylib](https://www.raylib.com/) for graphics, [raygui](https://github.com/raysan5/raygui) for UI, and (soon) [Boost.Asio](https://www.boost.org/doc/libs/release/doc/html/boost_asio.html) for networking.

**Q: How do I add a new room?**  
A: Add a new line with your desired room name to `../data/rooms.txt`.

---

## ✨ Credits

- [raylib](https://www.raylib.com/) for graphics
- [raygui](https://github.com/raysan5/raygui) for UI
- [Fira Code](https://github.com/tonsky/FiraCode) font (optional)

---

<p align="center">
  <b>Made with ❤️ in modern C++</b>
</p>
