using System.Windows.Forms;

namespace Nemesis.Forms.Utils.Process
{
    internal sealed class ProcessListView : ListView
    {
        private int _sortColumnIndex;

        /// <inheritdoc />
        /// <summary>
        /// Sets list view properties.
        /// </summary>
        public ProcessListView()
        {
            Columns.Add("Pid");
            Columns.Add("ProcessName");

            DoubleBuffered = true;
            Sorting = SortOrder.Ascending;
        }

        /// <summary>
        /// Loads the processes and adds them to the list.
        /// </summary>
        /// <returns>True if successful</returns>
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