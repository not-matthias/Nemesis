using MetroFramework.Controls;
using MetroFramework.Forms;
using System;

namespace Nemesis
{
    public partial class SettingsForm : MetroForm
    {
        public SettingsForm()
        {
            InitializeComponent();
        }

        //
        // Saves the settings in the config
        //
        private void SaveButton_Click(object sender, EventArgs e)
        {
            Config.SetValue("dump_location", dumpLocation.Text);
            Config.SetValue("file_name", fileName.Text);

            Config.SetValue("custom_dump_location", customDumpLocationToggle.Text);
            Config.SetValue("create_folder", createFolderToggle.Text);
            Config.SetValue("add_timestamp", addTimestampToggle.Text);
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
