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

            processListView.Columns.Add("Pid");
            processListView.Columns.Add("Name");

            //
            // Load the process list
            //
            for (int counter = 1; counter <= 50; counter++)
            {
                string[] arr = new string[2];
                ListViewItem itm;

                arr[0] = "Pid";
                arr[1] = "Name";
                itm = new ListViewItem(arr);

                processListView.Items.Add(itm);
            }

            //
            // Auto resize the columns
            //
            processListView.AutoResizeColumns(ColumnHeaderAutoResizeStyle.HeaderSize);
        }

        private void refreshButton_Click(object sender, System.EventArgs e)
        {
            NemesisConnector.StandardDump(15044, "D:/Test.exe");
        }

        private void dumpButton_Click(object sender, System.EventArgs e)
        {

        }
    }
}
