using System;
using System.Globalization;
using System.Speech.Recognition;
using System.Speech.Synthesis;
using System.IO.Ports;
using System.Threading;

namespace TalkToMe
{
    class ConsoleSpeechProgram
    {
        static SpeechSynthesizer ss = new SpeechSynthesizer();
        static SpeechRecognitionEngine sre;
        static bool done = false;
        static bool reset = false;
        static bool get = true;

        static bool green = true;
        static bool red = true;
        static bool blue = true;
        static bool black = true;

        static SerialPort port;
        static void Main(string[] args)

        {

            try
            {
                ss.SetOutputToDefaultAudioDevice();
                Console.WriteLine("\n(Speaking: I am awake)");
                ss.Speak("I am awake");

                if (port == null)
                {
                    port = new SerialPort("COM12", 9600);//Set your board COM
                    port.Open();
                }

                CultureInfo ci = new CultureInfo("en-us");
                sre = new SpeechRecognitionEngine(ci);
                sre.SetInputToDefaultAudioDevice();
                sre.SpeechRecognized += sre_SpeechRecognized;   // Calls the function whenever the speech is reckognized.

                // Create a list of Choices that 
                Choices ch_StartStopCommands = new Choices();
                ch_StartStopCommands.Add("speech on");
                ch_StartStopCommands.Add("speech off");
                ch_StartStopCommands.Add("green");
                ch_StartStopCommands.Add("red");
                ch_StartStopCommands.Add("blue");
                ch_StartStopCommands.Add("black");
                ch_StartStopCommands.Add("resetgreen");
                ch_StartStopCommands.Add("resetred");
                ch_StartStopCommands.Add("resetblue");
                ch_StartStopCommands.Add("resetblack");
                ch_StartStopCommands.Add("fuckyou");

                GrammarBuilder gb_StartStop = new GrammarBuilder();
                gb_StartStop.Append(ch_StartStopCommands);

                Grammar g_StartStop = new Grammar(gb_StartStop);
                Choices ch_Numbers = new Choices();
                GrammarBuilder gb_WhatIsXplusY = new GrammarBuilder();
                Grammar g_WhatIsXplusY = new Grammar(gb_WhatIsXplusY);
                sre.LoadGrammarAsync(g_StartStop);
                sre.LoadGrammarAsync(g_WhatIsXplusY);
                sre.RecognizeAsync(RecognizeMode.Multiple);
                while (done == false) {; }
                Console.WriteLine("\nHit <enter> to close shell\n");
                Console.ReadLine();
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                Console.ReadLine();
            }
        } // Main
        static void sre_SpeechRecognized(object sender,
          SpeechRecognizedEventArgs e)
        {
            string txt = e.Result.Text;
            float confidence = e.Result.Confidence;
            Console.WriteLine("\nRecognized: " + txt);
            if (confidence < 0.60) return;


            if (txt.IndexOf("resetgreen") >= 0)
            {
                Console.WriteLine("reset green");
                port.Write("A");
                green = true;
                reset = true;

            }
            if (txt.IndexOf("resetred") >= 0)
            {
                Console.WriteLine("reset red");
                port.Write("Q");
                red = true;
                reset = true;
            }
            if (txt.IndexOf("resetblue") >= 0)
            {
                Console.WriteLine("reset blue");
                port.Write("W");
                blue = true;
                reset = true;
            }
            if (txt.IndexOf("resetblack") >= 0)
            {
                Console.WriteLine("reset black");
                port.Write("E");
                black = true;
                reset = true;
            }

            if(!reset) { 
                if (txt.IndexOf("green") >= 0)
                {
                    if(green)
                    {
                        Console.WriteLine("get green");
                        port.Write("G");
                        green = false;
                    }
                    else
                    {
                        ss.Speak("Not there");
                    }
                }

                if (txt.IndexOf("red") >= 0)
                {
                    if(red)
                    {
                        Console.WriteLine("get red");
                        port.Write("R");
                        red = false;
                    }
                    else
                    {
                        ss.Speak("Not there");
                    }
                }
                if (txt.IndexOf("blue") >= 0)
                {
                    if(blue)
                    {
                        Console.WriteLine("get blue");
                        port.Write("B");
                        blue = false;
                    }
                    else
                    {
                        ss.Speak("Not there");
                    }
                
                }
                if (txt.IndexOf("black") >= 0)
                {
                    if(black)
                    {
                        Console.WriteLine("get black");
                        port.Write("C");
                        black = false;
                    }
                    else
                    {
                        ss.Speak("Not there");
                    }
                
                }
                
            }

            reset = false;

            if (txt.IndexOf("fuckyou") >= 0)
            {
                ss.Speak("Fuck you too");
            }

        } // sre_SpeechRecognized
    } // Program



} // ns