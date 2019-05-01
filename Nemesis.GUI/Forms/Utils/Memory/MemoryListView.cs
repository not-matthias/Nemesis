using System.Windows.Forms;
using Nemesis.Utils;

namespace Nemesis.Forms.Utils.Memory
{
    public sealed partial class MemoryListView: ListView
    {
        private int _sortColumnIndex;

        /// <inheritdoc />
        /// <summary>
        /// Sets list view properties and columns.
        /// </summary>
        public MemoryListView()
        {
            Columns.Add("BaseAddress");
            Columns.Add("RegionSize");
            Columns.Add("State");
            Columns.Add("Type");

            DoubleBuffered = true;
            Sorting = SortOrder.Ascending;
        }

        /// <summary>
        /// Loads the memory regions and adds them to the list.
        /// </summary>
        /// <returns>True if successful</returns>
        public bool LoadMemory(int processId)
        {
            var memory = NemesisApi.GetMemoryList(processId);

            //
            // Check if empty
            //
            if (memory.Count == 0) return false;

            //
            // Remove all previous processes
            //
            Items.Clear();

            //
            // Loop through all processes
            //
            foreach (var item in memory)
            {
                //
                // Create a new ProcessListItem
                //
                var memoryListItem = new MemoryListItem(item.BaseAddress, item.RegionSize, item.State, item.Type);

                //
                // Add it to the ListView
                //
                Items.Add(memoryListItem.GetListViewItem());
            }

            //
            // Auto resize the columns
            //
            AutoResizeColumns(ColumnHeaderAutoResizeStyle.HeaderSize);

            //
            // Sort the list
            //
            ListViewItemSorter = new MemorySorter(_sortColumnIndex, Sorting);

            return true;
        }

        /// <inheritdoc />
        /// <summary>
        /// Sorts the list by the clicked column.
        /// </summary>
        /// <param name="e"></param>
        protected override void OnColumnClick(ColumnClickEventArgs e)
        {
            //
            // Check if another column clicked
            //
            if (e.Column != _sortColumnIndex)
            {
                _sortColumnIndex = e.Column;
                Sorting = SortOrder.Descending;
            }
            else
            {
                //
                // Change the SortOrder to the opposite
                //
                Sorting = Sorting == SortOrder.Ascending ? SortOrder.Descending : SortOrder.Ascending;
            }

            //
            // Sort the list
            //
            ListViewItemSorter = new MemorySorter(e.Column, Sorting);
        }
    }
}
