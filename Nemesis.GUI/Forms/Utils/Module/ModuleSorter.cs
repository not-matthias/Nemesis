using System;
using System.Collections;
using System.Windows.Forms;

namespace Nemesis.Forms.Utils.Module
{
    internal class ModuleSorter : IComparer
    {
        private readonly int _columnIndex;
        private readonly SortOrder _sortOrder;

        /// <summary>
        /// Sets the specified data.
        /// </summary>
        /// <param name="columnIndex">The index of the column</param>
        /// <param name="sortOrder">The sort order (Ascending or Descending)</param>
        public ModuleSorter(int columnIndex, SortOrder sortOrder)
        {
            _columnIndex = columnIndex;
            _sortOrder = sortOrder;
        }

        /// <inheritdoc />
        /// <summary>
        /// Compares two module list items.
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <returns></returns>
        public int Compare(object x, object y)
        {
            //
            // Check if the object is a ListViewItem
            //
            if ((!(x is ListViewItem item1)) || (!(y is ListViewItem item2))) return 0;

            //
            // Check if the tag is a ProcesslistItem
            //
            if (!(item1.Tag is ModuleListItem p1) || !(item2.Tag is ModuleListItem p2)) return 0;

            var result = 0;

            //
            // Chose the sort by the column
            //
            switch (_columnIndex)
            {
                case 0:
                {
                    if (p1.BaseAddress > p2.BaseAddress)
                        result = 1;

                    if (p1.BaseAddress < p2.BaseAddress)
                        result = -1;
                    break;
                }

                case 1:
                    result = string.Compare(p1.ModuleName, p2.ModuleName, StringComparison.OrdinalIgnoreCase);
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
