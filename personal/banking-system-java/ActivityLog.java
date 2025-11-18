import java.time.LocalDateTime;

public class ActivityLog {
    String username, activityType;
    double amount;
    LocalDateTime time;

    public ActivityLog(String username, String activityType, double amount) {
        this.username = username;
        this.activityType = activityType;
        this.amount = amount;
        this.time = LocalDateTime.now();
    }

    @Override
    public String toString() {
        return "Username: " + username + ", Activity: " + activityType + ", Amount: " + (amount != 0 ? amount : "N/A") + ", Time: " + time;
    }
}