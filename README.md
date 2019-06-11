# Nemesis

A customizable process dumper library.

![alt](https://user-images.githubusercontent.com/26800596/59287543-22d42680-8c72-11e9-8f27-c4c6f132850a.png)

## Features

### General

- Both x86 and x64
- Dump:
  - Processes 
  - Modules
  - Memory
  - Drivers
- PE Rebuild
- Switch memory sources

### Application

- Simple and intuitive design

- Custom locations

- Sortable lists

- Keyboard shortcuts

- Customizable GUI

- Dark mode

## Memory Sources

### Problem

First of all, there's not really a public driver dumper, so you either had to rely on other people dumping them for you or write a dumper yourself. However, to be able to dump drivers, you need to have a kernel mode driver. It can be really annnoying if you just want to dump a simple process, if you have to load your driver beforehand. 

Of course there's tools which only dump processes with/without a kernel driver, but you'd need to install like 3 different programs just to be prepared for all situations.

### Solution

With Nemesis, you can simply switch memory sources with a single mouse click and use whatever you need. This does not only save you some time, but also a lot of disk space.

If you want to dump it with physical memory or via a hypervisor? Simply add a new memory source and you are good to go.

## Exports

Nemesis is also available as a dump library. If you want to implement a dumper, but don't want to mess with low level stuff, simply load the dll and use the following imports:

- [GetMemorySourcesExport](https://github.com/not-matthias/Nemesis/blob/master/Nemesis/MemorySourceExport.h#L20)

- [SetMemorySourceExport](https://github.com/not-matthias/Nemesis/blob/master/Nemesis/MemorySourceExport.h#L27)

- [DumpProcessExport](https://github.com/not-matthias/Nemesis/blob/master/Nemesis/DumpExport.hpp#L11)

- [DumpModuleExport](https://github.com/not-matthias/Nemesis/blob/master/Nemesis/DumpExport.hpp#L20)

- [DumpMemoryExport](https://github.com/not-matthias/Nemesis/blob/master/Nemesis/DumpExport.hpp#L30)

- [DumpDriverExport](https://github.com/not-matthias/Nemesis/blob/master/Nemesis/DumpExport.hpp#L38)

- [GetDriverListElementExport](https://github.com/not-matthias/Nemesis/blob/master/Nemesis/DriverExport.hpp#L31)

- [GetProcessListElementExport](https://github.com/not-matthias/Nemesis/blob/master/Nemesis/ProcessExport.hpp#L63)

- [GetModuleListElementExport](https://github.com/not-matthias/Nemesis/blob/master/Nemesis/ProcessExport.hpp#L72)

- [GetMemoryListElementExport](https://github.com/not-matthias/Nemesis/blob/master/Nemesis/ProcessExport.hpp#L81)

- [SaveDriverInformationExport](https://github.com/not-matthias/Nemesis/blob/master/Nemesis/DriverExport.hpp#L39)

### Keyboard Shortcuts

<kbd>CTRL+D</kbd> - Dump the selected process

<kbd>CTRL+R</kbd> - Refresh the processes

<kbd>CTRL+ALT+S</kbd> - Open the settings

## Disclaimer

Use at your own risk. It might destroy the Earth. 

## References

- https://github.com/NtQuery/Scylla/
- https://github.com/EquiFox/KsDumper
- https://www.unknowncheats.me/
- https://stackoverflow.com
- https://msdn.com
