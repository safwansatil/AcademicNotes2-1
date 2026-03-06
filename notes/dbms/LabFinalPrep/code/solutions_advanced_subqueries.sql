-- 6. Inactive in Comedy: Customers who have NEVER rented a Comedy film.
-- NOT EXISTS is powerful here: it checks if a record matching the criteria is missing.
SELECT c.customer_id, c.first_name, c.last_name
FROM customer c
WHERE NOT EXISTS (
    SELECT 1
    FROM rental r
    JOIN inventory i ON r.inventory_id = i.inventory_id
    JOIN film_category fc ON i.film_id = fc.film_id
    JOIN category cat ON fc.category_id = cat.category_id
    WHERE r.customer_id = c.customer_id 
    AND cat.name = 'Comedy'
);

-- 7. Above Average Spend: Names who spent more than the average total spending.
-- We first calculate the total spend per customer in a subquery, then compare it to the overall average.
SELECT cu.first_name, cu.last_name
FROM customer cu
JOIN (
    SELECT customer_id, SUM(amount) as total
    FROM payment
    GROUP BY customer_id
) AS customer_totals ON cu.customer_id = customer_totals.customer_id
WHERE customer_totals.total > (
    SELECT AVG(total_spent)
    FROM (
        SELECT SUM(amount) as total_spent
        FROM payment
        GROUP BY customer_id
    ) AS all_spends
);

-- 8. Multi-Store Actors: Actors with films in both store 1 AND store 2.
-- INTERSECT finds common elements between two sets.
SELECT a.first_name, a.last_name
FROM actor a
WHERE a.actor_id IN (
    SELECT fa.actor_id 
    FROM film_actor fa
    JOIN inventory i ON fa.film_id = i.film_id
    WHERE i.store_id = 1
    INTERSECT
    SELECT fa.actor_id 
    FROM film_actor fa
    JOIN inventory i ON fa.film_id = i.film_id
    WHERE i.store_id = 2
);
