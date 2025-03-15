#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <limits> // For input validation

// Constants
const std::string USER_FILE = "users.txt";
const int SALT_LENGTH = 16;

// Simple SHA-256 Implementation (for demonstration purposes)
class SHA256 {
public:
    static std::string hash(const std::string& data) {
        unsigned int hash = 0;
        for (char c : data) {
            hash = (hash * 31) + c;
        }
        std::stringstream ss;
        ss << std::hex << std::setw(64) << std::setfill('0') << hash;
        return ss.str();
    }
};

// User Model
struct User {
    std::string username;
    std::string hashedPassword;
    std::string salt;
};

// Validator
class Validator {
public:
    static bool validateUsername(const std::string& username) {
        return !username.empty() && username.find(',') == std::string::npos; // Prevent CSV injection
    }

    static bool validatePassword(const std::string& password) {
        if (password.length() < 8) return false;
        bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
        for (char c : password) {
            if (isupper(c)) hasUpper = true;
            if (islower(c)) hasLower = true;
            if (isdigit(c)) hasDigit = true;
            if (ispunct(c)) hasSpecial = true;
        }
        return hasUpper && hasLower && hasDigit && hasSpecial;
    }
};

// Password Hasher
class PasswordHasher {
public:
    static std::string generateSalt() {
        std::string salt;
        srand(time(0));
        for (int i = 0; i < SALT_LENGTH; ++i) {
            salt += static_cast<char>('a' + rand() % 26);
        }
        return salt;
    }

    static std::string hashPassword(const std::string& password, const std::string& salt) {
        return SHA256::hash(password + salt);
    }
};

// User Repository
class UserRepository {
public:
    static void saveUser(const User& user) {
        std::ofstream file(USER_FILE, std::ios::app);
        if (file.is_open()) {
            file << user.username << "," << user.hashedPassword << "," << user.salt << "\n";
            file.close();
        } else {
            std::cerr << "Error opening file for writing." << std::endl;
        }
    }

    static bool getUser(const std::string& username, User& user) {
        std::ifstream file(USER_FILE);
        std::string line;
        if (file.is_open()) {
            while (std::getline(file, line)) {
                std::istringstream iss(line);
                std::string uname, hashedPwd, salt;
                if (std::getline(iss, uname, ',') && std::getline(iss, hashedPwd, ',') && std::getline(iss, salt)) {
                    if (uname == username) {
                        user = {uname, hashedPwd, salt};
                        file.close();
                        return true;
                    }
                }
            }
            file.close();
        } else {
            std::cerr << "Error opening file for reading." << std::endl;
        }
        return false;
    }
};

// Session Class
class Session {
public:
    std::string sessionId;
    std::string username;
    std::time_t creationTime;
    std::time_t expirationTime;

    Session(const std::string& sessionId, const std::string& username)
        : sessionId(sessionId), username(username) {
        creationTime = std::time(nullptr); // Current time
        expirationTime = creationTime + 1800; // 30 minutes from now
    }

    bool isExpired() const {
        return std::time(nullptr) > expirationTime;
    }
};

// Session Manager
class SessionManager {
private:
    std::unordered_map<std::string, Session> sessions; // Map session ID to Session object

public:
    std::string createSession(const std::string& username) {
        std::string sessionId = generateSessionId(); // Generate a unique session ID
        sessions.emplace(sessionId, Session(sessionId, username)); // Use emplace to insert the session
        return sessionId;
    }

    Session* getSession(const std::string& sessionId) {
        auto it = sessions.find(sessionId);
        if (it != sessions.end() && !it->second.isExpired()) {
            return &it->second; // Return the session if it exists and is not expired
        }
        return nullptr; // Session not found or expired
    }

    void deleteSession(const std::string& sessionId) {
        sessions.erase(sessionId); // Remove the session
    }

private:
    std::string generateSessionId() {
        // Generate a unique session ID (e.g., using a random string or UUID)
        return "session_" + std::to_string(std::time(nullptr));
    }
};

// Authentication Service
class AuthService {
private:
    static SessionManager sessionManager; // Session manager instance

public:
    static void registerUser(const std::string& username, const std::string& password) {
        if (!Validator::validateUsername(username)) {
            std::cout << "Invalid username. Username cannot be empty or contain commas." << std::endl;
            return;
        }
        if (!Validator::validatePassword(password)) {
            std::cout << "Invalid password. Password must be at least 8 characters long and include uppercase, lowercase, digits, and special characters." << std::endl;
            return;
        }
        User existingUser;
        if (UserRepository::getUser(username, existingUser)) {
            std::cout << "Username already exists." << std::endl;
            return;
        }

        std::string salt = PasswordHasher::generateSalt();
        std::string hashedPassword = PasswordHasher::hashPassword(password, salt);
        User user = {username, hashedPassword, salt};
        UserRepository::saveUser(user);
        std::cout << "User registered successfully!" << std::endl;
    }

    static std::string loginUser(const std::string& username, const std::string& password) {
        User user;
        if (UserRepository::getUser(username, user)) {
            std::string hashedPassword = PasswordHasher::hashPassword(password, user.salt);
            if (hashedPassword == user.hashedPassword) {
                std::cout << "Login successful!" << std::endl;
                return sessionManager.createSession(username); // Create and return a session
            }
        }
        std::cout << "Login failed. Invalid username or password." << std::endl;
        return ""; // Return empty string if login fails
    }

    static void logoutUser(const std::string& sessionId) {
        sessionManager.deleteSession(sessionId); // Delete the session
        std::cout << "Logged out successfully." << std::endl;
    }
};

// Initialize static member
SessionManager AuthService::sessionManager;

// Utility Functions
void clearInputBuffer() {
    std::cin.clear(); // Clear error flags
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
}

std::string getPasswordInput() {
    std::string password;
    char ch;
    while ((ch = getchar()) != '\n') {
        if (ch == '\b' && !password.empty()) { // Handle backspace
            password.pop_back();
            std::cout << "\b \b"; // Erase the character from the console
        } else if (ch != '\b') {
            password += ch;
            std::cout << '*'; // Mask the password
        }
    }
    std::cout << std::endl;
    return password;
}

// Main Function
int main() {
    int choice;
    std::string username, password;
    std::string sessionId; // Track the current session

    while (true) {
        if (sessionId.empty()) {
            // User is not logged in
            std::cout << "1. Register\n2. Login\n3. Exit\nChoose an option: ";
        } else {
            // User is logged in
            std::cout << "1. Logout\n2. Exit\nChoose an option: ";
        }

        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number." << std::endl;
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        if (sessionId.empty()) {
            // User is not logged in
            switch (choice) {
                case 1: // Register
                    std::cout << "Enter username: ";
                    std::getline(std::cin, username);
                    std::cout << "Enter password: ";
                    password = getPasswordInput();
                    AuthService::registerUser(username, password);
                    break;
                case 2: // Login
                    std::cout << "Enter username: ";
                    std::getline(std::cin, username);
                    std::cout << "Enter password: ";
                    password = getPasswordInput();
                    sessionId = AuthService::loginUser(username, password); // Store session ID
                    break;
                case 3: // Exit
                    std::cout << "Exiting program." << std::endl;
                    return 0;
                default:
                    std::cout << "Invalid option. Please choose 1, 2, or 3." << std::endl;
            }
        } else {
            // User is logged in
            switch (choice) {
                case 1: // Logout
                    AuthService::logoutUser(sessionId);
                    sessionId = ""; // Clear session ID
                    break;
                case 2: // Exit
                    std::cout << "Exiting program." << std::endl;
                    return 0;
                default:
                    std::cout << "Invalid option. Please choose 1 or 2." << std::endl;
            }
        }
    }

    return 0;
}