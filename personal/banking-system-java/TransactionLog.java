import java.time.LocalDateTime;

public class TransactionLog {
    String username, transactionType;
    double amount, newBalance;
    LocalDateTime time;

    public TransactionLog(String username, String transactionType, double amount, double newBalance) {
        this.username = username;
        this.transactionType = transactionType;
        this.amount = amount;
        this.newBalance = newBalance;
        this.time = LocalDateTime.now();
    }

    @Override
    public String toString() {
        return "User: " + username + ", Transaction: " + transactionType + ", Amount: " + amount + ", New Balance: " + newBalance + ", Time: " + time;
    }
}