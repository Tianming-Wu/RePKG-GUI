# RePKG-GUI

This project is **not** based on RePKG-GUI by idzyr, but it is where the idea comes from.

The project is based on [Qt Opensource](https://www.qt.io/) and designed for [RePKG](https://github.com/notscuffed/repkg).

The goal is to provide a more user-friendly, highly customizable experience.

**Special Thanks** to the qtproject, they provide many powerful features that make this project possible.


# Features
- Unpack PKG files without studying the command-line options of RePKG.
- Multi-language support (Working). Feel free to work on it, see [Wiki]()
- Customizable Output Dir Matching Rule. (using regex)
- Simple drag-and-drop control logic.


# Configure
Most configurations can be found in the "Settings" tab.

The configuraton file is `repkg-gui.ini` in the same directory of the executable.

> [!IMPORTANT]
> For any path, use unix style "/" (Slash) instead of "\\"(BackSlash) even if you're on Windows.


Here are some excludes:

### RePKG-Path (RePKGPath)
The program detects repkg when launching, so it's hard to make it in the settings. You can manually specify it by adding this line in the configuration file:

```ini
[Application]
RePKGPath=C:/Your/Path/To/RePkg/repkg.exe
```

### These are available in Settings Tab:
### Default Open Path (DefaultOpenPath)
The dafault open directory each time you click on the "Browse" button of the source. If left empty, the program will use the path you opened last time.
```ini
[Default]
DefaultOpenPath=D:/SteamLibrary/steamapps/workshop/content/431960
```


### Auto Execute on Open/Drop (AutoExecute)
If set to true, will automatically start the action if you opened or dropped a file.
```ini
[Application]
AutoExecute=
```
