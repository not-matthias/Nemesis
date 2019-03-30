using MetroFramework.Controls;
using MetroFramework.Forms;
using System;

namespace Nemesis
{
    public partial class SettingsForm : MetroForm
    {
        //
        // Sets the values from the config
        //
        public SettingsForm()
        {
            InitializeComponent();

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
            addTimestampFolderToggle.Checked = Config.GetValue("create_timestamp_folder") == "On" ? true : false;
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
            Config.SetValue("create_timestamp_folder", addTimestampFolderToggle.Text);
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
                customDumpLocationToggle.Checked = false;
            }
        }
    }
}
