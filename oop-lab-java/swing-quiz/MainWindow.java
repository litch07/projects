import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;

public class MainWindow extends JFrame {
    JLabel l1, l2, l3, l4;
    JRadioButton rb1, rb2, rb3, rb4;
    JButton next_button, final_button;
    ButtonGroup bg = new ButtonGroup();
    static int correct = 0;

    public MainWindow(ArrayList<Questions>questions, int index_array) {

        l1 = new JLabel("Question's will appear here");
        l1.setText(questions.get(index_array).ques);
        l1.setBounds(25,30,400,30);

        l2 = new JLabel();
        l2.setBounds(125,140,300,30);
        l2.setVisible(false);

        l3 = new JLabel("Quiz ends here. Select Final for your result");
        l3.setBounds(70,140,250,30);
        l3.setVisible(false);

        l4 = new JLabel("Thank you");
        l4.setBounds(150,150,100,50);
        l4.setVisible(false);

        rb1 = new JRadioButton("Option 1");
        rb1.setBounds(25, 60, 400, 30);
        rb1.setText(questions.get(index_array).opt[0]);
        rb1.setActionCommand(questions.get(index_array).opt[0]);

        rb2 = new JRadioButton("Option 2");
        rb2.setBounds(25, 90, 400, 30);
        rb2.setText(questions.get(index_array).opt[1]);
        rb2.setActionCommand(questions.get(index_array).opt[1]);


        rb3 = new JRadioButton("Option 3");
        rb3.setBounds(25, 120, 400, 30);
        rb3.setText(questions.get(index_array).opt[2]);
        rb3.setActionCommand(questions.get(index_array).opt[2]);

        rb4 = new JRadioButton("Option 4");
        rb4.setBounds(25, 150, 400, 30);
        rb4.setText(questions.get(index_array).opt[3]);
        rb4.setActionCommand(questions.get(index_array).opt[3]);

        next_button = new JButton("Next");
        next_button.setBounds(150, 200, 80, 30);

        final_button = new JButton("Final");
        final_button.setBounds(150, 170, 80, 30);
        final_button.setVisible(false);

        bg.add(rb1);
        bg.add(rb2);
        bg.add(rb3);
        bg.add(rb4);

        add(l1,BorderLayout.CENTER);
        add(l2,BorderLayout.CENTER);
        add(l3,BorderLayout.CENTER);
        add(l4,BorderLayout.CENTER);
        add(rb1,BorderLayout.CENTER);
        add(rb2,BorderLayout.CENTER);
        add(rb3,BorderLayout.CENTER);
        add(rb4,BorderLayout.CENTER);
        add(next_button,BorderLayout.CENTER);
        add(final_button,BorderLayout.CENTER);

        ActionListener next_b = new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if(bg.getSelection() == null){
                    JOptionPane.showMessageDialog(null, "Please select an option.");
                }
                else {
                    String selected = bg.getSelection().getActionCommand();
                    if (selected.equals(questions.get(index_array).ans)) {
                        correct++;
                    }

                    if (index_array + 1 < questions.size()) {
                        new MainWindow(questions, index_array + 1);
                        dispose();
                    }

                    if (index_array == questions.size() - 1) {
                        next_button.setVisible(false);
                        l1.setVisible(false);
                        rb1.setVisible(false);
                        rb2.setVisible(false);
                        rb3.setVisible(false);
                        rb4.setVisible(false);
                        l3.setVisible(true);
                        final_button.setVisible(true);
                    }
                }
            }
        };

        ActionListener final_b = new ActionListener(){
            @Override
            public void actionPerformed(ActionEvent e) {
                final_button.setVisible(false);
                l2.setText("Your final score is: " +correct);
                l3.setVisible(false);
                l2.setVisible(true);
                l4.setVisible(true);
            }
        };

        next_button.addActionListener(next_b);
        final_button.addActionListener(final_b);

            setVisible(true);
            setLayout(new BorderLayout());
            setSize(400, 400);
            setDefaultCloseOperation(EXIT_ON_CLOSE);
    }
}