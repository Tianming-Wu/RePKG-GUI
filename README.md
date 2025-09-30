# RePKG-GUI

This project is not based on RePKG-GUI by idzyr, though the idea might be similar.

The project is based on [Qt Opensource](https://www.qt.io/) and [RePKG](https://github.com/notscuffed/repkg).

My target is to provide a more user-friendly, highly customizable experience.

**Special Thanks** to the qtproject, who provides many powerful features which make this project possible.

# Features
- Unpack PKG files without studying the command-line.
- Multi-language support (Working)
- Customizable Output Dir Matching Rule. (regex)
- Simple drag-and-drop control logic.


# Configure
Most configurations can be found in the "Settings" tab.

The configuraton file is `repkg-gui.ini` in the same directory of the executable.

Here are some excludes:

### RePKG-Path
The program detects repkg when launching, so it's hard to make it in the settings. You can manually specify it by adding this line in the configuration file:

```ini
[Application]
RePKGPath=C:/Your/Path/To/RePkg/repkg.exe
```

> [!IMPORTANT]
> Use unix style "/" (Slash) instead "\\"(BackSlash) even if you're on Windows.
