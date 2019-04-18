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
            moduleListView.LoadModules(_processId);

            //
            // Memory List View
            //
            memoryListView.LoadMemory(_processId);
        }
    }
}