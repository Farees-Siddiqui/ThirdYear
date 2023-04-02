package account;

//import java.lang.*;

public class Account {
    double amount;
    String name;

    // constructor
    public Account(String nm, double amnt) {
        amount = amnt;
        name = nm;
    }

    // functions
    synchronized void depsite(double money) {
        amount += money;
    }

    synchronized void withdraw(double money) {
        amount -= money;
    }

    synchronized void transfer(Account ac, double mn) {
        synchronized (ac) {
            amount -= mn;
            ac.amount += mn;
        }
    }

    synchronized void print() {
        // System.out.println(name + "--" + amount);
    }

}// end of class Acount