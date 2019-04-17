using System.Windows.Forms;

namespace Nemesis.Forms.Utils.Process
{
    internal sealed class ProcessListView : ListView
    {
        private int _sortColumnIndex = 0;

        //
        // Sets some properties
        //
        public ProcessListView()
        {
            Columns.Add("Pid");
            Columns.Add("ProcessName");

            DoubleBuffered = true;
            Sorting = SortOrder.Ascending;
        }

        //
        // Sets the processes in the list
        //
        public void LoadProcesses()
        {
            //
            // Get the process list
            //
            var processlist = System.Diagnostics.Process.GetProcesses();

            //
            // Remove all previous processes
            //
            Items.Clear();

            //
            // Loop through all processes
            //
            foreach (var process in processlist)
            {
                //
                // Create a new ProcessListItem
                //
                var processListItem = new ProcessListItem(process.Id.ToString(), process.ProcessName);

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
            ListViewItemSorter = new ProcessSorter(_sortColumnIndex, Sorting);
        }

        //
        // Sort the columns on click
        //
        protected override void OnColumnClick(ColumnClickEventArgs e)
        {
            //
            // Check if another column clicked
            //
            if (e.Column != _sortColumnIndex)
            {
                _sortColumnIndex = e.Column;
                Sorting = SortOrder.Ascending;
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
            ListViewItemSorter = new ProcessSorter(e.Column, Sorting);
        }
    }
}