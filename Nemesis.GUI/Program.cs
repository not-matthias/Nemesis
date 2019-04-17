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
            var driverList = NemesisApi.GetDriverList();
            foreach (var driver in driverList)
            {
                Console.WriteLine(driver.FullPathName);
            }

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Forms.Nemesis());
        }
    }
}