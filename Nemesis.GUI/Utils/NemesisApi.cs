using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace Nemesis.Utils
{
    internal struct MemorySourcesStruct
    {
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 12)]
        public IntPtr[] MemorySources;
    };

    internal class NemesisApi
    {
        //TODO: Replace paths

        [DllImport("D:\\Nemesis\\Nemesis\\x64\\Release\\Nemesis.dll")]
        public static extern bool DumpProcess(int processId, string fileName);

        [DllImport("D:\\Nemesis\\Nemesis\\x64\\Release\\Nemesis.dll")]
        public static extern bool DumpModule(int processId, IntPtr baseAddress, string fileName);

        [DllImport("D:\\Nemesis\\Nemesis\\x64\\Release\\Nemesis.dll")]
        public static extern bool DumpMemory(int processId, IntPtr startAddress, uint size, string fileName);


        [DllImport("D:\\Nemesis\\Nemesis\\x64\\Release\\Nemesis.dll")]
        private static extern void GetMemorySourcesExport(ref MemorySourcesStruct structure);

        [DllImport("D:\\Nemesis\\Nemesis\\x64\\Release\\Nemesis.dll")]
        private static extern bool SetMemorySourceExport(string memorySource);

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
            // Convert the pointers to strings
            //
            var list = new List<string>();

            foreach (var pointer in structure.MemorySources)
            {
                if (pointer != IntPtr.Zero)
                {
                    list.Add(Marshal.PtrToStringAnsi(pointer));
                }
            }

            //
            // Return the list
            //
            return list;
        }

        public static bool SetMemorySource(string memorySource)
        {
            return SetMemorySourceExport(memorySource);
        }
    }
}