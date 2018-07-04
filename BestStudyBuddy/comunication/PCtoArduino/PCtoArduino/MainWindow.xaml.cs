using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

using System.IO.Ports;
using System.Threading;


namespace PCtoArduino
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        SerialPort port;
        public MainWindow()
        {

            InitializeComponent();
            //this. += new FormClosedEventHandler(Form1_FormClosed);
            if (port == null)
            {
                port = new SerialPort("COM5", 9600);//Set your board COM
                port.Open();
            }

        }


        private void Button_Click(object sender, RoutedEventArgs e)
        {
            port.Write("G\n");
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            port.Write("R\n");
        }

        private void Button_Click_2(object sender, RoutedEventArgs e)
        {
            port.Write("B\n");
        }

        private void Button_Click_3(object sender, RoutedEventArgs e)
        {
            port.Write("C\n");
        }
    }
}
