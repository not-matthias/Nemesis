using MetroFramework.Forms;
using System;
using System.IO;
using System.Windows.Forms;

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
                ListViewItem selectedItem = processListView.SelectedItems[0];

                int processId = int.Parse(selectedItem.SubItems[0].Text);
                string processName = selectedItem.SubItems[1].Text;

                string path = "";


                //
                // Ask for location
                //
                if (Config.GetValue("ask_for_location") == "On")
                {
                    //
                    // Open the dialog
                    //
                    SaveFileDialog saveFile = new SaveFileDialog
                    {
                        // 
                        // Set the default name
                        // 
                        FileName = $@"{processName}{Config.GetValue("file_name")}",

                        // 
                        // Set the filters
                        // 
                        Filter = "Executable File (.exe)|*.exe"
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
                    string dump_location = Config.GetValue("dump_location");

                    //
                    // Absolute path
                    //
                    if (Path.IsPathRooted(path))
                    {
                        path = dump_location;
                    }

                    //
                    // Relative path
                    //
                    if (!Path.IsPathRooted(path))
                    {
                        path = $@"{Path.GetDirectoryName(Application.ExecutablePath)}/{dump_location}";
                    }

                    //
                    // Create process folder
                    //
                    if (Config.GetValue("create_process_folder") == "On")
                    {
                        path += $@"{processName}/";
                    }

                    //
                    // Create timestamp folder
                    //
                    if (Config.GetValue("create_timestamp_folder") == "On")
                    {
                        path += $@"{DateTime.Now.ToString("dd-MM-yyyy HH-mm-ss")}/";
                    }

                    //
                    // Create the directories (in case they are not existing)
                    //
                    try
                    {
                        Directory.CreateDirectory(path);
                        path += $@"/{processName}{Config.GetValue("file_name")}";
                    }
                    catch (Exception)
                    {
                        MessageBox.Show("Custom path is invalid. Make sure the path is correct.", "Warning");
                        return;
                    }

                }

                //
                // Dump it
                //
                try
                {
                    bool status = NemesisApi.StandardDump(processId, path);
                    if (status)
                    {
                        MessageBox.Show("Successfully dumped the process.", "Success");
                    }
                    else
                    {
                        MessageBox.Show("Failed to dump the process.", "Warning");
                    }
                }
                catch(Exception)
                {
                    MessageBox.Show("Nemesis threw an exception.", "Warning");
                }

               
            }
        }

        //
        // Opens the about window
        //
        private void AboutButton_Click(object sender, EventArgs e)
        {
            About about = new About();
            about.ShowDialog();
            about.Dispose();
        }

        //
        // Opens the settings window
        //
        private void SettingsButton_Click(object sender, EventArgs e)
        {
            Settings settings = new Settings();
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
                ListViewItem listViewItem = (ListViewItem)sender;
                


                ProcessInfo processInfo = new ProcessInfo();
                processInfo.ShowDialog();
                processInfo.Dispose();
            }
        }

        //
        // Shortcuts
        //
        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            //
            // Ctrl+D = Dump
            //
            if (keyData == (Keys.Control | Keys.D))
            {
                DumpButton_Click(null, null);

                return true;
            }

            //
            // Ctrl+R = Refresh
            //
            if (keyData == (Keys.Control | Keys.R))
            {
                RefreshButton_Click(null, null);
            }

            //
            // Ctrl+Alt+S
            //
            if (keyData == (Keys.Control | Keys.Alt | Keys.S))
            {
                SettingsButton_Click(null, null);
            }

            return base.ProcessCmdKey(ref msg, keyData);
        }
    }
}
