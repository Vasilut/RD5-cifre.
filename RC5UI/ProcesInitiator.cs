﻿using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RC5UI
{
    sealed class ProcesInitiator
    {
        //singleton, we need a single instance for ProcesInitiator
        private static readonly ProcesInitiator _procesInitiator = new ProcesInitiator();

        public static ProcesInitiator GetProcesInitiator()
        {
            return _procesInitiator;
        }

        public void InitProcess(string arguments)
        {
            var proc = new Process();

            proc.StartInfo.FileName = @"C:\Users\Lucian\Documents\Visual Studio 2015\Projects\ConsoleApplication3\Debug\CriptografieRC5.exe";
            proc.StartInfo.UseShellExecute = true;
            //proc.StartInfo.RedirectStandardInput = true;
            proc.StartInfo.CreateNoWindow = false;
            proc.StartInfo.Arguments = arguments;
            proc.Start();
            proc.WaitForExit();
            proc.Close();
        }
    }
}
