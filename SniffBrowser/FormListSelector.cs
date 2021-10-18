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
    public partial class FormListSelector : Form
    {
        public int ReturnValue = 0;

        public FormListSelector(List<object> itemList, string title, string description)
        {
            InitializeComponent();

            Text = title;
            lblDescription.Text = description;

            foreach (var item in itemList)
            {
                listBox1.Items.Add(item.ToString());
            }
        }

        private void btnOk_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.OK;
            Close();
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
            Close();
        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (listBox1.SelectedIndices.Count == 0)
                ReturnValue = 0;
            else
                ReturnValue = listBox1.SelectedIndices[0];
        }
    }
}
