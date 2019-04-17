using System.Windows.Forms;

namespace Nemesis.Forms.Utils.Memory
{
    internal class MemoryListItem
    {
        public long BaseAddress { get; }
        public int RegionSize { get; }
        public int State { get; }
        public int Type { get; }

        public MemoryListItem(long baseAddress, int regionSize, int state, int type)
        {
            BaseAddress = baseAddress;
            RegionSize = regionSize;
            State = state;
            Type = type;
        }

        public ListViewItem GetListViewItem()
        {
            var listViewItem = new ListViewItem(BaseAddress.ToString("X"));
            listViewItem.SubItems.Add(RegionSize.ToString("X"));
            listViewItem.SubItems.Add(State.ToString());
            listViewItem.SubItems.Add(Type.ToString());
            listViewItem.Tag = this;

            return listViewItem;
        }
    }
}