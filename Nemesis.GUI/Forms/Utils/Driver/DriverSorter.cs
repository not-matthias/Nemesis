using System;
using System.Collections;
using System.Windows.Forms;

namespace Nemesis.Forms.Utils.Driver
{
    internal class DriverSorter : IComparer
    {
        private readonly int _columnIndex;
        private readonly SortOrder _sortOrder;

        /// <summary>
        /// Sets the specified data.
        /// </summary>
        /// <param name="columnIndex">The index of the column</param>
        /// <param name="sortOrder">The sort order (Ascending or Descending)</param>
        public DriverSorter(int columnIndex, SortOrder sortOrder)
        {
            _columnIndex = columnIndex;
            _sortOrder = sortOrder;
        }

        /// <inheritdoc />
        /// <summary>
        /// Compares two driver list items.
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
            if (!(item1.Tag is DriverListItem p1) || !(item2.Tag is DriverListItem p2)) return 0;

            var result = 0;

            //
            // Chose the sort by the column
            //
            switch (_columnIndex)
            {
                // Name
                case 0:
                {
                    result = string.Compare(p1.FullPathName.Substring(p1.OffsetToFileName), p2.FullPathName.Substring(p2.OffsetToFileName),
                        StringComparison.OrdinalIgnoreCase);
                    break;
                }

                // ImageBase
                case 1:
                    if (p1.ImageBase > p2.ImageBase)
                        result = 1;

                    if (p1.ImageBase < p2.ImageBase)
                        result = -1;
                    break;

                // ImageSize
                case 2:
                    if (p1.ImageSize > p2.ImageSize)
                        result = 1;

                    if (p1.ImageSize < p2.ImageSize)
                        result = -1;
                    break;

                // FullPathName
                case 3:
                    result = string.Compare(p1.FullPathName, p2.FullPathName, StringComparison.OrdinalIgnoreCase);
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