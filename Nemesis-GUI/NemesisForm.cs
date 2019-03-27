using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Windows.Forms;

namespace Nemesis
{
    public partial class NemesisForm : MetroFramework.Forms.MetroForm
    {
        public NemesisForm()
        {
            InitializeComponent();

            //
            // Set some properties
            //
            processListView.View = View.Details;
            processListView.GridLines = false;
            processListView.FullRowSelect = true;

            processListView.Columns.Add("Pid", 500);
            processListView.Columns.Add("Name");

            // FIXME: Implement proper sorting
            processListView.Sorting = SortOrder.Descending;

            //
            // Set the process list
            //
            setProcessList();
        }

        private void refreshButton_Click(object sender, System.EventArgs e)
        {
            setProcessList();
        }

        private void dumpButton_Click(object sender, System.EventArgs e)
        {

        }

        private void setProcessList()
        {
            Process[] processlist = Process.GetProcesses();

            //
            // Clear the original list
            //
            processListView.Items.Clear();

            //
            // Load the process list
            //
            foreach (Process process in processlist)
            {
                try
                {
                    string Id = process.Id.ToString();
                    string ModuleName = process.MainModule.ModuleName;

                    ListViewItem listViewItem = new ListViewItem(Id);
                    listViewItem.SubItems.Add(ModuleName);

                    processListView.Items.Add(listViewItem);
                }
                catch (Exception)
                {

                }
            }

            //
            // Sort it per id
            //
            // processInfoList.Sort(delegate (ProcessInfo processInfo1, ProcessInfo processInfo2)
            //{
            //    if (processInfo1.Id > processInfo2.Id)
            //    {
            //        return 1;
            //    }

            //    if (processInfo1.Id < processInfo2.Id)
            //    {
            //        return -1;
            //    }

            //    return 0;
            //});

            //
            // Auto resize the columns
            //
            processListView.AutoResizeColumns(ColumnHeaderAutoResizeStyle.HeaderSize);
        }
    }
}
