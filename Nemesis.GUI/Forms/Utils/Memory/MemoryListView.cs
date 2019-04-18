using System.Windows.Forms;
using Nemesis.Utils;

namespace Nemesis.Forms.Utils.Memory
{
    public sealed partial class MemoryListView: ListView
    {
        public MemoryListView()
        {
            Columns.Add("BaseAddress");
            Columns.Add("RegionSize");
            Columns.Add("State");
            Columns.Add("Type");

            DoubleBuffered = true;
            Sorting = SortOrder.Ascending;
        }

        public void LoadMemory(int processId)
        {
            var memory = NemesisApi.GetMemoryList(processId);

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
                var memoryListItem = new MemoryListItem(item.base_address, item.region_size, item.state, item.type);

                //
                // Add it to the ListView
                //
                Items.Add(memoryListItem.GetListViewItem());
            }

            //
            // Auto resize the columns
            //
            AutoResizeColumns(ColumnHeaderAutoResizeStyle.HeaderSize);
        }
    }
}
