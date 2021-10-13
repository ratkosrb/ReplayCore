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

        private enum GUIOpcode
        {
            SMSG_EVENT_TYPE_LIST = 1,
            CMSG_REQUEST_EVENT_DATA = 2,
            SMSG_EVENT_DATA_LIST = 3,
            SMSG_EVENT_DATA_END = 4,
            CMSG_SET_TIME = 5,
            CMSG_GOTO_GUID = 6,
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

        class SniffedEvent
        {
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
            cmbEventTypes.DataSource = GetValues<EventTypeFilter>();
            cmbEventTypes.SelectedIndex = 0;
            cmbObjectType.DataSource = GetValues<ObjectTypeFilter>();
            cmbObjectType.SelectedIndex = 0;
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
                byte[] buffer = new byte[clientSocket.ReceiveBufferSize];
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
                {
                    return;
                }

                byte[] buffer = (byte[])AR.AsyncState;

                Invoke((Action)delegate
                {
                    HandlePacket(buffer);
                });

                buffer = new byte[clientSocket.ReceiveBufferSize];

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
            uint opcode = packet.ReadUInt32();
            
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
                    }
                    UpdateEventTypesList();
                    btnAdd_Click(null, null);
                    break;
                }
                case GUIOpcode.SMSG_EVENT_DATA_LIST:
                {
                    uint eventsCount = packet.ReadUInt32();
                    for (uint i = 0; i < eventsCount; i++)
                    {
                        SniffedEvent eventData = new SniffedEvent();
                        eventData.eventType = packet.ReadUInt32();
                        eventData.eventTime = packet.ReadUInt64();
                        eventData.sourceGuid = new ObjectGuid(packet.ReadUInt64());
                        eventData.targetGuid = new ObjectGuid(packet.ReadUInt64());
                        string shortDescription = packet.ReadCString();
                        eventData.longDescription = packet.ReadCString();

                        ListViewItem newItem = new ListViewItem();
                        newItem.Text = "";
                        newItem.SubItems.Add(String.Format("{0:n0}", eventData.eventTime));
                        newItem.SubItems.Add(shortDescription);
                        newItem.ImageIndex = SniffedEventImagesDict[eventData.eventType];
                        newItem.Tag = eventData;
                        lstEvents.Items.Add(newItem);
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

        private void UpdateEventTypesList()
        {
            lstEventFilters.Items.Clear();

            if (lstObjectFilters.SelectedItems.Count == 0)
                return;

            ListViewItem selectedObject = lstObjectFilters.SelectedItems[0];
            HashSet<uint> selectedEventTypeList = selectedObject.Tag as HashSet<uint>;

            foreach (var eventType in SniffedEventTypesDict)
            {
                bool isGameObject = eventType.Value.Contains("GameObject");
                bool isUnit = eventType.Value.Contains("Unit");
                bool isCreature = eventType.Value.Contains("Creature");
                bool isPlayer = eventType.Value.Contains("Player");
                bool isClient = eventType.Value.Contains("Client");

                switch ((EventTypeFilter)cmbEventTypes.SelectedIndex)
                {
                    case EventTypeFilter.All:
                    {
                        break;
                    }
                    case EventTypeFilter.GameObject:
                    {
                        if (!isGameObject)
                            continue;
                        break;
                    }
                    case EventTypeFilter.Unit:
                    {
                        if (!isUnit)
                            continue;
                        break;
                    }
                    case EventTypeFilter.Creature:
                    {
                        if (!isCreature)
                            continue;
                        break;
                    }
                    case EventTypeFilter.Player:
                    {
                        if (!isPlayer)
                            continue;
                        break;
                    }
                    case EventTypeFilter.Client:
                    {
                        if (!isClient)
                            continue;
                        break;
                    }
                    case EventTypeFilter.Miscellaneous:
                    {
                        if (isGameObject || isUnit || isCreature || isPlayer || isClient)
                            continue;
                        break;
                    }
                }

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
            newItem.SubItems.Add("All");

            HashSet<uint> eventTypesList = new HashSet<uint>();
            foreach (var eventType in SniffedEventTypesDict)
                eventTypesList.Add(eventType.Key);
            newItem.Tag = eventTypesList;

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
            packet.WriteUInt32((uint)GUIOpcode.CMSG_REQUEST_EVENT_DATA);
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

        private void btnJumpToEventTime_Click(object sender, EventArgs e)
        {
            if (lstEvents.SelectedItems.Count == 0)
            {
                MessageBox.Show("No event selected.");
                return;
            }

            ListViewItem selectedItem = lstEvents.SelectedItems[0];
            SniffedEvent sniffedEvent = (SniffedEvent)selectedItem.Tag;
            uint unixTime = (uint)(sniffedEvent.eventTime / 1000);

            ByteBuffer packet = new ByteBuffer();
            packet.WriteUInt32((uint)GUIOpcode.CMSG_SET_TIME);
            packet.WriteUInt32(unixTime);
            SendPacket(packet);
        }

        private void btnJumpToEventSource_Click(object sender, EventArgs e)
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

            ByteBuffer packet = new ByteBuffer();
            packet.WriteUInt32((uint)GUIOpcode.CMSG_GOTO_GUID);
            packet.WriteUInt64(sniffedEvent.sourceGuid.RawGuid);
            SendPacket(packet);
        }
    }
}
