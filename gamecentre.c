#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define RESET "\033[0m"
#define RED "\033[31m" // Red
#define GREEN "\033[32m" // Green
#define YELLOW "\033[33m" // Yellow
#define BLUE "\033[34m" // Blue
#define MAGENTA "\033[35m" // Magenta
#define CYAN "\033[36m" // Cyan
#define WHITE "\033[37m" // White

typedef struct {
    int id;
    char name[50];
    int wins;
    int losses;
} User;

void playGames(User users[], int *userCount);
void displayLeaderboard(User users[], int userCount);
void displayPersonalDetails(User users[], int userCount);
void loadUsers(User users[], int *userCount);
void saveUsers(User users[], int userCount);
int getUserIndexById(User users[], int userCount, int id);
int playTicTacToe();
int playNumberGuessingGame();
int playRockPaperScissors();
int playHangmanGame();
int playQuizgame();


int checkWin(char board[3][3], char player);

int main() {
    User users[100];
    int userCount = 0;
    int choice;

    loadUsers(users, &userCount);

    while (1) {
printf("========================================================================================================================================================\n");
printf("\t\t\t\t\t\t\t"BLUE"WELCOME TO GAMING HUB \n""\t\t\t\t\t\t\t""HERE WE HAVE INTERESTING GAMES FOR YOU \n\n"RESET);

printf("\t\t\t\t\t\t\t"CYAN "Menu:\n" RESET );
printf("\t\t\t\t\t\t\t"GREEN "1. Play Games\n" RESET);
printf("\t\t\t\t\t\t\t"YELLOW "2. Display Leaderboard\n" RESET);
printf("\t\t\t\t\t\t\t"RED "3. Display Personal Details\n" RESET);
printf("\t\t\t\t\t\t\t"MAGENTA "4. Exit\n" RESET);
printf("========================================================================================================================================================\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                playGames(users, &userCount);
                saveUsers(users, userCount);
                break;
            case 2:
                displayLeaderboard(users, userCount);
                break;
            case 3:
                displayPersonalDetails(users, userCount);
                break;
            case 4:
                saveUsers(users, userCount);
                printf("Exiting program. Data saved.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void playGames(User users[], int *userCount) {
    int id, choice;

    printf("Enter your user ID(max of 3 integers): ");
    scanf("%d", &id);

    int userIndex = getUserIndexById(users, *userCount, id);
    if (userIndex == -1) {
        // Checking the user if there is space to add
        if (*userCount >= 100) {
            printf("User limit reached. Cannot add more users.\n");
            return;
        }

        // Add new user
        printf("New user detected. \n");
        printf("Enter your name: ");
        scanf("%s", users[*userCount].name);

        // The ID is unique
        while (getUserIndexById(users, *userCount, id) != -1) {
            printf("This ID already exists. Please enter a unique ID: ");
            scanf("%d", &id);
        }

        users[*userCount].id = id;
        users[*userCount].wins = 0;
        users[*userCount].losses = 0;

        userIndex = (*userCount)++;
    }

    printf("Choose a game to play:\n");
    printf("1. Tic-Tac-Toe\n");
    printf("2. Number Guessing Game\n");
    printf("3. Rock, Paper, Scissors\n");
    printf("4. Hangman\n");
    printf("5. Quiz Game\n");
    printf("6. Back to Main Menu\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
        {
            int result = playTicTacToe();
            if (result) {
                printf("You won!\n");
                users[userIndex].wins++;
            }
            else {
                printf("You lost.\n");
                users[userIndex].losses++;
            }
        }
        break;
    case 2:
        {
            int result = playNumberGuessingGame();
            if (result) {
                printf("You won!\n");
                users[userIndex].wins++;

            } else {
                printf("You lost.\n");
                users[userIndex].losses++;
            }
        }
        break;
    case 3:
        {
            int result =playRockPaperScissors();
            if (result) {
                printf("You won. \n");
                users[userIndex].wins++;

            } else {
                printf("You lost.\n");
                users[userIndex].losses++;
            }
        }
        break;
    case 4:
        {
            int result = playHangmanGame();
            if (result) {
                printf("You won!\n");
                users[userIndex].wins++;
            } else {
                printf("You lost.\n");
                users[userIndex].losses++;
            }
        }
        break;
    case 5:
        {
            int result =playQuizgame();
            if (result) {
                printf("You won!\n");
                users[userIndex].wins++;
            } else {
                printf("You lost.\n");
                users[userIndex].losses++;
            }
        }
        break;
    case 6:
                printf("Returning to main menu...\n");
                break;


    default:
        break;
    }
}

void displayLeaderboard(User users[], int userCount) {
    printf("\nLeaderboard:\n");
    printf("ID\tName\tWins\tLosses\t Badge\n");
    printf("---------------------------------------\n");

    // Sorting the users according to their wins in descending order
    for (int i = 0; i < userCount - 1; i++) {
        for (int j = 0; j < userCount - i - 1; j++) {
            if (users[j].wins < users[j + 1].wins) {
                User temp = users[j];
                users[j] = users[j + 1];
                users[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < userCount; i++) {
        char badge[10];
        if (users[i].wins > 8) {
            strcpy(badge, "Golden");
        } else if (users[i].wins > 5) {
            strcpy(badge, "Silver");
        } else {
            strcpy(badge, "Bronze");
        }
        printf("%d\t%s\t%d\t%d\t%s\n", users[i].id, users[i].name, users[i].wins, users[i].losses, badge);
    }
}

void displayPersonalDetails(User users[], int userCount) {

    int id;
    printf("Enter your user ID: ");
    scanf("%d", &id);

    int userIndex = getUserIndexById(users, userCount, id);
    if (userIndex == -1) {
        printf("User not found.\n");
        return;
    }

    User user = users[userIndex];
    float winLossRatio = (user.losses == 0) ? user.wins : (float)user.wins / user.losses;
    char badge[10];
    if (user.wins > 8) {
        strcpy(badge, "Golden");
    } else if (user.wins > 5) {
        strcpy(badge, "Silver");
    } else {
        strcpy(badge, "Bronze");
    }

    printf("\nPersonal Details:\n");
    printf("ID: %d\n", user.id);
    printf("Name: %s\n", user.name);
    printf("Wins: %d\n", user.wins);
    printf("Losses: %d\n", user.losses);
    printf("Win/Loss Ratio: %.2f\n", winLossRatio);
    printf("Badge: %s\n", badge);
}

void loadUsers(User users[], int *userCount) {
    FILE *file = fopen("users.txt", "r");
    if (!file) {
        printf("No existing user data found. Starting fresh.\n");
        return;
    }

    while (fscanf(file, "%d %s %d %d", &users[*userCount].id, users[*userCount].name, &users[*userCount].wins, &users[*userCount].losses) == 4) {
        (*userCount)++;
    }

    fclose(file);
}

void saveUsers(User users[], int userCount) {
    FILE *file = fopen("users.txt", "w");
    if (!file) {
        printf("Error saving user data. Changes may not persist.\n");
        return;
    }

    for (int i = 0; i < userCount; i++) {
        fprintf(file, "%d %s %d %d \n", users[i].id, users[i].name, users[i].wins, users[i].losses);
    }

    fclose(file);
}

int getUserIndexById(User users[], int userCount, int id) {
    for (int i = 0; i < userCount; i++) {
        if (users[i].id == id) {
            return i;
        }
    }
    return -1;
}

int playTicTacToe() {
    char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
    char player, computer;
    int win = 0, moves = 0, row, col, choice;

    //Let User to choose their symbol
    printf("Choose your symbol (X or O): ");
    scanf(" %c", &player);
    computer = (player == 'X' || player == 'x') ? 'O' : 'X';

    printf("\nYou are '%c' and the computer is '%c'\n", player, computer);
    printf("\n");
    int num=0;
    printf("Do you want computer to take chance first or you \nPress 1 for yourself \nPress 2 for the computer to take the chance first");
    scanf("%d",&num);

    while (win == 0 && moves < 9) {
        // Display the tic tac toe board on which we have to move
        printf("\n");
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                printf(" %c ", board[i][j]);
                if (j < 2) printf("|");
            }
            printf("\n");
            if (i < 2) printf("---|---|---\n");
        }
        printf("\n");

        if(num==1){
            // Player's move
        if (moves % 2 == 0) {
            printf("\nYour turn! Enter the position (1-9): ");
            scanf("%d", &choice);

            // Convert choice to row and column
            row = (choice - 1) / 3;
            col = (choice - 1) % 3;

            // Check if the position entered is valid or not
            if (choice < 1 || choice > 9 || board[row][col] == player || board[row][col] == computer) {
                printf("Invalid move! Try again.\n");
                continue;
            }
            board[row][col] = player;
        } else {
            // Computer's move
            printf("\nComputer's turn...\n");
            do {
                row = rand() % 3;
                col = rand() % 3;
            } while (board[row][col] == player || board[row][col] == computer);
            board[row][col] = computer;
        }

        moves++;
        }
        else {
            // Computer's move
                  if (moves % 2 != 0) {
            printf("\nYour turn! Enter the position (1-9): ");
            scanf("%d", &choice);

            // Convert choice to row and column
            row = (choice - 1) / 3;
            col = (choice - 1) % 3;

            // Check if the position is availablle or not
            if (choice < 1 || choice > 9 || board[row][col] == player || board[row][col] == computer) {
                printf("Invalid move! Try again.\n");
                continue;
            }
            board[row][col] = player;
        } else {
            // Computer's move
            printf("\nComputer's turn...\n");
            do {
                row = rand() % 3;
                col = rand() % 3;
            } while (board[row][col] == player || board[row][col] == computer);
            board[row][col] = computer;
        }

        moves++;

        }
        // Check for a win
        if (checkWin(board, player)) {
            win = 1; // Player wins
            break;
        } else if (checkWin(board, computer)) {
            win = -1; // Computer wins
            break;
        }
    }

    // Display the final board
    printf("\nFinal board:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", board[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("---|---|---\n");
    }

    // Announcement of the result
    if (win == 1) {
        return 1; // Player wins
    } else if (win == -1) {
        return 0; // Computer wins
    } else {
        printf("\nIt's a draw!\n");
        return 1; // Draw must give the points to both computer and player
    }
}

int checkWin(char board[3][3], char player) {
    // Check rows, columns, and diagonals for a win
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return 1; // Win found
        }
    }

    // Check diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return 1; // Win found
    }

    return 0; // No win
}
int playNumberGuessingGame() {
    int number, guess, attempts = 0;
    number = rand() % 100 + 1; // Random number between 1 and 100

    printf("Welcome to the Number Guessing Game! Guess a number between 1 and 100.\n");
    printf("TO WIN ATTEMPTS SHOULD BE LESS THAN 10\n");
    do {
        printf("Enter your guess: ");
        scanf("%d", &guess);
        attempts++;
        if (guess < number) {
            printf("Too low!\n");
        } else if (guess > number) {
            printf("Too high!\n");
        } else {
            printf("Correct! You guessed the number in %d attempts.\n", attempts);

        }
    } while (guess != number);
    if (attempts<10)
    {
        return 1;
    }
    else{
        return 0;
    }

}
//Here the user is playing three rounds
//The average of the wins or losses decides whether the user finally wins the game or lose the game

int playRockPaperScissors() {
    char *choices[] = {"Rock", "Paper", "Scissors"};
    int player_choice, computer_choice;

    int wins=0,losses=0;
    for(int i=0;i<3;i++){
     printf("Rock, Paper, Scissors! Choose:\n1. Rock\n2. Paper\n3. Scissors\n");
    printf("Your Choice: ");
    scanf("%d", &player_choice);
    computer_choice = rand() % 3 + 1;

    printf("Computer chose: %s\n", choices[computer_choice - 1]);
    if (player_choice == computer_choice) {
        printf("It's a tie!\n");

    }
    else if ((player_choice == 1 && computer_choice == 3) ||
               (player_choice == 2 && computer_choice == 1) ||
               (player_choice == 3 && computer_choice == 2)) {
        printf("You won!\n");

        wins++;
    }
    else {
        printf("You lose !\n");
        losses++;
    }
    printf("\n");

}
//Here we are comparing the final scores of win and loss of three rounds
if(wins>losses){
    return 1;
}
else{
    return 0;
}
}

// Structure for storing a word and its corresponding hint
typedef struct {
    char word[100];
    char hint[100];
} WordHint;

// Function to generate a random number within a given range
int getRandomNumber(int max) {
    return rand() % max;
}

// Function to get a random word and its hint
void getRandomWord(WordHint* wh) {
    // List of words and hints
    WordHint wordList[] = {
        {"elephant", "A large mammal with a trunk."},
        {"programming", "The act of writing computer code."},
        {"python", "A type of snake and a popular programming language."},
        {"hangman", "A game where you guess letters to form a word."},
        {"ocean", "A large body of saltwater."},
        {"computer", "An electronic device for processing data."}
    };

    int numWords = sizeof(wordList) / sizeof(wordList[0]);
    //To get a random index
    int randomIndex = getRandomNumber(numWords);
    *wh = wordList[randomIndex]; // Select the random word and hint
}

int playHangmanGame() {
    WordHint wh;
     // Select a random word and hint
    getRandomWord(&wh);
    int attempts_left = 6;
    int word_length = strlen(wh.word);
    char guessed_letters[word_length];
    // To track guessed letters
    char guessed_characters[26] = {0};
    int correct_guesses = 0;

    // Initializing guessed letters with '_'
    for (int i = 0; i < word_length; i++) {
        guessed_letters[i] = '_';
    }

    printf("Welcome to Hangman!\n");
    // Providing the hint to the player

    printf("Hint: %s\n", wh.hint);

    while (attempts_left > 0) {
        int found = 0;
        printf("\nCurrent word: ");
        for (int i = 0; i < word_length; i++) {
            printf("%c ", guessed_letters[i]);
        }
        printf("\nYou have %d attempts left.\n", attempts_left);
        printf("Guessed letters: ");
        for (int i = 0; i < 26; i++) {
            if (guessed_characters[i]) {
                printf("%c ", 'a' + i);
            }
        }
        printf("\nEnter a letter: ");
        char guess;
        scanf(" %c", &guess); // Added space to skip any newline character

        guess = tolower(guess); // Convert input to lowercase

        if (!isalpha(guess)) {
            printf("Please enter a valid letter.\n");
            continue;
        }

        if (guessed_characters[guess - 'a']) {
            printf("You already guessed that letter.\n");
            continue;
        }

        guessed_characters[guess - 'a'] = 1; // Mark letter as guessed

        // Check if the guess is correct
        for (int i = 0; i < word_length; i++) {
            if (wh.word[i] == guess) {
                guessed_letters[i] = guess;
                found = 1;
                correct_guesses++;
            }
        }

        if (found) {
            printf("Correct guess!\n");
        } else {
            attempts_left--;
            printf("Incorrect guess!\n");
        }

        // Check if the word is completely guessed
        if (correct_guesses == word_length) {
            printf("\nCongratulations! You've guessed the word: %s\n", wh.word);
            return 1;
            break;
        }
    }

    if (correct_guesses < word_length) {
        printf("\nGame over! The word was: %s\n", wh.word);
        return 0;
    }
}

// Structure to store question details
typedef struct {
 char question[300];
 char options[4][64];
 int correct_option;
} Question;


void displayQuestion(Question q)
{
 printf("%s\n", q.question);
 for (int i = 0; i < 4; i++) {
  printf("%d. %s\n", i + 1, q.options[i]);
 }
}

int checkAnswer(Question q, int user_answer)
{
 return (user_answer == q.correct_option);
}

void print_instructions() {
    // Instructions of the game
    printf("\n");
    printf("Welcome to the Quiz Game!\n");
    printf("Here's how to play:\n");
    printf("1. You will be asked a series of questions.\n");
    printf("2. Each question will have multiple choice answers (1, 2, 3, or 4).\n");
    printf("3. Choose the correct answer by typing the corresponding letter.\n");
    printf("4. After each question, you'll be told whether you were correct or incorrect.\n");
    printf("5. At the end of the quiz, your score will be shown.\n");
    printf("\nGood luck!\n\n");
    printf("\n");
}

int playQuizgame()
{
       print_instructions();

 //Questions with options need to be asked in the quiz
 Question original_questions[5] = {
  { "In which year was Jaypee Institute of Information Technology (JIIT) established?",
  { "2000", "2001", "2003", "2004" },
  2 },
  { "What is the total area of the JIIT sec 62 campus?",
  { "15.5 acre", "10 acre", "20 acre", "25 acre" },
  1 },
  { "What is the full form of LRC?",
  { "Learn Read Code", "Library Resource Corner",
   "Learning Resource Center", "Literature resource center" },
  3 },
  { "What is the primary focus of the academic programs at JIIT?",
  { "Information Technology", "Engineering and Technology", "Management", "Biotechnology" },
  2 },
  { "Who is one of the many notable alumnis of JIIT?",
  { "Kunal Khemu", "Shubhangi Swaroop", "Vikas Khanna", "Kriti Sanon" },
  4 }
 };


 Question questions[5];
 memcpy(questions, original_questions,sizeof(original_questions));
 int num_questions = 5;
 int score = 0;
 for (int i = 0; i < 5; i++) {
    //Getting random question from 5
  int random_index = rand() % num_questions;
  Question current_question = questions[random_index];
  displayQuestion(current_question);
  int user_answer;
  printf("Enter your answer (1-4): ");
  scanf("%d", &user_answer);
  if (user_answer >= 1 && user_answer <= 4) {
   if (checkAnswer(current_question,
       user_answer)) {
    printf("Correct!\n");
    score++;
   }
   else {
    printf("Incorrect. The correct answer is "
     "%d. %s\n",
     current_question.correct_option,
     current_question.options
      [current_question.correct_option
       - 1]);
   }
  }
  else {
   printf("Invalid choice. Please enter a number "
    "between 1 and 4.\n");
  }
  questions[random_index]
   = questions[num_questions - 1];
  num_questions--;
 }
 printf("Well Done Champ !!!! Quiz completed! \nYour score: %d/%d\n",score, 5);
  if(score==5){
    return 1;
  }
  else{
    return 0;
  }

}

