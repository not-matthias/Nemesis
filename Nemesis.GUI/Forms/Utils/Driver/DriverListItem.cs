using System.Windows.Forms;

namespace Nemesis.Forms.Utils.Driver
{
    internal class DriverListItem
    {
        public long ImageBase { get; }
        public int ImageSize { get; }
        public ushort OffsetToFileName { get; }
        public string FullPathName { get; }

        /// <summary>
        /// Sets the specified data.
        /// </summary>
        /// <param name="imageBase">The base address of the driver</param>
        /// <param name="imageSize">The size of the driver memory</param>
        /// <param name="offsetToFileName">The offset to the filename</param>
        /// <param name="fullPathName">The full path name</param>
        public DriverListItem(long imageBase, int imageSize, ushort offsetToFileName, string fullPathName)
        {
            ImageBase = imageBase;
            ImageSize = imageSize;
            OffsetToFileName = offsetToFileName;
            FullPathName = fullPathName;
        }

        /// <summary>
        /// Returns the list view item for the driver list.
        /// </summary>
        /// <returns>ListViewItem</returns>
        public ListViewItem GetListViewItem()
        {
            var listViewItem = new ListViewItem(FullPathName.Substring(OffsetToFileName));
            listViewItem.SubItems.Add(ImageBase.ToString("X8"));
            listViewItem.SubItems.Add(ImageSize.ToString("X8"));
            listViewItem.SubItems.Add(FullPathName);
            listViewItem.Tag = this;

            return listViewItem;
        }
    }
}
