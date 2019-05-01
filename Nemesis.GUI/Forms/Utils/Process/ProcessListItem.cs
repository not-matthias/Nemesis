using System.Windows.Forms;

namespace Nemesis.Forms.Utils.Process
{
    internal class ProcessListItem
    {
        public string Id { get; }
        public string ProcessName { get; }

        /// <summary>
        /// Sets the specified data.
        /// </summary>
        /// <param name="id">The id of the process</param>
        /// <param name="processName">The name of the process</param>
        public ProcessListItem(string id, string processName)
        {
            Id = id;
            ProcessName = processName;
        }

        /// <summary>
        /// Returns the list view item for the process list.
        /// </summary>
        /// <returns>ListViewItem</returns>
        public ListViewItem GetListViewItem()
        {
            var listViewItem = new ListViewItem(Id);
            listViewItem.SubItems.Add(ProcessName);
            listViewItem.Tag = this;

            return listViewItem;
        }
    }
}