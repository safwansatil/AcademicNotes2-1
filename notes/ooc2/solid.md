# SOLID Principles

## Single Responsibility Principle (SRP)
A class should have only one reason to change, meaning it should have only one job or responsibility. This helps in maintaining and scaling the codebase.
Hence what responsibilty means here is a reason to change.

Example:
```java
// BAD: Multiple reasons to change
class StudentReport {
    // Reason 1 to change: Report format changes
    public void generateReport(Student s) {
        // report generation logic
    }
    
    // Reason 2 to change: Database schema changes
    public void saveToDatabase(Student s) {
        // database logic
    }
    
    // Reason 3 to change: Email service API changes
    public void emailReport(Student s) {
        // email sending logic
    }
}
// THREE reasons to change = violates SRP
``` 

<b>Ask this question:</b>
"Who/what would ask for changes to this class?"
"Can this change independently of that?"

<b>Why it matters:</b>

1. Maintainability → Changes affect only one place
2. Testability → Easier to write focused tests and unit tests
3. Reusability → Can reuse single-purpose classes
4. Reduced Coupling → Less dependency between changes
5. Team Collaboration → Clear ownership of components

Yes, the Single Responsibility Principle (SRP) is fundamentally about increasing cohesion by ensuring a class or module has only one reason to change, meaning its methods and data are closely related and focused on a single task, making the code easier to understand, maintain, and less prone to bugs from unrelated changes. It achieves this by grouping related functions and data that change for the same reasons, keeping them together while separating those that change for different reasons, which directly boosts cohesion. 

```java
// ✅ FOLLOWS SRP - Single Responsibility Classes
class Student {
    // ONLY student data
    private String name;
    private int age;
    // Getters/setters only
}

class EnrollmentService {
    // ONLY enrollment logic
    public void enroll(Student s, Course c) {
        // pure enrollment business logic
    }
}

class StudentRepository {
    // ONLY database operations
    public void save(Student s) {
        // pure database code
    }
}

class NotificationService {
    // ONLY notifications
    public void sendEmail(Student s, String message) {
        // pure email code
    }
}

class ReportGenerator {
    // ONLY reporting
    public Report generate(Student s) {
        // pure report generation
    }
}
```

## Open/Closed Principle (OCP)
Software entities (classes, modules, functions, etc.) should be open for extension but closed for modification. This means you should be able to add new functionality without changing existing code, which helps prevent bugs and keeps the system stable.

Translation: Can add new features. Don't change existing, tested code.

Key technique to acheive OCP: abstraction + polymorphism.

Some examples:
```java
// Step 1: Define ABSTRACTION (what's common)
interface Shape {
    double calculateArea();  // All shapes can calculate area
}

// Step 2: Implement CONCRETE classes
class Circle implements Shape {
    private double radius;
    public Circle(double radius) { this.radius = radius; }
    public double calculateArea() {
        return Math.PI * radius * radius;
    }
}

class Rectangle implements Shape {
    private double width, height;
    public Rectangle(double w, double h) { this.width = w; this.height = h; }
    public double calculateArea() {
        return width * height;
    }
}

// Step 3: Client code - CLOSED for modification
class AreaCalculator {
    // ✅ FOLLOWS OCP - No changes needed for new shapes!
    public double calculateArea(Shape shape) {
        return shape.calculateArea();  // Polymorphism at work!
    }
}

// Usage:
AreaCalculator calc = new AreaCalculator();
Shape circle = new Circle(5);
Shape rectangle = new Rectangle(4, 6);

calc.calculateArea(circle);     // Works!
calc.calculateArea(rectangle);  // Works!

// NEW SHAPE? Just implement Shape interface!
class Triangle implements Shape {
    private double base, height;
    public Triangle(double b, double h) { this.base = b; this.height = h; }
    public double calculateArea() {
        return 0.5 * base * height;
    }
}

// No changes to AreaCalculator needed!
Shape triangle = new Triangle(3, 4);
calc.calculateArea(triangle);  // Just works!
```
another example:
```java
// ❌ BAD: Must modify for each new notification type
class NotificationService {
    public void send(String type, String message) {
        if (type.equals("email")) {
            sendEmail(message);
        } else if (type.equals("sms")) {
            sendSMS(message);
        } else if (type.equals("push")) {
            sendPush(message);  // Had to MODIFY to add push
        }
    }
}

// ✅ GOOD: Open for new notification types
interface Notifier {
    void notify(String message);
}

class EmailNotifier implements Notifier {
    public void notify(String message) { /* email logic */ }
}

class SMSNotifier implements Notifier {
    public void notify(String message) { /* SMS logic */ }
}

class PushNotifier implements Notifier {
    public void notify(String message) { /* push logic */ }
}

class NotificationService {
    private List<Notifier> notifiers;
    
    public void send(String message) {
        for (Notifier notifier : notifiers) {
            notifier.notify(message);  // No changes needed for new types!
        }
    }
}

// Want WhatsApp? Just implement Notifier interface!
class WhatsAppNotifier implements Notifier {
    public void notify(String message) { /* WhatsApp logic */ }
}
// Add to list and it works!
```
ANOTHER EXAMPLE:
```java
// ❌ BAD: Discount logic tangled together
class DiscountCalculator {
    public double calculateDiscount(String customerType, double amount) {
        if (customerType.equals("regular")) {
            return amount * 0.05;
        } else if (customerType.equals("premium")) {
            return amount * 0.10;
        } else if (customerType.equals("vip")) {
            return amount * 0.15;
        } else if (customerType.equals("student")) {
            return amount * 0.20;  // Modified code to add student
        }
        return 0;
    }
}

// ✅ GOOD: Each discount strategy separate
interface DiscountStrategy {
    double calculate(double amount);
}

class RegularDiscount implements DiscountStrategy {
    public double calculate(double amount) { return amount * 0.05; }
}

class PremiumDiscount implements DiscountStrategy {
    public double calculate(double amount) { return amount * 0.10; }
}

class VIPDiscount implements DiscountStrategy {
    public double calculate(double amount) { return amount * 0.15; }
}

class DiscountCalculator {
    // ✅ CLOSED for modification
    public double calculate(DiscountStrategy strategy, double amount) {
        return strategy.calculate(amount);
    }
}

// New discount? Just create new strategy!
class StudentDiscount implements DiscountStrategy {
    public double calculate(double amount) { return amount * 0.20; }
}
// No changes to DiscountCalculator!
```

---

However, don't overenforce OCP. Try YAGNI (You Ain't Gonna Need It) 
```java
// Simple case - OCP might be overkill
class Logger {
    public void log(String message) {
        // Only logs to console
        System.out.println(message);
    }
}
// If you'll NEVER need file logging, database logging, etc.
// Don't create abstraction prematurely!
```

---

Apply ocp when: 
1. You KNOW requirements will change
2. You've been asked to add similar features multiple times
3. The domain naturally has multiple variations

