using MetroFramework.Controls;
using MetroFramework.Forms;
using System;
using System.Windows.Forms;
using Nemesis.Utils;

namespace Nemesis.Forms
{
    public partial class Settings : MetroForm
    {
        /// <summary>
        /// Loads and sets the config data.
        /// </summary>
        public Settings()
        {
            InitializeComponent();

            //
            // Set the styles
            //
            components.SetStyle(this);

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
                Config.SetValue("memory_source", "user_mode");
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

            //
            // Set the combo box values
            //
            themeComboBox.SelectedIndex = GetItemIndex(themeComboBox, Config.GetValue("theme"));
            colorComboBox.SelectedIndex = GetItemIndex(colorComboBox, Config.GetValue("style"));
            memoryComboBox.SelectedIndex = GetItemIndex(memoryComboBox, Config.GetValue("memory_source"));
        }

        /// <summary>
        /// Saves the settings to the config.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
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

            Config.SetValue("memory_source", memoryComboBox.Text);

            Close();
        }

        /// <summary>
        /// Enables the "custom dump location" option.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
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

        /// <summary>
        /// Enables the "create process folder" option.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
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

        /// <summary>
        /// Enables the "create timestamp folder" option.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
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

        /// <summary>
        /// Enables "ask for location" option.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
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

        /// <summary>
        /// Changes the theme of the application.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ThemeComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            StyleExtension.SetThemeStyle(StyleExtension.GetMetroThemeStyle(themeComboBox.Text));

            Refresh();
        }

        /// <summary>
        /// Changes the color of the application.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ColorComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            StyleExtension.SetColorStyle(StyleExtension.GetMetroColorStyle(colorComboBox.Text));

            Refresh();
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void MemoryComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (!NemesisApi.SetMemorySource(memoryComboBox.Text))
            {
                MessageBox.Show("Failed to set new memory source.", "Error");
            }
        }

        /// <summary>
        /// Returns the index of the specified item in the specified combo box.
        /// </summary>
        /// <param name="comboBox">The target combo box</param>
        /// <param name="value">The value of an item</param>
        /// <returns>Index or -1</returns>
        private int GetItemIndex(ComboBox comboBox, string value)
        {
            foreach (var item in comboBox.Items)
            {
                if (item as string == value)
                {
                    return comboBox.Items.IndexOf(item);
                }
            }

            return -1;
        }
    }
}