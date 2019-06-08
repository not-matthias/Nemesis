using Nemesis.Forms.Utils.Memory;
using Nemesis.Forms.Utils.Module;

namespace Nemesis.Forms
{
    sealed partial class ProcessInformation
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.metroTabPage2 = new MetroFramework.Controls.MetroTabPage();
            this.memoryLabel = new MetroFramework.Controls.MetroLabel();
            this.memoryListView = new Nemesis.Forms.Utils.Memory.MemoryListView();
            this.metroTabPage1 = new MetroFramework.Controls.MetroTabPage();
            this.moduleLabel = new MetroFramework.Controls.MetroLabel();
            this.moduleListView = new Nemesis.Forms.Utils.Module.ModuleListView();
            this.columnBase = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnName = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.tabControl = new MetroFramework.Controls.MetroTabControl();
            this.refreshButton = new MetroFramework.Controls.MetroButton();
            this.dumpButton = new MetroFramework.Controls.MetroButton();
            this.columnSize = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnPath = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.metroTabPage2.SuspendLayout();
            this.metroTabPage1.SuspendLayout();
            this.tabControl.SuspendLayout();
            this.SuspendLayout();
            // 
            // metroTabPage2
            // 
            this.metroTabPage2.Controls.Add(this.memoryLabel);
            this.metroTabPage2.Controls.Add(this.memoryListView);
            this.metroTabPage2.HorizontalScrollbarBarColor = true;
            this.metroTabPage2.HorizontalScrollbarHighlightOnWheel = false;
            this.metroTabPage2.HorizontalScrollbarSize = 10;
            this.metroTabPage2.Location = new System.Drawing.Point(4, 38);
            this.metroTabPage2.Name = "metroTabPage2";
            this.metroTabPage2.Size = new System.Drawing.Size(579, 220);
            this.metroTabPage2.TabIndex = 1;
            this.metroTabPage2.Text = "Memory";
            this.metroTabPage2.VerticalScrollbarBarColor = true;
            this.metroTabPage2.VerticalScrollbarHighlightOnWheel = false;
            this.metroTabPage2.VerticalScrollbarSize = 10;
            // 
            // memoryLabel
            // 
            this.memoryLabel.ForeColor = System.Drawing.SystemColors.ControlText;
            this.memoryLabel.Location = new System.Drawing.Point(17, 98);
            this.memoryLabel.Name = "memoryLabel";
            this.memoryLabel.Size = new System.Drawing.Size(548, 23);
            this.memoryLabel.TabIndex = 3;
            this.memoryLabel.Text = "Could not load memory list.";
            this.memoryLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // memoryListView
            // 
            this.memoryListView.FullRowSelect = true;
            this.memoryListView.HideSelection = false;
            this.memoryListView.Location = new System.Drawing.Point(3, 12);
            this.memoryListView.Name = "memoryListView";
            this.memoryListView.Size = new System.Drawing.Size(573, 197);
            this.memoryListView.Sorting = System.Windows.Forms.SortOrder.Ascending;
            this.memoryListView.TabIndex = 2;
            this.memoryListView.Text = "MemoryListView";
            this.memoryListView.UseCompatibleStateImageBehavior = false;
            this.memoryListView.View = System.Windows.Forms.View.Details;
            // 
            // metroTabPage1
            // 
            this.metroTabPage1.Controls.Add(this.moduleLabel);
            this.metroTabPage1.Controls.Add(this.moduleListView);
            this.metroTabPage1.HorizontalScrollbarBarColor = true;
            this.metroTabPage1.HorizontalScrollbarHighlightOnWheel = false;
            this.metroTabPage1.HorizontalScrollbarSize = 10;
            this.metroTabPage1.Location = new System.Drawing.Point(4, 38);
            this.metroTabPage1.Name = "metroTabPage1";
            this.metroTabPage1.Size = new System.Drawing.Size(579, 220);
            this.metroTabPage1.TabIndex = 0;
            this.metroTabPage1.Text = "Modules";
            this.metroTabPage1.VerticalScrollbarBarColor = true;
            this.metroTabPage1.VerticalScrollbarHighlightOnWheel = false;
            this.metroTabPage1.VerticalScrollbarSize = 10;
            // 
            // moduleLabel
            // 
            this.moduleLabel.ForeColor = System.Drawing.SystemColors.ControlText;
            this.moduleLabel.Location = new System.Drawing.Point(17, 98);
            this.moduleLabel.Name = "moduleLabel";
            this.moduleLabel.Size = new System.Drawing.Size(550, 23);
            this.moduleLabel.TabIndex = 2;
            this.moduleLabel.Text = "Could not load module list.";
            this.moduleLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // moduleListView
            // 
            this.moduleListView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnName,
            this.columnBase,
            this.columnSize,
            this.columnPath});
            this.moduleListView.FullRowSelect = true;
            this.moduleListView.HideSelection = false;
            this.moduleListView.Location = new System.Drawing.Point(3, 12);
            this.moduleListView.MultiSelect = false;
            this.moduleListView.Name = "moduleListView";
            this.moduleListView.Size = new System.Drawing.Size(573, 197);
            this.moduleListView.Sorting = System.Windows.Forms.SortOrder.Ascending;
            this.moduleListView.TabIndex = 0;
            this.moduleListView.Text = "ModuleListView";
            this.moduleListView.UseCompatibleStateImageBehavior = false;
            this.moduleListView.View = System.Windows.Forms.View.Details;
            // 
            // columnBase
            // 
            this.columnBase.Text = "ImageBase";
            this.columnBase.Width = 90;
            // 
            // columnName
            // 
            this.columnName.Text = "Name";
            this.columnName.Width = 125;
            // 
            // tabControl
            // 
            this.tabControl.Controls.Add(this.metroTabPage1);
            this.tabControl.Controls.Add(this.metroTabPage2);
            this.tabControl.ItemSize = new System.Drawing.Size(62, 34);
            this.tabControl.Location = new System.Drawing.Point(23, 63);
            this.tabControl.Name = "tabControl";
            this.tabControl.SelectedIndex = 0;
            this.tabControl.Size = new System.Drawing.Size(587, 262);
            this.tabControl.SizeMode = System.Windows.Forms.TabSizeMode.FillToRight;
            this.tabControl.TabIndex = 0;
            this.tabControl.UseSelectable = true;
            // 
            // refreshButton
            // 
            this.refreshButton.Location = new System.Drawing.Point(450, 316);
            this.refreshButton.Name = "refreshButton";
            this.refreshButton.Size = new System.Drawing.Size(75, 23);
            this.refreshButton.TabIndex = 4;
            this.refreshButton.Text = "Refresh";
            this.refreshButton.UseSelectable = true;
            this.refreshButton.Click += new System.EventHandler(this.RefreshButton_Click);
            // 
            // dumpButton
            // 
            this.dumpButton.Location = new System.Drawing.Point(531, 316);
            this.dumpButton.Name = "dumpButton";
            this.dumpButton.Size = new System.Drawing.Size(75, 23);
            this.dumpButton.TabIndex = 3;
            this.dumpButton.Text = "Dump";
            this.dumpButton.UseSelectable = true;
            this.dumpButton.Click += new System.EventHandler(this.DumpButton_Click);
            // 
            // columnSize
            // 
            this.columnSize.Text = "ImageSize";
            this.columnSize.Width = 80;
            // 
            // columnPath
            // 
            this.columnPath.Text = "Path";
            this.columnPath.Width = 225;
            // 
            // ProcessInformation
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(633, 355);
            this.Controls.Add(this.refreshButton);
            this.Controls.Add(this.dumpButton);
            this.Controls.Add(this.tabControl);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "ProcessInformation";
            this.Resizable = false;
            this.ShadowType = MetroFramework.Forms.MetroFormShadowType.AeroShadow;
            this.ShowInTaskbar = false;
            this.Text = "Process Information";
            this.metroTabPage2.ResumeLayout(false);
            this.metroTabPage1.ResumeLayout(false);
            this.tabControl.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private MetroFramework.Controls.MetroTabPage metroTabPage2;
        private MetroFramework.Controls.MetroTabPage metroTabPage1;
        private MetroFramework.Controls.MetroTabControl tabControl;
        
        private ModuleListView moduleListView;
        private MemoryListView memoryListView;
        private MetroFramework.Controls.MetroLabel moduleLabel;
        private MetroFramework.Controls.MetroLabel memoryLabel;
        private System.Windows.Forms.ColumnHeader columnBase;
        private System.Windows.Forms.ColumnHeader columnName;
        private MetroFramework.Controls.MetroButton refreshButton;
        private MetroFramework.Controls.MetroButton dumpButton;
        private System.Windows.Forms.ColumnHeader columnSize;
        private System.Windows.Forms.ColumnHeader columnPath;
    }
}