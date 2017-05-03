using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Text.RegularExpressions;
using System.Diagnostics;


namespace hw4
{
    public partial class Form1 : Form
    {
        int click = 0;
        public Form1()
        {
            InitializeComponent();
        }

        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {
           
        }

        private void richTextBox2_TextChanged(object sender, EventArgs e)
        {

        }
        //string to int
        private void button1_Click(object sender, EventArgs e)
        {
            richTextBox2.Text = null;
            search a = new search();
            string input = richTextBox1.Text;
            int len = 0;
            int temp = 0;
            string[] sarray = Regex.Split(input, " ", RegexOptions.IgnoreCase);
            foreach (string i in sarray) ;
          
            len = sarray.Length;
            int[] s = new int[len];
         
            for (int i = 0; i < len; i++)
            {
                Int32.TryParse(sarray[i], out temp);
                s[i] = temp;
                temp = 0;
            }
               
            a.len = len;
            a.s = s;
           
            Stopwatch time = new Stopwatch();
            time.Start(); 
            int[] sub = a.largesub(s, len);
            int sublen = sub.Length;
            time.Stop();
            for (int i = sub.Length - 1; i > 0; i--)
            {
                if (sub[i] == 0)
                    sublen--;
            }
            
            if (click > 0)
            {
                for (int i = 1; i < sublen; i++)
                    richTextBox2.Text = richTextBox2.Text + "  " + sub[i].ToString();
                textBox2.Text = (sublen - 1).ToString();
            }
            else
            {
                for (int i = 1; i < sublen; i++)
                    richTextBox2.Text = richTextBox2.Text + " " + sub[i].ToString();
                textBox2.Text = (sublen - 1).ToString();
            }
            float elapse = (time.ElapsedTicks / (float)Stopwatch.Frequency) * 1000000;
            time.Reset();
            textBox1.Text =elapse.ToString("f4");
        }

        private void button2_Click(object sender, EventArgs e)
        {
            richTextBox1.Text = null;
            richTextBox2.Text = null;
            textBox1.Text = textBox2.Text = textBox3.Text = textBox4.Text = null;
            click++;
        }

        private void label7_Click(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button3_Click(object sender, EventArgs e)
        {
            richTextBox1.Text = null;
            int rand = 0;
            int maxrand = 0;
            Int32.TryParse(textBox3.Text, out rand);
            Int32.TryParse(textBox4.Text, out maxrand);
            Random r = new Random();
            for (int i = 0; i < rand; i++)
                richTextBox1.Text = richTextBox1.Text + " " + (r.Next(1, maxrand)).ToString();
        }
        
    }
}
