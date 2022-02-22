using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Threading;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace lab_7_sp_winforms
{
    public partial class Form1 : Form
    {
        private bool paused = false;

        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Thread thread = new Thread(new ThreadStart(show));
            thread.Start();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (!paused) button2.Text = "Продолжить";
            else button2.Text = "Пауза";
            paused = !paused;
        }

        void pause()
        {
            while (paused) ;
            return;
        }

        void show()
        {
                Graphics dc = pictureBox1.CreateGraphics();
                dc.Clear(Color.White);
                Bitmap bm = new Bitmap("C:\\Users\\user\\source\\repos\\lab_7_sp\\lab_7_sp_winforms\\lab_7_sp_winforms\\bengalskaja-koshka-1.jpg");
                if (paused) pause();
                // label1.Text = "Бенгальская кошка";
                label1.BeginInvoke((MethodInvoker)(() => label1.Text = "Бенгальская кошка"));
                for (int i = 10; i > 0; --i)
                {
                    dc.DrawImage(bm, 0, 0, 500 / i, 400 / i);
                    Thread.Sleep(500);
                }
                bm.Dispose();
                if (paused) pause();
                Thread.Sleep(3000);
                if (paused) pause();
                dc.Clear(Color.White);
                bm = new Bitmap("C:\\Users\\user\\source\\repos\\lab_7_sp\\lab_7_sp_winforms\\lab_7_sp_winforms\\british-2.jpg");
                // label1.Text = "Британская кошка";
                label1.BeginInvoke((MethodInvoker)(() => label1.Text = "Британская кошка"));
                for (int i = 10; i > 0; --i)
                {
                    dc.DrawImage(bm, 0, 0, 500 / i, 400 / i);
                    Thread.Sleep(500);
                }
                if (paused) pause();
                Thread.Sleep(3000);
                if (paused) pause();
                dc.Clear(Color.White);
                bm = new Bitmap("C:\\Users\\user\\source\\repos\\lab_7_sp\\lab_7_sp_winforms\\lab_7_sp_winforms\\coon-3.png");
                // label1.Text = "Мейн-кун";
                label1.BeginInvoke((MethodInvoker)(() => label1.Text = "Мейн-кун"));
                for (int i = 10; i > 0; --i)
                {
                    dc.DrawImage(bm, 0, 0, 500 / i, 400 / i);
                    Thread.Sleep(500);
                }
                bm.Dispose();
                if (paused) pause();
                Thread.Sleep(3000);
                bm.Dispose();
                if (paused) pause();
        }
    }
}