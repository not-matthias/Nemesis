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
            this.metroTabPage1 = new MetroFramework.Controls.MetroTabPage();
            this.tabControl = new MetroFramework.Controls.MetroTabControl();
            this.moduleListView = new Nemesis.Forms.Utils.Module.ModuleListView();
            this.memoryListView = new Nemesis.Forms.Utils.Memory.MemoryListView();
            this.moduleLabel = new MetroFramework.Controls.MetroLabel();
            this.memoryLabel = new MetroFramework.Controls.MetroLabel();
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
            this.metroTabPage2.Size = new System.Drawing.Size(476, 246);
            this.metroTabPage2.TabIndex = 1;
            this.metroTabPage2.Text = "Memory";
            this.metroTabPage2.VerticalScrollbarBarColor = true;
            this.metroTabPage2.VerticalScrollbarHighlightOnWheel = false;
            this.metroTabPage2.VerticalScrollbarSize = 10;
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
            this.metroTabPage1.Size = new System.Drawing.Size(476, 246);
            this.metroTabPage1.TabIndex = 0;
            this.metroTabPage1.Text = "Modules";
            this.metroTabPage1.VerticalScrollbarBarColor = true;
            this.metroTabPage1.VerticalScrollbarHighlightOnWheel = false;
            this.metroTabPage1.VerticalScrollbarSize = 10;
            // 
            // tabControl
            // 
            this.tabControl.Controls.Add(this.metroTabPage1);
            this.tabControl.Controls.Add(this.metroTabPage2);
            this.tabControl.ItemSize = new System.Drawing.Size(62, 34);
            this.tabControl.Location = new System.Drawing.Point(23, 63);
            this.tabControl.Name = "tabControl";
            this.tabControl.SelectedIndex = 1;
            this.tabControl.Size = new System.Drawing.Size(484, 288);
            this.tabControl.SizeMode = System.Windows.Forms.TabSizeMode.FillToRight;
            this.tabControl.TabIndex = 0;
            this.tabControl.UseSelectable = true;
            // 
            // moduleListView
            // 
            this.moduleListView.FullRowSelect = true;
            this.moduleListView.HideSelection = false;
            this.moduleListView.Location = new System.Drawing.Point(3, 12);
            this.moduleListView.MultiSelect = false;
            this.moduleListView.Name = "moduleListView";
            this.moduleListView.Size = new System.Drawing.Size(470, 232);
            this.moduleListView.Sorting = System.Windows.Forms.SortOrder.Ascending;
            this.moduleListView.TabIndex = 0;
            this.moduleListView.Text = "ModuleListView";
            this.moduleListView.UseCompatibleStateImageBehavior = false;
            this.moduleListView.View = System.Windows.Forms.View.Details;
            // 
            // memoryListView
            // 
            this.memoryListView.FullRowSelect = true;
            this.memoryListView.HideSelection = false;
            this.memoryListView.Location = new System.Drawing.Point(3, 12);
            this.memoryListView.Name = "memoryListView";
            this.memoryListView.Size = new System.Drawing.Size(470, 231);
            this.memoryListView.Sorting = System.Windows.Forms.SortOrder.Ascending;
            this.memoryListView.TabIndex = 2;
            this.memoryListView.Text = "MemoryListView";
            this.memoryListView.UseCompatibleStateImageBehavior = false;
            this.memoryListView.View = System.Windows.Forms.View.Details;
            // 
            // moduleLabel
            // 
            this.moduleLabel.ForeColor = System.Drawing.SystemColors.ControlText;
            this.moduleLabel.Location = new System.Drawing.Point(13, 111);
            this.moduleLabel.Name = "moduleLabel";
            this.moduleLabel.Size = new System.Drawing.Size(448, 23);
            this.moduleLabel.TabIndex = 2;
            this.moduleLabel.Text = "Could not load module list.";
            this.moduleLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // memoryLabel
            // 
            this.memoryLabel.ForeColor = System.Drawing.SystemColors.ControlText;
            this.memoryLabel.Location = new System.Drawing.Point(14, 112);
            this.memoryLabel.Name = "memoryLabel";
            this.memoryLabel.Size = new System.Drawing.Size(448, 23);
            this.memoryLabel.TabIndex = 3;
            this.memoryLabel.Text = "Could not load memory list.";
            this.memoryLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // ProcessInformation
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(530, 374);
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
    }
}