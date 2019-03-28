using Nemesis.Utils;
using System.Diagnostics;
using System.Windows.Forms;

namespace Nemesis
{
    internal class ProcessListView : ListView
    {
        private int sortColumnIndex = 0;

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
            Process[] processlist = Process.GetProcesses();

            //
            // Remove all previous processes
            //
            Items.Clear();

            //
            // Loop through all processes
            //
            foreach (Process process in processlist)
            {
                //
                // Create a new ProcessListItem
                //
                ProcessListItem processListItem = new ProcessListItem(process.Id.ToString(), process.ProcessName);

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
            ListViewItemSorter = new ProcessSorter(sortColumnIndex, Sorting);
        }

        //
        // Sort the columns on click
        //
        protected override void OnColumnClick(ColumnClickEventArgs e)
        {
            //
            // Check if another column clicked
            //
            if (e.Column != sortColumnIndex)
            {
                sortColumnIndex = e.Column;
                Sorting = SortOrder.Ascending;
            }
            else
            {
                //
                // Change the SortOrder to the opposite
                //
                if (Sorting == SortOrder.Ascending)
                {
                    Sorting = SortOrder.Descending;
                }
                else
                {
                    Sorting = SortOrder.Ascending;
                }
            }

            //
            // Sort the list
            //
            ListViewItemSorter = new ProcessSorter(e.Column, Sorting);
        }
    }
}
