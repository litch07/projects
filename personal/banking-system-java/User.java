import java.util.ArrayList;

public class User extends Person {
    int age;
    double balance;
    ArrayList<TransactionLog> transactionLogs;

    public User(String name, int age, String username, String password, double balance) {
        super(name, username, password); // Call to the superclass constructor
        this.age = age;
        this.balance = balance;
        this.transactionLogs = new ArrayList<>();
    }

    public void deposit(double amount) {
        balance += amount;
        transactionLogs.add(new TransactionLog(username, "Deposit", amount, balance));
        System.out.println("Deposited " + amount + " successfully.");
    }

    public void withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            transactionLogs.add(new TransactionLog(username, "Withdraw", amount, balance));
            System.out.println("Withdrawn " + amount + " successfully.");
        } else {
            System.out.println("Insufficient balance.");
        }
    }

    public void viewTransactionLogs() {
        if (transactionLogs.isEmpty()) {
            System.out.println("No transaction logs available.");
        } else {
            for (TransactionLog log : transactionLogs) {
                System.out.println(log);
            }
        }
    }

    @Override
    public void displayDetails() {
        super.displayDetails();
        System.out.println("Age: " + age + ", Balance: " + balance);
    }
}