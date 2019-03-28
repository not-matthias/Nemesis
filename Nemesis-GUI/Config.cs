using System;
using System.Collections.Generic;
using System.Configuration;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Nemesis
{
    class Config
    {
        //
        // Sets the specified value in the config
        //
        private static void SetValue(string key, string value)
        {
            //
            // Get the config file
            //
            var configFile = ConfigurationManager.OpenExeConfiguration(ConfigurationUserLevel.None);
            var settings = configFile.AppSettings.Settings;

            //
            // Add the key/Change the value
            //
            if (settings[key] == null)
            {
                settings.Add(key, value);
            }
            else
            {
                settings[key].Value = value;
            }

            //
            // Save the configuration
            //
            configFile.Save(ConfigurationSaveMode.Modified);

            //
            // Refresh the section (will get retrieved from the disk next time)
            //
            ConfigurationManager.RefreshSection(configFile.AppSettings.SectionInformation.Name);
        }

        //
        // Retrieves the specified value from the config
        //
        private static string GetValue(string key) => ConfigurationManager.AppSettings[key];
    }
}
