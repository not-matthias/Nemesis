using System;
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
            // Set the metro color
            //
            Style = MetroFramework.MetroColorStyle.Default;
            //Default
            //Black
            //White
            //Silver
            //Blue
            //Green
            //Lime
            //Teal
            //Orange
            //Brown
            //Pink
            //Magenta
            //Purple
            //Red
            //Yellow

            //
            // Set the process list
            //
            processListView.LoadProcesses();
        }

        //
        // Refreshes the process list
        //
        private void RefreshButton_Click(object sender, EventArgs e) => processListView.LoadProcesses();

        //
        // Dumps the process
        //
        private void DumpButton_Click(object sender, EventArgs e)
        {
            if (processListView.SelectedItems.Count > 0)
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
                string fileName = $@"{System.IO.Path.GetDirectoryName(Application.ExecutablePath)}/{processName}_dump.exe";


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

                if (status)
                {
                    MessageBox.Show("Successfully dumped the process.");

                    // TODO: Ask if add path to config?
                }
                else
                {
                    MessageBox.Show("Failed to dump the process.");
                }
            }
        }
    }
}
