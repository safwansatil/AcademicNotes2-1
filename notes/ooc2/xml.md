# XML

XML = eXtensible Markup Language - a way to structure data that both humans and machines can read.

```xml
<!-- Simple XML Example -->
<student>
    <id>101</id>
    <name>John Doe</name>
    <age>21</age>
    <courses>
        <course>OOP</course>
        <course>Data Structures</course>
    </courses>
</student>
```

## Why XML?

1. Platform independent (works everywhere)
2. Human readable
3. Can represent complex data structures
4. Standard for data exchange

## DTD

DTD = Document Type Definition - defines what your XML should look like

```xml
<!-- student.dtd - The RULES -->
<!ELEMENT student (id, name, age, courses)>
<!ELEMENT id (#PCDATA)>
<!ELEMENT name (#PCDATA)>
<!ELEMENT age (#PCDATA)>
<!ELEMENT courses (course+)>  <!-- + means one or more -->
<!ELEMENT course (#PCDATA)>
```

---

Connect to DTD in xml:

```xml
<!DOCTYPE student SYSTEM "student.dtd">
```

---

## Serialization & Deserialization

Converting an object to bytes (save to file/database)
Converting bytes back to object (read from file)

```java
// make your object's class implements Serializable
public class SavePerson implements Serializable{
    public SavePerson(){
        Person person = new Person(“Jack Jones”);
        try{
            FileOutputStream fos = new FileOutputStream(“Name.txt”);
            ObjectOutputStream oos = new ObjectOutputStream(fos);
            System.out.print(“Person’s Name Written: “);
            System.out.println(person.getName());
            oos.writeObject(person);
            oos.flush();
            oos.close();
        } catch(Exception e){
            e.printStackTrace();
        }
    }
}
```

DeSerialize:
```java
public class DeserializeExample {
    public static void main(String[] args) {
        try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream("employee.dat"))) {
            Employee emp = (Employee) ois.readObject();
            System.out.println("Employee read: " + emp);
        } catch (IOException | ClassNotFoundException e) {
            e.printStackTrace();
        }
    }
}

```
