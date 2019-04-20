using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;

namespace Nemesis.Utils
{
    [StructLayout(LayoutKind.Sequential)]
    internal struct MemorySourcesStruct
    {
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 12)]
        public IntPtr[] MemorySources;
    }

    [StructLayout(LayoutKind.Sequential)]
    internal struct Driver
    {
        public long ImageBase;
        public int ImageSize;
        public ushort OffsetToFileName;

        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 256)]
        public string FullPathName;
    }

    [StructLayout(LayoutKind.Sequential)]
    internal struct Process
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 256)]
        public string image_name;

        public int unique_process_id;
        public int number_of_threads;
        public int base_priority;
        public int handle_count;
        public int session_id;
        public int peak_virtual_size;
        public int virtual_size;
        public int peak_working_set_size;
        public int working_set_size;
        public int quota_paged_pool_usage;
        public int quota_non_paged_pool_usage;
        public int page_file_usage;
        public int peak_page_file_usage;
        public int private_page_count;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct Module
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 260)]
        public string module_name;

        public long base_address;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct Memory
    {
        public long base_address;
        public int region_size;
        public int state;
        public int type;
    }

    internal class NemesisImports
    {
        [DllImport("Nemesis.dll")]
        protected static extern bool DumpProcessExport([In] int processId, [In] string fileName);

        [DllImport("Nemesis.dll")]
        protected static extern bool DumpModuleExport([In] int processId, [In] IntPtr baseAddress, [In] string fileName);

        [DllImport("D:\\3_Programming\\1_Github\\Nemesis\\x64\\Debug\\Nemesis.dll")]
        protected static extern bool DumpMemoryExport([In] int processId, [In] IntPtr startAddress, [In] uint size, [In] string fileName);


        [DllImport("Nemesis.dll")]
        protected static extern void GetMemorySourcesExport([In] [Out] ref MemorySourcesStruct structure);

        [DllImport("Nemesis.dll")]
        protected static extern bool SetMemorySourceExport([In] string memorySource);


        [DllImport("D:\\3_Programming\\1_Github\\Nemesis\\x64\\Debug\\Nemesis.dll")]
        protected static extern bool GetDriverListElementExport([In] uint index, [In] [Out] ref Driver structure);

        [DllImport("D:\\3_Programming\\1_Github\\Nemesis\\x64\\Debug\\Nemesis.dll")]
        protected static extern bool GetProcessListElementExport([In] uint index, [In] [Out] ref Process structure);

        [DllImport("D:\\3_Programming\\1_Github\\Nemesis\\x64\\Debug\\Nemesis.dll")]
        protected static extern bool GetModuleListElementExport([In] uint index, [In] int processId, [In] [Out] ref Module structure);

        [DllImport("D:\\3_Programming\\1_Github\\Nemesis\\x64\\Debug\\Nemesis.dll")]
        protected static extern bool GetMemoryListElementExport([In] uint index, [In] int processId, [In] [Out] ref Memory structure);
    }

    internal class NemesisApi : NemesisImports
    {
        public static bool DumpProcess(int processId, string fileName)
        {
            return DumpProcessExport(processId, fileName);
        }

        public static bool DumpModule(int processId, IntPtr baseAddress, string fileName)
        {
            return DumpModuleExport(processId, baseAddress, fileName);
        }

        public static bool DumpMemory(int processId, IntPtr startAddress, uint size, string fileName)
        {
            return DumpMemoryExport(processId, startAddress, size, fileName);
        }


        public static bool SetMemorySource(string memorySource)
        {
            return SetMemorySourceExport(memorySource);
        }

        public static List<string> GetMemorySources()
        {
            //
            // Create a new struct
            //
            var structure = new MemorySourcesStruct();

            //
            // Get the memory sources
            //
            GetMemorySourcesExport(ref structure);

            //
            // Convert the pointers to strings and return the list
            //
            return (from pointer in structure.MemorySources
                where pointer != IntPtr.Zero
                select Marshal.PtrToStringAnsi(pointer)).ToList();
        }


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