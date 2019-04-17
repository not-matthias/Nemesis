using System;
using System.Windows.Forms;
using Nemesis.Utils;

namespace Nemesis
{
    internal static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        private static void Main()
        {
            Console.WriteLine(NemesisApi.GetProcessList().Count);
            Console.WriteLine(NemesisApi.GetDriverList().Count);

            foreach (var driver in NemesisApi.GetDriverList())
            {
                Console.WriteLine(driver.ImageBase);
            }

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Forms.Nemesis());
        }
    }
}