using MetroFramework.Forms;

namespace Nemesis.Forms
{
    public sealed partial class processInformation : MetroForm
    {
        public processInformation()
        {
            InitializeComponent();
        }

        public processInformation(string processName)
        {
            Text = processName;

            InitializeComponent();
        }
    }
}