# DBMS Lab Final Practice Questions

This file contains a mix of "Class Average Booster" (Easy) and "Weak-Point Mastery" (Advanced) questions based on the DVD Rental schema.

---

## Part 1: Class Average Boosters (Easy/Intermediate)
These questions help you master standard joins, aggregates, and filtering.

1. **Category Popularity**: List all categories (`name`) and the total number of films in each category. Sort by the count in descending order.
2. **Short Films Search**: Find the titles of all films that have a duration less than 60 minutes and a rental rate of 0.99.
3. **Staff Performance**: List the `first_name` and `last_name` of each staff member along with the total number of rentals they processed.
4. **Member City**: List the customer `first_name`, `last_name`, and the `city` they live in. (Requires multiple joins: customer -> address -> city).
5. **Rating Counts**: Show the count of films for each rating (G, PG, R, etc.) but only for films that have a replacement cost between 15 and 20.

---

## Part 2: Weak-Point Mastery (Advanced)
Focus on Nested Subqueries, Procedures, and Table Functions.

### Nested Subqueries
6. **Inactive in Specific Category**: Find customers (ID and Name) who have **never** rented a film from the 'Comedy' category. (Use `NOT EXISTS`).
7. **Above Average Spend**: List customer names who have spent more than the average total spending of all customers. 
   - *Hint: Subquery in WHERE comparing to a SUM calculated in another subquery.*
8. **Multi-Store Actors**: List actors who have films available in both store 1 and store 2. (Use `INTERSECT` or two `EXISTS` clauses).

### PL/pgSQL & Procedures
9. **Procedure: Promo Credit**: Write a procedure `add_rental_credit(cust_id INT, credit_amount DECIMAL)` that "pays" for a customer's latest unpaid rental by inserting a record into the `payment` table with the current date.
10. **Table Function: High Value Inventory**: Write a function `get_expensive_inventory(min_cost DECIMAL)` that returns a table (`title`, `replacement_cost`, `store_id`) for all inventory items whose replacement cost is above the input parameter.
11. **Anonymous Block: Rental Status Check**: Write an anonymous block that takes a `film_id`. If every copy of that film is currently rented out (none are in the `inventory` table without a corresponding `return_date`), print "Out of Stock". Otherwise, print "Copies Available".

---

## Part 3: Date & Logic Challenges
12. **Recent Active Customers**: Find customers who have made at least 3 rentals in the last 180 days.
13. **Weighted Genre Score**: Calculate a "Comedy Score" for each store. The score is (Total Comedy Rentals * 1.5) + (Total Drama Rentals * 1.0). List store ID and the calculated score.
