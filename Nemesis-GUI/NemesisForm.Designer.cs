namespace Nemesis
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
            this.processListView = new System.Windows.Forms.ListView();
            this.SuspendLayout();
            // 
            // dumpButton
            // 
            this.dumpButton.Location = new System.Drawing.Point(585, 63);
            this.dumpButton.Name = "dumpButton";
            this.dumpButton.Size = new System.Drawing.Size(75, 23);
            this.dumpButton.TabIndex = 0;
            this.dumpButton.Text = "Dump";
            this.dumpButton.Click += new System.EventHandler(this.DumpButton_Click);
            // 
            // refreshButton
            // 
            this.refreshButton.Location = new System.Drawing.Point(504, 63);
            this.refreshButton.Name = "refreshButton";
            this.refreshButton.Size = new System.Drawing.Size(75, 23);
            this.refreshButton.TabIndex = 2;
            this.refreshButton.Text = "Refresh";
            this.refreshButton.Click += new System.EventHandler(this.RefreshButton_Click);
            // 
            // processListView
            // 
            this.processListView.Alignment = System.Windows.Forms.ListViewAlignment.Default;
            this.processListView.Location = new System.Drawing.Point(23, 92);
            this.processListView.MultiSelect = false;
            this.processListView.Name = "processListView";
            this.processListView.Size = new System.Drawing.Size(637, 385);
            this.processListView.TabIndex = 0;
            this.processListView.UseCompatibleStateImageBehavior = false;
            // 
            // NemesisForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(683, 500);
            this.Controls.Add(this.processListView);
            this.Controls.Add(this.refreshButton);
            this.Controls.Add(this.dumpButton);
            this.Name = "NemesisForm";
            this.Resizable = false;
            this.Text = "Nemesis";
            this.ResumeLayout(false);

        }

        #endregion

        private MetroFramework.Controls.MetroButton dumpButton;
        private MetroFramework.Controls.MetroButton refreshButton;
        private System.Windows.Forms.ListView processListView;
    }
}

