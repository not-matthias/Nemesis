using Nemesis.Utils;
using System.Collections;
using System.Windows.Forms;

namespace Nemesis
{
    public class ProcessSorter : IComparer
    {
        private readonly int columnIndex;
        private readonly SortOrder sortOrder;

        public ProcessSorter(int columnIndex, SortOrder sortOrder)
        {
            this.columnIndex = columnIndex;
            this.sortOrder = sortOrder;
        }

        //
        // Compare the two ProcessListItems
        //
        public int Compare(object x, object y)
        {
            if ((x is ListViewItem) && (y is ListViewItem))
            {
                ProcessListItem p1 = ((ListViewItem)x).Tag as ProcessListItem;
                ProcessListItem p2 = ((ListViewItem)y).Tag as ProcessListItem;

                if (!(p1 == null || p2 == null))
                {
                    int result = 0;

                    switch (columnIndex)
                    {
                        //
                        // ProcessId
                        //
                        case 0:
                            int pid1 = int.Parse(p1.Id);
                            int pid2 = int.Parse(p2.Id);

                            if (pid1 > pid2)
                                result = 1;

                            if (pid1 < pid2)
                                result = - 1;

                            break;

                        //
                        // ProcessName
                        //
                        case 1:
                            result = p1.ProcessName.CompareTo(p2.ProcessName);
                            break;
                    }

                    //
                    // Revert the sort if it's descending
                    //
                    if (sortOrder == SortOrder.Descending)
                    {
                        result = -result;
                    }

                    return result;
                }
            }

            return 0;
        }
    }
}

