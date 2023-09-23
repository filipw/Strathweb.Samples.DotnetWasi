using System;
namespace WasiExport;

public class Interop
{
    public static void Hello()
    {
        Console.WriteLine("hello world");
    }

    static void Main() {
        // no need to do anything, this will just bootstrap Mono
    }
}