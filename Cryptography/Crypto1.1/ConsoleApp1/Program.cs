using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Security.Cryptography;
namespace ConsoleApplication12
{
    class Program
    {
        static void Main()
        {
            Get_rsa();
            Console.ReadKey();
        }


        static void Get_rsa()
        {
            RSA data = RSA.Create();
            string secretkey = data.ToXmlString(true);
            string publickey = data.ToXmlString(false);
            Console.WriteLine("Public key:");
            Console.WriteLine(publickey);
            Console.WriteLine("Secret key:");
            Console.WriteLine(secretkey);
        }
    }
}
