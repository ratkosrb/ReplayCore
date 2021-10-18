namespace SniffBrowser
{
    partial class FormSniffBrowser
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
            this.lstEvents = new System.Windows.Forms.ListView();
            this.clmEventType = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.clmUnixTime = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.clmDescription = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.txtStartTime = new System.Windows.Forms.TextBox();
            this.lblStartTime = new System.Windows.Forms.Label();
            this.lblEndTime = new System.Windows.Forms.Label();
            this.txtEndTime = new System.Windows.Forms.TextBox();
            this.grpObjectFilters = new System.Windows.Forms.GroupBox();
            this.btnRemove = new System.Windows.Forms.Button();
            this.btnAdd = new System.Windows.Forms.Button();
            this.lstObjectFilters = new System.Windows.Forms.ListView();
            this.clmGuid = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.clmId = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.clmType = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.clmEvents = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.lblObjectType = new System.Windows.Forms.Label();
            this.cmbObjectType = new System.Windows.Forms.ComboBox();
            this.lblId = new System.Windows.Forms.Label();
            this.txtObjectId = new System.Windows.Forms.TextBox();
            this.lblObjectGuid = new System.Windows.Forms.Label();
            this.txtObjectGuid = new System.Windows.Forms.TextBox();
            this.grpEventFilters = new System.Windows.Forms.GroupBox();
            this.cmbEventTypes = new System.Windows.Forms.ComboBox();
            this.lblEventTypes = new System.Windows.Forms.Label();
            this.btnClear = new System.Windows.Forms.Button();
            this.btnSelectAll = new System.Windows.Forms.Button();
            this.lstEventFilters = new System.Windows.Forms.ListView();
            this.txtEventDescription = new System.Windows.Forms.TextBox();
            this.btnRefresh = new System.Windows.Forms.Button();
            this.btnReplayJumpToEventTime = new System.Windows.Forms.Button();
            this.btnReplayJumpToEventSource = new System.Windows.Forms.Button();
            this.btnMakeScript = new System.Windows.Forms.Button();
            this.btnMakeWaypoints = new System.Windows.Forms.Button();
            this.txtStartTimeDate = new System.Windows.Forms.TextBox();
            this.txtEndTimeDate = new System.Windows.Forms.TextBox();
            this.grpReplayControl = new System.Windows.Forms.GroupBox();
            this.btnJumpToEventTarget = new System.Windows.Forms.Button();
            this.btnReplayResetTime = new System.Windows.Forms.Button();
            this.btnReplayPause = new System.Windows.Forms.Button();
            this.btnReplayPlay = new System.Windows.Forms.Button();
            this.grpOptions = new System.Windows.Forms.GroupBox();
            this.cmbTimeDisplay = new System.Windows.Forms.ComboBox();
            this.lblTimeDisplay = new System.Windows.Forms.Label();
            this.cmbTimeType = new System.Windows.Forms.ComboBox();
            this.lblTimeType = new System.Windows.Forms.Label();
            this.grpObjectFilters.SuspendLayout();
            this.grpEventFilters.SuspendLayout();
            this.grpReplayControl.SuspendLayout();
            this.grpOptions.SuspendLayout();
            this.SuspendLayout();
            // 
            // lstEvents
            // 
            this.lstEvents.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.clmEventType,
            this.clmUnixTime,
            this.clmDescription});
            this.lstEvents.FullRowSelect = true;
            this.lstEvents.GridLines = true;
            this.lstEvents.HideSelection = false;
            this.lstEvents.Location = new System.Drawing.Point(12, 12);
            this.lstEvents.Name = "lstEvents";
            this.lstEvents.Size = new System.Drawing.Size(823, 350);
            this.lstEvents.TabIndex = 0;
            this.lstEvents.UseCompatibleStateImageBehavior = false;
            this.lstEvents.View = System.Windows.Forms.View.Details;
            this.lstEvents.SelectedIndexChanged += new System.EventHandler(this.lstEvents_SelectedIndexChanged);
            this.lstEvents.KeyDown += new System.Windows.Forms.KeyEventHandler(this.lstEvents_KeyDown);
            this.lstEvents.MouseClick += new System.Windows.Forms.MouseEventHandler(this.lstEvents_MouseClick);
            // 
            // clmEventType
            // 
            this.clmEventType.Text = "Event";
            this.clmEventType.Width = 70;
            // 
            // clmUnixTime
            // 
            this.clmUnixTime.Text = "Time";
            this.clmUnixTime.Width = 110;
            // 
            // clmDescription
            // 
            this.clmDescription.Text = "Description";
            this.clmDescription.Width = 620;
            // 
            // txtStartTime
            // 
            this.txtStartTime.Location = new System.Drawing.Point(910, 12);
            this.txtStartTime.Name = "txtStartTime";
            this.txtStartTime.Size = new System.Drawing.Size(141, 20);
            this.txtStartTime.TabIndex = 1;
            this.txtStartTime.TextChanged += new System.EventHandler(this.txtStartTime_TextChanged);
            // 
            // lblStartTime
            // 
            this.lblStartTime.AutoSize = true;
            this.lblStartTime.Location = new System.Drawing.Point(846, 15);
            this.lblStartTime.Name = "lblStartTime";
            this.lblStartTime.Size = new System.Drawing.Size(58, 13);
            this.lblStartTime.TabIndex = 2;
            this.lblStartTime.Text = "Start Time:";
            // 
            // lblEndTime
            // 
            this.lblEndTime.AutoSize = true;
            this.lblEndTime.Location = new System.Drawing.Point(849, 41);
            this.lblEndTime.Name = "lblEndTime";
            this.lblEndTime.Size = new System.Drawing.Size(55, 13);
            this.lblEndTime.TabIndex = 4;
            this.lblEndTime.Text = "End Time:";
            // 
            // txtEndTime
            // 
            this.txtEndTime.Location = new System.Drawing.Point(910, 38);
            this.txtEndTime.Name = "txtEndTime";
            this.txtEndTime.Size = new System.Drawing.Size(141, 20);
            this.txtEndTime.TabIndex = 3;
            this.txtEndTime.TextChanged += new System.EventHandler(this.txtEndTime_TextChanged);
            // 
            // grpObjectFilters
            // 
            this.grpObjectFilters.Controls.Add(this.btnRemove);
            this.grpObjectFilters.Controls.Add(this.btnAdd);
            this.grpObjectFilters.Controls.Add(this.lstObjectFilters);
            this.grpObjectFilters.Controls.Add(this.lblObjectType);
            this.grpObjectFilters.Controls.Add(this.cmbObjectType);
            this.grpObjectFilters.Controls.Add(this.lblId);
            this.grpObjectFilters.Controls.Add(this.txtObjectId);
            this.grpObjectFilters.Controls.Add(this.lblObjectGuid);
            this.grpObjectFilters.Controls.Add(this.txtObjectGuid);
            this.grpObjectFilters.Location = new System.Drawing.Point(852, 64);
            this.grpObjectFilters.Name = "grpObjectFilters";
            this.grpObjectFilters.Size = new System.Drawing.Size(408, 298);
            this.grpObjectFilters.TabIndex = 5;
            this.grpObjectFilters.TabStop = false;
            this.grpObjectFilters.Text = "Object Filters";
            // 
            // btnRemove
            // 
            this.btnRemove.Location = new System.Drawing.Point(330, 36);
            this.btnRemove.Name = "btnRemove";
            this.btnRemove.Size = new System.Drawing.Size(70, 23);
            this.btnRemove.TabIndex = 8;
            this.btnRemove.Text = "Remove";
            this.btnRemove.UseVisualStyleBackColor = true;
            this.btnRemove.Click += new System.EventHandler(this.btnRemove_Click);
            // 
            // btnAdd
            // 
            this.btnAdd.Location = new System.Drawing.Point(254, 36);
            this.btnAdd.Name = "btnAdd";
            this.btnAdd.Size = new System.Drawing.Size(70, 23);
            this.btnAdd.TabIndex = 7;
            this.btnAdd.Text = "Add";
            this.btnAdd.UseVisualStyleBackColor = true;
            this.btnAdd.Click += new System.EventHandler(this.btnAdd_Click);
            // 
            // lstObjectFilters
            // 
            this.lstObjectFilters.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.clmGuid,
            this.clmId,
            this.clmType,
            this.clmEvents});
            this.lstObjectFilters.FullRowSelect = true;
            this.lstObjectFilters.GridLines = true;
            this.lstObjectFilters.HideSelection = false;
            this.lstObjectFilters.Location = new System.Drawing.Point(7, 64);
            this.lstObjectFilters.MultiSelect = false;
            this.lstObjectFilters.Name = "lstObjectFilters";
            this.lstObjectFilters.Size = new System.Drawing.Size(395, 226);
            this.lstObjectFilters.TabIndex = 6;
            this.lstObjectFilters.UseCompatibleStateImageBehavior = false;
            this.lstObjectFilters.View = System.Windows.Forms.View.Details;
            this.lstObjectFilters.SelectedIndexChanged += new System.EventHandler(this.lstObjectFilters_SelectedIndexChanged);
            // 
            // clmGuid
            // 
            this.clmGuid.Text = "Guid";
            // 
            // clmId
            // 
            this.clmId.Text = "Id";
            // 
            // clmType
            // 
            this.clmType.Text = "Type";
            this.clmType.Width = 100;
            // 
            // clmEvents
            // 
            this.clmEvents.Text = "Events";
            this.clmEvents.Width = 150;
            // 
            // lblObjectType
            // 
            this.lblObjectType.AutoSize = true;
            this.lblObjectType.Location = new System.Drawing.Point(148, 22);
            this.lblObjectType.Name = "lblObjectType";
            this.lblObjectType.Size = new System.Drawing.Size(34, 13);
            this.lblObjectType.TabIndex = 5;
            this.lblObjectType.Text = "Type:";
            // 
            // cmbObjectType
            // 
            this.cmbObjectType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbObjectType.FormattingEnabled = true;
            this.cmbObjectType.Items.AddRange(new object[] {
            "Any",
            "GameObject",
            "Unit",
            "Creature",
            "Pet",
            "Player"});
            this.cmbObjectType.Location = new System.Drawing.Point(148, 38);
            this.cmbObjectType.Name = "cmbObjectType";
            this.cmbObjectType.Size = new System.Drawing.Size(102, 21);
            this.cmbObjectType.TabIndex = 4;
            // 
            // lblId
            // 
            this.lblId.AutoSize = true;
            this.lblId.Location = new System.Drawing.Point(77, 23);
            this.lblId.Name = "lblId";
            this.lblId.Size = new System.Drawing.Size(19, 13);
            this.lblId.TabIndex = 3;
            this.lblId.Text = "Id:";
            // 
            // txtObjectId
            // 
            this.txtObjectId.Location = new System.Drawing.Point(77, 39);
            this.txtObjectId.Name = "txtObjectId";
            this.txtObjectId.Size = new System.Drawing.Size(65, 20);
            this.txtObjectId.TabIndex = 2;
            // 
            // lblObjectGuid
            // 
            this.lblObjectGuid.AutoSize = true;
            this.lblObjectGuid.Location = new System.Drawing.Point(6, 23);
            this.lblObjectGuid.Name = "lblObjectGuid";
            this.lblObjectGuid.Size = new System.Drawing.Size(32, 13);
            this.lblObjectGuid.TabIndex = 1;
            this.lblObjectGuid.Text = "Guid:";
            // 
            // txtObjectGuid
            // 
            this.txtObjectGuid.Location = new System.Drawing.Point(6, 39);
            this.txtObjectGuid.Name = "txtObjectGuid";
            this.txtObjectGuid.Size = new System.Drawing.Size(65, 20);
            this.txtObjectGuid.TabIndex = 0;
            // 
            // grpEventFilters
            // 
            this.grpEventFilters.Controls.Add(this.cmbEventTypes);
            this.grpEventFilters.Controls.Add(this.lblEventTypes);
            this.grpEventFilters.Controls.Add(this.btnClear);
            this.grpEventFilters.Controls.Add(this.btnSelectAll);
            this.grpEventFilters.Controls.Add(this.lstEventFilters);
            this.grpEventFilters.Location = new System.Drawing.Point(852, 368);
            this.grpEventFilters.Name = "grpEventFilters";
            this.grpEventFilters.Size = new System.Drawing.Size(408, 285);
            this.grpEventFilters.TabIndex = 6;
            this.grpEventFilters.TabStop = false;
            this.grpEventFilters.Text = "Event Filters";
            // 
            // cmbEventTypes
            // 
            this.cmbEventTypes.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbEventTypes.FormattingEnabled = true;
            this.cmbEventTypes.Items.AddRange(new object[] {
            "All",
            "GameObject",
            "Unit",
            "Creature",
            "Player",
            "Client",
            "Miscellaneous"});
            this.cmbEventTypes.Location = new System.Drawing.Point(247, 255);
            this.cmbEventTypes.Name = "cmbEventTypes";
            this.cmbEventTypes.Size = new System.Drawing.Size(153, 21);
            this.cmbEventTypes.TabIndex = 4;
            this.cmbEventTypes.SelectedIndexChanged += new System.EventHandler(this.cmbEventTypes_SelectedIndexChanged);
            // 
            // lblEventTypes
            // 
            this.lblEventTypes.AutoSize = true;
            this.lblEventTypes.Location = new System.Drawing.Point(171, 260);
            this.lblEventTypes.Name = "lblEventTypes";
            this.lblEventTypes.Size = new System.Drawing.Size(70, 13);
            this.lblEventTypes.TabIndex = 3;
            this.lblEventTypes.Text = "Event Types:";
            // 
            // btnClear
            // 
            this.btnClear.Location = new System.Drawing.Point(90, 255);
            this.btnClear.Name = "btnClear";
            this.btnClear.Size = new System.Drawing.Size(75, 23);
            this.btnClear.TabIndex = 2;
            this.btnClear.Text = "Clear";
            this.btnClear.UseVisualStyleBackColor = true;
            this.btnClear.Click += new System.EventHandler(this.btnClear_Click);
            // 
            // btnSelectAll
            // 
            this.btnSelectAll.Location = new System.Drawing.Point(9, 255);
            this.btnSelectAll.Name = "btnSelectAll";
            this.btnSelectAll.Size = new System.Drawing.Size(75, 23);
            this.btnSelectAll.TabIndex = 1;
            this.btnSelectAll.Text = "Select All";
            this.btnSelectAll.UseVisualStyleBackColor = true;
            this.btnSelectAll.Click += new System.EventHandler(this.btnSelectAll_Click);
            // 
            // lstEventFilters
            // 
            this.lstEventFilters.CheckBoxes = true;
            this.lstEventFilters.Location = new System.Drawing.Point(9, 19);
            this.lstEventFilters.Name = "lstEventFilters";
            this.lstEventFilters.Size = new System.Drawing.Size(391, 230);
            this.lstEventFilters.TabIndex = 0;
            this.lstEventFilters.UseCompatibleStateImageBehavior = false;
            this.lstEventFilters.View = System.Windows.Forms.View.List;
            this.lstEventFilters.ItemChecked += new System.Windows.Forms.ItemCheckedEventHandler(this.lstEventFilters_ItemChecked);
            // 
            // txtEventDescription
            // 
            this.txtEventDescription.Font = new System.Drawing.Font("Arial", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.txtEventDescription.Location = new System.Drawing.Point(12, 368);
            this.txtEventDescription.Multiline = true;
            this.txtEventDescription.Name = "txtEventDescription";
            this.txtEventDescription.ReadOnly = true;
            this.txtEventDescription.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.txtEventDescription.Size = new System.Drawing.Size(530, 285);
            this.txtEventDescription.TabIndex = 7;
            // 
            // btnRefresh
            // 
            this.btnRefresh.Location = new System.Drawing.Point(1185, 663);
            this.btnRefresh.Name = "btnRefresh";
            this.btnRefresh.Size = new System.Drawing.Size(75, 23);
            this.btnRefresh.TabIndex = 8;
            this.btnRefresh.Text = "Refresh";
            this.btnRefresh.UseVisualStyleBackColor = true;
            this.btnRefresh.Click += new System.EventHandler(this.btnRefresh_Click);
            // 
            // btnReplayJumpToEventTime
            // 
            this.btnReplayJumpToEventTime.Location = new System.Drawing.Point(148, 48);
            this.btnReplayJumpToEventTime.Name = "btnReplayJumpToEventTime";
            this.btnReplayJumpToEventTime.Size = new System.Drawing.Size(131, 23);
            this.btnReplayJumpToEventTime.TabIndex = 9;
            this.btnReplayJumpToEventTime.Text = "Jump to Event Time";
            this.btnReplayJumpToEventTime.UseVisualStyleBackColor = true;
            this.btnReplayJumpToEventTime.Click += new System.EventHandler(this.btnReplayJumpToEventTime_Click);
            // 
            // btnReplayJumpToEventSource
            // 
            this.btnReplayJumpToEventSource.Location = new System.Drawing.Point(8, 77);
            this.btnReplayJumpToEventSource.Name = "btnReplayJumpToEventSource";
            this.btnReplayJumpToEventSource.Size = new System.Drawing.Size(131, 23);
            this.btnReplayJumpToEventSource.TabIndex = 10;
            this.btnReplayJumpToEventSource.Text = "Jump to Event Source";
            this.btnReplayJumpToEventSource.UseVisualStyleBackColor = true;
            this.btnReplayJumpToEventSource.Click += new System.EventHandler(this.btnReplayJumpToEventSource_Click);
            // 
            // btnMakeScript
            // 
            this.btnMakeScript.Location = new System.Drawing.Point(12, 663);
            this.btnMakeScript.Name = "btnMakeScript";
            this.btnMakeScript.Size = new System.Drawing.Size(100, 23);
            this.btnMakeScript.TabIndex = 11;
            this.btnMakeScript.Text = "Make Script";
            this.btnMakeScript.UseVisualStyleBackColor = true;
            this.btnMakeScript.Click += new System.EventHandler(this.btnMakeScript_Click);
            // 
            // btnMakeWaypoints
            // 
            this.btnMakeWaypoints.Location = new System.Drawing.Point(118, 663);
            this.btnMakeWaypoints.Name = "btnMakeWaypoints";
            this.btnMakeWaypoints.Size = new System.Drawing.Size(100, 23);
            this.btnMakeWaypoints.TabIndex = 12;
            this.btnMakeWaypoints.Text = "Make Waypoints";
            this.btnMakeWaypoints.UseVisualStyleBackColor = true;
            // 
            // txtStartTimeDate
            // 
            this.txtStartTimeDate.Location = new System.Drawing.Point(1057, 12);
            this.txtStartTimeDate.Name = "txtStartTimeDate";
            this.txtStartTimeDate.ReadOnly = true;
            this.txtStartTimeDate.Size = new System.Drawing.Size(203, 20);
            this.txtStartTimeDate.TabIndex = 13;
            // 
            // txtEndTimeDate
            // 
            this.txtEndTimeDate.Location = new System.Drawing.Point(1057, 38);
            this.txtEndTimeDate.Name = "txtEndTimeDate";
            this.txtEndTimeDate.ReadOnly = true;
            this.txtEndTimeDate.Size = new System.Drawing.Size(203, 20);
            this.txtEndTimeDate.TabIndex = 14;
            // 
            // grpReplayControl
            // 
            this.grpReplayControl.Controls.Add(this.btnJumpToEventTarget);
            this.grpReplayControl.Controls.Add(this.btnReplayResetTime);
            this.grpReplayControl.Controls.Add(this.btnReplayPause);
            this.grpReplayControl.Controls.Add(this.btnReplayPlay);
            this.grpReplayControl.Controls.Add(this.btnReplayJumpToEventTime);
            this.grpReplayControl.Controls.Add(this.btnReplayJumpToEventSource);
            this.grpReplayControl.Location = new System.Drawing.Point(548, 368);
            this.grpReplayControl.Name = "grpReplayControl";
            this.grpReplayControl.Size = new System.Drawing.Size(287, 109);
            this.grpReplayControl.TabIndex = 15;
            this.grpReplayControl.TabStop = false;
            this.grpReplayControl.Text = "Replay Control";
            // 
            // btnJumpToEventTarget
            // 
            this.btnJumpToEventTarget.Location = new System.Drawing.Point(148, 77);
            this.btnJumpToEventTarget.Name = "btnJumpToEventTarget";
            this.btnJumpToEventTarget.Size = new System.Drawing.Size(131, 23);
            this.btnJumpToEventTarget.TabIndex = 14;
            this.btnJumpToEventTarget.Text = "Jump to Event Target";
            this.btnJumpToEventTarget.UseVisualStyleBackColor = true;
            // 
            // btnReplayResetTime
            // 
            this.btnReplayResetTime.Location = new System.Drawing.Point(8, 48);
            this.btnReplayResetTime.Name = "btnReplayResetTime";
            this.btnReplayResetTime.Size = new System.Drawing.Size(131, 23);
            this.btnReplayResetTime.TabIndex = 13;
            this.btnReplayResetTime.Text = "Reset Time";
            this.btnReplayResetTime.UseVisualStyleBackColor = true;
            // 
            // btnReplayPause
            // 
            this.btnReplayPause.Location = new System.Drawing.Point(148, 19);
            this.btnReplayPause.Name = "btnReplayPause";
            this.btnReplayPause.Size = new System.Drawing.Size(131, 23);
            this.btnReplayPause.TabIndex = 12;
            this.btnReplayPause.Text = "Pause";
            this.btnReplayPause.UseVisualStyleBackColor = true;
            // 
            // btnReplayPlay
            // 
            this.btnReplayPlay.Location = new System.Drawing.Point(8, 19);
            this.btnReplayPlay.Name = "btnReplayPlay";
            this.btnReplayPlay.Size = new System.Drawing.Size(131, 23);
            this.btnReplayPlay.TabIndex = 11;
            this.btnReplayPlay.Text = "Play";
            this.btnReplayPlay.UseVisualStyleBackColor = true;
            // 
            // grpOptions
            // 
            this.grpOptions.Controls.Add(this.cmbTimeDisplay);
            this.grpOptions.Controls.Add(this.lblTimeDisplay);
            this.grpOptions.Controls.Add(this.cmbTimeType);
            this.grpOptions.Controls.Add(this.lblTimeType);
            this.grpOptions.Location = new System.Drawing.Point(548, 483);
            this.grpOptions.Name = "grpOptions";
            this.grpOptions.Size = new System.Drawing.Size(287, 170);
            this.grpOptions.TabIndex = 16;
            this.grpOptions.TabStop = false;
            this.grpOptions.Text = "Options";
            // 
            // cmbTimeDisplay
            // 
            this.cmbTimeDisplay.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbTimeDisplay.FormattingEnabled = true;
            this.cmbTimeDisplay.Items.AddRange(new object[] {
            "Milliseconds",
            "Seconds",
            "Formatted"});
            this.cmbTimeDisplay.Location = new System.Drawing.Point(96, 51);
            this.cmbTimeDisplay.Name = "cmbTimeDisplay";
            this.cmbTimeDisplay.Size = new System.Drawing.Size(183, 21);
            this.cmbTimeDisplay.TabIndex = 3;
            this.cmbTimeDisplay.SelectedIndexChanged += new System.EventHandler(this.cmbTimeDisplay_SelectedIndexChanged);
            // 
            // lblTimeDisplay
            // 
            this.lblTimeDisplay.AutoSize = true;
            this.lblTimeDisplay.Location = new System.Drawing.Point(6, 54);
            this.lblTimeDisplay.Name = "lblTimeDisplay";
            this.lblTimeDisplay.Size = new System.Drawing.Size(67, 13);
            this.lblTimeDisplay.TabIndex = 2;
            this.lblTimeDisplay.Text = "Time Display";
            // 
            // cmbTimeType
            // 
            this.cmbTimeType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbTimeType.FormattingEnabled = true;
            this.cmbTimeType.Items.AddRange(new object[] {
            "Exact Time",
            "Time Since First Event",
            "Time Since Previous Event"});
            this.cmbTimeType.Location = new System.Drawing.Point(96, 24);
            this.cmbTimeType.Name = "cmbTimeType";
            this.cmbTimeType.Size = new System.Drawing.Size(183, 21);
            this.cmbTimeType.TabIndex = 1;
            this.cmbTimeType.SelectedIndexChanged += new System.EventHandler(this.cmbTimeType_SelectedIndexChanged);
            // 
            // lblTimeType
            // 
            this.lblTimeType.AutoSize = true;
            this.lblTimeType.Location = new System.Drawing.Point(6, 27);
            this.lblTimeType.Name = "lblTimeType";
            this.lblTimeType.Size = new System.Drawing.Size(57, 13);
            this.lblTimeType.TabIndex = 0;
            this.lblTimeType.Text = "Time Type";
            // 
            // FormSniffBrowser
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1272, 693);
            this.Controls.Add(this.grpOptions);
            this.Controls.Add(this.grpReplayControl);
            this.Controls.Add(this.txtEndTimeDate);
            this.Controls.Add(this.txtStartTimeDate);
            this.Controls.Add(this.btnMakeWaypoints);
            this.Controls.Add(this.btnMakeScript);
            this.Controls.Add(this.btnRefresh);
            this.Controls.Add(this.txtEventDescription);
            this.Controls.Add(this.grpEventFilters);
            this.Controls.Add(this.grpObjectFilters);
            this.Controls.Add(this.lblEndTime);
            this.Controls.Add(this.txtEndTime);
            this.Controls.Add(this.lblStartTime);
            this.Controls.Add(this.txtStartTime);
            this.Controls.Add(this.lstEvents);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "FormSniffBrowser";
            this.Text = "Sniff Browser";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.grpObjectFilters.ResumeLayout(false);
            this.grpObjectFilters.PerformLayout();
            this.grpEventFilters.ResumeLayout(false);
            this.grpEventFilters.PerformLayout();
            this.grpReplayControl.ResumeLayout(false);
            this.grpOptions.ResumeLayout(false);
            this.grpOptions.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListView lstEvents;
        private System.Windows.Forms.ColumnHeader clmEventType;
        private System.Windows.Forms.ColumnHeader clmUnixTime;
        private System.Windows.Forms.ColumnHeader clmDescription;
        private System.Windows.Forms.TextBox txtStartTime;
        private System.Windows.Forms.Label lblStartTime;
        private System.Windows.Forms.Label lblEndTime;
        private System.Windows.Forms.TextBox txtEndTime;
        private System.Windows.Forms.GroupBox grpObjectFilters;
        private System.Windows.Forms.Button btnRemove;
        private System.Windows.Forms.Button btnAdd;
        private System.Windows.Forms.ListView lstObjectFilters;
        private System.Windows.Forms.ColumnHeader clmGuid;
        private System.Windows.Forms.ColumnHeader clmId;
        private System.Windows.Forms.ColumnHeader clmType;
        private System.Windows.Forms.ColumnHeader clmEvents;
        private System.Windows.Forms.Label lblObjectType;
        private System.Windows.Forms.ComboBox cmbObjectType;
        private System.Windows.Forms.Label lblId;
        private System.Windows.Forms.TextBox txtObjectId;
        private System.Windows.Forms.Label lblObjectGuid;
        private System.Windows.Forms.TextBox txtObjectGuid;
        private System.Windows.Forms.GroupBox grpEventFilters;
        private System.Windows.Forms.ListView lstEventFilters;
        private System.Windows.Forms.TextBox txtEventDescription;
        private System.Windows.Forms.Button btnRefresh;
        private System.Windows.Forms.Button btnReplayJumpToEventTime;
        private System.Windows.Forms.Button btnReplayJumpToEventSource;
        private System.Windows.Forms.Button btnMakeScript;
        private System.Windows.Forms.Button btnMakeWaypoints;
        private System.Windows.Forms.ComboBox cmbEventTypes;
        private System.Windows.Forms.Label lblEventTypes;
        private System.Windows.Forms.Button btnClear;
        private System.Windows.Forms.Button btnSelectAll;
        private System.Windows.Forms.TextBox txtStartTimeDate;
        private System.Windows.Forms.TextBox txtEndTimeDate;
        private System.Windows.Forms.GroupBox grpReplayControl;
        private System.Windows.Forms.Button btnReplayResetTime;
        private System.Windows.Forms.Button btnReplayPause;
        private System.Windows.Forms.Button btnReplayPlay;
        private System.Windows.Forms.Button btnJumpToEventTarget;
        private System.Windows.Forms.GroupBox grpOptions;
        private System.Windows.Forms.ComboBox cmbTimeDisplay;
        private System.Windows.Forms.Label lblTimeDisplay;
        private System.Windows.Forms.ComboBox cmbTimeType;
        private System.Windows.Forms.Label lblTimeType;
    }
}

