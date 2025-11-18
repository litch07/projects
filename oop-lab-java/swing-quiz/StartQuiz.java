import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;

public class StartQuiz extends JFrame {
        JButton b1;
        public StartQuiz(ArrayList<Questions>questions) {
            b1 = new JButton("Start Quiz");
            b1.setBounds(130,100,100, 40);

            add(b1);

            ActionListener al = new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    new MainWindow(questions, 0);
                    dispose();
                }
            };

            b1.addActionListener(al);

            setTitle("Start Quiz");
            setVisible(true);
            setLayout(new GridBagLayout());
            setSize(400,400);
            setDefaultCloseOperation(EXIT_ON_CLOSE);
        }
}