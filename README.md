# AsciiArt 🎨🖼️

**AsciiArt** is a high-performance C++20 command-line tool that converts images (JPG, PNG, BMP, etc.) into colored ASCII art rendered directly in your terminal using ANSI truecolor escape sequences.

---

## Features

- **ANSI Truecolor Support:** Renders 24-bit RGB colors directly to compatible terminal environments.
- **Sobel Edge Detection:** Detects object outlines and draws clean edge lines (`/`, `|`, `\`, `-`) for extra detail.
- **Aspect Ratio Correction:** Automatically scales down the horizontal axis (50% compression by default) to compensate for tall terminal font cells.
- **Header Magic-Byte Detection:** Checks file signatures (`JPG`, `PNG`) to select the appropriate loader dynamically.
- **File Export:** Saves monochrome ASCII art outputs to plain `.txt` files for easy sharing.

---

## Architecture

```text
AsciiArt/
├── CMakeLists.txt
├── CMakePresets.json
├── README.md
├── LICENSE.md
├── .gitignore
├── external/
│   └── stb/               # Third-party image decoders (stb_image)
├── include/               # Header interfaces
│   ├── HeaderChecker.hpp
│   ├── ImageConverter.hpp
│   ├── ImageLoader.hpp
│   └── Pixel.hpp
└── src/                   # Entrypoint & core implementations
    ├── AsciiArt.cpp
    ├── HeaderChecker.cpp
    ├── ImageConverter.cpp
    └── ImageLoader.cpp
```

---

## Personal Project Disclaimer

This is a personal hobby project provided **"as-is"**. 

It may contain bugs, unhandled edge cases, or breaking changes. You are free to view, copy, modify, and use this software for any purpose, but the author assumes no responsibility or liability for any issues or damages arising from its use.