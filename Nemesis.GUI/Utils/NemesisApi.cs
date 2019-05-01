using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;

namespace Nemesis.Utils
{
    /// <summary>
    /// Contains the list of memory sources.
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    internal struct MemorySource
    {
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 12)]
        public IntPtr[] MemorySources;
    }

    /// <summary>
    /// Contains data about a driver.
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    internal struct Driver
    {
        public long ImageBase;
        public int ImageSize;
        public ushort OffsetToFileName;

        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 256)]
        public string FullPathName;
    }

    /// <summary>
    /// Contains data about a process.
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    internal struct Process
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 256)]
        public string ImageName;

        public int UniqueProcessId;
        public int NumberOfThreads;
        public int BasePriority;
        public int HandleCount;
        public int SessionId;
        public int PeakVirtualSize;
        public int VirtualSize;
        public int PeakWorkingSetSize;
        public int WorkingSetSize;
        public int QuotaPagedPoolUsage;
        public int QuotaNonPagedPoolUsage;
        public int PageFileUsage;
        public int PeakPageFileUsage;
        public int PrivatePageCount;
    }

    /// <summary>
    /// Contains data about a module of a process.
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct Module
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 260)]
        public string module_name;

        public long base_address;
    }

    /// <summary>
    /// Contains data about a memory region.
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct Memory
    {
        public long BaseAddress;
        public int RegionSize;
        public int State;
        public int Type;
    }

    internal class NemesisImports
    {
        [DllImport("Nemesis.dll")]
        protected static extern bool DumpProcessExport([In] int processId, [In] string fileName);

        [DllImport("Nemesis.dll")]
        protected static extern bool DumpModuleExport([In] int processId, [In] IntPtr baseAddress, [In] string fileName);

        [DllImport("Nemesis.dll")]
        protected static extern bool DumpMemoryExport([In] int processId, [In] IntPtr startAddress, [In] uint size, [In] string fileName);


        [DllImport("Nemesis.dll")]
        protected static extern void GetMemorySourcesExport([In] [Out] ref MemorySource structure);

        [DllImport("Nemesis.dll")]
        protected static extern bool SetMemorySourceExport([In] string memorySource);
        

        [DllImport("Nemesis.dll")]
        protected static extern bool GetDriverListElementExport([In] uint index, [In] [Out] ref Driver structure);

        [DllImport("Nemesis.dll")]
        protected static extern bool GetProcessListElementExport([In] uint index, [In] [Out] ref Process structure);

        [DllImport("Nemesis.dll")]
        protected static extern bool GetModuleListElementExport([In] uint index, [In] int processId, [In] [Out] ref Module structure);

        [DllImport("Nemesis.dll")]
        protected static extern bool GetMemoryListElementExport([In] uint index, [In] int processId, [In] [Out] ref Memory structure);
    }

    internal class NemesisApi : NemesisImports
    {
        /// <summary>
        /// Dumps and saves the specified process.
        /// </summary>
        /// <param name="processId">The id of the process</param>
        /// <param name="fileName">The dump location</param>
        /// <returns>True if successful</returns>
        public static bool DumpProcess(int processId, string fileName)
        {
            return DumpProcessExport(processId, fileName);
        }

        /// <summary>
        /// Dumps and saves the specified module.
        /// </summary>
        /// <param name="processId">The id of the process in which the module is</param>
        /// <param name="baseAddress">The base address of the module</param>
        /// <param name="fileName">The dump location</param>
        /// <returns>True if successful</returns>
        public static bool DumpModule(int processId, IntPtr baseAddress, string fileName)
        {
            return DumpModuleExport(processId, baseAddress, fileName);
        }

        /// <summary>
        /// Dumps and saves the specified memory.
        /// </summary>
        /// <param name="processId">The id of the process in which the memory is</param>
        /// <param name="startAddress">The starting address of the memory region</param>
        /// <param name="size">The size of the memory region</param>
        /// <param name="fileName">The dump location</param>
        /// <returns>True if successful</returns>
        public static bool DumpMemory(int processId, IntPtr startAddress, uint size, string fileName)
        {
            return DumpMemoryExport(processId, startAddress, size, fileName);
        }

        /// <summary>
        /// Sets the memory source in Nemesis.
        /// </summary>
        /// <param name="memorySource">The new memory source name</param>
        /// <returns>True if successful</returns>
        public static bool SetMemorySource(string memorySource)
        {
            return SetMemorySourceExport(memorySource);
        }

        /// <summary>
        /// Returns the available memory sources.
        /// </summary>
        /// <returns>List of memory source names</returns>
        public static List<string> GetMemorySources()
        {
            //
            // Create a new struct
            //
            var structure = new MemorySource();

            //
            // Get the memory sources
            //
            GetMemorySourcesExport(ref structure);

            //
            // Convert the pointers to strings and return the list
            //
            return (from pointer in structure.MemorySources
                where pointer != IntPtr.Zero
                select Marshal.PtrToStringAnsi(pointer)?.Split('|')[0]).ToList();
        }

        /// <summary>
        /// Returns the list of drivers.
        /// </summary>
        /// <returns>List of driver objects</returns>
        public static List<Driver> GetDriverList()
        {
            var list = new List<Driver>();

            //
            // Get the memory sources
            //
            for (uint index = 0; index < 512; index++)
            {
                //
                // Create the driver object
                //
                var structure = new Driver();

                //
                // Get the driver at the specified index
                //
                if (!GetDriverListElementExport(index, ref structure))
                {
                    break;
                }

                //
                // Add the item to the list
                //
                list.Add(structure);
            }

            //
            // Return the list
            //
            return list;
        }

        /// <summary>
        /// Returns the list of processes.
        /// </summary>
        /// <returns>List of process objects</returns>
        public static List<Process> GetProcessList()
        {
            var list = new List<Process>();

            //
            // Get the memory sources
            //
            for (uint index = 0; index < 512; index++)
            {
                //
                // Create the driver object
                //
                var structure = new Process();

                //
                // Get the driver at the specified index
                //
                if (!GetProcessListElementExport(index, ref structure))
                {
                    break;
                }

                //
                // Add the item to the list
                //
                list.Add(structure);
            }

            //
            // Return the list
            //
            return list;
        }

        /// <summary>
        /// Returns the list of modules of a process.
        /// </summary>
        /// <param name="processId">The id of the process</param>
        /// <returns>List of module objects</returns>
        public static List<Module> GetModuleList(int processId)
        {
            var list = new List<Module>();

            //
            // Get the memory sources
            //
            for (uint index = 0; index < 256; index++)
            {
                //
                // Create the driver object
                //
                var structure = new Module();

                //
                // Get the driver at the specified index
                //
                if (!GetModuleListElementExport(index, processId, ref structure))
                {
                    break;
                }

                //
                // Add the item to the list
                //
                list.Add(structure);
            }

            //
            // Return the list
            //
            return list;
        }

        /// <summary>
        /// Returns the list of memory regions of a process.
        /// </summary>
        /// <param name="processId">The id of the process</param>
        /// <returns>List of memory objects</returns>
        public static List<Memory> GetMemoryList(int processId)
        {
            var list = new List<Memory>();

            //
            // Get the memory sources
            //
            for (uint index = 0; index < 256; index++)
            {
                //
                // Create the driver object
                //
                var structure = new Memory();

                //
                // Get the driver at the specified index
                //
                if (!GetMemoryListElementExport(index, processId, ref structure))
                {
                    break;
                }

                //
                // Add the item to the list
                //
                list.Add(structure);
            }

            //
            // Return the list
            //
            return list;
        }
    }
}