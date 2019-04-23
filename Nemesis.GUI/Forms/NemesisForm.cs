using MetroFramework.Forms;
using System;
using System.Collections.Generic;
using System.IO;
using System.Windows.Forms;
using Nemesis.Forms.Utils.Module;
using Nemesis.Forms.Utils.Process;
using Nemesis.Utils;

namespace Nemesis.Forms
{
    public partial class NemesisForm : MetroForm
    {
        private readonly Dictionary<int, ProcessInformation> _processInformationList = new Dictionary<int, ProcessInformation>();

        // 
        // Sets the process list
        // 
        public NemesisForm()
        {
            InitializeComponent();

            //
            // Load data
            //
            processListView.LoadProcesses();
            driverListView.LoadDrivers();
        }

        //
        // Refreshes the process list
        //
        private void RefreshButton_Click(object sender, EventArgs e) => processListView.LoadProcesses();

        //
        // Dumps the process
        //
        private void DumpButton_Click(object sender, EventArgs e)
        {
            if (processListView.SelectedItems.Count <= 0 && driverListView.SelectedItems.Count <= 0) return;

            //
            // Set the variables
            //
            var extension = tabControl.SelectedIndex == 0 ? ".exe" : ".sys";
            var filter = tabControl.SelectedIndex == 0 ? "Executable File (.exe)|*.exe" : "System file (.sys)|*.sys";
            var name = tabControl.SelectedIndex == 0
                ? processListView.SelectedItems[0].SubItems[1].Text
                : Path.GetFileNameWithoutExtension(driverListView.SelectedItems[0].SubItems[0].Text);

            var path = "";


            //
            // Ask for location
            //
            if (Config.GetValue("ask_for_location") == "On")
            {
                //
                // Open the dialog
                //
                var saveFile = new SaveFileDialog
                {
                    // 
                    // Set the default name
                    // 
                    FileName = $@"{name}{Config.GetValue("file_name")}{extension}",

                    // 
                    // Set the filters
                    // 
                    Filter = filter
                };

                //
                // Show the dialog
                //
                if (saveFile.ShowDialog() == DialogResult.OK)
                {
                    path = saveFile.FileName;
                }
                else
                {
                    return;
                }
            }

            //
            // Use custom dump location
            //
            if ((Config.GetValue("custom_dump_location")) == "On")
            {
                var dumpLocation = Path.GetFullPath(Config.GetValue("dump_location"));

                //
                // Absolute path
                //
                if (Path.IsPathRooted(path))
                {
                    path = dumpLocation;
                }

                //
                // Relative path
                //
                if (!Path.IsPathRooted(path))
                {
                    path = $@"{Path.Combine(Path.GetDirectoryName(Application.ExecutablePath) ?? throw new InvalidOperationException(), dumpLocation)}";
                }

                //
                // Create process folder
                //
                if (Config.GetValue("create_process_folder") == "On" && name != null)
                {
                    path = Path.Combine(path, name);
                }

                //
                // Create timestamp folder
                //
                if (Config.GetValue("create_timestamp_folder") == "On")
                {
                    path = Path.Combine(path, $@"{DateTime.Now:dd-MM-yyyy HH-mm-ss}");
                }

                //
                // Create the directories (in case they are not existing)
                //
                try
                {
                    Directory.CreateDirectory(path);

                    path = Path.Combine(path, $@"{name}{Config.GetValue("file_name")}");
                }
                catch (Exception exception)
                {
                    MessageBox.Show($@"{exception.Message}", @"Warning");
                    return;
                }
            }

            try
            {
                //
                // Dump it
                //
                var status = false;
                if (tabControl.SelectedIndex == 0)
                {
                    //
                    // Process
                    //
                    if (processListView.SelectedItems[0].Tag is ProcessListItem process)
                    {
                        var processId = int.Parse(process.Id);
                        status = NemesisApi.DumpProcess(processId, path);
                    }
                }
                else
                {
                    //
                    // Driver
                    //
                    if (driverListView.SelectedItems[0].Tag is ModuleListItem module)
                    {
                        var baseAddress = module.BaseAddress;
                        status = NemesisApi.DumpModule(4, (IntPtr) baseAddress, path);
                    }
                }

                //
                // Check status
                //
                var type = tabControl.SelectedIndex == 0 ? "process" : "driver";
                if (status)
                {
                    MessageBox.Show($@"Successfully dumped the {type}.", @"Success");
                }
                else
                {
                    MessageBox.Show($@"Failed to dump the {type}.", @"Warning");
                }
            }
            catch (Exception)
            {
                MessageBox.Show(@"Nemesis threw an exception.", @"Warning");
            }
        }

        //
        // Opens the about window
        //
        private void AboutButton_Click(object sender, EventArgs e)
        {
            var about = new About();
            about.ShowDialog();
            about.Dispose();
        }

        //
        // Opens the settings window
        //
        private void SettingsButton_Click(object sender, EventArgs e)
        {
            var settings = new Settings();
            settings.ShowDialog();
            settings.Dispose();
        }

        //
        // Opens the process information window
        //
        private void ProcessListView_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            //
            // Check if element selected
            //
            if (processListView.SelectedItems.Count <= 0) return;

            //
            // Check if tag is valid
            //
            if (!(processListView.SelectedItems[0].Tag is ProcessListItem item)) return;

            //
            // Use cached process information if available
            //
            var processId = int.Parse(item.Id);
            var processInfo = _processInformationList.ContainsKey(processId) ? _processInformationList[processId] : new ProcessInformation(processId);

            _processInformationList[processId] = processInfo;


            processInfo.ShowDialog();
        }

        //
        // Shortcuts
        //
        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            switch (keyData)
            {
                //
                // Ctrl+D = Dump
                //
                case Keys.Control | Keys.D:
                    DumpButton_Click(null, null);

                    return true;
                //
                // Ctrl+R = Refresh
                //
                case Keys.Control | Keys.R:
                    RefreshButton_Click(null, null);
                    break;
                //
                // Ctrl+Alt+S
                //
                case Keys.Control | Keys.Alt | Keys.S:
                    SettingsButton_Click(null, null);
                    break;
            }

            return base.ProcessCmdKey(ref msg, keyData);
        }
    }
}