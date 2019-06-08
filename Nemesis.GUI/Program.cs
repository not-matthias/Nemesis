using System;
using System.Diagnostics;
using System.IO;
using System.Reflection;
using System.Security.Principal;
using System.Windows.Forms;
using Process = System.Diagnostics.Process;

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
            //
            // Run as administrator
            //
            if (!new WindowsPrincipal(WindowsIdentity.GetCurrent()).IsInRole(WindowsBuiltInRole.Administrator))
            {
                var path = Assembly.GetExecutingAssembly().Location;
                using (var process = Process.Start(new ProcessStartInfo(path)
                {
                    Verb = "runas"
                }))
                {
                    process?.WaitForExit();
                    return;
                }
            }

            //
            // Check if Nemesis.dll exists
            //
            if (!File.Exists("Nemesis.dll"))
            {
                MessageBox.Show("Nemesis.dll not found.");
                return;
            }

            //
            // Start application
            //
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Forms.NemesisForm());
        }
    }
}