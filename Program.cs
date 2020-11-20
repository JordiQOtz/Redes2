using System;
using System.Collections.Generic;
using System.IO;
using System.Threading;
using OpenCvSharp;

namespace Practica1
{
    public class FilasHilo
    {
        public int Filas { get; set; }
        public int Inicio { get; set; }
        public int Fin { get; set; }
    }

    public class Parte2
    {
        Dictionary<Thread, FilasHilo> Hilos;
        Random r = new Random();
        int[,] A;
        int[,] B;
        int[,] C;
        int nHilos;

        public void Multiplicar(object nFilas)
        {
            FilasHilo n = (FilasHilo)nFilas;
            if (n.Filas > 0)
            {
                for (int i = n.Inicio; i <= n.Fin; i++)
                {
                    for (int j = 0; j < B.GetLength(1); j++)
                    {
                        for (int k = 0; k < B.GetLength(0); k++)
                        {
                            C[i, j] += A[i, k] * B[k, j];
                        }
                    }
                }
            }
        }

        public void LlenarMatrices()
        {
            for (int i = 0; i < A.GetLength(0); i++)
            {
                for (int j = 0; j < A.GetLength(1); j++)
                {
                    A[i, j] = r.Next(100);
                }
            }
            for (int i = 0; i < B.GetLength(0); i++)
            {
                for (int j = 0; j < B.GetLength(1); j++)
                {
                    B[i, j] = r.Next(100);
                }
            }
            for (int i = 0; i < C.GetLength(0); i++)
            {
                for (int j = 0; j < C.GetLength(1); j++)
                {
                    C[i, j] = 0;
                }
            }
        }

        public Parte2()
        {
            Hilos = new Dictionary<Thread, FilasHilo>();
            A = new int[2000, 1500];
            B = new int[1500, 2000];
            C = new int[A.GetLength(0), B.GetLength(1)];
            LlenarMatrices();
            Console.Write("Numero de hilos: ");
            nHilos = Convert.ToInt32(Console.ReadLine()); 
            int dFilas = (C.GetLength(0) + nHilos - 1) / nHilos;
            int cFilas = 0;
            System.Diagnostics.Stopwatch watch = System.Diagnostics.Stopwatch.StartNew();
            for (int i = 0; i < nHilos; i++)
            {
                Thread t = new Thread(Multiplicar);
                FilasHilo n = new FilasHilo();
                if (cFilas + dFilas < C.GetLength(0))
                {
                    n.Inicio = cFilas;
                    n.Fin = cFilas + dFilas - 1;
                    n.Filas = dFilas;
                    cFilas += dFilas;
                    Console.WriteLine("Al hilo {0} le corresponden {1} filas. Comienza en la fila {2} y termina en la fila {3}", i + 1, n.Filas, n.Inicio, n.Fin);
                }
                else
                {
                    n.Inicio = C.GetLength(0) - cFilas;
                    n.Fin = cFilas + C.GetLength(0) - cFilas - 1;
                    n.Filas = C.GetLength(0) - cFilas;
                    cFilas += C.GetLength(0) - cFilas;
                    Console.WriteLine("Al hilo {0} le corresponden {1} filas. Comienza en la fila {2} y termina en la fila {3}", i + 1, n.Filas, n.Inicio, n.Fin);
                }
                Hilos.Add(t, n);
                t.Start(n);
            }
            foreach (Thread t in Hilos.Keys)
            {
                t.Join();
            }
            watch.Stop();
            long elapsedMs = watch.ElapsedMilliseconds;
            Console.WriteLine("\nTiempo con {0} hilos: {1}s", nHilos, elapsedMs/1000.0);
        }
    }

    public class Parte1
    {
        string[] imagenes;
        List<Thread> Hilos;

        private void ModificarImagen(object imagePath)
        {
            Mat img = Cv2.ImRead((string)imagePath, ImreadModes.Color);
            Mat R = img.Clone();
            Mat G = img.Clone();
            Mat B = img.Clone();
            for (int y = 0; y < img.Height; y++)
            {
                for (int x = 0; x < img.Width; x++)
                {
                    Vec3b colorR = R.Get<Vec3b>(y, x);
                    Vec3b colorG = G.Get<Vec3b>(y, x);
                    Vec3b colorB = B.Get<Vec3b>(y, x);
                    colorR.Item2 = 255;
                    colorG.Item1 = 255;
                    colorB.Item0 = 255;
                    R.Set<Vec3b>(y, x, colorR);
                    G.Set<Vec3b>(y, x, colorG);
                    B.Set<Vec3b>(y, x, colorB);
                }
            }
            Cv2.ImWrite("../../../Imagenes/" + Path.GetFileNameWithoutExtension((string)imagePath) + "R.jpg", R);
            Cv2.ImWrite("../../../Imagenes/" + Path.GetFileNameWithoutExtension((string)imagePath) + "G.jpg", G);
            Cv2.ImWrite("../../../Imagenes/" + Path.GetFileNameWithoutExtension((string)imagePath) + "B.jpg", B);
        }

        public Parte1()
        {
            Hilos = new List<Thread>();
            imagenes = Directory.GetFiles("../../../Imagenes");
            foreach(string path in imagenes)
            {
                Thread t = new Thread(ModificarImagen);
                Hilos.Add(t);
                t.Start(path);
            }
            foreach(Thread hilo in Hilos)
            {
                hilo.Join();
            }
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            int opt = 0;
            Console.WriteLine("Opciones:\n\t1.- Inciso 1\n\t2.- Inciso 2\n");
            Console.Write("Opcion: ");
            opt = Convert.ToInt32(Console.ReadLine());
            if (opt == 1)
            {
                Parte1 p1 = new Parte1();
            }
            else if (opt == 2)
            {
                Parte2 p2 = new Parte2();
            }
        }
    }
}
