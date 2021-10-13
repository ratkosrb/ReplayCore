using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace SniffBrowser
{
    public partial class FormConnectionDialog : Form
    {
        public string ReturnIpAddress = "127.0.0.1";
        public int ReturnPort = 3800;
        public FormConnectionDialog()
        {
            InitializeComponent();
        }

        private void btnConnect_Click(object sender, EventArgs e)
        {
            ReturnIpAddress = txtIpAddress.Text;
            ReturnPort = Int32.Parse(txtPort.Text);

            DialogResult = DialogResult.OK;
            Close();
        }
    }
}
