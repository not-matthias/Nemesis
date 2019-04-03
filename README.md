# Nemesis
A customizable process dumper library.

![alt](https://user-images.githubusercontent.com/26800596/55280408-94fcc680-5325-11e9-945b-912a16b1ed5d.jpg)

## Features
- both x86 and x64 supported
- Dump processes 
- Dump drivers (TODO)
- Dump modules
- Dump sections
- Dump memory regions
- PE Rebuild
- Switch memory sources

## Exports
**Nemesis**:
- DumpMainModule
- DumpModule
- DumpMemory

**NemsisUtils**:
TODO

--- 

## User Interface
### Features 
- Simple and intuitive design
- Custom dump name
- Custom dump directory location
- Sortable process list
- Keyboard shortcuts

### Keyboard Shortcuts
<kbd>CTRL+D</kbd> - Dump the selected process

<kbd>CTRL+R</kbd> - Refresh the processes

<kbd>CTRL+ALT+S</kbd> - Open the settings

---

## References
- https://github.com/NtQuery/Scylla/
- https://github.com/EquiFox/KsDumper
