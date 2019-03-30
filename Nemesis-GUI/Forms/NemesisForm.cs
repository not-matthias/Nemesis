using MetroFramework.Forms;
using System;
using System.Windows.Forms;

namespace Nemesis
{
    public partial class NemesisForm : MetroForm
    {
        // 
        // Sets the process list
        // 
        public NemesisForm()
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
                // Create process folder
                //
                if (Config.GetValue("create_process_folder") == "On")
                {
                    path += processName + "/";
                    System.IO.Directory.CreateDirectory(path);
                }

                //
                // Create timestamp folder
                //
                if (Config.GetValue("create_timestamp_folder") == "On")
                {
                    path += DateTime.Now.ToString("MM.dd.yyyy HH:mm:ss") + "/";
                    System.IO.Directory.CreateDirectory(path);
                }

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
                if ((path = Config.GetValue("custom_dump_location")) == "On")
                {
                    path += $@"/{processName}{Config.GetValue("file_name")}";
                }


                //
                // Dump it
                //
                bool status = NemesisApi.StandardDump(processId, path);
                if (status)
                {
                    MessageBox.Show("Successfully dumped the process.", "Success");
                }
                else
                {
                    MessageBox.Show("Failed to dump the process.", "Failure");
                }
            }
        }

        //
        // Opens the about window
        //
        private void AboutButton_Click(object sender, EventArgs e)
        {
            AboutForm aboutForm = new AboutForm();
            aboutForm.ShowDialog();
            aboutForm.Dispose();
        }

        //
        // Opens the settings window
        //
        private void SettingsButton_Click(object sender, EventArgs e)
        {
            SettingsForm settingsForm = new SettingsForm();
            settingsForm.ShowDialog();
            settingsForm.Dispose();
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
