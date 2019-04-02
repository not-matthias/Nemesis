using MetroFramework.Forms;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Nemesis.Forms
{
    public partial class ProcessInfo : MetroForm
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
