import javax.swing.*;
import java.awt.*;

public class Grading extends JFrame {
    JLabel[] gradeLetter;
    JLabel[] gradePointLabeloint;
    JLabel[] marks;
    JLabel letterGradeLabel, gradePointLabel, marksLabel;

    public Grading() {
        gradeLetter = new JLabel[10];
        gradePointLabeloint = new JLabel[10];
        marks = new JLabel[10];
        letterGradeLabel = new JLabel("Letter Grade", SwingConstants.CENTER);
        gradePointLabel = new JLabel("Grade Point", SwingConstants.CENTER);
        marksLabel = new JLabel("Marks (%)", SwingConstants.CENTER);

        gradeLetter[0] = new JLabel("A", SwingConstants.CENTER);
        gradeLetter[1] = new JLabel("A-", SwingConstants.CENTER);
        gradeLetter[2] = new JLabel("B+", SwingConstants.CENTER);
        gradeLetter[3] = new JLabel("B", SwingConstants.CENTER);
        gradeLetter[4] = new JLabel("B-", SwingConstants.CENTER);
        gradeLetter[5] = new JLabel("C+", SwingConstants.CENTER);
        gradeLetter[6] = new JLabel("C", SwingConstants.CENTER);
        gradeLetter[7] = new JLabel("C-", SwingConstants.CENTER);
        gradeLetter[8] = new JLabel("D+", SwingConstants.CENTER);
        gradeLetter[9] = new JLabel("D", SwingConstants.CENTER);

        gradePointLabeloint[0] = new JLabel("4.00", SwingConstants.CENTER);
        gradePointLabeloint[1] = new JLabel("3.67", SwingConstants.CENTER);
        gradePointLabeloint[2] = new JLabel("3.33", SwingConstants.CENTER);
        gradePointLabeloint[3] = new JLabel("3.00", SwingConstants.CENTER);
        gradePointLabeloint[4] = new JLabel("2.67", SwingConstants.CENTER);
        gradePointLabeloint[5] = new JLabel("2.33", SwingConstants.CENTER);
        gradePointLabeloint[6] = new JLabel("2.00", SwingConstants.CENTER);
        gradePointLabeloint[7] = new JLabel("1.67", SwingConstants.CENTER);
        gradePointLabeloint[8] = new JLabel("1.33", SwingConstants.CENTER);
        gradePointLabeloint[9] = new JLabel("1.00", SwingConstants.CENTER);

        marks[0] = new JLabel("90-100", SwingConstants.CENTER);
        marks[1] = new JLabel("86-89", SwingConstants.CENTER);
        marks[2] = new JLabel("82-85", SwingConstants.CENTER);
        marks[3] = new JLabel("78-81", SwingConstants.CENTER);
        marks[4] = new JLabel("74-77", SwingConstants.CENTER);
        marks[5] = new JLabel("70-73", SwingConstants.CENTER);
        marks[6] = new JLabel("66-69", SwingConstants.CENTER);
        marks[7] = new JLabel("62-65", SwingConstants.CENTER);
        marks[8] = new JLabel("58-61", SwingConstants.CENTER);
        marks[9] = new JLabel("55-57", SwingConstants.CENTER);

        setLayout(new BorderLayout());

        JPanel headerPanel = new JPanel(new GridLayout(1, 3));
        headerPanel.add(letterGradeLabel);
        headerPanel.add(gradePointLabel);
        headerPanel.add(marksLabel);
        add(headerPanel, BorderLayout.NORTH);

        JPanel mainPanel = new JPanel(new GridLayout(10, 3, 0, 7));

        for (int i = 0; i < 10; i++) {
            gradeLetter[i].setBorder(BorderFactory.createLineBorder(Color.BLACK));
            gradePointLabeloint[i].setBorder(BorderFactory.createLineBorder(Color.BLACK));
            marks[i].setBorder(BorderFactory.createLineBorder(Color.BLACK));

            mainPanel.add(gradeLetter[i]);
            mainPanel.add(gradePointLabeloint[i]);
            mainPanel.add(marks[i]);
        }

        add(mainPanel, BorderLayout.CENTER);
        setSize(400, 400);
        setVisible(true);
    }
}