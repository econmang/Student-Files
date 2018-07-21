package cs258;

//This program reads the SeqText.dat and seqText2.dat files.
//These files were created by TextWriter.
//They are in sequential text format.
//They contain records of name, age, and salary.

import java.io.File;
import java.text.DecimalFormat;
import java.text.NumberFormat;

public class TextReader
{   public static final int NAME_SIZE=30;
 public static void main(String args[])
 {  String name;
    int    age;
    double salary;
             
    if (!new File("seqtext.dat").exists() ||
        !new File("seqtext2.dat").exists())
    {  System.out.println("Files don't exist");
       System.exit(1);
    }
    TextRead file1 = new TextRead("seqtext.dat");
    TextRead file2 = new TextRead("seqtext2.dat");
    NumberFormat money = NumberFormat.getCurrencyInstance();
    DecimalFormat fmt = new DecimalFormat("##0.##");
    String spaces = "                              ";

    System.out.println("Text file reader\n");
    do
    {  if (!file1.endOfFile())
       {  name = file1.readString();
          age  = file1.readInt();
          salary = file1.readDouble();
          System.out.print(name);
          if (name.length() < NAME_SIZE)              
             System.out.print
                ( spaces.substring(0, NAME_SIZE-name.length()) );
          System.out.println
                ( " " + fmt.format(age) + " " + money.format(salary) );
       }
       if (!file2.endOfFile())
       {  name = file2.readString();
          age  = file2.readInt();
          salary = file2.readDouble();
          System.out.print(name);
          if (name.length() < NAME_SIZE)      
             System.out.print
                ( spaces.substring(0, NAME_SIZE-name.length()) );
          System.out.println
                ( " " + fmt.format(age) + " " + money.format(salary) );
       }
    }  while (!file1.endOfFile()||!file2.endOfFile());
   file1.close();
   file2.close();
   System.out.println("\nTextReader complete; data printed");
}
}