namespace Nemesis.Forms
{
    partial class Settings
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
            this.metroLabel1 = new MetroFramework.Controls.MetroLabel();
            this.metroLabel2 = new MetroFramework.Controls.MetroLabel();
            this.saveButton = new MetroFramework.Controls.MetroButton();
            this.cancelButton = new MetroFramework.Controls.MetroButton();
            this.customDumpLocationToggle = new MetroFramework.Controls.MetroToggle();
            this.dumpLocation = new MetroFramework.Controls.MetroTextBox();
            this.metroLabel3 = new MetroFramework.Controls.MetroLabel();
            this.createFolderToggle = new MetroFramework.Controls.MetroToggle();
            this.metroLabel5 = new MetroFramework.Controls.MetroLabel();
            this.fileName = new MetroFramework.Controls.MetroTextBox();
            this.metroLabel6 = new MetroFramework.Controls.MetroLabel();
            this.createTimestampFolderToggle = new MetroFramework.Controls.MetroToggle();
            this.metroLabel4 = new MetroFramework.Controls.MetroLabel();
            this.askForLocationToggle = new MetroFramework.Controls.MetroToggle();
            this.metroLabel7 = new MetroFramework.Controls.MetroLabel();
            this.SuspendLayout();
            // 
            // metroLabel1
            // 
            this.metroLabel1.AutoSize = true;
            this.metroLabel1.Location = new System.Drawing.Point(23, 60);
            this.metroLabel1.Name = "metroLabel1";
            this.metroLabel1.Size = new System.Drawing.Size(105, 19);
            this.metroLabel1.TabIndex = 0;
            this.metroLabel1.Text = "Dump Location: ";
            // 
            // metroLabel2
            // 
            this.metroLabel2.AutoSize = true;
            this.metroLabel2.Location = new System.Drawing.Point(23, 128);
            this.metroLabel2.Name = "metroLabel2";
            this.metroLabel2.Size = new System.Drawing.Size(146, 19);
            this.metroLabel2.TabIndex = 3;
            this.metroLabel2.Text = "Custom dump location:";
            // 
            // saveButton
            // 
            this.saveButton.Location = new System.Drawing.Point(432, 254);
            this.saveButton.Name = "saveButton";
            this.saveButton.Size = new System.Drawing.Size(75, 23);
            this.saveButton.TabIndex = 4;
            this.saveButton.Text = "Save";
            this.saveButton.UseSelectable = true;
            this.saveButton.Click += new System.EventHandler(this.SaveButton_Click);
            // 
            // cancelButton
            // 
            this.cancelButton.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.cancelButton.Location = new System.Drawing.Point(351, 254);
            this.cancelButton.Name = "cancelButton";
            this.cancelButton.Size = new System.Drawing.Size(75, 23);
            this.cancelButton.TabIndex = 5;
            this.cancelButton.Text = "Cancel";
            this.cancelButton.UseSelectable = true;
            // 
            // customDumpLocationToggle
            // 
            this.customDumpLocationToggle.AutoSize = true;
            this.customDumpLocationToggle.Location = new System.Drawing.Point(207, 130);
            this.customDumpLocationToggle.Name = "customDumpLocationToggle";
            this.customDumpLocationToggle.Size = new System.Drawing.Size(80, 17);
            this.customDumpLocationToggle.TabIndex = 6;
            this.customDumpLocationToggle.Text = "Off";
            this.customDumpLocationToggle.UseSelectable = true;
            this.customDumpLocationToggle.CheckedChanged += new System.EventHandler(this.CustomDumpLocationToggle_CheckedChanged);
            // 
            // dumpLocation
            // 
            // 
            // 
            // 
            this.dumpLocation.CustomButton.Image = null;
            this.dumpLocation.CustomButton.Location = new System.Drawing.Point(220, 1);
            this.dumpLocation.CustomButton.Name = "";
            this.dumpLocation.CustomButton.Size = new System.Drawing.Size(21, 21);
            this.dumpLocation.CustomButton.Style = MetroFramework.MetroColorStyle.Blue;
            this.dumpLocation.CustomButton.TabIndex = 1;
            this.dumpLocation.CustomButton.Theme = MetroFramework.MetroThemeStyle.Light;
            this.dumpLocation.CustomButton.UseSelectable = true;
            this.dumpLocation.CustomButton.Visible = false;
            this.dumpLocation.Lines = new string[0];
            this.dumpLocation.Location = new System.Drawing.Point(207, 60);
            this.dumpLocation.MaxLength = 32767;
            this.dumpLocation.Name = "dumpLocation";
            this.dumpLocation.PasswordChar = '\0';
            this.dumpLocation.ReadOnly = true;
            this.dumpLocation.ScrollBars = System.Windows.Forms.ScrollBars.None;
            this.dumpLocation.SelectedText = "";
            this.dumpLocation.SelectionLength = 0;
            this.dumpLocation.SelectionStart = 0;
            this.dumpLocation.ShortcutsEnabled = true;
            this.dumpLocation.Size = new System.Drawing.Size(242, 23);
            this.dumpLocation.TabIndex = 7;
            this.dumpLocation.UseSelectable = true;
            this.dumpLocation.WaterMarkColor = System.Drawing.Color.FromArgb(((int)(((byte)(109)))), ((int)(((byte)(109)))), ((int)(((byte)(109)))));
            this.dumpLocation.WaterMarkFont = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Pixel);
            // 
            // metroLabel3
            // 
            this.metroLabel3.AutoSize = true;
            this.metroLabel3.Location = new System.Drawing.Point(23, 151);
            this.metroLabel3.Name = "metroLabel3";
            this.metroLabel3.Size = new System.Drawing.Size(159, 19);
            this.metroLabel3.TabIndex = 8;
            this.metroLabel3.Text = "Create folder for process:";
            // 
            // createFolderToggle
            // 
            this.createFolderToggle.AutoSize = true;
            this.createFolderToggle.Location = new System.Drawing.Point(207, 153);
            this.createFolderToggle.Name = "createFolderToggle";
            this.createFolderToggle.Size = new System.Drawing.Size(80, 17);
            this.createFolderToggle.TabIndex = 9;
            this.createFolderToggle.Text = "Off";
            this.createFolderToggle.UseSelectable = true;
            this.createFolderToggle.CheckedChanged += new System.EventHandler(this.CreateFolderToggle_CheckedChanged);
            // 
            // metroLabel5
            // 
            this.metroLabel5.AutoSize = true;
            this.metroLabel5.Location = new System.Drawing.Point(23, 86);
            this.metroLabel5.Name = "metroLabel5";
            this.metroLabel5.Size = new System.Drawing.Size(76, 19);
            this.metroLabel5.TabIndex = 12;
            this.metroLabel5.Text = "File Name: ";
            // 
            // fileName
            // 
            // 
            // 
            // 
            this.fileName.CustomButton.Image = null;
            this.fileName.CustomButton.Location = new System.Drawing.Point(220, 1);
            this.fileName.CustomButton.Name = "";
            this.fileName.CustomButton.Size = new System.Drawing.Size(21, 21);
            this.fileName.CustomButton.Style = MetroFramework.MetroColorStyle.Blue;
            this.fileName.CustomButton.TabIndex = 1;
            this.fileName.CustomButton.Theme = MetroFramework.MetroThemeStyle.Light;
            this.fileName.CustomButton.UseSelectable = true;
            this.fileName.CustomButton.Visible = false;
            this.fileName.Lines = new string[] {
        "_dump.exe"};
            this.fileName.Location = new System.Drawing.Point(207, 86);
            this.fileName.MaxLength = 32767;
            this.fileName.Name = "fileName";
            this.fileName.PasswordChar = '\0';
            this.fileName.ScrollBars = System.Windows.Forms.ScrollBars.None;
            this.fileName.SelectedText = "";
            this.fileName.SelectionLength = 0;
            this.fileName.SelectionStart = 0;
            this.fileName.ShortcutsEnabled = true;
            this.fileName.Size = new System.Drawing.Size(242, 23);
            this.fileName.TabIndex = 13;
            this.fileName.Text = "_dump.exe";
            this.fileName.UseSelectable = true;
            this.fileName.WaterMarkColor = System.Drawing.Color.FromArgb(((int)(((byte)(109)))), ((int)(((byte)(109)))), ((int)(((byte)(109)))));
            this.fileName.WaterMarkFont = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Pixel);
            // 
            // metroLabel6
            // 
            this.metroLabel6.AutoSize = true;
            this.metroLabel6.Location = new System.Drawing.Point(25, 170);
            this.metroLabel6.Name = "metroLabel6";
            this.metroLabel6.Size = new System.Drawing.Size(103, 19);
            this.metroLabel6.TabIndex = 14;
            this.metroLabel6.Text = "Add timestamp:";
            // 
            // createTimestampFolderToggle
            // 
            this.createTimestampFolderToggle.AutoSize = true;
            this.createTimestampFolderToggle.Location = new System.Drawing.Point(207, 176);
            this.createTimestampFolderToggle.Name = "createTimestampFolderToggle";
            this.createTimestampFolderToggle.Size = new System.Drawing.Size(80, 17);
            this.createTimestampFolderToggle.TabIndex = 15;
            this.createTimestampFolderToggle.Text = "Off";
            this.createTimestampFolderToggle.UseSelectable = true;
            this.createTimestampFolderToggle.CheckedChanged += new System.EventHandler(this.CreateTimestampFolderToggle_CheckedChanged);
            // 
            // metroLabel4
            // 
            this.metroLabel4.AutoSize = true;
            this.metroLabel4.Location = new System.Drawing.Point(23, 197);
            this.metroLabel4.Name = "metroLabel4";
            this.metroLabel4.Size = new System.Drawing.Size(124, 19);
            this.metroLabel4.TabIndex = 16;
            this.metroLabel4.Text = "Ask for file location:";
            // 
            // askForLocationToggle
            // 
            this.askForLocationToggle.AutoSize = true;
            this.askForLocationToggle.Location = new System.Drawing.Point(207, 199);
            this.askForLocationToggle.Name = "askForLocationToggle";
            this.askForLocationToggle.Size = new System.Drawing.Size(80, 17);
            this.askForLocationToggle.TabIndex = 17;
            this.askForLocationToggle.Text = "Off";
            this.askForLocationToggle.UseSelectable = true;
            this.askForLocationToggle.CheckedChanged += new System.EventHandler(this.AskForLocationToggle_CheckedChanged);
            // 
            // metroLabel7
            // 
            this.metroLabel7.AutoSize = true;
            this.metroLabel7.Location = new System.Drawing.Point(23, 174);
            this.metroLabel7.Name = "metroLabel7";
            this.metroLabel7.Size = new System.Drawing.Size(157, 19);
            this.metroLabel7.TabIndex = 14;
            this.metroLabel7.Text = "Create timestamp folder:";
            // 
            // Settings
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.cancelButton;
            this.ClientSize = new System.Drawing.Size(530, 300);
            this.Controls.Add(this.askForLocationToggle);
            this.Controls.Add(this.metroLabel4);
            this.Controls.Add(this.createTimestampFolderToggle);
            this.Controls.Add(this.metroLabel7);
            this.Controls.Add(this.metroLabel6);
            this.Controls.Add(this.fileName);
            this.Controls.Add(this.metroLabel5);
            this.Controls.Add(this.createFolderToggle);
            this.Controls.Add(this.metroLabel3);
            this.Controls.Add(this.dumpLocation);
            this.Controls.Add(this.customDumpLocationToggle);
            this.Controls.Add(this.cancelButton);
            this.Controls.Add(this.saveButton);
            this.Controls.Add(this.metroLabel2);
            this.Controls.Add(this.metroLabel1);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Settings";
            this.Resizable = false;
            this.ShadowType = MetroFramework.Forms.MetroFormShadowType.AeroShadow;
            this.ShowInTaskbar = false;
            this.Text = "Settings";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private MetroFramework.Controls.MetroLabel metroLabel1;
        private MetroFramework.Controls.MetroLabel metroLabel2;
        private MetroFramework.Controls.MetroButton saveButton;
        private MetroFramework.Controls.MetroButton cancelButton;
        private MetroFramework.Controls.MetroToggle customDumpLocationToggle;
        private MetroFramework.Controls.MetroTextBox dumpLocation;
        private MetroFramework.Controls.MetroLabel metroLabel3;
        private MetroFramework.Controls.MetroToggle createFolderToggle;
        private MetroFramework.Controls.MetroLabel metroLabel5;
        private MetroFramework.Controls.MetroTextBox fileName;
        private MetroFramework.Controls.MetroLabel metroLabel6;
        private MetroFramework.Controls.MetroToggle createTimestampFolderToggle;
        private MetroFramework.Controls.MetroLabel metroLabel4;
        private MetroFramework.Controls.MetroToggle askForLocationToggle;
        private MetroFramework.Controls.MetroLabel metroLabel7;
    }
}