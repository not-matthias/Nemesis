using System;
using System.Runtime.InteropServices;

namespace Nemesis.Utils
{
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
        public static extern IntPtr GetMemorySources();

        [DllImport("D:\\Nemesis\\Nemesis\\x64\\Release\\Nemesis.dll")]
        public static extern void SetMemorySource(string memorySource);

    }
}