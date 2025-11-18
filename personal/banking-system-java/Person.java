public class Person {
    String name;
    String username;
    String password;

    public Person(String name, String username, String password) {
        this.name = name;
        this.username = username;
        this.password = password;
    }

    public void displayDetails() {
        System.out.println("Name: " + name + ", Username: " + username);
    }
}
