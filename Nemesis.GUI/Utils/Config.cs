using System.Configuration;

namespace Nemesis.Utils
{
    internal class Config
    {
        /// <summary>
        /// Sets the specified value in the config.
        /// </summary>
        /// <param name="key">The key of the value</param>
        /// <param name="value">The actual value</param>
        public static void SetValue(string key, string value)
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

        /// <summary>
        /// Retrieves the specified value from the config.
        /// </summary>
        /// <param name="key">The key of the value</param>
        /// <returns>The value as a string</returns>
        public static string GetValue(string key) => ConfigurationManager.AppSettings[key];
    }
}