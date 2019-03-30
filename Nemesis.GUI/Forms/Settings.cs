using MetroFramework.Controls;
using MetroFramework.Forms;
using System;
using System.Windows.Forms;

namespace Nemesis.Forms
{
    public partial class Settings : MetroForm
    {
        //
        // Sets the values from the config
        //
        public Settings()
        {
            InitializeComponent();

            //
            // Set default values the first time
            //
            if(Config.GetValue("first_time_started") == null)
            {
                Config.SetValue("file_name", "_dump.exe");
                Config.SetValue("ask_for_location", "On");

                Config.SetValue("first_time_started", ".");
            }

            //
            // TextFields
            //
            dumpLocation.Text = Config.GetValue("dump_location");
            fileName.Text = Config.GetValue("file_name");

            //
            // Toggles
            //
            // TODO: Find a better way
            customDumpLocationToggle.Checked = Config.GetValue("custom_dump_location") == "On" ? true : false;
            createFolderToggle.Checked = Config.GetValue("create_process_folder") == "On" ? true : false;
            createTimestampFolderToggle.Checked = Config.GetValue("create_timestamp_folder") == "On" ? true : false;
            askForLocationToggle.Checked = Config.GetValue("ask_for_location") == "On" ? true : false;
        }

        //
        // Saves the settings in the config
        //
        private void SaveButton_Click(object sender, EventArgs e)
        {
            Config.SetValue("dump_location", dumpLocation.Text);
            Config.SetValue("file_name", fileName.Text);

            Config.SetValue("custom_dump_location", customDumpLocationToggle.Text);
            Config.SetValue("create_process_folder", createFolderToggle.Text);
            Config.SetValue("create_timestamp_folder", createTimestampFolderToggle.Text);
            Config.SetValue("ask_for_location", askForLocationToggle.Text);

            Close();
        }

        //
        // Enables the custom dump location option
        //
        private void CustomDumpLocationToggle_CheckedChanged(object sender, EventArgs e)
        {
            MetroToggle toggle = (MetroToggle)sender;

            //
            // Disable "ask for location" if enabled
            //
            if (toggle.Checked)
            {
                dumpLocation.ReadOnly = false;
                askForLocationToggle.Checked = false;
            }
            else
            {
                dumpLocation.Clear();
                dumpLocation.ReadOnly = true;
            }
        }

        //
        // Enables the process folder option
        //
        private void CreateFolderToggle_CheckedChanged(object sender, EventArgs e)
        {
            MetroToggle toggle = (MetroToggle)sender;

            //
            // Disable "ask for location" if enabled
            //
            if (toggle.Checked)
            {
                askForLocationToggle.Checked = false;
            }
        }

        //
        // Enables the timestamp folder option
        //
        private void CreateTimestampFolderToggle_CheckedChanged(object sender, EventArgs e)
        {
            MetroToggle toggle = (MetroToggle)sender;

            //
            // Disable "ask for location" if enabled
            //
            if (toggle.Checked)
            {
                askForLocationToggle.Checked = false;
            }
        }

        //
        // Enables ask for location option
        // 
        private void AskForLocationToggle_CheckedChanged(object sender, EventArgs e)
        {
            MetroToggle toggle = (MetroToggle)sender;

            //
            // Disable "custom dump location" if enabled
            //
            if (toggle.Checked)
            {
                dumpLocation.Clear();

                //
                // Can't have generated folders when having this option enabled
                //
                customDumpLocationToggle.Checked = false;
                createFolderToggle.Checked = false;
                createTimestampFolderToggle.Checked = false;
            }
        }

    }
}
