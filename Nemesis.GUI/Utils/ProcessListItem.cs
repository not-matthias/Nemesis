using System.Windows.Forms;

namespace Nemesis.Utils
{
    internal class ProcessListItem
    {
        public string Id { get; }
        public string ProcessName { get; }

        public ProcessListItem(string id, string processName)
        {
            Id = id;
            ProcessName = processName;
        }

        //
        // Creates a new ListViewItem from the id and name
        //
        public ListViewItem GetListViewItem()
        {
            var listViewItem = new ListViewItem(Id);
            listViewItem.SubItems.Add(ProcessName);
            listViewItem.Tag = this;

            return listViewItem;
        }
    }
}