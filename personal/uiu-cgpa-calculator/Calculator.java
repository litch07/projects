import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Calculator extends JFrame {
    JLabel completedCreditsLabel, currentCgpaLabel, bannerLabel, bannerUpBar, bannerDownBar, gpaResultLabel, cgpaResultLabel;
    JLabel[] courseCreditsLabels, cgpaLabels;
    JComboBox<String>[] courseCreditBoxes;
    JComboBox<String>[] cgpaBoxes;
    JTextField completedCreditsText, currentCgpaText;
    JButton addButton, removeButton, countButton, gradingButton;
    static final int COURSE_COUNT = 8;
    int currentCourses = 1;
    double finalCgpa, totalCgpaCount, gpaTotalCount, finalGpa;
    int cgpaCreditCount, gpaCreditCount;
    int shiftButtonY = 165;

    public Calculator() {
        completedCreditsLabel = new JLabel("Completed Credits: ");
        completedCreditsLabel.setBounds(30, 60, 130, 20);

        completedCreditsText = new JTextField();
        completedCreditsText.setBounds(150, 60, 70, 20);

        currentCgpaLabel = new JLabel("CGPA: ");
        currentCgpaLabel.setBounds(230, 60, 120, 20);

        currentCgpaText = new JTextField();
        currentCgpaText.setBounds(280, 60, 70, 20);

        bannerUpBar = new JLabel("____________________________________________________________");
        bannerUpBar.setBounds(0, 5, 400, 15);
        bannerLabel = new JLabel("CGPA is Just a Floating Number :3", SwingConstants.CENTER);
        bannerLabel.setBounds(0, 20, 400, 15);
        bannerDownBar = new JLabel("____________________________________________________________");
        bannerDownBar.setBounds(0, 20, 400, 20);

        gpaResultLabel = new JLabel();
        gpaResultLabel.setVisible(false);

        cgpaResultLabel = new JLabel();
        cgpaResultLabel.setVisible(false);

        removeButton = new JButton("Remove");
        removeButton.setBounds(30, 165, 100, 30);
        removeButton.setEnabled(false);

        countButton = new JButton("Count");
        countButton.setBounds(155, 165, 100, 40);

        addButton = new JButton("Add");
        addButton.setBounds(270, 165, 100, 30);

        gradingButton = new JButton("Grading");
        gradingButton.setBounds(270, 410, 100, 30);

        add(completedCreditsLabel);
        add(completedCreditsText);
        add(currentCgpaLabel);
        add(currentCgpaText);
        add(bannerUpBar);
        add(bannerLabel);
        add(bannerDownBar);
        add(gpaResultLabel);
        add(cgpaResultLabel);
        add(addButton);
        add(countButton);
        add(removeButton);
        add(gradingButton);

        courseCreditsLabels = new JLabel[COURSE_COUNT];
        cgpaLabels = new JLabel[COURSE_COUNT];
        courseCreditBoxes = new JComboBox[COURSE_COUNT];
        cgpaBoxes = new JComboBox[COURSE_COUNT];

        String[] creditOptions = {"Select", "1", "2", "3", "4"};
        String[] gradeOptions = {"Select", "4.00", "3.67", "3.33", "3.00", "2.67", "2.33", "2.00", "1.67", "1.33", "1.00"};

        int yPosition = 100;
        for (int i = 0; i < COURSE_COUNT; i++) {
            courseCreditsLabels[i] = new JLabel((i + 1) + ". Course credit:");
            courseCreditsLabels[i].setBounds(40, yPosition, 100, 20);
            courseCreditsLabels[i].setVisible(i == 0);
            add(courseCreditsLabels[i]);

            courseCreditBoxes[i] = new JComboBox<>(creditOptions);
            courseCreditBoxes[i].setBounds(150, yPosition, 70, 20);
            courseCreditBoxes[i].setVisible(i == 0);
            add(courseCreditBoxes[i]);

            cgpaLabels[i] = new JLabel("CGPA: ");
            cgpaLabels[i].setBounds(230, yPosition, 40, 20);
            cgpaLabels[i].setVisible(i == 0);
            add(cgpaLabels[i]);

            cgpaBoxes[i] = new JComboBox<>(gradeOptions);
            cgpaBoxes[i].setBounds(280, yPosition, 70, 20);
            cgpaBoxes[i].setVisible(i == 0);
            add(cgpaBoxes[i]);

            yPosition += 30;
        }

        ActionListener addButtonListener = new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (currentCourses < COURSE_COUNT) {
                    courseCreditsLabels[currentCourses].setVisible(true);
                    courseCreditBoxes[currentCourses].setVisible(true);
                    cgpaLabels[currentCourses].setVisible(true);
                    cgpaBoxes[currentCourses].setVisible(true);
                    currentCourses++;

                    shiftButtonY += 30;

                    removeButton.setBounds(30, shiftButtonY, 100, 30);
                    addButton.setBounds(270, shiftButtonY, 100, 30);
                    countButton.setBounds(155, shiftButtonY, 100, 40);

                    removeButton.setEnabled(true);

                    if (currentCourses == COURSE_COUNT) {
                        addButton.setEnabled(false);
                    }
                    gpaResultLabel.setVisible(false);
                    cgpaResultLabel.setVisible(false);
                }
            }
        };
        
        addButton.addActionListener(addButtonListener);

        ActionListener removeButtonListener = new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (currentCourses > 1) {
                    currentCourses--;

                    courseCreditBoxes[currentCourses].setSelectedIndex(0);
                    cgpaBoxes[currentCourses].setSelectedIndex(0);

                    courseCreditsLabels[currentCourses].setVisible(false);
                    courseCreditBoxes[currentCourses].setVisible(false);
                    cgpaLabels[currentCourses].setVisible(false);
                    cgpaBoxes[currentCourses].setVisible(false);

                    shiftButtonY -= 30;
                    removeButton.setBounds(30, shiftButtonY, 100, 30);
                    addButton.setBounds(270, shiftButtonY, 100, 30);
                    countButton.setBounds(155, shiftButtonY, 100, 40);

                    if (currentCourses == 1) {
                        removeButton.setEnabled(false);
                    }

                    addButton.setEnabled(true);
                    gpaResultLabel.setVisible(false);
                    cgpaResultLabel.setVisible(false);
                }
            }
        };

        
        removeButton.addActionListener(removeButtonListener);

        ActionListener countButtonListener = new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                totalCgpaCount = 0;
                cgpaCreditCount = 0;
                gpaCreditCount = 0;
                gpaTotalCount = 0;

                if (!currentCgpaText.getText().isEmpty() && !completedCreditsText.getText().isEmpty()) {
                    try {
                        int cred = Integer.parseInt(completedCreditsText.getText());
                        double cg = Double.parseDouble(currentCgpaText.getText());

                        if (cg < 0 || cg > 4) {
                            JOptionPane.showMessageDialog(null, "Please enter a valid CGPA between 0 and 4.", "Input Error", JOptionPane.ERROR_MESSAGE);
                            return;
                        }

                        totalCgpaCount += cred * cg;
                        cgpaCreditCount += cred;
                    } catch (NumberFormatException ex) {
                        if (completedCreditsText.getText().contains(".")) {
                            JOptionPane.showMessageDialog(null, "Credits must be a whole number (no decimal points).", "Input Error", JOptionPane.ERROR_MESSAGE);
                        } else {
                            JOptionPane.showMessageDialog(null, "Invalid input for CGPA or Completed Credits.", "Input Error", JOptionPane.ERROR_MESSAGE);
                        }
                        return;
                    }
                }

                boolean allSelected = true;

                for (int i = 0; i < currentCourses; i++) {
                    if (courseCreditBoxes[i].getSelectedItem().equals("Select") || cgpaBoxes[i].getSelectedItem().equals("Select")) {
                        allSelected = false;
                        JOptionPane.showMessageDialog(null, "Please select valid options for all course credits and CGPAs.", "Selection Error", JOptionPane.ERROR_MESSAGE);
                        break;
                    }

                    int cred = Integer.parseInt((String) courseCreditBoxes[i].getSelectedItem());
                    double cg = Double.parseDouble((String) cgpaBoxes[i].getSelectedItem());
                    totalCgpaCount += cred * cg;
                    cgpaCreditCount += cred;

                    gpaTotalCount += cred * cg;
                    gpaCreditCount += cred;
                }

                if (allSelected) {
                    if (cgpaCreditCount > 0 || gpaCreditCount > 0) {
                        finalCgpa = totalCgpaCount / cgpaCreditCount;
                        finalGpa = gpaTotalCount / gpaCreditCount;

                        gpaResultLabel.setText(String.format("GPA : %.2f", finalGpa));
                        cgpaResultLabel.setText(String.format("CGPA: %.2f", finalCgpa));

                        gpaResultLabel.setBounds(20, shiftButtonY - 40, 300, 15);
                        cgpaResultLabel.setBounds(20, shiftButtonY - 20, 300, 15);
                        gpaResultLabel.setVisible(true);
                        cgpaResultLabel.setVisible(true);
                    } else {
                        System.out.println("Error: No valid credits entered to calculate CGPA.");
                    }
                }
            }
        };

        countButton.addActionListener(countButtonListener);

        ActionListener gradingButtonListener = new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                new Grading();
            }
        };
        
        gradingButton.addActionListener(gradingButtonListener);

        setVisible(true);
        setLayout(null);
        setSize(400, 480);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
    }
}