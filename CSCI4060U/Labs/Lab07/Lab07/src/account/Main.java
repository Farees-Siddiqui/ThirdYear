package account;

import java.io.*;

public class Main {

    public static void main(String[] args) {

        for (int i = 0; i < 2500; i++) {

            PrintStream out = null;
            try {
                if (args.length > 0) {
                    out = new PrintStream(new FileOutputStream(args[0]));
                    // System.setOut(out);//directint all the "out" printing to the file.
                    if (args.length == 1) {// the default value=little
                        System.out.println("The default value=little");
                    }
                    out.print("<Account program,");
                    if (args.length == 2) {// the concurrency is optional
                        String concurrencyLevel = args[1];
                        if (concurrencyLevel.compareTo("little") == 0) {
                            ManageAccount.num = 2;
                            // System.out.println("concurrency level = little");
                        } else if (concurrencyLevel.compareTo("average") == 0) {
                            ManageAccount.num = 5;
                            // System.out.println("concurrency level = average");
                        } else if (concurrencyLevel.compareTo("lot") == 0) {
                            ManageAccount.num = 10;
                            // System.out.println("concurrency level = lot");
                        } else {// wrong second argument
                            // System.out.println("The second argument should be one of the
                            // following:\nlittle,average or lot");
                            System.exit(1);
                        }
                    } else {// more than 2 arguments
                        if (args.length > 2) {
                            // System.out.println("The program can accept only one or two arguments");
                            System.exit(1);
                        }
                    }
                } else {// main's parameter is missing
                    // System.out.println("The output file name is missing");
                    System.exit(1);
                }
                // System.out.println("The Initial values:");
                ManageAccount[] bank = new ManageAccount[ManageAccount.num];// 2 is the default size
                String[] accountName = { new String("A"), new String("B"), new String("C"), new String("D"),
                        new String("E"),
                        new String("F"), new String("G"), new String("H"), new String("I"), new String("J"), };
                for (int j = 0; j < ManageAccount.num; j++) {
                    bank[j] = new ManageAccount(accountName[j], 100);
                    ManageAccount.accounts[j].print();
                    ;// print it
                }

                // start the threads
                for (int k = 0; k < ManageAccount.num; k++) {
                    bank[k].start();
                }

                // wait until all are finished
                for (int k = 0; k < ManageAccount.num; k++) {
                    bank[k].join();
                }
                // System.out.println("The final values:");
                ManageAccount.printAllAccounts();

                // updating the output file
                boolean less = false, more = false;// flags which will indicate the kind of the bug
                for (int k = 0; k < ManageAccount.num; k++) {
                    if (ManageAccount.accounts[k].amount < 300) {
                        less = true;
                    } else if (ManageAccount.accounts[k].amount > 300) {
                        more = true;
                    }
                }
                if ((less == true) && (more == true))
                    System.out.println(
                            " There is amount with more than 300and there is amount with less than 300, No Lock>");
                if ((less == false) && (more == true))
                    System.out.println(" There is amount with more than 300, No Lock>");
                if ((less == true) && (more == false))
                    System.out.println(" There is amount with less than 300, No Lock>");
                // if ((less == false) && (more == false))
                // System.out.println("");
                out.close();
            } catch (Exception e) {// FileNotFound,Security
                if (out != null)
                    out.close();
            }
        }
    }// end of function main
}// end of class Main