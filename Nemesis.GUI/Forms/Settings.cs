using MetroFramework.Controls;
using MetroFramework.Forms;
using System;
using System.Windows.Forms;
using MetroFramework;
using Nemesis.Utils;

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
            if (Config.GetValue("first_time_started") == null)
            {
                Config.SetValue("file_name", "_dump");
                Config.SetValue("ask_for_location", "On");

                Config.SetValue("first_time_started", ".");
                Config.SetValue("theme", "Default");
                Config.SetValue("style", "Default");
            }

            //
            // TextFields
            //
            dumpLocation.Text = Config.GetValue("dump_location");
            fileName.Text = Config.GetValue("file_name");

            //
            // Toggles
            //
            customDumpLocationToggle.Checked = Config.GetValue("custom_dump_location") == "On";
            createFolderToggle.Checked = Config.GetValue("create_process_folder") == "On";
            createTimestampFolderToggle.Checked = Config.GetValue("create_timestamp_folder") == "On";
            askForLocationToggle.Checked = Config.GetValue("ask_for_location") == "On";

            // Theme and Style: Located in NemesisForm (because StyleManager does not exist here yet)

            //
            // Fill the combo boxes
            //
            themeComboBox.Items.AddRange(new object[] {"Dark", "Light"});
            colorComboBox.Items.AddRange(new object[]
                {"Default", "Black", "White", "Silver", "Blue", "Green", "Lime", "Teal", "Orange", "Brown", "Pink", "Magenta", "Purple", "Red", "Yellow"});
            memoryComboBox.Items.AddRange(NemesisApi.GetMemorySources().ToArray());
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

            Config.SetValue("theme", themeComboBox.Text);
            Config.SetValue("style", colorComboBox.Text);

            Close();
        }

        //
        // Enables the custom dump location option
        //
        private void CustomDumpLocationToggle_CheckedChanged(object sender, EventArgs e)
        {
            var toggle = (MetroToggle) sender;

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
            var toggle = (MetroToggle) sender;

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
            var toggle = (MetroToggle) sender;

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
            var toggle = (MetroToggle) sender;

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

        private void ThemeComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            StyleManager.Theme = GetMetroThemeStyle(themeComboBox.Text);

            Refresh();
        }

        private void ColorComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            StyleManager.Style = GetMetroColorStyle(colorComboBox.Text);

            Refresh();
        }

        public static MetroThemeStyle GetMetroThemeStyle(string name)
        {
            try
            {
                Enum.TryParse(name, out MetroThemeStyle color);

                return color;
            }
            catch (ArgumentException)
            {
                return MetroThemeStyle.Default;
            }
        }

        public static MetroColorStyle GetMetroColorStyle(string name)
        {
            try
            {
                Enum.TryParse(name, out MetroColorStyle color);

                return color;
            }
            catch (ArgumentException)
            {
                return MetroColorStyle.Default;
            }
        }

        private void MemoryComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (!NemesisApi.SetMemorySource(memoryComboBox.Text))
            {
                MessageBox.Show("Failed to set new memory source.", "Error");
            }
        }
    }
}