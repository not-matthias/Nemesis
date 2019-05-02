using System;
using System.Collections.Generic;
using System.ComponentModel;
using MetroFramework;
using MetroFramework.Components;
using MetroFramework.Forms;

namespace Nemesis.Utils
{
    public static class StyleExtension
    {
        private static readonly List<MetroStyleManager> StyleManagers = new List<MetroStyleManager>();

        private static MetroColorStyle _colorStyle = GetMetroColorStyle(Config.GetValue("style"));
        private static MetroThemeStyle _themeStyle = GetMetroThemeStyle(Config.GetValue("theme"));

        /// <summary>
        /// Creates a new MetroStyleManager and sets the styles.
        /// </summary>
        /// <param name="container">The component container</param>
        /// <param name="ownerForm">The metro form</param>
        public static void SetStyle(this IContainer container, MetroForm ownerForm)
        {
            if (container == null)
            {
                container = new Container();
            }

            //
            // Create new MetroStyleManager and add it to the list
            //
            StyleManagers.Add(new MetroStyleManager(container) {Owner = ownerForm});

            //
            // Update the styles
            //
            UpdateStyles();
        }

        /// <summary>
        /// Sets a new color style.
        /// </summary>
        /// <param name="colorStyle">The new color style</param>
        public static void SetColorStyle(MetroColorStyle colorStyle)
        {
            _colorStyle = colorStyle;

            UpdateStyles();
        }

        /// <summary>
        /// Sets a new theme style.
        /// </summary>
        /// <param name="themeStyle">The new theme style</param>
        public static void SetThemeStyle(MetroThemeStyle themeStyle)
        {
            _themeStyle = themeStyle;

            UpdateStyles();
        }

        /// <summary>
        /// Updates the style and theme of all forms.
        /// </summary>
        public static void UpdateStyles()
        {
            foreach (var styleManager in StyleManagers)
            {
                var metroForm = (MetroForm) styleManager.Owner;
                metroForm.Theme = _themeStyle;
                metroForm.Style = _colorStyle;

                styleManager.Theme = _themeStyle;
                styleManager.Style = _colorStyle;
            }
        }

        /// <summary>
        /// Returns the metro theme enum value for the specified name.
        /// </summary>
        /// <param name="name">The name of the enum value</param>
        /// <returns>Specified enum value or MetroThemeStyle.Default</returns>
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

        /// <summary>
        /// Returns the metro color enum value for the specified name.
        /// </summary>
        /// <param name="name">The name of the enum value</param>
        /// <returns>Specified enum value or MetroColorStyle.Default</returns>
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
    }
}