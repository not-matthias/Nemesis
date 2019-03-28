using System;
using System.Diagnostics;
using System.Windows.Forms;

namespace Nemesis
{
    public partial class NemesisForm : MetroFramework.Forms.MetroForm
    {
        // 
        // Sets the process list
        // 
        public NemesisForm()
        {
            InitializeComponent();

            //
            // Set some properties
            //
            processListView.View = View.Details;
            processListView.GridLines = false;
            processListView.FullRowSelect = true;

            processListView.Columns.Add("Pid");
            processListView.Columns.Add("ProcessName");

            //
            // Sort it ascending by pid
            //
            processListView.Sorting = SortOrder.Ascending;
            processListView.ListViewItemSorter = new PidSorter();

            //
            // Set the process list
            //
            SetProcessList();
        }

        //
        // Refreshes the process list
        //
        private void RefreshButton_Click(object sender, System.EventArgs e)
        {
            SetProcessList();
        }

        //
        // Dumps the process
        //
        private void DumpButton_Click(object sender, EventArgs e)
        {
            if(processListView.SelectedItems.Count > 0)
            { 
                //
                // Get the selected item
                //
                ListViewItem selectedItem = processListView.SelectedItems[0];

                //
                // Get the pid
                //
                int pid = int.Parse(selectedItem.SubItems[0].Text);
                string processName = selectedItem.SubItems[1].Text;

                //
                // Create the dump file name
                //
                string fileName = $@"{System.IO.Path.GetDirectoryName(Application.ExecutablePath)}/{processName}_dump.exe" ;

                //
                // Open the dialog
                //
                SaveFileDialog saveFile = new SaveFileDialog();

                // 
                // Set the default name
                // 
                saveFile.FileName = $@"{processName}_dump.exe";

                // 
                // Set the filters
                // 
                saveFile.Filter = "Executable File (.exe)|*.exe";

                //
                // Show the dialog
                //
                if (saveFile.ShowDialog() == DialogResult.OK)
                {
                    MessageBox.Show(saveFile.FileName);
                    //string fileName = savefile.FileName;
                }


                //
                // Dump it
                //
                bool status = NemesisApi.StandardDump(pid, fileName);

                if(status)
                {
                    MessageBox.Show("Successfully dumped the process.");
                }
                else
                {
                    MessageBox.Show("Failed to dump the process.");
                }
            }
        }

        //
        // Sets the process list in the ListView
        //
        private void SetProcessList()
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
                    // 
                    // Create strings
                    // 
                    string id = process.Id.ToString();
                    string processName = process.ProcessName;

                    //
                    // Create a ListViewItem
                    //
                    ListViewItem listViewItem = new ListViewItem(id);
                    listViewItem.SubItems.Add(processName);

                    //
                    // Add it to the ListView
                    //
                    processListView.Items.Add(listViewItem);
                }
                catch (Exception)
                {
                    
                }
            }

            //
            // Auto resize the columns
            //
            processListView.AutoResizeColumns(ColumnHeaderAutoResizeStyle.HeaderSize);
        }
    }
}
