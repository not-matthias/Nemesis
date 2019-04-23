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
            this.tabControl = new MetroFramework.Controls.MetroTabControl();
            this.processesTabPage = new MetroFramework.Controls.MetroTabPage();
            this.processListView = new Nemesis.Forms.Utils.Process.ProcessListView();
            this.metroTabPage2 = new MetroFramework.Controls.MetroTabPage();
            this.driverListView = new Nemesis.Forms.Utils.Driver.DriverListView();
            this.columnName = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnBase = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnSize = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnPath = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.tabControl.SuspendLayout();
            this.processesTabPage.SuspendLayout();
            this.metroTabPage2.SuspendLayout();
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
            // tabControl
            // 
            this.tabControl.Controls.Add(this.processesTabPage);
            this.tabControl.Controls.Add(this.metroTabPage2);
            this.tabControl.Location = new System.Drawing.Point(23, 63);
            this.tabControl.Name = "tabControl";
            this.tabControl.SelectedIndex = 0;
            this.tabControl.Size = new System.Drawing.Size(754, 334);
            this.tabControl.TabIndex = 6;
            this.tabControl.UseSelectable = true;
            // 
            // processesTabPage
            // 
            this.processesTabPage.Controls.Add(this.processListView);
            this.processesTabPage.HorizontalScrollbarBarColor = true;
            this.processesTabPage.HorizontalScrollbarHighlightOnWheel = false;
            this.processesTabPage.HorizontalScrollbarSize = 10;
            this.processesTabPage.Location = new System.Drawing.Point(4, 38);
            this.processesTabPage.Name = "processesTabPage";
            this.processesTabPage.Size = new System.Drawing.Size(746, 292);
            this.processesTabPage.TabIndex = 0;
            this.processesTabPage.Text = "Processes";
            this.processesTabPage.VerticalScrollbarBarColor = true;
            this.processesTabPage.VerticalScrollbarHighlightOnWheel = false;
            this.processesTabPage.VerticalScrollbarSize = 10;
            // 
            // processListView
            // 
            this.processListView.Alignment = System.Windows.Forms.ListViewAlignment.Default;
            this.processListView.FullRowSelect = true;
            this.processListView.HideSelection = false;
            this.processListView.Location = new System.Drawing.Point(3, 12);
            this.processListView.MultiSelect = false;
            this.processListView.Name = "processListView";
            this.processListView.Size = new System.Drawing.Size(740, 277);
            this.processListView.Sorting = System.Windows.Forms.SortOrder.Ascending;
            this.processListView.TabIndex = 0;
            this.processListView.UseCompatibleStateImageBehavior = false;
            this.processListView.View = System.Windows.Forms.View.Details;
            this.processListView.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.ProcessListView_MouseDoubleClick);
            // 
            // metroTabPage2
            // 
            this.metroTabPage2.Controls.Add(this.driverListView);
            this.metroTabPage2.HorizontalScrollbarBarColor = true;
            this.metroTabPage2.HorizontalScrollbarHighlightOnWheel = false;
            this.metroTabPage2.HorizontalScrollbarSize = 10;
            this.metroTabPage2.Location = new System.Drawing.Point(4, 38);
            this.metroTabPage2.Name = "metroTabPage2";
            this.metroTabPage2.Size = new System.Drawing.Size(746, 292);
            this.metroTabPage2.TabIndex = 1;
            this.metroTabPage2.Text = "Drivers";
            this.metroTabPage2.VerticalScrollbarBarColor = true;
            this.metroTabPage2.VerticalScrollbarHighlightOnWheel = false;
            this.metroTabPage2.VerticalScrollbarSize = 10;
            // 
            // driverListView
            // 
            this.driverListView.Alignment = System.Windows.Forms.ListViewAlignment.Default;
            this.driverListView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnName,
            this.columnBase,
            this.columnSize,
            this.columnPath});
            this.driverListView.FullRowSelect = true;
            this.driverListView.HideSelection = false;
            this.driverListView.Location = new System.Drawing.Point(3, 12);
            this.driverListView.MultiSelect = false;
            this.driverListView.Name = "driverListView";
            this.driverListView.Size = new System.Drawing.Size(740, 277);
            this.driverListView.Sorting = System.Windows.Forms.SortOrder.Ascending;
            this.driverListView.TabIndex = 0;
            this.driverListView.UseCompatibleStateImageBehavior = false;
            this.driverListView.View = System.Windows.Forms.View.Details;
            // 
            // columnName
            // 
            this.columnName.Text = "Name";
            this.columnName.Width = 190;
            // 
            // columnBase
            // 
            this.columnBase.Text = "ImageBase";
            this.columnBase.Width = 125;
            // 
            // columnSize
            // 
            this.columnSize.Text = "ImageSize";
            this.columnSize.Width = 80;
            // 
            // columnPath
            // 
            this.columnPath.Text = "Path";
            this.columnPath.Width = 314;
            // 
            // NemesisForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.tabControl);
            this.Controls.Add(this.aboutButton);
            this.Controls.Add(this.settingsButton);
            this.Controls.Add(this.refreshButton);
            this.Controls.Add(this.dumpButton);
            this.MaximizeBox = false;
            this.Name = "NemesisForm";
            this.Resizable = false;
            this.ShadowType = MetroFramework.Forms.MetroFormShadowType.AeroShadow;
            this.Text = "Nemesis";
            this.tabControl.ResumeLayout(false);
            this.processesTabPage.ResumeLayout(false);
            this.metroTabPage2.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private MetroFramework.Controls.MetroButton dumpButton;
        private MetroFramework.Controls.MetroButton refreshButton;
        private ProcessListView processListView;
        private MetroFramework.Controls.MetroButton settingsButton;
        private MetroFramework.Controls.MetroButton aboutButton;
        private MetroFramework.Controls.MetroTabControl tabControl;
        private MetroFramework.Controls.MetroTabPage processesTabPage;
        private MetroFramework.Controls.MetroTabPage metroTabPage2;
        private Utils.Driver.DriverListView driverListView;
        private System.Windows.Forms.ColumnHeader columnName;
        private System.Windows.Forms.ColumnHeader columnBase;
        private System.Windows.Forms.ColumnHeader columnSize;
        private System.Windows.Forms.ColumnHeader columnPath;
    }
}

