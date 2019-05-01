using System.Windows.Forms;

namespace Nemesis.Forms.Utils.Module
{
    internal class ModuleListItem
    {
        public long BaseAddress { get; }
        public string ModuleName { get; }

        /// <summary>
        /// Sets the specified data.
        /// </summary>
        /// <param name="baseAddress">The base address of the module</param>
        /// <param name="moduleName">The name of the module</param>
        public ModuleListItem(long baseAddress, string moduleName)
        {
            BaseAddress = baseAddress;
            ModuleName = moduleName;
        }

        /// <summary>
        /// Returns the list view item for the module list.
        /// </summary>
        /// <returns>ListViewItem</returns>
        public ListViewItem GetListViewItem()
        {
            var listViewItem = new ListViewItem(BaseAddress.ToString("X8"));
            listViewItem.SubItems.Add(ModuleName);
            listViewItem.Tag = this;

            return listViewItem;
        }
    }
}
