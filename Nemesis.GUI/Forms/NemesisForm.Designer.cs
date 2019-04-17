using Nemesis.Forms.Utils;
using Nemesis.Forms.Utils.Process;

namespace Nemesis.Forms
{
    partial class NemesisForm
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
            this.dumpButton = new MetroFramework.Controls.MetroButton();
            this.refreshButton = new MetroFramework.Controls.MetroButton();
            this.settingsButton = new MetroFramework.Controls.MetroButton();
            this.aboutButton = new MetroFramework.Controls.MetroButton();
            this.processListView = new Nemesis.Forms.Utils.Process.ProcessListView();
            this.SuspendLayout();
            // 
            // dumpButton
            // 
            this.dumpButton.Location = new System.Drawing.Point(702, 403);
            this.dumpButton.Name = "dumpButton";
            this.dumpButton.Size = new System.Drawing.Size(75, 23);
            this.dumpButton.TabIndex = 0;
            this.dumpButton.Text = "Dump";
            this.dumpButton.UseSelectable = true;
            this.dumpButton.Click += new System.EventHandler(this.DumpButton_Click);
            // 
            // refreshButton
            // 
            this.refreshButton.Location = new System.Drawing.Point(621, 403);
            this.refreshButton.Name = "refreshButton";
            this.refreshButton.Size = new System.Drawing.Size(75, 23);
            this.refreshButton.TabIndex = 2;
            this.refreshButton.Text = "Refresh";
            this.refreshButton.UseSelectable = true;
            this.refreshButton.Click += new System.EventHandler(this.RefreshButton_Click);
            // 
            // settingsButton
            // 
            this.settingsButton.Location = new System.Drawing.Point(104, 403);
            this.settingsButton.Name = "settingsButton";
            this.settingsButton.Size = new System.Drawing.Size(75, 23);
            this.settingsButton.TabIndex = 3;
            this.settingsButton.Text = "Settings";
            this.settingsButton.UseSelectable = true;
            this.settingsButton.Click += new System.EventHandler(this.SettingsButton_Click);
            // 
            // aboutButton
            // 
            this.aboutButton.Location = new System.Drawing.Point(23, 403);
            this.aboutButton.Name = "aboutButton";
            this.aboutButton.Size = new System.Drawing.Size(75, 23);
            this.aboutButton.TabIndex = 4;
            this.aboutButton.Text = "About";
            this.aboutButton.UseSelectable = true;
            this.aboutButton.Click += new System.EventHandler(this.AboutButton_Click);
            // 
            // processListView
            // 
            this.processListView.Alignment = System.Windows.Forms.ListViewAlignment.Default;
            this.processListView.FullRowSelect = true;
            this.processListView.HideSelection = false;
            this.processListView.Location = new System.Drawing.Point(23, 79);
            this.processListView.MultiSelect = false;
            this.processListView.Name = "processListView";
            this.processListView.Size = new System.Drawing.Size(754, 318);
            this.processListView.Sorting = System.Windows.Forms.SortOrder.Ascending;
            this.processListView.TabIndex = 0;
            this.processListView.UseCompatibleStateImageBehavior = false;
            this.processListView.View = System.Windows.Forms.View.Details;
            this.processListView.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.ProcessListView_MouseDoubleClick);
            // 
            // NemesisForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.aboutButton);
            this.Controls.Add(this.settingsButton);
            this.Controls.Add(this.processListView);
            this.Controls.Add(this.refreshButton);
            this.Controls.Add(this.dumpButton);
            this.MaximizeBox = false;
            this.Name = "NemesisForm";
            this.Resizable = false;
            this.ShadowType = MetroFramework.Forms.MetroFormShadowType.AeroShadow;
            this.Text = "Nemesis";
            this.ResumeLayout(false);

        }

        #endregion

        private MetroFramework.Controls.MetroButton dumpButton;
        private MetroFramework.Controls.MetroButton refreshButton;
        private ProcessListView processListView;
        private MetroFramework.Controls.MetroButton settingsButton;
        private MetroFramework.Controls.MetroButton aboutButton;
    }
}

