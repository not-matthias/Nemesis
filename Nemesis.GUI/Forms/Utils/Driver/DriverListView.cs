using System.Windows.Forms;
using Nemesis.Utils;

namespace Nemesis.Forms.Utils.Driver
{
    public sealed partial class DriverListView : ListView
    {
        private int _sortColumnIndex;

        public DriverListView()
        {
            DoubleBuffered = true;
            Sorting = SortOrder.Ascending;
        }

        public bool LoadDrivers()
        {
            var drivers = NemesisApi.GetDriverList();

            //
            // Remove all previous drivers
            //
            Items.Clear();

            //
            // Loop through all drivers
            //
            foreach (var item in drivers)
            {
                //
                // Create a new DriverListItem
                //
                var driverListItem = new DriverListItem(item.ImageBase, item.ImageSize, item.OffsetToFileName, item.FullPathName);

                //
                // Add it to the ListView
                //
                Items.Add(driverListItem.GetListViewItem());
            }

            //
            // Auto resize the columns
            //
            AutoResizeColumns(ColumnHeaderAutoResizeStyle.None);

            //
            // Sort the list
            //
            ListViewItemSorter = new DriverSorter(_sortColumnIndex, Sorting);

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
            ListViewItemSorter = new DriverSorter(e.Column, Sorting);
        }
    }
}
