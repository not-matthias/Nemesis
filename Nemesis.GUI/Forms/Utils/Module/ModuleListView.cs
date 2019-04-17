using System.Collections.Generic;
using System.Windows.Forms;

namespace Nemesis.Forms.Utils.Module
{
    public sealed partial class ModuleListView : ListView
    {
        public ModuleListView()
        {
            Columns.Add("Name");
            Columns.Add("BaseAddress");

            DoubleBuffered = true;
            Sorting = SortOrder.Ascending;
        }

        public void LoadModules(List<Nemesis.Utils.Module> modules)
        {
            //
            // Remove all previous processes
            //
            Items.Clear();

            //
            // Loop through all processes
            //
            foreach (var module in modules)
            {
                //
                // Create a new ProcessListItem
                //
                var processListItem = new ModuleListItem(module.module_name, module.base_address);

                //
                // Add it to the ListView
                //
                Items.Add(processListItem.GetListViewItem());
            }

            //
            // Auto resize the columns
            //
            AutoResizeColumns(ColumnHeaderAutoResizeStyle.HeaderSize);
        }
    }
}