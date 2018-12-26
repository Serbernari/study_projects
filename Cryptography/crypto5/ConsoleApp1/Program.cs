using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Drawing;
using System.Security.Cryptography;
using System.Xml;
namespace ConsoleApplication12
{

    class Program
    {

        static void Main()
        {
            string publicKey = "<RSAKeyValue><Modulus>xZSebMx5zUjPsQ45snc0R2iMOdoUnNz4nin8tN5/eHfut7tq+uqLz02YlPwA14tFnHWxuY520+DtXRi8beJ+7Fyk2AGLeEtRnJ9xkoMpT9iyPU207w/P9M9fia9e0oZ4pQEQ5w8nUjyUIsfAWOXW1EXewRiDGCCI9f6KvPVTRhE=</Modulus><Exponent>AQAB</Exponent></RSAKeyValue>";
            string secretKey = "<RSAKeyValue><Modulus>lk5div6UsXmK5BBexmrgp3Oc5KoSd9gLS6K5G1nX6auRac24n0jDw7lFwP2rbEIT8Q7O7/E7ADboQRsgjuDj+3GeYucfCwDtmkfKmyNz1VUjOUje1VbYn7QmiYASzLdcuGbpWavRoX9GYSPg2fKAWRiSueD4TPbwUFzgf8UAs5U=</Modulus><Exponent>AQAB</Exponent><P>wZ6ffjgdIYxw8yDzJnwP3r7MCsUST0D48TFAxnxcWFWw/R8zlFjnblUHniwPMQuwwE3OMp7pEbGohgNfodBwKw==</P><Q>xrtTtwprJryyquQehlVjPxjrZ8H8uVG/adpvpKEmNqQT0n/aKWiqQ+BdBsNq/pDbxbRziS3eIGBG2PuXyMnLPw==</Q><DP>ZCBGdHxKPEYnRuO8OiOgBV1/oPYmsMt1sSz6RWqcSqYNv+g5wTZ0f+8C4H4CYSedgOT7g9v/xUGtV5g5BTIIPw==</DP><DQ>xRN51lfnoLeaOuwT9UVyMV1l/TQbii+uMavj8Q+6FI+r9KDDWTMpPjyeJBng3egLeckUliI9WEABoiYGBKFRAw==</DQ><InverseQ>TAxhL3MFTRpP6Hr/90FbAMcpUZe47EsRDtAbolg5M0KUadzLv+9LfNTN2u2gnH4PPkdAe+p18epOq6aDinKn0A==</InverseQ><D>NN5jsNxTWQmzfPz1GT3Gv5++8/+Od3EaqAQYsDIt7BdZEqo14nEpytKEYpnXjkC/2u6mg2eKpUyq7RupnBgmmGUgmVkqgyCHWOXmga+k9n8UpBrMzQgDNpj1BJ6GmQsTozL4AzU9mRE8hFPyewiGMBLtlhUc9fSFdABZMCj8GhE=</D></RSAKeyValue>";
            //Sign_rsa(secretKey);
            //Check_rsa();
            EncryptImg();
            //DecryptImg(secretKey);
            Console.ReadKey();
        }

        static void Sign_rsa(string secretKey)
        {
            var srcEncoding = Encoding.GetEncoding(1251);
            var dstEncoding = Encoding.UTF8;

            RSA data = RSA.Create();
            data.FromXmlString(secretKey);
            string text;
            using (var src = new StreamReader("D:\\text.txt", encoding: srcEncoding))
                text = src.ReadLine();
            byte[] sign = data.SignData(Encoding.ASCII.GetBytes(text), HashAlgorithmName.SHA256, RSASignaturePadding.Pkcs1);
            string[] res = new string[2];
            res[0] = text;
            res[1] = Convert.ToBase64String(sign);
            File.WriteAllLines("D:\\signed.txt", res);
            Console.WriteLine("File have been signed. Let's check it.");
        }

        static void Check_rsa()
        {
            string publKey;
            string nameFile;
            Console.WriteLine("Enter name of the file:");
            nameFile = Console.ReadLine();
            Console.WriteLine("Enter public RSA key:");
            publKey = Console.ReadLine();
            RSA data = RSA.Create();
            data.FromXmlString(publKey);
            string[] res = new string[2];
            res = File.ReadAllLines(nameFile);
            bool is_ok;
            string text = res[0];
            byte[] sign = Convert.FromBase64String(res[1]);
            is_ok = data.VerifyData(Encoding.ASCII.GetBytes(text), sign, HashAlgorithmName.SHA256, RSASignaturePadding.Pkcs1);
            if (is_ok) Console.WriteLine("Verification passed");
            else Console.WriteLine("Verification is not passed");
        }

        static void EncryptImg()
        {
            byte[] img = File.ReadAllBytes("D:\\selfie.jpg");
            var aes = Aes.Create();
            aes.GenerateKey();
            aes.GenerateIV();

            var rsa = RSA.Create();
            Console.WriteLine("Enter other's public RSA key:");
            string publKey = Console.ReadLine();
            rsa.FromXmlString(publKey);
            byte[] iv = aes.IV;
            File.WriteAllText("D:\\group8_iv_aes.txt", Convert.ToBase64String(iv));
            string[] res = new string[2];
            var encryptor = aes.CreateEncryptor();
            byte[] encrypted_img = encryptor.TransformFinalBlock(img, 0, img.Length);
            byte[] encrypted_aes_key = rsa.Encrypt(aes.Key, RSAEncryptionPadding.Pkcs1);
            res[0] = Convert.ToBase64String(encrypted_img);
            res[1] = Convert.ToBase64String(encrypted_aes_key);
            File.WriteAllLines("D:\\encrypted_selfie.bin", res);
        }

        static void DecryptImg(string secretKey)
        {
            string[] res = new string[2];
            res = File.ReadAllLines("D:\\myselfie.bin");
            byte[] image = Convert.FromBase64String(res[0]);
            byte[] sign_encrypted = Convert.FromBase64String(res[1]);

            var rsa = RSA.Create();
            //Console.WriteLine("Enter other's public RSA key:");
            rsa.FromXmlString(secretKey);
            var aes = Aes.Create();

            string iv = File.ReadAllText("D:\\myiv.txt");
            aes.IV = Convert.FromBase64String(iv);
            aes.Key = rsa.Decrypt(sign_encrypted, RSAEncryptionPadding.Pkcs1);

            var decryptor = aes.CreateDecryptor();
            image = decryptor.TransformFinalBlock(image, 0, image.Length);
            File.WriteAllBytes("D:\\decrypted_image.jpg", image);

            Console.ReadKey();

        }
    }
}
