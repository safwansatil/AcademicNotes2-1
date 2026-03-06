# DBMS Lab Final Study Guide: PostgreSQL Mastery

This guide skips the basics and focuses on high-level topics essential for the lab final, based on the DVD Rental schema.

---

## 1. Advanced Aggregates and Filtering
The lab final often requires calculating complex metrics across multiple tables.

### Weighted Calculations & Ranking
You can perform math directly in the `SELECT` clause and use `ORDER BY` with `LIMIT` to rank results.
- **Example**: Ranking films by a custom score.
  ```sql
  SELECT title, 
         (rental_rate * 0.5) + (length * 0.1) AS score
  FROM film
  ORDER BY score DESC
  LIMIT 3;
  ```

### GROUP BY and HAVING
- `GROUP BY` collapses rows into groups.
- `HAVING` filters those groups *after* aggregation.
- **Common Trick**: Use `COUNT(DISTINCT column)` to get unique counts across groups.

---

## 2. Nested Subqueries
This is a critical area. Focus on where the subquery is placed.

### Correlated Subqueries
A subquery that refers to a column from the outer query. It is executed once for every row in the outer query.
- **EXISTS / NOT EXISTS**: Best for checking presence. Often more efficient than `IN`.
  ```sql
  -- Customers who have never rented a specific film
  SELECT c.first_name, c.last_name
  FROM customer c
  WHERE NOT EXISTS (
      SELECT 1 FROM rental r 
      JOIN inventory i ON r.inventory_id = i.inventory_id
      WHERE r.customer_id = c.customer_id AND i.film_id = 10
  );
  ```

### Subqueries in FROM (Derived Tables)
Think of these as "temporary tables" you create on the fly.
```sql
SELECT AVG(total_spent)
FROM (
    SELECT customer_id, SUM(amount) as total_spent
    FROM payment
    GROUP BY customer_id
) as customer_totals;
```

---

## 3. PL/pgSQL: Beyond the Basics

### Anonymous Blocks (`DO` blocks)
Used for one-time logic without creating a permanent object.
```sql
DO $$
DECLARE
    target_id INT := 5;
    total DECIMAL;
BEGIN
    SELECT SUM(amount) INTO total FROM payment WHERE customer_id = target_id;
    IF total > 100 THEN
        RAISE NOTICE 'High value customer';
    ELSE
        RAISE NOTICE 'Regular customer';
    END IF;
END $$;
```

### Procedures vs. Functions
- **Procedures (`CREATE PROCEDURE`)**: Use `CALL`. They do not return values (usually). Use for actions like updates.
- **Functions (`CREATE FUNCTION`)**: Use `SELECT`. Must have a `RETURNS` clause. Use for calculations or returning data.

### Loops with RECORDs
The most common way to iterate over query results in PL/pgSQL.
```sql
DECLARE
    rec RECORD;
BEGIN
    FOR rec IN SELECT title FROM film LIMIT 5 LOOP
        RAISE NOTICE 'Film Title: %', rec.title;
    END LOOP;
END;
```

---

## 4. Date and Time Manipulation
PostgreSQL is powerful with intervals.
- `CURRENT_DATE`: Today's date.
- `NOW()`: Current timestamp.
- `INTERVAL 'N days'`: Adding/Subtracting time.
- `AGE(timestamp1, timestamp2)`: Returns the interval between two dates.
- `EXTRACT(YEAR FROM date)`: Get specific parts of a date.

**Math Example**:
`WHERE payment_date >= CURRENT_DATE - INTERVAL '30 days'`
