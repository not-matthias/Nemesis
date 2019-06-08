using System.Windows.Forms;

namespace Nemesis.Forms.Utils.Module
{
    internal class ModuleListItem
    {
        public long ImageBase { get; }
        public long ImageSize { get; }
        public string ModuleName { get; }
        public string ModulePath { get; }

        /// <summary>
        /// Sets the specified data.
        /// </summary>
        /// <param name="imageBase">The base address of the module</param>
        /// <param name="imageSize">The size of the image</param>
        /// <param name="moduleName">The name of the module</param>
        /// <param name="modulePath">The path to the image</param>
        public ModuleListItem(long imageBase, long imageSize, string moduleName, string modulePath)
        {
            ImageBase = imageBase;
            ImageSize = imageSize;
            ModuleName = moduleName;
            ModulePath = modulePath;
        }

        /// <summary>
        /// Returns the list view item for the module list.
        /// </summary>
        /// <returns>ListViewItem</returns>
        public ListViewItem GetListViewItem()
        {
            var listViewItem = new ListViewItem(ModuleName);
            listViewItem.SubItems.Add(ImageBase.ToString("X8"));
            listViewItem.SubItems.Add(ImageSize.ToString("X8"));
            listViewItem.SubItems.Add(ModulePath);
            listViewItem.Tag = this;

            return listViewItem;
        }
    }
}
