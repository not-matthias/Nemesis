using System;
using System.Windows.Forms;

namespace Nemesis.Forms.Utils.Memory
{
    internal class MemoryListItem
    {
        public long BaseAddress { get; }
        public int RegionSize { get; }
        public int State { get; }
        public int Type { get; }

        /// <summary>
        /// Sets the specified data.
        /// </summary>
        /// <param name="baseAddress">The base address of the memory region</param>
        /// <param name="regionSize">The size of the memory region</param>
        /// <param name="state">The state of the memory region (MEM_COMMIT, MEM_RESERVE, MEM_FREE, MEM_PRIVATE, MEM_MAPPED, or MEM_IMAGE)</param>
        /// <param name="type">The type of the memory region (MEM_IMAGE, MEM_MAPPED or MEM_PRIVATE)</param>
        public MemoryListItem(long baseAddress, int regionSize, int state, int type)
        {
            BaseAddress = baseAddress;
            RegionSize = regionSize;
            State = state;
            Type = type;
        }

        /// <summary>
        /// Returns the list view item for the memory list.
        /// </summary>
        /// <returns>ListViewItem</returns>
        public ListViewItem GetListViewItem()
        {
            var listViewItem = new ListViewItem(BaseAddress.ToString("X8"));
            listViewItem.SubItems.Add(RegionSize.ToString("X8"));

            var state = "";
            state += (State & 0x1000) != 0 ? "MEM_COMMIT" : "";
            state += (State & 0x10000) != 0 ? "MEM_FREE" : "";
            state += (State & 0x2000) != 0 ? "MEM_RESERVE" : "";
            listViewItem.SubItems.Add(State.ToString());

            var type = "";
            type += (Type & 0x1000000) != 0 ? "MEM_IMAGE" : "";
            type += (Type & 0x40000) != 0 ? "MEM_MAPPED" : "";
            type += (Type & 0x20000) != 0 ? "MEM_PRIVATE" : "";
            listViewItem.SubItems.Add(Type.ToString());
            listViewItem.Tag = this;

            return listViewItem;
        }
    }
}