using System.Collections.Generic;
using MetroFramework.Forms;
using Nemesis.Utils;

namespace Nemesis.Forms
{
    public sealed partial class ProcessInformation : MetroForm
    {
        private int _processId;

        private List<Module> _modules;
        private List<Memory> _memory;

        public ProcessInformation(int processId)
        {
            InitializeComponent();

            _processId = processId;

            _modules = NemesisApi.GetModuleList(processId);
            _memory = NemesisApi.GetMemoryList(processId);

            //
            // Modules List View
            //
            moduleListView.LoadModules(_modules);

            //
            // Memory List View
            // 
        }
    }
}