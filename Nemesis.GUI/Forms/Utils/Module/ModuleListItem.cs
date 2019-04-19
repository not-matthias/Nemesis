using System.Windows.Forms;

namespace Nemesis.Forms.Utils.Module
{
    internal class ModuleListItem
    {
        public long BaseAddress { get; }
        public string ModuleName { get; }

        public ModuleListItem(long baseAddress, string moduleName)
        {
            BaseAddress = baseAddress;
            ModuleName = moduleName;
        }

        public ListViewItem GetListViewItem()
        {
            var listViewItem = new ListViewItem(BaseAddress.ToString("X8"));
            listViewItem.SubItems.Add(ModuleName);
            listViewItem.Tag = this;

            return listViewItem;
        }
    }
}
