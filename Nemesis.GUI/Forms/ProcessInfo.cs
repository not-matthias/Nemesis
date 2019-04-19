using System.Windows.Forms;
using MetroFramework.Forms;

namespace Nemesis.Forms
{
    public sealed partial class ProcessInformation : MetroForm
    {
        private readonly int _processId;

        public ProcessInformation(int processId)
        {
            InitializeComponent();

            _processId = processId;

            //
            // Load modules and memory (can take some time)
            //
            Cursor.Current = Cursors.WaitCursor;
            LoadData();
            Cursor.Current = Cursors.Default;
        }

        private void LoadData()
        {
            //
            // Module List View
            //
            if (moduleListView.LoadModules(_processId))
            {
                moduleListView.Show();
                moduleLabel.Hide();
            }
            else
            {
                moduleListView.Hide();
                moduleLabel.Show();
            }

            //
            // Memory List View
            //
            if(memoryListView.LoadMemory(_processId))
            {
                memoryListView.Show();
                memoryLabel.Hide();
            }
            else
            {
                memoryListView.Hide();
                memoryLabel.Show();
            }
        }
    }
}