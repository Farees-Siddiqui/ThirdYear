package account;

public class ManageAccount extends Thread {
    Account account;
    static Account[] accounts = new Account[10];// we may add more later to increase the parallelism level
    static int num = 2;// the number of the accounts
    static int accNum = 0;// index to insert the next account
    int i;// the index

    public ManageAccount(String name, double amount) {
        account = new Account(name, amount);
        i = accNum;
        accounts[i] = account;
        accNum = (accNum + 1) % num;// the next index in a cyclic order
    }

    public void run() {
        account.depsite(300);
        account.withdraw(100);
        Account acc = accounts[(i + 1) % num];// transfering to the next account
        account.transfer(acc, 99);
    }

    static public void printAllAccounts() {
        for (int j = 0; j < num; j++) {
            if (ManageAccount.accounts[j] != null) {
                ManageAccount.accounts[j].print();
                ;// print it
            }
        }
    }

}// end of class ManageAccount