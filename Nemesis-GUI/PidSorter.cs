using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Nemesis
{
    class PidSorter : IComparer
    {
        public int Column = 0;
        public System.Windows.Forms.SortOrder Order = SortOrder.Ascending;

        public int Compare(object x, object y)
        {
            if (!(x is ListViewItem))
                return (0);
            if (!(y is ListViewItem))
                return (0);

            ListViewItem listViewItem1 = (ListViewItem)x;
            ListViewItem listViewItem2 = (ListViewItem)y;

            int pid1 = int.Parse(listViewItem1.SubItems[Column].Text);
            int pid2 = int.Parse(listViewItem2.SubItems[Column].Text);

            if (Order == SortOrder.Ascending)
            {
                if (pid1 > pid2)
                    return 1;

                if (pid1 < pid2)
                    return -1;

                return 0;
            }
            else
            {
                if (pid1 < pid2)
                    return 1;

                if (pid1 > pid2)
                    return -1;

                return 0;
            }
        }
    }
}
