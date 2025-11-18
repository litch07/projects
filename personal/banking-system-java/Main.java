import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        ArrayList<User> users = new ArrayList<>();
        ArrayList<ActivityLog> activityLogs = new ArrayList<>();
        Admin admin = new Admin();

        while (true) {
            System.out.println("\n---- Welcome ----");
            System.out.println("1. Sign Up\n2. Sign In\n3. Admin Login\n4. About me\n5. Exit");
            int choice = sc.nextInt();
            sc.nextLine();

            if (choice == 1) {
                System.out.print("Enter your name: ");
                String name = sc.nextLine();

                System.out.print("Enter your age: ");
                int age = sc.nextInt();
                sc.nextLine();

                if (age < 18) {
                    System.out.println("You must be at least 18 years old.");
                    continue;
                }

                System.out.print("Enter a username: ");
                String username = sc.nextLine();

                System.out.print("Enter a password: ");
                String password = sc.nextLine();

                System.out.print("Enter initial deposit: ");
                double balance = sc.nextDouble();

                users.add(new User(name, age, username, password, balance));
                activityLogs.add(new ActivityLog(username, "User Created", balance));
                System.out.println("Signed up successfully. Please Sign in to continue.");
            }

            else if (choice == 2) {
                System.out.print("Enter username: ");
                String username = sc.nextLine();

                System.out.print("Enter password: ");
                String password = sc.nextLine();

                User loggedInUser = null;
                for (User user : users) {
                    if (user.username.equals(username) && user.password.equals(password)) {
                        loggedInUser = user;
                        break;
                    }
                }

                if (loggedInUser == null) {
                    System.out.println("Invalid username or password.");
                } else {
                    System.out.println("Welcome, " + loggedInUser.name + "!");
                    activityLogs.add(new ActivityLog(username, "User Logged In", 0));

                    while (true) {
                        System.out.println("\n1. View Balance\n2. Deposit\n3. Withdraw\n4. Transaction Logs\n5. Log Out");
                        int option = sc.nextInt();
                        sc.nextLine();

                        if (option == 1) {
                            System.out.println("Current Balance: " + loggedInUser.balance);
                        } else if (option == 2) {
                            System.out.print("Enter deposit amount: ");
                            double amount = sc.nextDouble();
                            loggedInUser.deposit(amount);
                            activityLogs.add(new ActivityLog(username, "Deposit", amount));
                        } else if (option == 3) {
                            System.out.print("Enter withdrawal amount: ");
                            double amount = sc.nextDouble();
                            loggedInUser.withdraw(amount);
                            activityLogs.add(new ActivityLog(username, "Withdraw", amount));
                        } else if (option == 4) {
                            loggedInUser.viewTransactionLogs();
                        } else if (option == 5) {
                            System.out.println("Logged out successfully.");
                            activityLogs.add(new ActivityLog(username, "User Logged Out", 0));
                            break;
                        } else {
                            System.out.println("Invalid option.");
                        }
                    }
                }
            }

            else if (choice == 3) {
                System.out.print("Enter admin username: ");
                String adminUsername = sc.nextLine();

                System.out.print("Enter admin password: ");
                String adminPassword = sc.nextLine();

                if (admin.authenticate(adminUsername, adminPassword)) {
                    System.out.println("Admin logged in.");
                    activityLogs.add(new ActivityLog("Admin", "Logged In", 0));

                    while (true) {
                        System.out.println("\n1. View All Users\n2. Search User\n3. Remove User\n4. View Activity Logs\n5. Log Out");
                        int option = sc.nextInt();
                        sc.nextLine();

                        if (option == 1) {
                            admin.viewAllUsers(users);
                        } else if (option == 2) {
                            System.out.print("Enter username to search: ");
                            String username = sc.nextLine();
                            User user = admin.searchUser(users, username);
                            if (user != null) {
                                user.displayDetails();
                            } else {
                                System.out.println("User not found.");
                            }
                        } else if (option == 3) {
                            System.out.print("Enter username to remove: ");
                            String username = sc.nextLine();
                            admin.deleteUser(users, username);
                            activityLogs.add(new ActivityLog("Admin", "Removed User: " + username, 0));
                        } else if (option == 4) {
                            admin.viewActivityLogs(activityLogs);
                        } else if (option == 5) {
                            System.out.println("Admin logged out.");
                            activityLogs.add(new ActivityLog("Admin", "Logged Out", 0));
                            break;
                        } else {
                            System.out.println("Invalid option.");
                        }
                    }
                } else {
                    System.out.println("Invalid username or password.");
                }
            }

            else if(choice == 4){
                System.out.println("   Name: Sadid Ahmed\n" + "\t ID: 0112330154");
            }

            else if (choice == 5) {
                String message = "Thank you for using our Banking System. Goodbye!";
                char[] chars = message.toCharArray();

                for (int i = 0; i < chars.length; i++){
                    System.out.print(chars[i]);
                    try {
                        Thread.sleep(100);
                    }
                    catch (InterruptedException e){
                        System.out.println("Got Interrupted in sleep");
                    }
                }
                break;
            }
            else {
                System.out.println("Invalid selection. Please try again.");
            }
        }
        sc.close();
    }
}