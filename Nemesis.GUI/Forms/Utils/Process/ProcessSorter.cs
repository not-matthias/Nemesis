using System;
using System.Collections;
using System.Windows.Forms;

namespace Nemesis.Forms.Utils.Process
{
    public class ProcessSorter : IComparer
    {
        private readonly int _columnIndex;
        private readonly SortOrder _sortOrder;

        public ProcessSorter(int columnIndex, SortOrder sortOrder)
        {
            _columnIndex = columnIndex;
            _sortOrder = sortOrder;
        }

        //
        // Compare the two ProcessListItems
        //
        public int Compare(object x, object y)
        {
            //
            // Check if the object is a ListViewItem
            //
            if ((!(x is ListViewItem item1)) || (!(y is ListViewItem item2))) return 0;

            //
            // Check if the tag is a ProcesslistItem
            //
            if (!(item1.Tag is ProcessListItem p1) || !(item2.Tag is ProcessListItem p2)) return 0;

            var result = 0;

            //
            // Chose the sort by the column
            //
            switch (_columnIndex)
            {
                case 0:
                {
                    var pid1 = int.Parse(p1.Id);
                    var pid2 = int.Parse(p2.Id);

                    if (pid1 > pid2)
                        result = 1;

                    if (pid1 < pid2)
                        result = -1;
                    break;
                }

                case 1:
                    result = string.Compare(p1.ProcessName, p2.ProcessName, StringComparison.Ordinal);
                    break;
            }

            //
            // Revert the sort if it's descending
            //
            if (_sortOrder == SortOrder.Descending)
            {
                result = -result;
            }

            return result;
        }
    }
}