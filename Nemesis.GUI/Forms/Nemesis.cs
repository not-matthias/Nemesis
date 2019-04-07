using MetroFramework.Forms;
using System;
using System.IO;
using System.Windows.Forms;
using Nemesis.Utils;

namespace Nemesis.Forms
{
    public partial class Nemesis : MetroForm
    {
        // 
        // Sets the process list
        // 
        public Nemesis()
        {
            InitializeComponent();

            //
            // Set the process list
            //
            processListView.LoadProcesses();
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
            if (processListView.SelectedItems.Count > 0)
            {
                var selectedItem = processListView.SelectedItems[0];
                var processId = int.Parse(selectedItem.SubItems[0].Text);
                var processName = selectedItem.SubItems[1].Text;
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
                        FileName = $@"{processName}{Config.GetValue("file_name")}",

                        // 
                        // Set the filters
                        // 
                        Filter = @"Executable File (.exe)|*.exe"
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
                        path = $@"{Path.Combine(Path.GetDirectoryName(Application.ExecutablePath), dumpLocation)}";
                    }

                    //
                    // Create process folder
                    //
                    if (Config.GetValue("create_process_folder") == "On")
                    {
                        path = Path.Combine(path, processName);
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

                        path = Path.Combine(path, $@"{processName}{Config.GetValue("file_name")}");
                    }
                    catch (Exception exception)
                    {
                        MessageBox.Show($@"{exception.Message}", @"Warning");
                        return;
                    }
                }

                //
                // Dump it
                //
                try
                {
                    var status = NemesisApi.DumpProcess(processId, path);
                    if (status)
                    {
                        MessageBox.Show(@"Successfully dumped the process.", @"Success");
                    }
                    else
                    {
                        MessageBox.Show(@"Failed to dump the process.", @"Warning");
                    }
                }
                catch (Exception)
                {
                    MessageBox.Show(@"Nemesis threw an exception.", @"Warning");
                }
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
            if (processListView.SelectedItems.Count > 0)
            {
                var listViewItem = (ListViewItem) sender;

                var processInfo = new ProcessInfo();
                processInfo.ShowDialog();
                processInfo.Dispose();
            }
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