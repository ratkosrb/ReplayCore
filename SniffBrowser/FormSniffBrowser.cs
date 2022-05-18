using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows.Forms;

namespace SniffBrowser
{
    public partial class FormSniffBrowser : Form
    {
        [DllImport("user32.dll")]
        [return: MarshalAs(UnmanagedType.Bool)]
        private static extern bool ShowScrollBar(IntPtr hWnd, int wBar, bool bShow);

        private enum ScrollBarDirection
        {
            SB_HORZ = 0,
            SB_VERT = 1,
            SB_CTL = 2,
            SB_BOTH = 3
        }

        // for SMSG packets header contains uint16 size, then uint8 opcode
        // for CMSG packets header contains only the uint8 opcode

        private enum GUIOpcode
        {
            SMSG_EVENT_TYPE_LIST = 1,
            CMSG_REQUEST_EVENT_DATA = 2,
            SMSG_EVENT_DATA_LIST = 3,
            SMSG_EVENT_DATA_END = 4,
            CMSG_CHAT_COMMAND = 5,
            CMSG_GOTO_GUID = 6,
            CMSG_MAKE_SCRIPT = 7,
        }

        private Socket clientSocket;

        Dictionary<uint, string> SniffedEventTypesDict = new Dictionary<uint, string>();
        Dictionary<uint, int> SniffedEventImagesDict = new Dictionary<uint, int>();
        enum ObjectTypeFilter
        {
            Any = 0,
            GameObject = 1,
            Transport = 2,
            Unit = 3,
            Creature = 4,
            Pet = 5,
            Player = 6,
        };

        public static IEnumerable<T> GetValues<T>()
        {
            return Enum.GetValues(typeof(T)).Cast<T>();
        }

        private ObjectTypeFilter GetObjectTypeFilterValueFromString(string name)
        {
            foreach (var item in GetValues<ObjectTypeFilter>())
                if (item.ToString() == name)
                    return item;
            return ObjectTypeFilter.Any;
        }

        enum EventTypeFilter
        {
            All,
            GameObject,
            Unit,
            Creature,
            Player,
            Client,
            Miscellaneous
        }

        Color RowColor_Grey = Color.FromArgb(240, 240, 240);
        Color RowColor_GameObject = Color.FromArgb(255, 240, 240);
        Color RowColor_Creature = Color.FromArgb(240, 240, 255);
        Color RowColor_Player = Color.FromArgb(240, 255, 240);
        Color RowColor_Misc = Color.FromArgb(255, 255, 240);

        enum RowColorType
        {
            None = 0,
            Alternating = 1,
            SourceBased = 2
        }

        Dictionary<uint, EventTypeFilter> SniffedEventCategoryDict = new Dictionary<uint, EventTypeFilter>();

        class SniffedEvent
        {
            public uint uniqueIdentifier;
            public uint eventType;
            public ulong eventTime;
            public ObjectGuid sourceGuid;
            public ObjectGuid targetGuid;
            public string longDescription;
        }

        public FormSniffBrowser()
        {
            InitializeComponent();
            
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            ShowScrollBar(lstEvents.Handle, (int)ScrollBarDirection.SB_VERT, true);
            this.MinimumSize = this.Size;
            lstObjectFilters.MinimumSize = lstObjectFilters.Size;

            cmbEventTypes.DataSource = GetValues<EventTypeFilter>();
            cmbEventTypes.SelectedIndex = 0;
            cmbObjectType.DataSource = GetValues<ObjectTypeFilter>();
            cmbObjectType.SelectedIndex = 0;
            cmbTimeType.SelectedIndex = 0;
            cmbTimeDisplay.SelectedIndex = 0;
            cmbRowColors.SelectedIndex = 1;

            if (lstObjectFilters.Items.Count > 0)
            {
                lstObjectFilters.Items[0].Selected = true;
                lstObjectFilters.Select();
            }
            ImageList imageList = new ImageList { ImageSize = new Size(64, 64) };

            // 0
            imageList.Images.Add(new Bitmap(Properties.Resources.placeholder));

            // 1
            imageList.Images.Add(new Bitmap(Properties.Resources.weather_update));

            // 2
            imageList.Images.Add(new Bitmap(Properties.Resources.world_text));

            // 3
            imageList.Images.Add(new Bitmap(Properties.Resources.world_state_update));

            // 4
            imageList.Images.Add(new Bitmap(Properties.Resources.world_object_create1));

            // 5
            imageList.Images.Add(new Bitmap(Properties.Resources.world_object_create2));

            // 6
            imageList.Images.Add(new Bitmap(Properties.Resources.world_object_destroy));

            // 7
            imageList.Images.Add(new Bitmap(Properties.Resources.unit_attack_log));

            // 8
            imageList.Images.Add(new Bitmap(Properties.Resources.unit_attack_start));

            // 9
            imageList.Images.Add(new Bitmap(Properties.Resources.unit_attack_stop));

            // 10
            imageList.Images.Add(new Bitmap(Properties.Resources.unit_emote));

            // 11
            imageList.Images.Add(new Bitmap(Properties.Resources.unit_clientside_movement));

            // 12
            imageList.Images.Add(new Bitmap(Properties.Resources.unit_serverside_movement));

            // 13
            imageList.Images.Add(new Bitmap(Properties.Resources.unit_update_entry));

            // 14
            imageList.Images.Add(new Bitmap(Properties.Resources.unit_update_scale));

            // 15
            imageList.Images.Add(new Bitmap(Properties.Resources.unit_update_displayid));

            // 16
            imageList.Images.Add(new Bitmap(Properties.Resources.unit_update_mount));

            // 17
            imageList.Images.Add(new Bitmap(Properties.Resources.unit_update_faction));

            // 18
            imageList.Images.Add(new Bitmap(Properties.Resources.unit_update_level));

            // 19
            imageList.Images.Add(new Bitmap(Properties.Resources.unit_update_aurastate));

            // 20
            imageList.Images.Add(new Bitmap(Properties.Resources.unit_update_emotestate));

            // 21
            imageList.Images.Add(new Bitmap(Properties.Resources.unit_update_stand_state));

            // 22
            imageList.Images.Add(new Bitmap(Properties.Resources.unit_update_vis_flags));

            // 23
            imageList.Images.Add(new Bitmap(Properties.Resources.unit_update_sheath_state));

            // 24
            imageList.Images.Add(new Bitmap(Properties.Resources.unit_update_shapeshift_form));

            // 25
            imageList.Images.Add(new Bitmap(Properties.Resources.unit_update_npc_flags));

            // 26
            imageList.Images.Add(new Bitmap(Properties.Resources.unit_update_unit_flags));

            // 27
            imageList.Images.Add(new Bitmap(Properties.Resources.unit_update_dynamic_flags));

            // 28
            imageList.Images.Add(new Bitmap(Properties.Resources.unit_update_health));

            // 29
            imageList.Images.Add(new Bitmap(Properties.Resources.unit_update_mana));

            // 30
            imageList.Images.Add(new Bitmap(Properties.Resources.unit_update_bounding_radius));

            // 31
            imageList.Images.Add(new Bitmap(Properties.Resources.unit_update_combat_reach));

            // 32
            imageList.Images.Add(new Bitmap(Properties.Resources.unit_update_main_hand_attack_time));

            // 33
            imageList.Images.Add(new Bitmap(Properties.Resources.unit_update_off_hand_attack_time));

            // 34
            imageList.Images.Add(new Bitmap(Properties.Resources.unit_update_channel_spell));

            // 35
            imageList.Images.Add(new Bitmap(Properties.Resources.unit_update_guid_value));

            // 36
            imageList.Images.Add(new Bitmap(Properties.Resources.unit_update_speed));

            // 37
            imageList.Images.Add(new Bitmap(Properties.Resources.unit_update_auras));

            // 38
            imageList.Images.Add(new Bitmap(Properties.Resources.creature_text));

            // 39
            imageList.Images.Add(new Bitmap(Properties.Resources.unit_threat_clear));

            // 40
            imageList.Images.Add(new Bitmap(Properties.Resources.unit_threat_update));

            // 41
            imageList.Images.Add(new Bitmap(Properties.Resources.creature_equipment_update));

            // 42
            imageList.Images.Add(new Bitmap(Properties.Resources.player_chat));

            // 43
            imageList.Images.Add(new Bitmap(Properties.Resources.player_equipment_update));

            // 44
            imageList.Images.Add(new Bitmap(Properties.Resources.gameobject_custom_anim));

            // 45
            imageList.Images.Add(new Bitmap(Properties.Resources.gameobject_despawn_anim));

            // 46
            imageList.Images.Add(new Bitmap(Properties.Resources.gameobject_update_flags));

            // 47
            imageList.Images.Add(new Bitmap(Properties.Resources.gameobject_update_state));

            // 48
            imageList.Images.Add(new Bitmap(Properties.Resources.gameobject_update_artkit));

            // 49
            imageList.Images.Add(new Bitmap(Properties.Resources.gameobject_update_dynamic_flags));

            // 50
            imageList.Images.Add(new Bitmap(Properties.Resources.gameobject_update_path_progress));

            // 51
            imageList.Images.Add(new Bitmap(Properties.Resources.play_music));

            // 52
            imageList.Images.Add(new Bitmap(Properties.Resources.play_sound));

            // 53
            imageList.Images.Add(new Bitmap(Properties.Resources.play_spell_visual_kit));

            // 54
            imageList.Images.Add(new Bitmap(Properties.Resources.spell_cast_failed));

            // 55
            imageList.Images.Add(new Bitmap(Properties.Resources.spell_cast_start));

            // 56
            imageList.Images.Add(new Bitmap(Properties.Resources.spell_cast_go));

            // 57
            imageList.Images.Add(new Bitmap(Properties.Resources.client_quest_accept));

            // 58
            imageList.Images.Add(new Bitmap(Properties.Resources.client_quest_complete));

            // 59
            imageList.Images.Add(new Bitmap(Properties.Resources.client_creature_interact));

            // 60
            imageList.Images.Add(new Bitmap(Properties.Resources.client_gameobject_use));

            // 61
            imageList.Images.Add(new Bitmap(Properties.Resources.client_item_use));

            // 62
            imageList.Images.Add(new Bitmap(Properties.Resources.client_reclaim_corpse));

            // 63
            imageList.Images.Add(new Bitmap(Properties.Resources.client_release_spirit));

            // 64
            imageList.Images.Add(new Bitmap(Properties.Resources.quest_update_complete));

            // 65
            imageList.Images.Add(new Bitmap(Properties.Resources.quest_update_failed));

            // 66
            imageList.Images.Add(new Bitmap(Properties.Resources.xp_gain));

            // 67
            imageList.Images.Add(new Bitmap(Properties.Resources.faction_standing_update));

            // 68
            imageList.Images.Add(new Bitmap(Properties.Resources.login));

            // 69
            imageList.Images.Add(new Bitmap(Properties.Resources.logout));

            // 70
            imageList.Images.Add(new Bitmap(Properties.Resources.cinematic_begin));

            // 71
            imageList.Images.Add(new Bitmap(Properties.Resources.cinematic_end));

            lstEvents.SmallImageList = imageList;
            ConnectToReplayCore();
        }

        private void ConnectToReplayCore()
        {
            showdialog: FormConnectionDialog dialog = new FormConnectionDialog();
            if (dialog.ShowDialog(this) != DialogResult.OK)
                Close();

            try
            {
                clientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                // Connect to the specified host.
                var endPoint = new IPEndPoint(IPAddress.Parse(dialog.ReturnIpAddress), dialog.ReturnPort);
                clientSocket.BeginConnect(endPoint, ConnectCallback, null);
            }
            catch (Exception ex)
            {
                if (MessageBox.Show(ex.Message, "Socket Error", MessageBoxButtons.RetryCancel, MessageBoxIcon.Error) == DialogResult.Retry)
                    goto showdialog;
            }
        }

        private void ConnectCallback(IAsyncResult AR)
        {
            try
            {
                clientSocket.EndConnect(AR);
                clientSocket.ReceiveBufferSize = 65535;
                byte[] buffer = new byte[sizeof(ushort)];
                clientSocket.BeginReceive(buffer, 0, buffer.Length, SocketFlags.None, ReceiveCallback, buffer);
            }
            catch (Exception ex)
            {
                if (MessageBox.Show(ex.Message, "Connection Error", MessageBoxButtons.RetryCancel, MessageBoxIcon.Error) == DialogResult.Retry)
                    ConnectToReplayCore();
                else
                {
                    Invoke((Action)delegate
                    {
                        Close();
                    });
                }
            }
        }

        private void ReceiveCallback(IAsyncResult AR)
        {
            try
            {
                int received = clientSocket.EndReceive(AR);

                if (received == 0)
                    return;

                if (received != sizeof(ushort))
                {
                    MessageBox.Show("Received " + received + " bytes when reading header!", "Packet Read Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }

                byte[] buffer = (byte[])AR.AsyncState;
                ushort packetSize = BitConverter.ToUInt16(buffer, 0);

                if (packetSize != 0)
                {
                    if (packetSize > clientSocket.ReceiveBufferSize)
                    {
                        MessageBox.Show("Packet size is greater than max buffer size!", "Packet Read Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                        return;
                    }

                    buffer = new byte[packetSize];
                    received = 0;
                    while (received != packetSize)
                    {
                        int receivedNow = clientSocket.Receive(buffer, received, packetSize - received, SocketFlags.None);
                        if (receivedNow == 0)
                            return;

                        received += receivedNow;
                    }

                    Invoke((Action)delegate
                    {
                        HandlePacket(buffer);
                    });
                }
                else
                {
                    MessageBox.Show("Received an empty packet!", "Packet Read Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }

                buffer = new byte[sizeof(ushort)];

                // Start receiving data again.
                clientSocket.BeginReceive(buffer, 0, buffer.Length, SocketFlags.None, ReceiveCallback, buffer);
            }
            // Avoid Pokemon exception handling in cases like these.
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Packet Read Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void HandlePacket(byte[] buffer)
        {
            ByteBuffer packet = new ByteBuffer(buffer);
            byte opcode = packet.ReadUInt8();
            
            switch ((GUIOpcode)opcode)
            {
                case GUIOpcode.SMSG_EVENT_TYPE_LIST:
                {
                    SniffedEventTypesDict.Clear();

                    uint startTime = packet.ReadUInt32();
                    txtStartTime.Text = startTime.ToString();
                    uint endTime = packet.ReadUInt32();
                    txtEndTime.Text = endTime.ToString();

                    uint eventsCount = packet.ReadUInt32();
                    for (uint i = 0; i < eventsCount; i++)
                    {
                        uint eventId = packet.ReadUInt32();
                        int imageIndex = packet.ReadInt32();
                        string eventName = packet.ReadCString();
                        SniffedEventTypesDict.Add(eventId, eventName);
                        SniffedEventImagesDict.Add(eventId, imageIndex);
                        SniffedEventCategoryDict.Add(eventId, DetermineEventCategory(eventName));
                    }
                    UpdateEventTypesList();
                    btnAdd_Click(null, null);
                    break;
                }
                case GUIOpcode.SMSG_EVENT_DATA_LIST:
                {
                    uint eventsCount = packet.ReadUInt32();
                    ulong firstEventTime = 0;
                    ulong previousEventTime = 0;
                    for (uint i = 0; i < eventsCount; i++)
                    {
                        SniffedEvent eventData = new SniffedEvent();
                        eventData.uniqueIdentifier = packet.ReadUInt32();
                        eventData.eventType = packet.ReadUInt32();
                        eventData.eventTime = packet.ReadUInt64();
                        eventData.sourceGuid = new ObjectGuid(packet.ReadUInt64());
                        eventData.targetGuid = new ObjectGuid(packet.ReadUInt64());
                        string shortDescription = packet.ReadCString();
                        eventData.longDescription = packet.ReadCString();

                        if (i == 0)
                        {
                            firstEventTime = eventData.eventTime;
                            previousEventTime = eventData.eventTime;
                        }

                        ListViewItem newItem = new ListViewItem();
                        newItem.Text = "";
                        newItem.SubItems.Add(FormatTimeString(eventData.eventTime, firstEventTime, previousEventTime));
                        newItem.SubItems.Add(shortDescription);
                        newItem.ImageIndex = SniffedEventImagesDict[eventData.eventType];
                        newItem.Tag = eventData;
                        lstEvents.Items.Add(newItem);

                        previousEventTime = eventData.eventTime;
                    }
                    
                    break;
                }
                case GUIOpcode.SMSG_EVENT_DATA_END:
                {
                    Text = "Sniff Browser - Showing " + lstEvents.Items.Count.ToString() + " Events";
                    btnRefresh.Enabled = true;
                    break;
                }
            }
        }

        private void SendCallback(IAsyncResult AR)
        {
            try
            {
                clientSocket.EndSend(AR);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Packet Send Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void SendPacket(ByteBuffer packet)
        {
            try
            {
                clientSocket.BeginSend(packet.GetData(), 0, (int)packet.GetSize(), SocketFlags.None, SendCallback, null);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Packet Write Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private string FormatTimeString(ulong unixTimeMs, ulong firstEventTime, ulong previousEventTime)
        {
            ulong displayTime = 0;
            switch (cmbTimeType.SelectedIndex)
            {
                case 0: // Exact Time
                {
                    displayTime = unixTimeMs;
                    break;
                }
                case 1: // Time Since First Event
                {
                    displayTime = unixTimeMs - firstEventTime;
                    break;
                }
                case 2: // Time Since Previous Event
                {
                    displayTime = unixTimeMs - previousEventTime;
                    break;
                }
            }

            string timeString = "";
            switch (cmbTimeDisplay.SelectedIndex)
            {
                case 0: // Milliseconds
                {
                    timeString = String.Format("{0:n0}", displayTime);
                    break;
                }
                case 1: // Seconds
                {
                    displayTime = displayTime / 1000;
                    timeString = String.Format("{0:n0}", displayTime);
                    break;
                }
                case 2: // Formatted
                {
                    TimeSpan t = TimeSpan.FromMilliseconds(displayTime);
                    timeString = string.Format("{0:D2}h:{1:D2}m:{2:D2}s:{3:D3}ms",
                                    t.Hours,
                                    t.Minutes,
                                    t.Seconds,
                                    t.Milliseconds);
                    break;
                }
            }
            return timeString;
        }

        private EventTypeFilter DetermineEventCategory(string eventName)
        {
            if (eventName.StartsWith("Client"))
                return EventTypeFilter.Client;
            if (eventName.StartsWith("Player"))
                return EventTypeFilter.Player;
            if (eventName.StartsWith("Creature"))
                return EventTypeFilter.Creature;
            if (eventName.StartsWith("Unit"))
                return EventTypeFilter.Unit;
            if (eventName.StartsWith("GameObject"))
                return EventTypeFilter.GameObject;

            return EventTypeFilter.Miscellaneous;
        }

        private void UpdateEventTypesList()
        {
            lstEventFilters.Items.Clear();

            if (lstObjectFilters.SelectedItems.Count == 0)
                return;

            ListViewItem selectedObject = lstObjectFilters.SelectedItems[0];
            HashSet<uint> selectedEventTypeList = selectedObject.Tag as HashSet<uint>;

            foreach (var eventType in SniffedEventTypesDict)
            {
                if ((EventTypeFilter)cmbEventTypes.SelectedIndex != EventTypeFilter.All &&
                    SniffedEventCategoryDict[eventType.Key] != (EventTypeFilter)cmbEventTypes.SelectedIndex)
                    continue;

                ListViewItem newItem = new ListViewItem();
                newItem.Text = eventType.Value;
                newItem.Tag = eventType.Key;

                if (selectedEventTypeList.Contains(eventType.Key))
                    newItem.Checked = true;

                lstEventFilters.Items.Add(newItem);
            }
        }

        private void lstEventFilters_ItemChecked(object sender, ItemCheckedEventArgs e)
        {
            if (lstObjectFilters.SelectedItems.Count > 0)
            {
                // Get the selected item.
                ListViewItem selectedObject = lstObjectFilters.SelectedItems[0];
                HashSet<uint> selectedEventTypeList = selectedObject.Tag as HashSet<uint>;

                ListViewItem item = e.Item;
                uint eventId = (uint)item.Tag;

                if (item.Checked)
                    selectedEventTypeList.Add(eventId);
                else
                    selectedEventTypeList.Remove(eventId);

                if (selectedEventTypeList.Count == SniffedEventTypesDict.Count)
                    selectedObject.SubItems[3].Text = "All";
                else
                {
                    string eventTypesList = "";
                    foreach (var eventType in selectedEventTypeList)
                    {
                        if (!String.IsNullOrEmpty(eventTypesList))
                            eventTypesList += ", ";

                        eventTypesList += eventType.ToString();
                    }
                    selectedObject.SubItems[3].Text = eventTypesList;
                }
            }
        }

        private void cmbEventTypes_SelectedIndexChanged(object sender, EventArgs e)
        {
            UpdateEventTypesList();
        }

        private void lstObjectFilters_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (lstObjectFilters.SelectedItems.Count == 0)
            {
                grpEventFilters.Enabled = false;
                return;
            }

            grpEventFilters.Enabled = true;
            UpdateEventTypesList();
        }

        private void btnAdd_Click(object sender, EventArgs e)
        {
            uint objectGuidInt = 0;
            UInt32.TryParse(txtObjectGuid.Text, out objectGuidInt);
            uint objectIdInt = 0;
            UInt32.TryParse(txtObjectId.Text, out objectIdInt);

            string objectGuid = objectGuidInt != 0 ? objectGuidInt.ToString() : "Any";
            string objectId = objectIdInt != 0 ? objectIdInt.ToString() : "Any";
            string objectType = cmbObjectType.Text;

            foreach (ListViewItem item in lstObjectFilters.Items)
            {
                if (item.Text == objectGuid &&
                    item.SubItems[1].Text == objectId &&
                    item.SubItems[2].Text == objectType)
                {
                    MessageBox.Show("Duplicate object filter.", "Cannot add filter", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }
            }

            ListViewItem newItem = new ListViewItem();
            newItem.Text = objectGuid;
            newItem.SubItems.Add(objectId);
            newItem.SubItems.Add(objectType);

            if (lstObjectFilters.SelectedItems.Count > 0)
            {
                ListViewItem selectedItem = lstObjectFilters.SelectedItems[0];
                newItem.SubItems.Add(selectedItem.SubItems[3].Text);
                newItem.Tag = new HashSet<uint>((HashSet<uint>)selectedItem.Tag);
            }
            else
            {
                newItem.SubItems.Add("All");
                HashSet<uint> eventTypesList = new HashSet<uint>();
                foreach (var eventType in SniffedEventTypesDict)
                    eventTypesList.Add(eventType.Key);
                newItem.Tag = eventTypesList;
            }

            lstObjectFilters.Items.Add(newItem);
            lstObjectFilters.FocusedItem = newItem;
            newItem.Selected = true;
            lstObjectFilters.Select();
        }

        private void btnRemove_Click(object sender, EventArgs e)
        {
            if (lstObjectFilters.SelectedItems.Count == 0)
                return;

            grpEventFilters.Enabled = false;
            ListViewItem deleteItem = lstObjectFilters.SelectedItems[0];
            lstObjectFilters.Items.Remove(deleteItem);
        }

        private void btnRefresh_Click(object sender, EventArgs e)
        {
            Text = "Sniff Browser - Requesting Event Data";
            txtEventDescription.Text = "";
            btnRefresh.Enabled = false;
            lstEvents.Items.Clear();

            ByteBuffer packet = new ByteBuffer();
            packet.WriteUInt8((byte)GUIOpcode.CMSG_REQUEST_EVENT_DATA);
            packet.WriteUInt32(UInt32.Parse(txtStartTime.Text));
            packet.WriteUInt32(UInt32.Parse(txtEndTime.Text));
            packet.WriteUInt32((uint)lstObjectFilters.Items.Count);
            foreach (ListViewItem objectFilter in lstObjectFilters.Items)
            {
                uint objectGuid = 0;
                UInt32.TryParse(objectFilter.Text, out objectGuid);
                packet.WriteUInt32(objectGuid);

                uint objectId = 0;
                UInt32.TryParse(objectFilter.SubItems[1].Text, out objectId);
                packet.WriteUInt32(objectId);

                uint objectType = (uint)GetObjectTypeFilterValueFromString(objectFilter.SubItems[2].Text);
                packet.WriteUInt32(objectType);

                HashSet<uint> eventTypeList = objectFilter.Tag as HashSet<uint>;
                packet.WriteUInt32((uint)eventTypeList.Count);
                foreach (uint eventType in eventTypeList)
                    packet.WriteUInt32(eventType);
            }

            SendPacket(packet);
        }

        private void UpdateStartTime()
        {
            uint startUnixTime = 0;
            UInt32.TryParse(txtStartTime.Text, out startUnixTime);

            DateTime startTime = Utility.GetDateTimeFromUnixTime(startUnixTime);
            txtStartTimeDate.Text = startTime.ToString();
        }

        private void UpdateEndTime()
        {
            uint endUnixTime = 0;
            UInt32.TryParse(txtEndTime.Text, out endUnixTime);

            DateTime endTime = Utility.GetDateTimeFromUnixTime(endUnixTime);
            txtEndTimeDate.Text = endTime.ToString();
        }

        private void txtStartTime_TextChanged(object sender, EventArgs e)
        {
            UpdateStartTime();
        }

        private void txtEndTime_TextChanged(object sender, EventArgs e)
        {
            UpdateEndTime();
        }

        private void btnClear_Click(object sender, EventArgs e)
        {
            foreach (ListViewItem item in lstEventFilters.Items)
                item.Checked = false;
        }

        private void btnSelectAll_Click(object sender, EventArgs e)
        {
            foreach (ListViewItem item in lstEventFilters.Items)
                item.Checked = true;
        }


        private void lstEvents_DrawItem(object sender, DrawListViewItemEventArgs e)
        {
            e.DrawDefault = true;

            switch ((RowColorType)cmbRowColors.SelectedIndex)
            {
                case RowColorType.None:
                {
                    e.Item.BackColor = Color.White;
                    e.Item.UseItemStyleForSubItems = true;
                    return;
                }
                case RowColorType.Alternating:
                {
                    if ((e.ItemIndex % 2) == 1)
                    {
                        e.Item.BackColor = RowColor_Grey;
                        e.Item.UseItemStyleForSubItems = true;
                    }
                    return;
                }
                case RowColorType.SourceBased:
                {
                    SniffedEvent sniffedEvent = e.Item.Tag as SniffedEvent;
                    if (sniffedEvent.sourceGuid.IsEmpty())
                        e.Item.BackColor = Color.White;
                    else if (sniffedEvent.sourceGuid.GetObjectType() == ObjectType.GameObject)
                        e.Item.BackColor = RowColor_GameObject;
                    else if (sniffedEvent.sourceGuid.GetObjectType() == ObjectType.Creature)
                        e.Item.BackColor = RowColor_Creature;
                    else if (sniffedEvent.sourceGuid.GetObjectType() == ObjectType.Player)
                        e.Item.BackColor = RowColor_Player;
                    else
                        e.Item.BackColor = RowColor_Misc;
                    e.Item.UseItemStyleForSubItems = true;
                    return;
                }
            }
        }

        private void lstEvents_DrawColumnHeader(object sender, DrawListViewColumnHeaderEventArgs e)
        {
            e.DrawDefault = true;
        }

        private void lstEvents_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (lstEvents.SelectedItems.Count == 0)
            {
                txtEventDescription.Text = "";
                return;
            }

            ListViewItem selectedItem = lstEvents.SelectedItems[0];
            SniffedEvent sniffedEvent = (SniffedEvent)selectedItem.Tag;

            txtEventDescription.Text = "-- Generic Information --" + Environment.NewLine;
            txtEventDescription.Text += "Event Type: " + SniffedEventTypesDict[sniffedEvent.eventType] + Environment.NewLine;
            txtEventDescription.Text += "Event Time: " + sniffedEvent.eventTime.ToString() + " (" + Utility.GetDateTimeFromUnixTimeMs(sniffedEvent.eventTime).ToString() + ")" + Environment.NewLine;
            txtEventDescription.Text += "Source: " + sniffedEvent.sourceGuid.ToString() + Environment.NewLine;
            txtEventDescription.Text += "Target: " + sniffedEvent.targetGuid.ToString() + Environment.NewLine + Environment.NewLine;
            txtEventDescription.Text += "-- Event Specific Data --" + Environment.NewLine + sniffedEvent.longDescription;
        }

        private void lstEvents_MouseClick(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
            {
                foreach (ListViewItem item in lstEvents.Items)
                {
                    if (item.Bounds.Contains(new Point(e.X, e.Y)))
                    {
                        ContextMenu eventListContextMenu = new ContextMenu();
                        eventListContextMenu.MenuItems.Add("Copy Event Time",
                            delegate (object sender2, EventArgs e2)
                            {
                                CopyEventTime(sender, e, (SniffedEvent)item.Tag);
                            });
                        eventListContextMenu.MenuItems.Add("Copy Event Source",
                            delegate (object sender2, EventArgs e2)
                            {
                                CopyEventSource(sender, e, (SniffedEvent)item.Tag);
                            });
                        eventListContextMenu.MenuItems.Add("Copy Event Target",
                            delegate (object sender2, EventArgs e2)
                            {
                                CopyEventTarget(sender, e, (SniffedEvent)item.Tag);
                            });
                        eventListContextMenu.MenuItems.Add("Remove This Event",
                            delegate (object sender2, EventArgs e2)
                            {
                                lstEvents.Items.Remove(item);
                            });
                        eventListContextMenu.MenuItems.Add("Remove This Source",
                           delegate (object sender2, EventArgs e2)
                           {
                               RemoveEventsWithSource(sender, e, ((SniffedEvent)item.Tag).sourceGuid);
                           });
                        eventListContextMenu.MenuItems.Add("Remove This Target",
                           delegate (object sender2, EventArgs e2)
                           {
                               RemoveEventsWithTarget(sender, e, ((SniffedEvent)item.Tag).targetGuid);
                           });
                        eventListContextMenu.Show(lstEvents, new Point(e.X, e.Y));
                        break;
                    }
                }
            }
        }

        private void SetObjectFilterFieldsFromGuid(ObjectGuid guid)
        {
            int index = (int)GetObjectTypeFilterValueFromString(guid.GetObjectType().ToString());
            cmbObjectType.SelectedIndex = index;
            txtObjectGuid.Text = guid.GetCounter().ToString();
            txtObjectId.Text = guid.GetEntry().ToString();
        }

        private void CopyEventTime(object sender, MouseEventArgs e, SniffedEvent sniffedEvent)
        {
            string unixTime = (sniffedEvent.eventTime / 1000).ToString();
            txtStartTime.Text = unixTime;
            txtEndTime.Text = unixTime;
        }

        private void CopyEventSource(object sender, MouseEventArgs e, SniffedEvent sniffedEvent)
        {
            if (sniffedEvent.sourceGuid.IsEmpty())
            {
                MessageBox.Show("Event has no source!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            SetObjectFilterFieldsFromGuid(sniffedEvent.sourceGuid);
        }

        private void CopyEventTarget(object sender, MouseEventArgs e, SniffedEvent sniffedEvent)
        {
            if (sniffedEvent.targetGuid.IsEmpty())
            {
                MessageBox.Show("Event has no target!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            SetObjectFilterFieldsFromGuid(sniffedEvent.targetGuid);
        }

        private void RemoveEventsWithSource(object sender, MouseEventArgs e, ObjectGuid sourceGuid)
        {
            if (sourceGuid.IsEmpty())
            {
                MessageBox.Show("Event has no source!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            List<ListViewItem> itemsToRemove = new List<ListViewItem>();
            for (int i = 0; i < lstEvents.Items.Count; i++)
            {
                SniffedEvent sniffedEvent = (SniffedEvent)lstEvents.Items[i].Tag;
                if (sniffedEvent.sourceGuid == sourceGuid)
                    itemsToRemove.Add(lstEvents.Items[i]);
            }

            foreach (var item in itemsToRemove)
                lstEvents.Items.Remove(item);
        }

        private void RemoveEventsWithTarget(object sender, MouseEventArgs e, ObjectGuid targetGuid)
        {
            if (targetGuid.IsEmpty())
            {
                MessageBox.Show("Event has no target!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            List<ListViewItem> itemsToRemove = new List<ListViewItem>();
            for (int i = 0; i < lstEvents.Items.Count; i++)
            {
                SniffedEvent sniffedEvent = (SniffedEvent)lstEvents.Items[i].Tag;
                if (sniffedEvent.targetGuid == targetGuid)
                    itemsToRemove.Add(lstEvents.Items[i]);
            }

            foreach (var item in itemsToRemove)
                lstEvents.Items.Remove(item);
        }

        private void lstEvents_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyData == (Keys.A | Keys.Control))
                foreach (ListViewItem item in lstEvents.Items)
                    item.Selected = true;
        }

        private void UpdateTimeDisplayForAllEvents()
        {
            ulong firstEventTime = 0;
            ulong previousEventTime = 0;
            for (int i = 0; i < lstEvents.Items.Count; i++)
            {
                ListViewItem lvi = lstEvents.Items[i];
                SniffedEvent sniffedEvent = (SniffedEvent)lvi.Tag;

                if (i == 0)
                {
                    firstEventTime = sniffedEvent.eventTime;
                    previousEventTime = sniffedEvent.eventTime;
                }

                lvi.SubItems[1].Text = FormatTimeString(sniffedEvent.eventTime, firstEventTime, previousEventTime);
                previousEventTime = sniffedEvent.eventTime;
            }
        }

        private void cmbTimeType_SelectedIndexChanged(object sender, EventArgs e)
        {
            UpdateTimeDisplayForAllEvents();
        }

        private void cmbTimeDisplay_SelectedIndexChanged(object sender, EventArgs e)
        {
            UpdateTimeDisplayForAllEvents();
        }

        // Replay Controls

        private void SendChatCommand(string command)
        {
            ByteBuffer packet = new ByteBuffer();
            packet.WriteUInt8((byte)GUIOpcode.CMSG_CHAT_COMMAND);
            packet.WriteCString(command);
            SendPacket(packet);
        }

        private void btnReplayPlay_Click(object sender, EventArgs e)
        {
            SendChatCommand("play");
        }

        private void btnReplayPause_Click(object sender, EventArgs e)
        {
            SendChatCommand("stop");
        }

        private void btnReplayResetTime_Click(object sender, EventArgs e)
        {
            SendChatCommand("resettime");
        }

        private void btnReplayGoToClientPosition_Click(object sender, EventArgs e)
        {
            SendChatCommand("gotoclient");
        }

        private void btnReplaySkipTime_Click(object sender, EventArgs e)
        {
            string seconds = "10";
            if (Utility.ShowInputDialog(ref seconds, "Seconds to skip") != DialogResult.OK)
                return;

            SendChatCommand("skiptime " + seconds);
        }

        private void btnReplayJumpToEventTime_Click(object sender, EventArgs e)
        {
            if (lstEvents.SelectedItems.Count == 0)
            {
                MessageBox.Show("No event selected.");
                return;
            }

            ListViewItem selectedItem = lstEvents.SelectedItems[0];
            SniffedEvent sniffedEvent = (SniffedEvent)selectedItem.Tag;
            uint unixTime = (uint)(sniffedEvent.eventTime / 1000);
            SendChatCommand("settime " + unixTime.ToString());
        }

        private void SendTeleportToGuid(ObjectGuid guid)
        {
            ByteBuffer packet = new ByteBuffer();
            packet.WriteUInt8((byte)GUIOpcode.CMSG_GOTO_GUID);
            packet.WriteUInt64(guid.RawGuid);
            SendPacket(packet);
        }

        private void btnReplayJumpToEventSource_Click(object sender, EventArgs e)
        {
            if (lstEvents.SelectedItems.Count == 0)
            {
                MessageBox.Show("No event selected.");
                return;
            }

            ListViewItem selectedItem = lstEvents.SelectedItems[0];
            SniffedEvent sniffedEvent = (SniffedEvent)selectedItem.Tag;

            if (sniffedEvent.sourceGuid.IsEmpty())
            {
                MessageBox.Show("Event has no source.");
                return;
            }

            SendTeleportToGuid(sniffedEvent.sourceGuid);
        }

        private void btnReplayJumpToEventTarget_Click(object sender, EventArgs e)
        {
            if (lstEvents.SelectedItems.Count == 0)
            {
                MessageBox.Show("No event selected.");
                return;
            }

            ListViewItem selectedItem = lstEvents.SelectedItems[0];
            SniffedEvent sniffedEvent = (SniffedEvent)selectedItem.Tag;

            if (sniffedEvent.targetGuid.IsEmpty())
            {
                MessageBox.Show("Event has no target.");
                return;
            }

            SendTeleportToGuid(sniffedEvent.targetGuid);
        }

        // Script And Waypoint Making

        private void btnMakeScript_Click(object sender, EventArgs e)
        {
            if (lstEvents.SelectedItems.Count == 0)
            {
                MessageBox.Show("No event selected.");
                return;
            }

            string mainScriptIdStr = "1";
            if (Utility.ShowInputDialog(ref mainScriptIdStr, "Main Script Id") != DialogResult.OK)
                return;
            uint mainScriptId = UInt32.Parse(mainScriptIdStr);

            string genericScriptIdStr = "50000";
            if (Utility.ShowInputDialog(ref genericScriptIdStr, "Generic Script Id") != DialogResult.OK)
                return;
            uint genericScriptId = UInt32.Parse(genericScriptIdStr);

            string tableName = "generic_scripts";
            if (Utility.ShowInputDialog(ref tableName, "Table Name") != DialogResult.OK)
                return;

            string commentPrefix = "";
            if (Utility.ShowInputDialog(ref commentPrefix, "Comment Prefix") != DialogResult.OK)
                return;

            bool hasGameObjectSpawn = false;
            List<object> guidList = new List<object>();
            guidList.Add(ObjectGuid.Empty);
            foreach (ListViewItem lvi in lstEvents.SelectedItems)
            {
                SniffedEvent sniffedEvent = (SniffedEvent)lvi.Tag;
                if (!sniffedEvent.sourceGuid.IsEmpty() &&
                    !guidList.Contains(sniffedEvent.sourceGuid))
                {
                    guidList.Add(sniffedEvent.sourceGuid);
                }
                if (!sniffedEvent.targetGuid.IsEmpty() &&
                    !guidList.Contains(sniffedEvent.targetGuid))
                {
                    guidList.Add(sniffedEvent.targetGuid);
                }
                if (sniffedEvent.sourceGuid.GetObjectType() == ObjectType.GameObject &&
                    lvi.SubItems[2].Text.Contains("spawns"))
                    hasGameObjectSpawn = true;
            }

            FormListSelector frmListSelector1 = new FormListSelector(guidList, "Make Script", "Select source object:");
            if (frmListSelector1.ShowDialog() != DialogResult.OK)
                return;

            ObjectGuid sourceGuid = (ObjectGuid)guidList[frmListSelector1.ReturnValue];

            FormListSelector frmListSelector2 = new FormListSelector(guidList, "Make Script", "Select target object:");
            if (frmListSelector2.ShowDialog() != DialogResult.OK)
                return;

            byte saveGameObjectSpawnsToDatabase = 0;
            if (hasGameObjectSpawn &&
                MessageBox.Show("Save gameobject spawns to database?", "Make Script", MessageBoxButtons.YesNo) == DialogResult.Yes)
                saveGameObjectSpawnsToDatabase = 1;

            ObjectGuid targetGuid = (ObjectGuid)guidList[frmListSelector1.ReturnValue];

            ByteBuffer packet = new ByteBuffer();
            packet.WriteUInt8((byte)GUIOpcode.CMSG_MAKE_SCRIPT);
            packet.WriteUInt32(mainScriptId);
            packet.WriteUInt32(genericScriptId);
            packet.WriteCString(tableName);
            packet.WriteCString(commentPrefix);
            packet.WriteUInt64(sourceGuid.RawGuid);
            packet.WriteUInt64(targetGuid.RawGuid);
            packet.WriteUInt8(saveGameObjectSpawnsToDatabase);
            packet.WriteUInt32((uint)lstEvents.SelectedItems.Count);
            foreach (ListViewItem lvi in lstEvents.SelectedItems)
            {
                SniffedEvent sniffedEvent = (SniffedEvent)lvi.Tag;
                packet.WriteUInt32(sniffedEvent.uniqueIdentifier);
            }
            SendPacket(packet);
        }

        private void btnMakeWaypoints_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Not Yet Implemented");
        }

        private void FormSniffBrowser_ResizeEnd(object sender, EventArgs e)
        {
            lstEvents.Size = new Size(lstEvents.MinimumSize.Width + (this.Size.Width - this.MinimumSize.Width), lstEvents.MinimumSize.Height + (this.Size.Height - this.MinimumSize.Height));
            lstEvents.Columns[2].Width = 622 + (this.Size.Width - this.MinimumSize.Width);
            txtEventDescription.Size = new Size(txtEventDescription.MinimumSize.Width + (this.Size.Width - this.MinimumSize.Width), txtEventDescription.Size.Height);
            txtEventDescription.Location = new Point(txtEventDescription.Location.X, lstEvents.Location.Y + lstEvents.Size.Height + 6);
            btnMakeScript.Location = new Point(btnMakeScript.Location.X, txtEventDescription.Location.Y + txtEventDescription.Size.Height + 10);
            btnMakeWaypoints.Location = new Point(btnMakeWaypoints.Location.X, txtEventDescription.Location.Y + txtEventDescription.Size.Height + 10);
            grpOptions.Location = new Point(txtEventDescription.Location.X + txtEventDescription.Size.Width + 6, txtEventDescription.Location.Y);
            grpReplayControl.Location = new Point(grpOptions.Location.X, grpOptions.Location.Y + grpOptions.Size.Height + 6);
            lblStartTime.Location = new Point(lstEvents.Location.X + lstEvents.Size.Width + 11, lblStartTime.Location.Y);
            lblEndTime.Location = new Point(lstEvents.Location.X + lstEvents.Size.Width + 14, lblEndTime.Location.Y);
            txtStartTime.Location = new Point(lblStartTime.Location.X + lblStartTime.Size.Width + 6, txtStartTime.Location.Y);
            txtEndTime.Location = new Point(lblEndTime.Location.X + lblEndTime.Size.Width + 6, txtEndTime.Location.Y);
            txtStartTimeDate.Location = new Point(txtStartTime.Location.X + txtStartTime.Size.Width + 6, txtStartTimeDate.Location.Y);
            txtEndTimeDate.Location = new Point(txtEndTime.Location.X + txtEndTime.Size.Width + 6, txtEndTimeDate.Location.Y);
            grpObjectFilters.Location = new Point(lstEvents.Location.X + lstEvents.Size.Width + 17, grpObjectFilters.Location.Y);
            grpObjectFilters.Size = new Size(grpObjectFilters.Size.Width, grpObjectFilters.MinimumSize.Height + (this.Size.Height - this.MinimumSize.Height));
            lstObjectFilters.Size = new Size(lstObjectFilters.Size.Width, lstObjectFilters.MinimumSize.Height + (this.Size.Height - this.MinimumSize.Height));
            grpEventFilters.Location = new Point(lstEvents.Location.X + lstEvents.Size.Width + 17, grpObjectFilters.Location.Y + grpObjectFilters.Size.Height + 6);
            btnRefresh.Location = new Point(this.Size.Width - 93, btnMakeScript.Location.Y);
        }

        FormWindowState LastWindowState = FormWindowState.Minimized;
        private void FormSniffBrowser_Resize(object sender, EventArgs e)
        {
            if (WindowState != LastWindowState)
            {
                LastWindowState = WindowState;
                FormSniffBrowser_ResizeEnd(sender, e);
            }
        }
    }
}
