# Nemesis

A customizable process dumper.

![alt](https://user-images.githubusercontent.com/26800596/59287543-22d42680-8c72-11e9-8f27-c4c6f132850a.png)

## Usage

Just select whatever you want (Process, Dll, Driver, ...) and click on the dump button. If it was successful, you can load the file into decompilers like [IDA Pro], [Ghidra] or [Binary Ninja]. Some of these programs are available for free, but of course they won't be as good as the paid ones. Here's a short list of the different versions:

Paid: 
- [IDA Pro]
- [Binary Ninja]

Free:
- [Ghidra]
- [IDA Freeware]
- [Binary Ninja Demo]

[IDA Pro]: https://www.hex-rays.com/products/ida/index.shtml
[Ghidra]: https://ghidra-sre.org/
[Binary Ninja]: https://binary.ninja/
[IDA Freeware]: https://www.hex-rays.com/products/ida/support/download_freeware.shtml
[Binary Ninja Demo]: https://binary.ninja/demo/

> Note: If you want another decompiler added, feel free to create a pull request or issue.

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

Nemesis is also available as a dump library. If you want to implement a dumper, but don't want to mess with low level stuff, simply load the dll and use the following imports.

### ConfigExport


- [SetConfigValueExport](https://github.com/not-matthias/Nemesis/blob/master/Nemesis/ConfigExport.hpp#L9)

- [GetConfigValueExport](https://github.com/not-matthias/Nemesis/blob/master/Nemesis/ConfigExport.hpp#L11)

### DriverExport

- [GetDriverListElementExport](https://github.com/not-matthias/Nemesis/blob/master/Nemesis/DriverExport.hpp#L31)

- [SaveDriverInformationExport](https://github.com/not-matthias/Nemesis/blob/master/Nemesis/DriverExport.hpp#L39)

### DumpExport

- [DumpProcessExport](https://github.com/not-matthias/Nemesis/blob/master/Nemesis/DumpExport.hpp#L11)

- [DumpModuleExport](https://github.com/not-matthias/Nemesis/blob/master/Nemesis/DumpExport.hpp#L20)

- [DumpMemoryExport](https://github.com/not-matthias/Nemesis/blob/master/Nemesis/DumpExport.hpp#L30)

- [DumpDriverExport](https://github.com/not-matthias/Nemesis/blob/master/Nemesis/DumpExport.hpp#L38)

### MemorySourceExport

- [GetMemorySourcesExport](https://github.com/not-matthias/Nemesis/blob/master/Nemesis/MemorySourceExport.h#L16)

### ProcessExport

- [GetProcessListElementExport](https://github.com/not-matthias/Nemesis/blob/master/Nemesis/ProcessExport.hpp#L64)

- [GetModuleListElementExport](https://github.com/not-matthias/Nemesis/blob/master/Nemesis/ProcessExport.hpp#L73)

- [GetManualModuleListElementExport](https://github.com/not-matthias/Nemesis/blob/master/Nemesis/ProcessExport.hpp#L82)

- [GetMemoryListElementExport](https://github.com/not-matthias/Nemesis/blob/master/Nemesis/ProcessExport.hpp#L91)

### Keyboard Shortcuts

<kbd>CTRL+D</kbd> - Dump the selected process or driver

<kbd>CTRL+R</kbd> - Refresh the process and driver list

<kbd>CTRL+ALT+S</kbd> - Open the settings

## Disclaimer

Use at your own risk. It might destroy the Earth. 

## References

- https://github.com/NtQuery/Scylla/
- https://github.com/EquiFox/KsDumper
- https://www.unknowncheats.me/
- https://stackoverflow.com
- https://msdn.com
