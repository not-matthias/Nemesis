using System;
using System.IO;
using System.Windows.Forms;
using MetroFramework.Forms;
using Nemesis.Forms.Utils.Memory;
using Nemesis.Forms.Utils.Module;
using Nemesis.Utils;

namespace Nemesis.Forms
{
    public sealed partial class ProcessInformation : MetroForm
    {
        private readonly int _processId;

        /// <summary>
        /// Loads the data of the specified process.
        /// </summary>
        /// <param name="processId">The id of the process</param>
        public ProcessInformation(int processId)
        {
            InitializeComponent();

            _processId = processId;

            //
            // Set styles
            //
            components.SetStyle(this);

            //
            // Load modules and memory (can take some time)
            //
            Cursor.Current = Cursors.WaitCursor;
            LoadData();
            Cursor.Current = Cursors.Default;
        }

        /// <summary>
        /// Loads the modules and memory of the process.
        /// </summary>
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
            if (memoryListView.LoadMemory(_processId))
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

        /// <summary>
        /// Shows the context menu at the cursor position.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ModuleListView_MouseUp(object sender, MouseEventArgs e)
        {
            if (e.Button != MouseButtons.Right) return;

            //
            // Check if intersecting
            //
            if ((moduleListView.FocusedItem == null || !moduleListView.FocusedItem.Bounds.Contains(e.Location)))
                return;

            moduleContextMenu.Show(Cursor.Position);
        }

        /// <summary>
        /// Shows the context menu at the cursor position.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void MemoryListView_MouseUp(object sender, MouseEventArgs e)
        {
            if (e.Button != MouseButtons.Right) return;

            //
            // Check if intersecting
            //
            if (memoryListView.FocusedItem == null || !memoryListView.FocusedItem.Bounds.Contains(e.Location))
                return;

            memoryContextMenu.Show(Cursor.Position);
        }

        /// <summary>
        /// Dumps the selected module when context menu item gets clicked.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void DumpToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (moduleListView.SelectedItems.Count == 0) return;
            if (moduleListView.SelectedItems.Count == 0) return;
            if (!(moduleListView.SelectedItems[0].Tag is ModuleListItem module)) return;

            DumpModule(module);
        }

        /// <summary>
        /// Dumps the selected memory when context menu item gets clicked.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void MemoryContextMenu_Click(object sender, EventArgs e)
        {
            if (memoryListView.SelectedItems.Count == 0) return;
            if (memoryListView.SelectedItems.Count == 0) return;
            if (!(memoryListView.SelectedItems[0].Tag is MemoryListItem memory)) return;

            DumpMemory(memory);
        }

        /// <summary>
        /// Dumps the specified module.
        /// </summary>
        /// <param name="module">The module of a process</param>
        private void DumpModule(ModuleListItem module)
        {
            //
            // Get the destination path
            //
            string path;
            var saveFile = new SaveFileDialog
            {
                FileName = $@"{Path.GetFileName(module.ModuleName)}",
                Filter = @"Executable File (.dll)|*.dll"
            };

            //
            // Show the dialog
            //
            if (saveFile.ShowDialog() == DialogResult.OK)
            {
                path = saveFile.FileName;
            }
            else
            {
                return;
            }

            //
            // Dump module
            //
            if (!NemesisApi.DumpModule(_processId, (IntPtr) module.BaseAddress, path))
            {
                MessageBox.Show("Failed to dump module.");
            }
            else
            {
                MessageBox.Show("Successfully dumped the module.");
            }
        }

        /// <summary>
        /// Dumps the specified memory.
        /// </summary>
        /// <param name="memory">The memory of a process.</param>
        private void DumpMemory(MemoryListItem memory)
        {
            //
            // Get the destination path
            //
            string path;
            var saveFile = new SaveFileDialog
            {
                FileName = $@"MEM_{memory.BaseAddress:X8}_{memory.RegionSize}.bin",
                Filter = @"Executable File (.bin)|*.bin"
            };

            //
            // Show the dialog
            //
            if (saveFile.ShowDialog() == DialogResult.OK)
            {
                path = saveFile.FileName;
            }
            else
            {
                return;
            }

            //
            // Dump module
            //
            if (!NemesisApi.DumpMemory(_processId, (IntPtr) memory.BaseAddress, (uint) memory.RegionSize, path))
            {
                MessageBox.Show("Failed to dump module.");
            }
            else
            {
                MessageBox.Show("Successfully dumped the module.");
            }
        }
    }
}