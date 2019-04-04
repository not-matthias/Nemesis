using MetroFramework.Forms;

namespace Nemesis.Forms
{
    public sealed partial class ProcessInfo : MetroForm
    {
        public ProcessInfo()
        {
            InitializeComponent();
        }

        public ProcessInfo(string processName)
        {
            Text = processName;

            InitializeComponent();
        }
    }
}