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
            //string publicKey = "<RSAKeyValue><Modulus>4IohZ4FOgm1p3hKvgJuXV0LEYgQeuqXryaN+bTLj0qK8nUowUCPT4aYB3SrL+I6hi6JuO+SpIblJUgpam1FDXSuNZSgOfBvKrpmur+oIe6Vb8GmK0Ujnpwg6t8XUp+vQOQ0Fmo6z9t5hRw6WI4jMDF0a6bt9Bp00rYkqERwht1U=</Modulus><Exponent>AQAB</Exponent></RSAKeyValue>";
            //string secretKey = "<RSAKeyValue><Modulus>4IohZ4FOgm1p3hKvgJuXV0LEYgQeuqXryaN+bTLj0qK8nUowUCPT4aYB3SrL+I6hi6JuO+SpIblJUgpam1FDXSuNZSgOfBvKrpmur+oIe6Vb8GmK0Ujnpwg6t8XUp+vQOQ0Fmo6z9t5hRw6WI4jMDF0a6bt9Bp00rYkqERwht1U=</Modulus><Exponent>AQAB</Exponent><P>8u1Mpok9GyqcZJ5NpE082ZSFI3GjkFwCDdNhL6VTBFjU1rLjddHkGKPEIhaOtSsPSVtLuqn5OuaasL3IIOZpVw==</P><Q>7J+EGlxz7LHaTCFmKMganZpn4EFOqkbTMCdELepR7QZA9CLQQhLPopL79PbsIouuTiPlxyQGzsYcewO5EEc9Mw==</Q><DP>rWKhqtuZOaKYLVivoe1e2Q0gWcPqMkb5UFTmsNMXBatBflv/7T/5xXxdqNbg1H3/UyROUNSwhlHBZxSNmq3Z0Q==</DP><DQ>5OOtIt7Z2FV2h/wq2Tov3NJ2twwVb0tRkJv7LLskgrZw8HgYokGWDnpGNYEBjK03cCjzZX4pA63J8Qj55JA01w==</DQ><InverseQ>rqtS9e/qIC5J9qBtVSu6lvyNZhE0kCKErQvYmHGNfRm2TVpE3PA0ccLgNwSU9OEp0j3ySgeW9mApr8AuSpCwvQ==</InverseQ><D>t9Vfc/aR6Ibb3k0+EvVP+slXL0hgQEAHw5Zvs8eubo1+DujmlTZACsZ3UDPxuxZLfJ8H0VFsh4fDV7/SXscxdlXLQ7UR2PIAXxX+U7r/9ec4Q0fmbWCpR3lm66silUWly1AtF7lXB4iLEOUopbQV1eBDlZjki2XOMw5WxT1/hSE=</D></RSAKeyValue>";
            Sign_rsa(secretKey);
            //Check_rsa();
            //EncryptImg();
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
