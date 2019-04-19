using System.Windows.Forms;
using Nemesis.Utils;

namespace Nemesis.Forms.Utils.Module
{
    public sealed partial class ModuleListView : ListView
    {
        private int _sortColumnIndex = 0;

        public ModuleListView()
        {
            Columns.Add("ImageBase");
            Columns.Add("Path");

            DoubleBuffered = true;
            Sorting = SortOrder.Ascending;
        }

        public bool LoadModules(int processId)
        {
            var modules = NemesisApi.GetModuleList(processId);

            //
            // Check if empty
            //
            if (modules.Count == 0) return false;

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
                var processListItem = new ModuleListItem(module.base_address, module.module_name);

                //
                // Add it to the ListView
                //
                Items.Add(processListItem.GetListViewItem());
            }

            //
            // Auto resize the columns
            //
            AutoResizeColumns(ColumnHeaderAutoResizeStyle.HeaderSize);

            //
            // Sort the list
            //
            ListViewItemSorter = new ModuleSorter(_sortColumnIndex, Sorting);

            return true;
        }

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
            ListViewItemSorter = new ModuleSorter(e.Column, Sorting);
        }
    }
}