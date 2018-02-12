using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

namespace Bitmap_CV
{
    public partial class Form1 : Form
    {
        Bitmap bmp=null;
        public Form1()
        {
            InitializeComponent();
        }

        private void btnShow_Click(object sender, EventArgs e)
        {
            bmp = CVBridge.MatConvert.Load();
            cvPicture.Width = bmp.Width;
            cvPicture.Height = bmp.Width;
            cvPicture.Image = bmp;
            
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (bmp != null)
                bmp.Dispose();
        }
    }
}
