using System.Windows.Forms;

namespace Nemesis.Forms.Utils.Driver
{
    internal class DriverListItem
    {
        public long ImageBase { get; }
        public int ImageSize { get; }
        public ushort OffsetToFileName { get; }
        public string FullPathName { get; }

        public DriverListItem(long imageBase, int imageSize, ushort offsetToFileName, string fullPathName)
        {
            ImageBase = imageBase;
            ImageSize = imageSize;
            OffsetToFileName = offsetToFileName;
            FullPathName = fullPathName;
        }

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
