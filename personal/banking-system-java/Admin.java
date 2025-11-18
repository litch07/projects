import java.util.ArrayList;

public class Admin extends Person {
    private static final String ADMIN_USERNAME = "admin";
    private static final String ADMIN_PASSWORD = "admin";

    public Admin() {
        super("Admin", ADMIN_USERNAME, ADMIN_PASSWORD);
    }

    public boolean authenticate(String username, String password) {
        return username.equals(ADMIN_USERNAME) && password.equals(ADMIN_PASSWORD);
    }

    public void viewAllUsers(ArrayList<User> users) {
        if (users.isEmpty()) {
            System.out.println("No registered users.");
        } else {
            for (User user : users) {
                user.displayDetails();
            }
        }
    }

    public User searchUser(ArrayList<User> users, String username) {
        for (User user : users) {
            if (user.username.equals(username)) {
                return user;
            }
        }
        return null;
    }

    public void deleteUser(ArrayList<User> users, String username) {
        User user = searchUser(users, username);
        if (user != null) {
            users.remove(user);
            System.out.println("User " + username + " removed successfully.");
        } else {
            System.out.println("User not found.");
        }
    }

    public void viewActivityLogs(ArrayList<ActivityLog> activityLogs) {
        if (activityLogs.isEmpty()) {
            System.out.println("No activities recorded.");
        } else {
            for (ActivityLog log : activityLogs) {
                System.out.println(log);
            }
        }
    }
}