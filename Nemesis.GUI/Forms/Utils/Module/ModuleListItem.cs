using System.Windows.Forms;

namespace Nemesis.Forms.Utils.Module
{
    internal class ModuleListItem
    {
        public string ModuleName { get; }
        public long BaseAddress { get; }

        public ModuleListItem(string moduleName, long baseAddress)
        {
            ModuleName = moduleName;
            BaseAddress = baseAddress;
        }

        public ListViewItem GetListViewItem()
        {
            var listViewItem = new ListViewItem(ModuleName);
            listViewItem.SubItems.Add(BaseAddress.ToString("X"));
            listViewItem.Tag = this;

            return listViewItem;
        }
    }
}
