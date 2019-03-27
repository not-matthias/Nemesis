using System.Runtime.InteropServices;

namespace Nemesis
{
    internal class NemesisConnector
    {
        //TODO: Replace path
        [DllImport("D:\\Nemesis\\Nemesis\\x64\\Release\\Nemesis.dll")]
        public static extern bool StandardDump(int Pid, string FileName);
    }
}
