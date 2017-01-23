using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace RC5UI
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void label8_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            string parameter = "1 " + textBox1.Text + " " + textBox2.Text + " " + textBox3.Text;
            ProcesInitiator.GetProcesInitiator().InitProcess(parameter);
            ReadFileCryptedFile();
        }

        private void textBox4_TextChanged(object sender, EventArgs e)
        {

        }

        private void ReadFileCryptedFile()
        {
            string path = @"C:\Users\Lucian\Documents\Visual Studio 2015\Projects\ConsoleApplication3\RC5UI\bin\Debug\cryptedfiles.out";
            var filestream = new FileStream(path,FileMode.Open,FileAccess.Read);
            using (var readingStream = new StreamReader(filestream,Encoding.UTF8))
            {
                int i = 0;
                string line;
                while((line = readingStream.ReadLine()) != null)
                {
                    if( i == 0)
                    {
                        string[] numbers = line.Split(' ');
                        textBox4.Text = numbers[0];
                        textBox5.Text = numbers[1];
                        textBox6.Text = numbers[0];
                        textBox7.Text = numbers[1];
                        break; 
                    }
                }
            }
        }

        private void ReadDecryptedFile()
        {
            string path = @"C:\Users\Lucian\Documents\Visual Studio 2015\Projects\ConsoleApplication3\RC5UI\bin\Debug\decryptedfiles.out";
            var filestream = new FileStream(path, FileMode.Open, FileAccess.Read);
            using (var readingStream = new StreamReader(filestream, Encoding.UTF8))
            {
                int i = 0;
                string line;
                while ((line = readingStream.ReadLine()) != null)
                {
                    if (i == 0)
                    {
                        string[] numbers = line.Split(' ');
                        textBox9.Text = numbers[0];
                        textBox10.Text = numbers[1];
                        break;
                    }
                }
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            string parameter = "2 " + textBox6.Text + " " + textBox7.Text + " " + textBox8.Text;
            ProcesInitiator.GetProcesInitiator().InitProcess(parameter);
            ReadDecryptedFile();
        }

        private void textBox6_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox8_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox9_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
