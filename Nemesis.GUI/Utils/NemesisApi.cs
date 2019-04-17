using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace Nemesis.Utils
{
    [StructLayout(LayoutKind.Sequential)]
    internal struct MemorySourcesStruct
    {
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 12)]
        public IntPtr[] MemorySources;
    };


    [StructLayout(LayoutKind.Sequential)]
    internal struct Driver
    {
        public IntPtr ImageBase;
        public int ImageSize;
        public int OffsetToFileName;
        public char[] FullPathName;
    }

    [StructLayout(LayoutKind.Sequential)]
    internal struct DriverListStruct
    {
        [MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.Struct, SizeConst = 512)]
        public IntPtr[] DriverList;
    }


    [StructLayout(LayoutKind.Sequential)]
    internal struct Process
    {

    }

    [StructLayout(LayoutKind.Sequential)]
    internal struct ProcessListExport
    {
        [MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.Struct, SizeConst = 512)]
        public Process[] ProcessList;
    }

    internal class NemesisImports
    {
        [DllImport("Nemesis.dll")]
        protected static extern bool DumpProcessExport(int processId, string fileName);

        [DllImport("Nemesis.dll")]
        protected static extern bool DumpModuleExport(int processId, IntPtr baseAddress, string fileName);

        [DllImport("Nemesis.dll")]
        protected static extern bool DumpMemoryExport(int processId, IntPtr startAddress, uint size, string fileName);


        [DllImport("Nemesis.dll")]
        protected static extern void GetMemorySourcesExport(ref MemorySourcesStruct structure);

        [DllImport("Nemesis.dll")]
        protected static extern bool SetMemorySourceExport(string memorySource);

        
        [DllImport("D:\\3_Programming\\1_Github\\Nemesis\\x64\\Debug\\Nemesis.dll")]
        protected static extern void GetDriverListExport(ref DriverListStruct structure);

        [DllImport("D:\\3_Programming\\1_Github\\Nemesis\\x64\\Debug\\Nemesis.dll")]
        protected static extern void GetProcessListExport(ref ProcessListExport structure);
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
            //
            // Create a new struct
            //
            var structure = new DriverListStruct();

            //
            // Get the memory sources
            //
            GetDriverListExport(ref structure);

            //
            // Convert the pointers to structures and return the list
            //
            List<Driver> list = new List<Driver>();
            foreach (var pointer in structure.DriverList)
            {
                if (pointer != IntPtr.Zero)
                {
                    list.Add(Marshal.PtrToStructure<Driver>(pointer));
                }
            }


            //
            // Return the list
            //
            //return structure.DriverList.ToList();
            return list;
        }

        public static List<Process> GetProcessList()
        {
            //
            // Create a new struct
            //
            var structure = new ProcessListExport();

            //
            // Get the memory sources
            //
            GetProcessListExport(ref structure);

            //
            // Return the list
            //
            return structure.ProcessList.ToList();
        }
    }
}