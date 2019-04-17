using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using MetroFramework.Forms;
using Nemesis.Forms.Utils.Module;

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

        public void LoadMemory(List<Nemesis.Utils.Memory> memory)
        {
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
