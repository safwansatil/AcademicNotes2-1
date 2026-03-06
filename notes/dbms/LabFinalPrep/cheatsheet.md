###### 1. Core Selection & Joins
- **Weighted Rank**: `SELECT title, (rate*0.5 + len*0.1) AS score FROM film ORDER BY score DESC LIMIT 3;``
- **String Match**: `title LIKE '% %'` (Multi-word), `title ILIKE 'a%'` (Insensitive).

###### 2. Aggregates & Partition
- **Filter Groups**: `GROUP BY store_id HAVING COUNT(*) > 500;`
- **Missing Ties**: `SELECT c.city FROM city c LEFT JOIN customer u USING (city_id) WHERE u.customer_id IS NULL;` -- Find cities with 0 customers.
- **Revenue Share**: 
```sql
SELECT name, amount /
SUM(amount) OVER(PARTITION BY store_id) * 100 
FROM payment JOIN customer USING (customer_id);
```

###### 3. Subqueries & Exists
- **Check Exists**: `WHERE EXISTS (SELECT 1 FROM table WHERE cond);`
- **Correlated**: `SELECT c.name FROM customer c WHERE EXISTS (SELECT 1 FROM rental r WHERE r.customer_id = c.customer_id AND r.return_date IS NULL);`
- **Not In**: `WHERE id NOT IN (SELECT id FROM table);` -- Careful with NULLs, NOT EXISTS is safer. even LEFT JOIN with IS NULL is often better.

###### 4. Date & Interval Math
- **Last N Days**: `rental_date >= CURRENT_DATE - (N || ' days')::INTERVAL`
- **Logic**: `AGE(return, rental)`, `EXTRACT(YEAR FROM date)`

###### 5. PL/pgSQL Patterns

**CRITICAL: SELECT ... INTO**
`SELECT count(*) INTO v_count FROM rental WHERE customer_id = cid;`
*Rule: SQL -> INTO variable -> procedural logic.*

**Anonymous Block**
```sql
DO $$ 
DECLARE cid INT := 1; has_r BOOLEAN; 
BEGIN
  SELECT EXISTS(SELECT 1 FROM rental 
  WHERE customer_id=cid AND return_date IS NULL) INTO has_r;
  IF has_r THEN RAISE NOTICE 'Active'; 
  ELSE RAISE NOTICE 'None'; END IF;
END $$;
```

**Procedure (Updates)**
```sql
CREATE OR REPLACE PROCEDURE update_em(cid INT, new_em VARCHAR)
LANGUAGE plpgsql AS $$
BEGIN
  UPDATE customer SET email=new_em, last_update=NOW()
   WHERE customer_id=cid;
END $$; -- Usage: CALL update_em(5, 'a@b.com');
```

**Table Function (Complex Select)**
```sql
CREATE OR REPLACE FUNCTION get_rentals(days INT) 
RETURNS TABLE(fn VARCHAR, t VARCHAR) 
LANGUAGE plpgsql AS $$
BEGIN
  RETURN QUERY SELECT c.first_name, f.title FROM customer c
  JOIN rental r USING(customer_id) JOIN inventory i USING
  (inventory_id) JOIN film f USING(film_id)
  WHERE r.rental_date >= CURRENT_DATE - (days || ' days')
  ::INTERVAL;
END $$; -- Usage: SELECT * FROM get_rentals(7);
```

**Loop Template**
```sql
FOR rec IN SELECT col1, col2 FROM table LOOP
  RAISE NOTICE 'Data: %', rec.col1;
END LOOP;
```

###### 6. Exam-Saving Tips

- **Concat**: `'Text ' || column`
- **Defaults**: `COALESCE(column, 0)`
- **Unique Count**: `COUNT(DISTINCT column)`
- **Cast**: `val::INT`, `val::DECIMAL(10,2)`

###### 7. PL/pgSQL Tips
- **Assign Value**: `v_count := 10;`
- **Return from Function**: `RETURN v_result;` (Ends function & sends value back)
`
CREATE FUNCTION get_sum(a INT, b INT) RETURNS INT AS $$
BEGIN
    RETURN a + b; -- Function stops here
END;
$$ LANGUAGE plpgsql;
`
- **Handle Empty Query**: `SELECT ... INTO v_id; IF NOT FOUND THEN ... END IF;` (Runs if query returned 0 rows)
`SELECT user_name INTO v_name FROM users WHERE id = 999;
IF NOT FOUND THEN
    RAISE EXCEPTION 'User not found';
END IF;`
- **Notice with %**: `RAISE NOTICE 'Total: %, Name: %', v_sum, v_name;`
- **Null & Bool Logic**: `IF v_var IS NULL THEN ...` | `IF NOT v_is_active THEN ...`
