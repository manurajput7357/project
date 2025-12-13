import java.io.*;
import java.util.*;

// --------- Question Class ----------
class Question {
    String question;
    String[] options;
    int correctOption; // 1-4

    public Question(String question, String[] options, int correctOption) {
        this.question = question;
        this.options = options;
        this.correctOption = correctOption;
    }

    public String serialize() {
        // question|option1|option2|option3|option4|correctOption
        return question + "|" + options[0] + "|" + options[1] + "|" + options[2] + "|" + options[3] + "|" + correctOption;
    }

    public static Question deserialize(String line) {
        String[] parts = line.split("\\|");
        String[] opts = new String[4];
        for (int i = 0; i < 4; i++) opts[i] = parts[i + 1];
        int correct = Integer.parseInt(parts[5]);
        return new Question(parts[0], opts, correct);
    }

    public void display() {
        System.out.println("\n" + question);
        for (int i = 0; i < 4; i++) {
            System.out.println((i + 1) + ". " + options[i]);
        }
    }
}

// --------- Quiz Management ----------
class QuizSystem {
    List<Question> questions;
    final String questionFile = "questions.txt";
    final String resultFile = "results.txt";
    Scanner sc;

    public QuizSystem() {
        questions = new ArrayList<>();
        sc = new Scanner(System.in);
        loadQuestions();
    }

    // -------- File Operations --------
    void loadQuestions() {
        questions.clear();
        try (BufferedReader br = new BufferedReader(new FileReader(questionFile))) {
            String line;
            while ((line = br.readLine()) != null) {
                if (!line.trim().isEmpty())
                    questions.add(Question.deserialize(line));
            }
        } catch (Exception e) {
            System.out.println("No questions found. Admin can add questions.");
        }
    }

    void saveQuestions() {
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(questionFile))) {
            for (Question q : questions)
                bw.write(q.serialize() + "\n");
        } catch (Exception e) {
            System.out.println("Error saving questions.");
        }
    }

    void saveResult(String username, int score) {
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(resultFile, true))) {
            bw.write(username + "|" + score + "\n");
        } catch (Exception e) {
            System.out.println("Error saving result.");
        }
    }

    // -------- Admin Functions --------
    void adminMenu() {
        while (true) {
            System.out.println("\n--- Admin Menu ---");
            System.out.println("1. Add Question");
            System.out.println("2. View All Questions");
            System.out.println("3. Exit Admin Menu");
            System.out.print("Enter choice: ");
            int choice = Integer.parseInt(sc.nextLine());
            switch (choice) {
                case 1: addQuestion(); break;
                case 2: viewQuestions(); break;
                case 3: return;
                default: System.out.println("Invalid choice!");
            }
        }
    }

    void addQuestion() {
        System.out.print("Enter question: ");
        String qText = sc.nextLine();
        String[] opts = new String[4];
        for (int i = 0; i < 4; i++) {
            System.out.print("Enter option " + (i + 1) + ": ");
            opts[i] = sc.nextLine();
        }
        System.out.print("Enter correct option number (1-4): ");
        int correct = Integer.parseInt(sc.nextLine());
        Question q = new Question(qText, opts, correct);
        questions.add(q);
        saveQuestions();
        System.out.println("Question added successfully!");
    }

    void viewQuestions() {
        if (questions.isEmpty()) {
            System.out.println("No questions available.");
            return;
        }
        int i = 1;
        for (Question q : questions) {
            System.out.println("\nQuestion " + i++);
            q.display();
            System.out.println("Correct Option: " + q.correctOption);
        }
    }

    // -------- User Functions --------
    void takeQuiz(String username) {
        if (questions.isEmpty()) {
            System.out.println("No questions available. Contact admin.");
            return;
        }
        int score = 0;
        for (Question q : questions) {
            q.display();
            int ans = 0;
            while (true) {
                try {
                    System.out.print("Enter your answer (1-4): ");
                    ans = Integer.parseInt(sc.nextLine());
                    if (ans < 1 || ans > 4) throw new Exception();
                    break;
                } catch (Exception e) {
                    System.out.println("Invalid input! Enter number 1-4.");
                }
            }
            if (ans == q.correctOption) score++;
        }
        System.out.println("\nQuiz Completed! Your Score: " + score + " / " + questions.size());
        saveResult(username, score);
    }

    void mainMenu() {
        while (true) {
            System.out.println("\n=== Quiz Management System ===");
            System.out.println("1. Admin Login");
            System.out.println("2. Take Quiz (User)");
            System.out.println("3. Exit");
            System.out.print("Enter choice: ");
            int choice = Integer.parseInt(sc.nextLine());
            switch (choice) {
                case 1:
                    System.out.print("Enter Admin Password: ");
                    String pwd = sc.nextLine();
                    if (pwd.equals("admin123")) adminMenu();
                    else System.out.println("Wrong password!");
                    break;
                case 2:
                    System.out.print("Enter your name: ");
                    String uname = sc.nextLine();
                    takeQuiz(uname);
                    break;
                case 3: System.out.println("Exiting..."); return;
                default: System.out.println("Invalid choice!");
            }
        }
    }
}

// --------- Main Function ----------
public class QuizManagementSystem {
    public static void main(String[] args) {
        QuizSystem qs = new QuizSystem();
        qs.mainMenu();
    }
}
