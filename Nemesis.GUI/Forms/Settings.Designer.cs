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
            this.components = new System.ComponentModel.Container();
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
            this.metroTabControl1 = new MetroFramework.Controls.MetroTabControl();
            this.metroTabPage1 = new MetroFramework.Controls.MetroTabPage();
            this.metroTabPage2 = new MetroFramework.Controls.MetroTabPage();
            this.colorComboBox = new MetroFramework.Controls.MetroComboBox();
            this.themeComboBox = new MetroFramework.Controls.MetroComboBox();
            this.metroTabPage3 = new MetroFramework.Controls.MetroTabPage();
            this.metroLabel9 = new MetroFramework.Controls.MetroLabel();
            this.manualModuleList = new MetroFramework.Controls.MetroToggle();
            this.metroLabel8 = new MetroFramework.Controls.MetroLabel();
            this.saveOffsetsToggle = new MetroFramework.Controls.MetroToggle();
            this.memoryComboBox = new MetroFramework.Controls.MetroComboBox();
            this.colorDialog = new System.Windows.Forms.ColorDialog();
            this.settingStyleManager = new MetroFramework.Components.MetroStyleManager(this.components);
            this.metroLabel10 = new MetroFramework.Controls.MetroLabel();
            this.headerFromFile = new MetroFramework.Controls.MetroToggle();
            this.metroTabControl1.SuspendLayout();
            this.metroTabPage1.SuspendLayout();
            this.metroTabPage2.SuspendLayout();
            this.metroTabPage3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.settingStyleManager)).BeginInit();
            this.SuspendLayout();
            // 
            // metroLabel1
            // 
            this.metroLabel1.AutoSize = true;
            this.metroLabel1.Location = new System.Drawing.Point(2, 18);
            this.metroLabel1.Name = "metroLabel1";
            this.metroLabel1.Size = new System.Drawing.Size(105, 19);
            this.metroLabel1.TabIndex = 0;
            this.metroLabel1.Text = "Dump Location: ";
            // 
            // metroLabel2
            // 
            this.metroLabel2.AutoSize = true;
            this.metroLabel2.Location = new System.Drawing.Point(2, 86);
            this.metroLabel2.Name = "metroLabel2";
            this.metroLabel2.Size = new System.Drawing.Size(146, 19);
            this.metroLabel2.TabIndex = 3;
            this.metroLabel2.Text = "Custom dump location:";
            // 
            // saveButton
            // 
            this.saveButton.Location = new System.Drawing.Point(500, 322);
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
            this.cancelButton.Location = new System.Drawing.Point(419, 322);
            this.cancelButton.Name = "cancelButton";
            this.cancelButton.Size = new System.Drawing.Size(75, 23);
            this.cancelButton.TabIndex = 5;
            this.cancelButton.Text = "Cancel";
            this.cancelButton.UseSelectable = true;
            // 
            // customDumpLocationToggle
            // 
            this.customDumpLocationToggle.AutoSize = true;
            this.customDumpLocationToggle.Location = new System.Drawing.Point(186, 88);
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
            this.dumpLocation.Location = new System.Drawing.Point(186, 18);
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
            this.metroLabel3.Location = new System.Drawing.Point(2, 109);
            this.metroLabel3.Name = "metroLabel3";
            this.metroLabel3.Size = new System.Drawing.Size(159, 19);
            this.metroLabel3.TabIndex = 8;
            this.metroLabel3.Text = "Create folder for process:";
            // 
            // createFolderToggle
            // 
            this.createFolderToggle.AutoSize = true;
            this.createFolderToggle.Location = new System.Drawing.Point(186, 111);
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
            this.metroLabel5.Location = new System.Drawing.Point(2, 44);
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
        "_dump"};
            this.fileName.Location = new System.Drawing.Point(186, 44);
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
            this.fileName.Text = "_dump";
            this.fileName.UseSelectable = true;
            this.fileName.WaterMarkColor = System.Drawing.Color.FromArgb(((int)(((byte)(109)))), ((int)(((byte)(109)))), ((int)(((byte)(109)))));
            this.fileName.WaterMarkFont = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Pixel);
            // 
            // metroLabel6
            // 
            this.metroLabel6.AutoSize = true;
            this.metroLabel6.Location = new System.Drawing.Point(4, 128);
            this.metroLabel6.Name = "metroLabel6";
            this.metroLabel6.Size = new System.Drawing.Size(103, 19);
            this.metroLabel6.TabIndex = 14;
            this.metroLabel6.Text = "Add timestamp:";
            // 
            // createTimestampFolderToggle
            // 
            this.createTimestampFolderToggle.AutoSize = true;
            this.createTimestampFolderToggle.Location = new System.Drawing.Point(186, 134);
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
            this.metroLabel4.Location = new System.Drawing.Point(2, 155);
            this.metroLabel4.Name = "metroLabel4";
            this.metroLabel4.Size = new System.Drawing.Size(124, 19);
            this.metroLabel4.TabIndex = 16;
            this.metroLabel4.Text = "Ask for file location:";
            // 
            // askForLocationToggle
            // 
            this.askForLocationToggle.AutoSize = true;
            this.askForLocationToggle.Location = new System.Drawing.Point(186, 157);
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
            this.metroLabel7.Location = new System.Drawing.Point(2, 132);
            this.metroLabel7.Name = "metroLabel7";
            this.metroLabel7.Size = new System.Drawing.Size(157, 19);
            this.metroLabel7.TabIndex = 14;
            this.metroLabel7.Text = "Create timestamp folder:";
            // 
            // metroTabControl1
            // 
            this.metroTabControl1.Controls.Add(this.metroTabPage1);
            this.metroTabControl1.Controls.Add(this.metroTabPage3);
            this.metroTabControl1.Controls.Add(this.metroTabPage2);
            this.metroTabControl1.Location = new System.Drawing.Point(23, 63);
            this.metroTabControl1.Name = "metroTabControl1";
            this.metroTabControl1.SelectedIndex = 0;
            this.metroTabControl1.Size = new System.Drawing.Size(552, 253);
            this.metroTabControl1.TabIndex = 18;
            this.metroTabControl1.UseSelectable = true;
            // 
            // metroTabPage1
            // 
            this.metroTabPage1.Controls.Add(this.askForLocationToggle);
            this.metroTabPage1.Controls.Add(this.metroLabel4);
            this.metroTabPage1.Controls.Add(this.dumpLocation);
            this.metroTabPage1.Controls.Add(this.createTimestampFolderToggle);
            this.metroTabPage1.Controls.Add(this.metroLabel1);
            this.metroTabPage1.Controls.Add(this.metroLabel7);
            this.metroTabPage1.Controls.Add(this.metroLabel2);
            this.metroTabPage1.Controls.Add(this.metroLabel6);
            this.metroTabPage1.Controls.Add(this.customDumpLocationToggle);
            this.metroTabPage1.Controls.Add(this.fileName);
            this.metroTabPage1.Controls.Add(this.metroLabel3);
            this.metroTabPage1.Controls.Add(this.metroLabel5);
            this.metroTabPage1.Controls.Add(this.createFolderToggle);
            this.metroTabPage1.HorizontalScrollbarBarColor = true;
            this.metroTabPage1.HorizontalScrollbarHighlightOnWheel = false;
            this.metroTabPage1.HorizontalScrollbarSize = 10;
            this.metroTabPage1.Location = new System.Drawing.Point(4, 38);
            this.metroTabPage1.Name = "metroTabPage1";
            this.metroTabPage1.Size = new System.Drawing.Size(544, 211);
            this.metroTabPage1.TabIndex = 0;
            this.metroTabPage1.Text = "General";
            this.metroTabPage1.VerticalScrollbarBarColor = true;
            this.metroTabPage1.VerticalScrollbarHighlightOnWheel = false;
            this.metroTabPage1.VerticalScrollbarSize = 10;
            // 
            // metroTabPage2
            // 
            this.metroTabPage2.Controls.Add(this.colorComboBox);
            this.metroTabPage2.Controls.Add(this.themeComboBox);
            this.metroTabPage2.HorizontalScrollbarBarColor = true;
            this.metroTabPage2.HorizontalScrollbarHighlightOnWheel = false;
            this.metroTabPage2.HorizontalScrollbarSize = 10;
            this.metroTabPage2.Location = new System.Drawing.Point(4, 38);
            this.metroTabPage2.Name = "metroTabPage2";
            this.metroTabPage2.Size = new System.Drawing.Size(544, 211);
            this.metroTabPage2.TabIndex = 1;
            this.metroTabPage2.Text = "Styles";
            this.metroTabPage2.VerticalScrollbarBarColor = true;
            this.metroTabPage2.VerticalScrollbarHighlightOnWheel = false;
            this.metroTabPage2.VerticalScrollbarSize = 10;
            // 
            // colorComboBox
            // 
            this.colorComboBox.FormattingEnabled = true;
            this.colorComboBox.ItemHeight = 23;
            this.colorComboBox.Location = new System.Drawing.Point(3, 54);
            this.colorComboBox.Name = "colorComboBox";
            this.colorComboBox.PromptText = "Color";
            this.colorComboBox.Size = new System.Drawing.Size(161, 29);
            this.colorComboBox.TabIndex = 6;
            this.colorComboBox.UseSelectable = true;
            this.colorComboBox.SelectedIndexChanged += new System.EventHandler(this.ColorComboBox_SelectedIndexChanged);
            // 
            // themeComboBox
            // 
            this.themeComboBox.FormattingEnabled = true;
            this.themeComboBox.ItemHeight = 23;
            this.themeComboBox.Location = new System.Drawing.Point(3, 18);
            this.themeComboBox.Name = "themeComboBox";
            this.themeComboBox.PromptText = "Theme";
            this.themeComboBox.Size = new System.Drawing.Size(161, 29);
            this.themeComboBox.TabIndex = 5;
            this.themeComboBox.UseSelectable = true;
            this.themeComboBox.SelectedIndexChanged += new System.EventHandler(this.ThemeComboBox_SelectedIndexChanged);
            // 
            // metroTabPage3
            // 
            this.metroTabPage3.Controls.Add(this.metroLabel10);
            this.metroTabPage3.Controls.Add(this.headerFromFile);
            this.metroTabPage3.Controls.Add(this.metroLabel9);
            this.metroTabPage3.Controls.Add(this.manualModuleList);
            this.metroTabPage3.Controls.Add(this.metroLabel8);
            this.metroTabPage3.Controls.Add(this.saveOffsetsToggle);
            this.metroTabPage3.Controls.Add(this.memoryComboBox);
            this.metroTabPage3.HorizontalScrollbarBarColor = true;
            this.metroTabPage3.HorizontalScrollbarHighlightOnWheel = false;
            this.metroTabPage3.HorizontalScrollbarSize = 10;
            this.metroTabPage3.Location = new System.Drawing.Point(4, 38);
            this.metroTabPage3.Name = "metroTabPage3";
            this.metroTabPage3.Size = new System.Drawing.Size(544, 211);
            this.metroTabPage3.TabIndex = 2;
            this.metroTabPage3.Text = "Miscellaneous";
            this.metroTabPage3.VerticalScrollbarBarColor = true;
            this.metroTabPage3.VerticalScrollbarHighlightOnWheel = false;
            this.metroTabPage3.VerticalScrollbarSize = 10;
            // 
            // metroLabel9
            // 
            this.metroLabel9.AutoSize = true;
            this.metroLabel9.Location = new System.Drawing.Point(3, 89);
            this.metroLabel9.Name = "metroLabel9";
            this.metroLabel9.Size = new System.Drawing.Size(148, 19);
            this.metroLabel9.TabIndex = 7;
            this.metroLabel9.Text = "Use manual module list:";
            // 
            // manualModuleList
            // 
            this.manualModuleList.AutoSize = true;
            this.manualModuleList.Location = new System.Drawing.Point(178, 91);
            this.manualModuleList.Name = "manualModuleList";
            this.manualModuleList.Size = new System.Drawing.Size(80, 17);
            this.manualModuleList.TabIndex = 6;
            this.manualModuleList.Text = "Off";
            this.manualModuleList.UseSelectable = true;
            // 
            // metroLabel8
            // 
            this.metroLabel8.AutoSize = true;
            this.metroLabel8.Location = new System.Drawing.Point(3, 61);
            this.metroLabel8.Name = "metroLabel8";
            this.metroLabel8.Size = new System.Drawing.Size(169, 19);
            this.metroLabel8.TabIndex = 5;
            this.metroLabel8.Text = "Save driver base addresses:";
            // 
            // saveOffsetsToggle
            // 
            this.saveOffsetsToggle.AutoSize = true;
            this.saveOffsetsToggle.Location = new System.Drawing.Point(178, 63);
            this.saveOffsetsToggle.Name = "saveOffsetsToggle";
            this.saveOffsetsToggle.Size = new System.Drawing.Size(80, 17);
            this.saveOffsetsToggle.TabIndex = 4;
            this.saveOffsetsToggle.Text = "Off";
            this.saveOffsetsToggle.UseSelectable = true;
            // 
            // memoryComboBox
            // 
            this.memoryComboBox.FormattingEnabled = true;
            this.memoryComboBox.ItemHeight = 23;
            this.memoryComboBox.Location = new System.Drawing.Point(3, 18);
            this.memoryComboBox.Name = "memoryComboBox";
            this.memoryComboBox.PromptText = "Memory Source";
            this.memoryComboBox.Size = new System.Drawing.Size(161, 29);
            this.memoryComboBox.TabIndex = 2;
            this.memoryComboBox.UseSelectable = true;
            // 
            // settingStyleManager
            // 
            this.settingStyleManager.Owner = null;
            // 
            // metroLabel10
            // 
            this.metroLabel10.AutoSize = true;
            this.metroLabel10.Location = new System.Drawing.Point(3, 118);
            this.metroLabel10.Name = "metroLabel10";
            this.metroLabel10.Size = new System.Drawing.Size(141, 19);
            this.metroLabel10.TabIndex = 9;
            this.metroLabel10.Text = "Read header from file:";
            // 
            // headerFromFile
            // 
            this.headerFromFile.AutoSize = true;
            this.headerFromFile.Location = new System.Drawing.Point(178, 120);
            this.headerFromFile.Name = "headerFromFile";
            this.headerFromFile.Size = new System.Drawing.Size(80, 17);
            this.headerFromFile.TabIndex = 8;
            this.headerFromFile.Text = "Off";
            this.headerFromFile.UseSelectable = true;
            // 
            // Settings
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.cancelButton;
            this.ClientSize = new System.Drawing.Size(598, 356);
            this.Controls.Add(this.metroTabControl1);
            this.Controls.Add(this.cancelButton);
            this.Controls.Add(this.saveButton);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Settings";
            this.Resizable = false;
            this.ShadowType = MetroFramework.Forms.MetroFormShadowType.AeroShadow;
            this.ShowInTaskbar = false;
            this.Text = "Settings";
            this.metroTabControl1.ResumeLayout(false);
            this.metroTabPage1.ResumeLayout(false);
            this.metroTabPage1.PerformLayout();
            this.metroTabPage2.ResumeLayout(false);
            this.metroTabPage3.ResumeLayout(false);
            this.metroTabPage3.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.settingStyleManager)).EndInit();
            this.ResumeLayout(false);

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
        private MetroFramework.Controls.MetroTabControl metroTabControl1;
        private MetroFramework.Controls.MetroTabPage metroTabPage1;
        private MetroFramework.Controls.MetroTabPage metroTabPage2;
        private System.Windows.Forms.ColorDialog colorDialog;
        private MetroFramework.Controls.MetroComboBox themeComboBox;
        private MetroFramework.Controls.MetroComboBox colorComboBox;
        private MetroFramework.Controls.MetroTabPage metroTabPage3;
        private MetroFramework.Controls.MetroComboBox memoryComboBox;
        private MetroFramework.Components.MetroStyleManager settingStyleManager;
        private MetroFramework.Controls.MetroLabel metroLabel8;
        private MetroFramework.Controls.MetroToggle saveOffsetsToggle;
        private MetroFramework.Controls.MetroLabel metroLabel9;
        private MetroFramework.Controls.MetroToggle manualModuleList;
        private MetroFramework.Controls.MetroLabel metroLabel10;
        private MetroFramework.Controls.MetroToggle headerFromFile;
    }
}